#!/bin/bash

# Insert the paths to your PCSX2 executable and your copy of the game below
PCSX2_PATH=""
ISO_PATH=""

"$PCSX2_PATH" --nogui --console --gameargs="-d --debug" --elf="./SCUS_971.98" "$ISO_PATH"
