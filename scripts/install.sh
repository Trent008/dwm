# installs dwm with my .xinitrc status display
cd ~
sudo cp dwm/configuration/.xinitrc ~
sudo cp dwm/configuration/settings.ini ~/.config/gtk-3.0
sudo cp dwm/configuration/.Xresources ~
sudo cp dwm/configuration/.gtkrc-2.0 ~
cd dwm
sudo make clean install
cd ~