#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

sudo chown 770 parse
sudo chmod u+x parse

$SCRIPT_DIR/parse $1