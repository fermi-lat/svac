#!/bin/csh

source ${svacPlRoot}/setup/commonRuntime.cshrc

setenv eLogTaskVersion v2r0
setenv eLogTask updateELogDB-$iAndTPhase-${eLogTaskVersion}

setenv configReportTaskVersion v2r0
setenv configReportTask configReport-$iAndTPhase-${configReportTaskVersion}

setenv digitizationTaskVersion v2r0
setenv digitizationTask digitization-$iAndTPhase-${digitizationTaskVersion}

setenv digiReportTaskVersion v2r0
setenv digiReportTask digiReport-$iAndTPhase-${digiReportTaskVersion}

setenv reconTaskVersion v2r0
setenv reconTask recon-$iAndTPhase-${reconTaskVersion}

setenv reconReportTaskVersion v2r0
setenv reconReportTask reconReport-$iAndTPhase-${reconReportTaskVersion}

setenv svacTupleTaskVersion v2r0
setenv svacTupleTask svacTuple-$iAndTPhase-${svacTupleTaskVersion}
