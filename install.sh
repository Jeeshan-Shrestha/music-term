#!/usr/bin/env bash

set -e

APP_NAME="download-music"
SOURCE="music.c"

echo "Compiling $SOURCE..."

gcc "$SOURCE" -o "$APP_NAME" -O2 -Wall

echo "Installing to /usr/local/bin..."

sudo install -Dm755 "$APP_NAME" "/usr/local/bin/$APP_NAME"

echo "Cleaning up..."
rm -f "$APP_NAME"

echo
echo "Installation complete!"
echo
echo "You can now run:"
echo "    $APP_NAME <search query>"
