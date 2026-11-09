#!/bin/sh
set -eu

repo_root=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)

if command -v clang-format >/dev/null 2>&1; then
    clang_format=clang-format
elif command -v xcrun >/dev/null 2>&1; then
    clang_format=$(xcrun --find clang-format)
else
    printf '%s\n' "clang-format is required for the C++ style check" >&2
    exit 1
fi

cd "$repo_root"
find src/backend -type f \( -name '*.cpp' -o -name '*.h' -o -name '*.hpp' \) -print0 \
    | xargs -0 "$clang_format" --dry-run --Werror --style=file

cd "$repo_root/src/frontend"
npm run style:check