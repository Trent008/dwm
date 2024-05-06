# add items to autostart here
./ultimate-system/monitor.sh &
dunst &
picom &
rclone mount --daemon Dordt-OneDrive: /home/trent/Dordt-OneDrive &
rclone mount --daemon "Google Drive:" /home/trent/Google-Drive &
feh --bg-max ultimate-system/wallpapers/