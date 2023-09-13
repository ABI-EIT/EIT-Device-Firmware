#!/bin/bash

GDB_HOSTNAME="gdb-server"

GATEWAY=$(ip r | grep default | cut -f3 -d" ")

echo "Found gateway : $GATEWAY"

if grep -q "$GDB_HOSTNAME" /etc/hosts
then
    echo "$GDB_HOSTNAME exists in /etc/hosts, updating to $GATEWAY"
    sed -ie "s/\\d+\\.\\d+\\.\\d+\\.\\d+(?=\s+$GDB_HOSTNAME[^\w])/$GATEWAY/g" /etc/hosts
else
    echo " Adding $GDB_HOSTNAME ($GATEWAY) to /etc/hosts"
    printf "\n$GATEWAY\t$GDB_HOSTNAME\n" >> /etc/hosts
fi