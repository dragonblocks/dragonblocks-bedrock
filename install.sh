#! /bin/bash
cp . /usr/share/dragonblocks -R
echo "
cd /usr/share/dragonblocks
bin/dragonblocks \$*
" > /usr/bin/dragonblocks
chmod +x /usr/bin/dragonblocks
