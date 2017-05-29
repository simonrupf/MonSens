#!/bin/sh

if [ -z "$1" ]
then
    echo "usage: $0 [path/to/Arduino/sketchbooks]"
    exit 1
fi

SKETCHBOOK_PATH="$(echo "$1" | sed 's:/*$::')"

if [ ! -w "$SKETCHBOOK_PATH" ]
then
    echo "error: path '$SKETCHBOOK_PATH' is not writable"
    exit 2
fi

for SKETCH in monsens-temperature-internal
do
    mkdir -p "$SKETCHBOOK_PATH/$SKETCH"
    cp $SKETCH.ino "$SKETCHBOOK_PATH/$SKETCH/$SKETCH.ino"
done
