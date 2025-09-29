#!/bin/bash
set -e

KEEP_BINARY=0

# Check for -k flag
if [ "$1" == "-k" ]; then
    KEEP_BINARY=1
    shift
fi

# Check if a C file is provided
if [ -z "$1" ]; then
    echo "Usage: $0 [-k] <file.c>"
    exit 1
fi

CFILE="$1"
BINARY="${CFILE%.*}"

# Compile
gcc "$CFILE" -o "$BINARY" || { echo "Compilation failed"; exit 1; }

# Run the binary
./"$BINARY"

# Delete the binary if -k was not provided
if [ $KEEP_BINARY -eq 0 ]; then
    rm -f "$BINARY"
fi
