# add items to autostart here
./ultimate-system/monitor.sh &
dunst &
picom &
swtpm socket --tpm2 --tpmstate dir=/home/trent/vm-tpm --ctrl type=unixio,path=/home/trent/vm-tpm/swtpm-sock &
rclone mount --daemon Dordt-OneDrive: /home/trent/Dordt-OneDrive &
rclone mount --daemon "Google Drive:" /home/trent/Google-Drive &
feh --bg-max ultimate-system/wallpapers/