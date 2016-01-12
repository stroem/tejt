#!/bin/bash 

ROOT_UID=0   # Only the root can install a firewall
E_NOTROOT=67 # Error code

if [ $UID -ne $ROOT_UID ]
then
    echo "You must be root to run this script."
    exit $E_NOTROOT
fi  

echo "Installing the service..."

cp $PWD/serverinit.sh /etc/init.d

X=1
while [ $X -le 5 ] 
do
    if [ -e /etc/rc$X.d/*serverinit.sh ]
        then rm /etc/rc$X.d/*serverinit.sh
    fi
    X=$((X+1))
done

update-rc.d serverinit.sh defaults

echo -n "Making sure that the script isn't executed at rc 0 and 6..."

rm /etc/rc0.d/*serverinit.sh
rm /etc/rc6.d/*serverinit.sh

echo "Done!"

/etc/init.d/serverinit.sh

echo "Changes applied, your computer is now a Tejtpuck server."
