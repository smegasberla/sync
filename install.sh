#!/bin/bash
set -e

echo "Building Folder Sync Tool..."

Compile using C++17 standard

g++ -std=c++17 -O2 main.cpp -o sync_tool

INSTALL_DIR="/usr/local/bin"

if [ -w "$INSTALL_DIR" ]; then
mv sync_tool "$INSTALL_DIR/sync_tool"
else
echo "Elevated permissions required to install to $INSTALL_DIR."
sudo mv sync_tool "$INSTALL_DIR/sync_tool"
fi

echo "Installation complete! You can now run 'sync_tool' from anywhere in your terminal."