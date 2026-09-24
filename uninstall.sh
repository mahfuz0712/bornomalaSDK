#!/bin/bash

set -e

echo "Removing Bornomala SDK..."

sudo rm -f /usr/local/bin/bsa
sudo rm -rf /opt/BornomalaSDK

echo "✓ Bornomala SDK removed."