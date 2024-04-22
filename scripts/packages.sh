# installs my packages including yay
sudo pacman -Syu
sudo pacman -S libxinerama libx11 libxft xorg-server xorg-xinit xorg-xsetroot xorg-xrandr
sudo pacman -S code nano kitty nemo feh rofi picom spotify-launcher playerctl dunst
sudo pacman -S adapta-gtk-theme ttf-nerd-fonts-symbols-mono flameshot brightnessctl firefox
cd ~
git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si
yay -S breeze-light-cursor-theme papirus-icon-theme bluetuith
sudo systemctl enable --now bluetooth.service
sudo systemctl enable --now NetworkManager.service
cd ~
