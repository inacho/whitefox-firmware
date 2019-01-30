#!/usr/bin/env bash

set -e

APP_PATH="$( cd -P "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$APP_PATH"

if [[ ! -f "$APP_PATH/whitefox_nacho.bin" ]]; then
    echo "File whitefox_nacho.bin not exists"
    echo "Compile the firmware first"
    exit
fi

# Countdown to have enough time to put the keyboard in flash mode

echo -n "Flashing the firmware in "
for i in {8..1};do echo -n "$i." && sleep 1; done
echo ""

dfu-util -d 1c11:b007 -D "$APP_PATH/whitefox_nacho.bin"
