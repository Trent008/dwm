# installs my packages including yay
sudo pacman -Syu
sudo pacman -S libxinerama libx11 libxft xorg-server xorg-xinit xorg-xsetroot xorg-xrandr
sudo pacman -S code terminator pcmanfm feh spotify-launcher playerctl dunst
sudo pacman -S adapta-gtk-theme ttf-nerd-fonts-symbols-mono shotgun brightnessctl firefox
cd ~
git clone https://aur.archlinux.org/yay.git
git clone https://git.suckless.org/dmenu
cd yay
makepkg -si
cd ~/dmenu
sudo make clean install
yay -S xcursor-breeze papirus-icon-theme bluetuith
sudo systemctl enable --now bluetooth.service
sudo systemctl enable --now NetworkManager.service
cd ~
