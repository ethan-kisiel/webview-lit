#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
build_dir="$repo_root/build"

cmake -S "$repo_root/src/backend" -B "$build_dir"
cmake --build "$build_dir"