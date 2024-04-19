# installs my packages including yay
sudo pacman -Syu
sudo pacman -S libxinerama libx11 libxft xorg-server xorg-xinit xorg-xsetroot arandr kitty rofi feh picom dunst
sudo pacman -S lxappearance adapta-gtk-theme ttf-meslo-nerd ttf-nerd-fonts-symbols-mono code nano
sudo pacman -S bluez spotify-launcher nemo playerctl pavucontrol blueberry
cd ~
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si
sudo systemctl enable --now bluetooth.service
sudo systemctl enable --now NetworkManager.service
yay -S breeze-light-cursor-theme papirus-icon-theme thorium-browser-bin
cd ~