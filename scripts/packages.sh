# installs my packages including yay
sudo pacman -Syu
sudo pacman -S libxinerama libx11 libxft xorg-server xorg-xinit xorg-xsetroot xorg-xrandr
sudo pacman -S terminator feh playerctl firefox
sudo pacman -S adapta-gtk-theme ttf-nerd-fonts-symbols-mono brightnessctl
cd ~
git clone https://aur.archlinux.org/yay.git
git clone https://git.suckless.org/dmenu
cd yay
makepkg -si
cd ~/dmenu
sudo make clean install
yay -S xcursor-breeze papirus-icon-theme bluetuith
sudo systemctl enable --now NetworkManager.service
cd ~
