#!/bin/tcsh

# setup for oracle db to be accessed by the SVAC pipeline

setenv TWO_TASK SLACPROD
setenv ORACLE_HOME /afs/slac/package/oracle/8.1.6/sun4x_56
setenv TNS_ADMIN /afs/slac/package/oracle/8.1.6/sun4x_56/network/admin/tnsnames.ora
setenv LIBHOME /afs/slac/package/oracle/8.1.6/sun4x_56/lib
setenv dbName DBI:Oracle:${TWO_TASK}
setenv userName GLAST_CAL
setenv passWd "9square#"
