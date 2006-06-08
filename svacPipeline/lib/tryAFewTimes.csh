#!/bin/tcsh

set args="$*"

set nTries=5
set delay=23

echo Attempting [$args] up to $nTries times.
date

foreach xxx (`seq $nTries`)
    $args && set done=1 || set done=0
	if ($done) break
    sleep $delay
end
if (! $done) then
    echo Failed $xxx times.
    date
    exit 1
endif
echo Succeded after $xxx tries.

date
