#!/bin/bash
set -e

echo "Building Folder Sync Tool..."

# Compile using Makefile
make all

INSTALL_DIR="/usr/local/bin"

if [ -w "$INSTALL_DIR" ]; then
    mv fsync "$INSTALL_DIR/fsync"
else
    echo "Elevated permissions required to install to $INSTALL_DIR."
    sudo mv fsync "$INSTALL_DIR/fsync"
fi

echo "Installation complete! You can now run 'fsync' from anywhere in your terminal.""
