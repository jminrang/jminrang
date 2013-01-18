#!/bin/bash

# refer by linux/script/ver_linux
# store this computer's env and neccesary untility info

echo "====================================================="
echo "                   version check"
echo "====================================================="

gcc -dumpversion 2>&1 | awk \
	    'NR==1{print "Gnu C		", $1}' > Env.txt


make --version 2>&1 | awk -F, '{print $1}' | awk \
	     '/GNU Make/{print "Gnu make	",$NF}' >> Env.txt

qemu-system-x86_64 --version | cut -d" " -f4 | awk \
	     'NR==1{print "Qemu            ",$NF}' >> Env.txt
	
echo "binutils         $(ld -v | egrep -o '[0-9]+\.[0-9\.]+')" >> Env.txt

uname -p 2>&1 | awk \
	     'NR=1{print "Processor       ", $1}' >> Env.txt

cat Env.txt
