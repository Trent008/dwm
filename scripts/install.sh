# installs dwm with my .xinitrc status display
cd ~
sudo cp dwm/xinitrc ~/.xinitrc
sudo cp dwm/settings.ini /etc/gtk-3.0
sudo echo "Xcursor.size: 32" > ~/.Xresources
cd dwm
sudo make clean install
cd ~