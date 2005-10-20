#!/bin/tcsh

# setup for oracle db to be accessed by the SVAC pipeline
# uses Oracle v8 libraries for Python scripts

setenv TWO_TASK SLACPROD

setenv ORACLE_HOME /afs/slac/package/oracle/current/@sys
setenv TNS_ADMIN ${ORACLE_HOME}/network/adm
setenv LIBHOME ${ORACLE_HOME}/lib
setenv ORACLE_LD_PATH .:/afs/slac.stanford.edu/g/glast/applications/python/Python-2.2.2/Lib:/afs/slac.stanford.edu/g/glast/applications/python/Oracle/i386_linux24/DCOracle2:${LIBHOME}:${ORACLE_HOME}/rdbms/lib

setenv dbName DBI:Oracle:${TWO_TASK}
setenv userName GLAST_CAL
setenv passWd "9square#"
