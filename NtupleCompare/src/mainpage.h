/*! @mainpage  package EngineeringModelRoot

@author Xin Chen

@section intro Introduction

This package contains code to compare variables in two sets of merit(SVAC) ntuple files using KS test, produce a result report in both html and latex format using Doxygen. 

The package includes the following executables/scripts:

<ul>
<li> pl/GenKsReport.pl: It reads in a job option file. The script uses its first argument as name of the option file; when there is no argument, it uses ../src/ReportOption.dat as the option file. See below for content of the job option file</li>
<li> NtupleCompare.exe: The executable doing the actual work </li>
</ul>

@section jobOpt Example of the option file

@verbinclude ReportOption.dat

*/
