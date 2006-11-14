#!/bin/tcsh

cd $svacPlRoot

foreach genXml (*/genXml.pl)
    echo running $genXml
    $genXml
end

echo running setup/genHtAccess.pl
setup/genHtAccess.pl

echo =========================================================================
echo Now upload these XML files:
ls $svacPlRoot/*.xml
echo =========================================================================
