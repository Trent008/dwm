xrdb .Xresources
# neccessary for commands to work for all users
cd ~
# display date and time
while true; do
        xsetroot -name "Battery: $(cat /sys/class/power_supply/BAT0/capacity)%    $( date +"%a %b %d   %I:%M %P" )"
        sleep 2
done &

# start dwm
exec dwm
