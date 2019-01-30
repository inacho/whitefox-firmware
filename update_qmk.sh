#!/usr/bin/env bash

set -e

APP_PATH="$( cd -P "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$APP_PATH"

if [[ -d ./qmk_firmware ]]; then
    rm -rf ./qmk_firmware
fi

echo "Cloning qmk_firmware repository"
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git qmk_firmware
./qmk_firmware/util/qmk_install.sh

echo "Done. Execute ./compile.sh to compile the firmware"
