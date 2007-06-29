#!/bin/tcsh

# setup for oracle db to be accessed by the SVAC pipeline

setenv TWO_TASK SLACPROD
setenv ORACLE_HOME /afs/slac/package/oracle/8.1.6/sun4x_56
setenv TNS_ADMIN /afs/slac/package/oracle/8.1.6/sun4x_56/network/admin/tnsnames.ora
setenv LIBHOME /afs/slac/package/oracle/8.1.6/sun4x_56/lib
setenv ORACLE_LD_PATH .:/afs/slac.stanford.edu/g/glast/applications/install/i386_linux22/usr/lib/python2.2:${ORACLE_HOME}/lib:${ORACLE_HOME}/rdbms/lib

setenv dbName DBI:Oracle:${TWO_TASK}
setenv userName GLAST_CAL
setenv passWd "9square#"
