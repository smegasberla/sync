#!/bin/bash
set -e

INSTALL_DIR="/usr/local/bin"
TARGET="$INSTALL_DIR/sync_tool"

if [ -f "$TARGET" ]; then
if [ -w "$INSTALL_DIR" ]; then
rm "$TARGET"
else
echo "Elevated permissions required to remove $TARGET."
sudo rm "$TARGET"
fi
echo "Folder Sync Tool successfully uninstalled."
else
echo "sync_tool binary not found in $INSTALL_DIR."
fi