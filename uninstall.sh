#!/bin/bash
set -e

INSTALL_DIR="/usr/local/bin"
TARGET="$INSTALL_DIR/fsync"

if [ -f "$TARGET" ]; then
if [ -w "$INSTALL_DIR" ]; then
rm "$TARGET"
else
echo "Elevated permissions required to remove $TARGET."
sudo rm "$TARGET"
fi
echo "Fsync binary successfully uninstalled."
else
echo "fsync binary not found in $INSTALL_DIR."
fi