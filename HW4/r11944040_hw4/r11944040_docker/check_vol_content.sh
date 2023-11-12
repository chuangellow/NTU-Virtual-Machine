user_type=$1

if [ "$user_type" = "server" ]; then
    docker run -it --rm -v r11944040_docker_r11944040_servervol:/r11944040_servervol alpine cat /r11944040_servervol/sent.txt
elif [ "$user_type" = "client" ]; then
    docker run -it --rm -v r11944040_docker_r11944040_clientvol:/r11944040_clientvol alpine cat /r11944040_clientvol/received.txt
else
    echo "Invalid user_type. Please specify either 'server' or 'client'."
fi
