# installs dwm with my .xinitrc status display
cd ~
sudo echo "$(cat dwm/xinitrc)" > .xinitrc
cd dwm
sudo make clean install
cd ~
