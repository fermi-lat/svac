// (Special "header" just for doxygen)

/*! @mainpage  package EngineeringModelRoot

This package contains codes to generate ntuple for I&T/SVAC. The package includes following executables/scripts

<ul>
<li> RunRootAnalyzer.exe. It read data from 3 root files: mc, digi and recon. It produce 2 root files: *_svac.root contains ntuple for I&T/SVAC, *_hist.root contains histograms for I&T/SVAC. Names of the root files are contained in a option file. The exe uses its first argument as name of the option file; when there is no argument, it uses ../src/AnalyzerOption.dat as the option file</li>
<li> merge_raRoot.exe. It merges a list of SVAC and merit ntuple files. </li>
<li> ../pl/RunRootAnalyzer.pl. It is used to run RunRootAnalyzer.exe at batch. </li>
</ul>

Definition of SVAC ntuple is as the following:

<TABLE>
<CAPTION ALIGN="TOP"> Run variable </CAPTION>
<TR> <TD> Run </TD> <TD> run number </TD> </TR>
<TR> <TD> Event </TD> <TD> event number </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> MC variable </CAPTION>
<TR> <TD> McSeqNo </TD> <TD> sequence number </TD> </TR>
<TR> <TD> McId </TD> <TD> PDG id for primary MC particle </TD> </TR>
<TR> <TD> McTotalEnergy </TD> <TD> total energy of the particle including it's mass </TD> </TR>
<TR> <TD> McX0 </TD> <TD> X coordinate of origin of the particle </TD> </TR>
<TR> <TD> McY0 </TD> <TD> Y coordinate of origin of the particle </TD> </TR>
<TR> <TD> McZ0 </TD> <TD> Z coordinate of origin of the particle </TD> </TR>
<TR> <TD> McXDir </TD> <TD> X direction of the particle </TD> </TR>
<TR> <TD> McYDir </TD> <TD> Y direction of the particle </TD> </TR>
<TR> <TD> McZDir </TD> <TD> Z direction of the particle </TD> </TR>
<TR> <TD> McConvPointX </TD> <TD> X coordinate of photon conversion point </TD> </TR>
<TR> <TD> McConvPointY </TD> <TD> Y coordinate of photon conversion point </TD> </TR>
<TR> <TD> McConvPointZ </TD> <TD> Z coordinate of photon conversion point </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> TKR variable </CAPTION>
<TR> <TD> TkrNumDigis </TD> <TD> number of TKR digis</TD> </TR>
<TR> <TD> TkrNumStrips[tower][layer][view] </TD> <TD> number of strips in every tower, layer and view </TD> </TR>
<TR> <TD> tot[tower][layer][view][end] </TD> <TD> tot value at every tower, layer, view and end </TD> </TR>
<TR> <TD> totCorrL[tower][layer][view][end] </TD> <TD> corrected tot value at every tower, layer, view and end, using Hiro's linear correction formula. At the moment only valid for EM1 data </TD> </TR>
<TR> <TD> totCorrQ[tower][layer][view][end] </TD> <TD> corrected tot value at every tower, layer, view and end, using Hiro's quadratic correction formula. At the moment only valid for EM1 data </TD> </TR>
<TR> <TD> TkrNumClusters[tower][layer][view] </TD> <TD> number of clusters at every tower, layer and view</TD> </TR>
<TR> <TD> TkrNumTracks </TD> <TD> number of reconstructed tracks</TD> </TR>
</TABLE>
*/
