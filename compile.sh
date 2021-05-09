#!/usr/bin/env bash

set -e

APP_PATH="$( cd -P "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$APP_PATH"


KEYMAP_FOLDER="$APP_PATH/qmk_firmware/keyboards/whitefox/keymaps/nacho"
VISUALIZERS_FOLDER="$APP_PATH/qmk_firmware/quantum/visualizer"


if [[ ! -d ./qmk_firmware ]]; then
    echo "Cloning qmk_firmware repository"

    git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git qmk_firmware
    ./qmk_firmware/util/qmk_install.sh
fi

# Copy the keymap to qmk_firmware

rm -rf "$KEYMAP_FOLDER"
mkdir -p "$KEYMAP_FOLDER"

cp "$APP_PATH/default_animations.c" "$VISUALIZERS_FOLDER"
cp "$APP_PATH/keymap.c" "$KEYMAP_FOLDER"
cp "$APP_PATH/custom_defines.h" "$KEYMAP_FOLDER"
cp "$APP_PATH/rules.mk" "$KEYMAP_FOLDER"

# Compile the firmware

rm -f "$APP_PATH/whitefox_nacho.bin"
cd "$APP_PATH/qmk_firmware"
make whitefox:nacho:bin
cp "$APP_PATH/qmk_firmware/whitefox_nacho.bin" "$APP_PATH"

# Delete the keymap from qmk_firmware

rm -rf "$KEYMAP_FOLDER"

echo "Done"
echo "Run ./flash.sh to flash the keyboard"
