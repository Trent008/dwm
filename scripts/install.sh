# installs dwm with my .xinitrc status display
cd ~
sudo cp dwm/configuration/.xinitrc ~
sudo cp dwm/configuration/settings.ini /etc/gtk-3.0
mkdir ~/.config/gtk-3.0
cp dwm/configuration/settings.ini ~/.config/gtk-3.0/settings.ini
cp dwm/configuration/.Xresources ~
cp dwm/configuration/.gtkrc-2.0 ~
cd dwm
sudo make clean install
cd ~