#!/bin/tcsh

if (! { test -d $localDisk })  then
	echo No scratch dir to clean out.
	exit
endif

cd $localDisk

#set dirs=`ls -l | awk '/(glastdpf|glastdpt|glastdpd).*[:blank:][0-9]+$/{print $NF}'`
set dirs=`ls -l | awk '/(glastdpf|glastdpt|glastdpd).*[0-9]+$/{print $NF}'`
if ({ test -z "$dirs" }) then
	echo No chunk dirs to remove.
	exit
else
	echo Removing $dirs
	rm -rf $dirs
endif

