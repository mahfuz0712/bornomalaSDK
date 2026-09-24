#!/bin/bash

set -e

PREFIX="/opt/BornomalaSDK"

echo "Installing Bornomala SDK..."

# Create directories
sudo mkdir -p "$PREFIX"
sudo mkdir -p /usr/local/bin

# Install SDK files
sudo cp -r sdk "$PREFIX/"
sudo cp -r templates "$PREFIX/"

# Copy docs if exists
if [ -d docs ]; then
    sudo cp -r docs "$PREFIX/"
fi

# Install CLI
sudo install -m 755 bin/bsa /usr/local/bin/bsa

echo ""
echo "✓ Bornomala SDK installed successfully."
echo "CLI: /usr/local/bin/bsa"
echo "SDK: $PREFIX"
echo ""
echo "Run: bsa doctor"