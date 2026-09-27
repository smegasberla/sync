#!/bin/bash
set -e

echo "Building Folder Sync Tool..."

# Compile using C++17 standard

g++ -std=c++17 -O2 src/main.cpp -o sync

INSTALL_DIR="/usr/local/bin"

if [ -w "$INSTALL_DIR" ]; then
mv sync "$INSTALL_DIR/sync"
else
echo "Elevated permissions required to install to $INSTALL_DIR."
sudo mv sync "$INSTALL_DIR/sync"
fi

echo "Installation complete! You can now run 'sync' from anywhere in your terminal."