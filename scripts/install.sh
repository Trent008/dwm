# installs dwm with my .xinitrc status display and applies appearance config
cd ~
sudo cp dwm/configuration/.xinitrc ~
sudo cp dwm/configuration/settings.ini /etc/gtk-3.0
mkdir .config/gtk-3.0
mkdir .icons .icons/default
cp dwm/configuration/settings.ini .config/gtk-3.0
cp dwm/configuration/index.theme .icons/default
cp dwm/configuration/.Xresources ~
cp dwm/configuration/.gtkrc-2.0 ~
cd dwm
sudo make clean install
cd ~