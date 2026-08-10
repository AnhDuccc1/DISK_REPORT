#!/bin/bash
set -e

echo "Removing DRP from /usr/local/bin..."
sudo rm -f /usr/local/bin/drp

echo "--------------------------------------------------------"
echo "Uninstallation successful! (Reports in ~/.drp/ were preserved)"
