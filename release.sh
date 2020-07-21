#!/bin/sh

set -e
cd "$(dirname "${0}")"

rm -rf tmp/release
mkdir -p tmp

git clone . tmp/release
make -C tmp/release release || :
for i in tmp/release/tmp/*/*.hex; do
  cp -v "${i}" "hex/USB2Amiga.$(basename "${i}")"
done
rm -rf tmp/release

cat <<EOF

All done!

now run:
git commit --amend

EOF

git add -v hex/
