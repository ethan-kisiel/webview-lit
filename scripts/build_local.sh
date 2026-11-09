#!/bin/sh
set -eu

script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)

sh "$script_dir/check_style.sh"
sh "$script_dir/build_backend.sh"
sh "$script_dir/build_frontend.sh"
