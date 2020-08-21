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
cat >hex/build_info.txt <<EOF
These builds were done using the "arduino-mk" package on the following system:
$(lsb_release -a)
Build run completed at: $(date -u)
EOF
rm -rf tmp/release

cat <<EOF

All done!

now run:
git commit --amend

EOF

git add -v hex/
