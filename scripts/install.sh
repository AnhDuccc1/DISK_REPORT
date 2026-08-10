#!/bin/bash
set -e

echo "Building DRP..."
mkdir -p build
cd build
cmake ..
make

echo "Installing DRP to /usr/local/bin..."
sudo cp drp /usr/local/bin/drp

echo "--------------------------------------------------------"
echo "Installation successful! You can now run 'drp <directory>' anywhere."
