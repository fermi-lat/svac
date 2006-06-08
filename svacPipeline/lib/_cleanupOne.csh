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
	foreach dir ($dirs)
		if ({ ps uwww $dir }) then
			echo Process still active, not removing $dir
		else
			echo Removing $dir
			rm -rf $dir
		endif
	end
endif

