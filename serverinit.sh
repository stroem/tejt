#/bin/bash/

ifconfig eth0 down
ifconfig eth0 inet 172.30.2.26
route add default gw 172.30.0.1
ifconfig eth0 up

Tejtserv 7317 sommarserver
