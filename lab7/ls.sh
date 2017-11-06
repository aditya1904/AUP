#!/bin/bash

echo "calling ls -l /proc/self/fd to list open file descriptors"
ls -l /proc/self/fd

echo writing \"from child\" to file descriptor 3
echo "from child" >&3
echo reading from file descriptor 4
cat <&4 
