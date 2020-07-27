#!/bin/sh

branch="$(git branch | grep '^\* ' | sed 's/^\* //')"

case "${branch}" in
windows) git checkout master;;
esac

find * -type l > symlinks.tmp
git checkout windows
cat symlinks.tmp | while read l ; do
  d="$(dirname "${l}")"
  b="$(basename "${l}")"
  cd "${d}"
  rm -f "${b}"
  cp -v "../Modules/${b}" "${b}"
  git add "${b}"
  cd ..
done
rm symlinks.tmp

git commit -m "symlink-free copy for windows"

