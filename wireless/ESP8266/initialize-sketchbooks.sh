#!/bin/sh

if [ -z "$1" ]
then
    echo "usage: $0 [path/to/Arduino/sketchbooks]"
    exit 1
fi

SKETCHBOOK_PATH="$(echo "$1" | sed 's:/*$::')"
LIBRARY_PATH="$SKETCHBOOK_PATH/libraries"
SELF_PATH="$(cd "$(dirname "$0")"; pwd)"

if [ ! -w "$SKETCHBOOK_PATH" ]
then
    echo "error: path '$SKETCHBOOK_PATH' is not writable"
    exit 2
fi

if [ ! -w "$LIBRARY_PATH" ]
then
    echo "error: path '$LIBRARY_PATH' is not writable"
    exit 2
fi

if ! command -v git >/dev/null 2>&1
then
    echo "error: git not installed, required to download and update Adafruit libraries"
    exit 3
fi

# Adafruit libraries
for LIBRARY in Adafruit_BME280_Library Adafruit_BMP280_Library Adafruit_Sensor
do
    if [ -w "$LIBRARY_PATH/$LIBRARY" ]
    then
        cd "$LIBRARY_PATH/$LIBRARY"
        git pull >/dev/null
        cd $SELF_PATH
    else
        git clone https://github.com/adafruit/$LIBRARY.git "$LIBRARY_PATH/$LIBRARY" >/dev/null
    fi
done

# MonSens libraries, excluding DigiSpark (those only works when the Arduino IDE
# is set to that board)
cp -r "$SELF_PATH/../../libraries/MonSens" "$LIBRARY_PATH/"
rm "$LIBRARY_PATH/MonSens/MonSens_DigiSpark"*

# MonSens sketches
for SKETCH in monsens-esp8266-example
do
    mkdir -p "$SKETCHBOOK_PATH/$SKETCH"
    cp "$SELF_PATH/$SKETCH.ino" "$SKETCHBOOK_PATH/$SKETCH/$SKETCH.ino"
done
