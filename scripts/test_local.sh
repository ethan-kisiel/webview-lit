#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)

sh "$repo_root/scripts/check_style.sh"
sh "$repo_root/scripts/build_backend.sh"
ctest --test-dir "$repo_root/build" --output-on-failure

cd "$repo_root/src/frontend"
npm test