// (Special "header" just for doxygen)

/*! @mainpage  package EngineeringModelRoot

@author Xin Chen

@section intro Introduction

This package contains codes to generate ntuple for I&T/SVAC. The package includes following executables/scripts

<ul>
<li> RunRootAnalyzer.exe. It read data from 3 root files: mc, digi and recon. It produce 2 root files: *_svac.root contains ntuple for I&T/SVAC, *_hist.root contains histograms for I&T/SVAC. Names of the root files are contained in a option file. The exe uses its first argument as name of the option file; when there is no argument, it uses ../src/AnalyzerOption.dat as the option file</li>
<li> merge_raRoot.exe. It merges a list of SVAC and merit ntuple files. </li>
<li> ../pl/RunRootAnalyzer.pl. It is used to run RunRootAnalyzer.exe at batch. </li>
</ul>

@section def Definition of SVAC ntuple

<TABLE>
<CAPTION ALIGN="TOP"> Run and Event variable </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> Run </TD> <TD> run number </TD> </TR>
<TR> <TD> Event </TD> <TD> event number </TD> </TR>
<TR> <TD> GltWord </TD> <TD> trigger </TD> </TR>
<TR> <TD> EvtSecond </TD> <TD> event time </TD> </TR>
<TR> <TD> EvtNanoSecond </TD> <TD> event time </TD> </TR>
<TR> <TD> EvtUpperTime </TD> <TD> event time (this will change)</TD> </TR>
<TR> <TD> EvtLowerTime </TD> <TD> event time (this will change)</TD> </TR>
<TR> <TD> EvtSummary </TD> <TD> summary word for each event</TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> MC variable </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> McSeqNo </TD> <TD> sequence number </TD> </TR>
<TR> <TD> McId </TD> <TD> PDG id for primary MC particle </TD> </TR>
<TR> <TD> McTotalEnergy </TD> <TD> total energy of the particle including it's mass </TD> </TR>
<TR> <TD> McX0 </TD> <TD> x coordinate of origin of the particle </TD> </TR>
<TR> <TD> McY0 </TD> <TD> y coordinate of origin of the particle </TD> </TR>
<TR> <TD> McZ0 </TD> <TD> z coordinate of origin of the particle </TD> </TR>
<TR> <TD> McXDir </TD> <TD> x direction of the particle </TD> </TR>
<TR> <TD> McYDir </TD> <TD> y direction of the particle </TD> </TR>
<TR> <TD> McZDir </TD> <TD> z direction of the particle </TD> </TR>
<TR> <TD> McConvPointX </TD> <TD> X coordinate of photon conversion point </TD> </TR>
<TR> <TD> McConvPointY </TD> <TD> Y coordinate of photon conversion point </TD> </TR>
<TR> <TD> McConvPointZ </TD> <TD> Z coordinate of photon conversion point </TD> </TR>
<TR> <TD> McCalEneSum </TD> <TD> MC sum of energies deposited in each crystal </TD> </TR>
<TR> <TD> McTkr1Ene </TD> <TD> MC energy of first track if there is a pair production </TD> </TR>
<TR> <TD> McTkr2Ene </TD> <TD> MC energy of second track if there is a pair production </TD> </TR>
<TR> <TD> McTime </TD> <TD> Time stamp of a MC event </TD> </TR>
<TR> <TD> McConvAngle </TD> <TD> Openning angle of e+/e- pair if there is a pair production </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> Vertex variable </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> VtxX0 </TD> <TD> x coordinate of first vertex </TD> </TR>
<TR> <TD> VtxY0 </TD> <TD> y coordinate of first vertex </TD> </TR>
<TR> <TD> VtxZ0 </TD> <TD> z coordinate of first vertex </TD> </TR>
<TR> <TD> VtxXDir </TD> <TD> x direction of best track </TD> </TR>
<TR> <TD> VtxYDir </TD> <TD> y direction of best track </TD> </TR>
<TR> <TD> VtxZDir </TD> <TD> z direction of best track </TD> </TR>
<TR> <TD> Vtx1NumTkrs </TD> <TD> number of tracks associated with first vertex </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> TKR variable </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> TkrNumDigis </TD> <TD> number of TKR digis</TD> </TR>
<TR> <TD> TkrNumStrips[tower][layer][view] </TD> <TD> number of strips in every tower, layer and view </TD> </TR>
<TR> <TD> tot[tower][layer][view][end] </TD> <TD> tot value at every tower, layer, view and end </TD> </TR>
<TR> <TD> totCorrL[tower][layer][view][end] </TD> <TD> corrected tot value at every tower, layer, view and end, using Hiro's linear correction formula. At the moment only valid for EM1 data </TD> </TR>
<TR> <TD> totCorrQ[tower][layer][view][end] </TD> <TD> corrected tot value at every tower, layer, view and end, using Hiro's quadratic correction formula. At the moment only valid for EM1 data </TD> </TR>
<TR> <TD> TkrNumClusters[tower][layer][view] </TD> <TD> number of clusters at every tower, layer and view</TD> </TR>
<TR> <TD> TkrNumTracks </TD> <TD> number of reconstructed tracks</TD> </TR>
<TR> <TD> TkrNumVertices </TD> <TD> number of reconstructed vertices</TD> </TR>
<TR> <TD> EvtEnergySumOpt </TD> <TD> Energy stored in first vertex  </TD> </TR>
<TR> <TD> Tkr1NumHits </TD> <TD> number of clusters in first track </TD> </TR>
<TR> <TD> Tkr2NumHits </TD> <TD> number of clusters in second track </TD> </TR>
<TR> <TD> Tkr1Chisq </TD> <TD> chi square of first track </TD> </TR>
<TR> <TD> Tkr2Chisq </TD> <TD> chi square of second track </TD> </TR>
<TR> <TD> Tkr1ChisqS </TD> <TD> smoothed chi square of first track </TD> </TR>
<TR> <TD> Tkr2ChisqS </TD> <TD> smoothed chi square of second track </TD> </TR>
<TR> <TD> Tkr1Rms </TD> <TD> rms value of first track </TD> </TR>
<TR> <TD> Tkr2Rms </TD> <TD> rms value of second track </TD> </TR>
<TR> <TD> Tkr1KalThetaMs </TD> <TD> muiltiple scattering angle of first track calculated by Kalman filter</TD> </TR>
<TR> <TD> Tkr2KalThetaMs </TD> <TD> muiltiple scattering angle of second track calculated by Kalman filter</TD> </TR>
<TR> <TD> Tkr1KalEne </TD> <TD> energy of first track calculated by Kalman filter</TD> </TR>
<TR> <TD> Tkr2KalEne </TD> <TD> energy of second track calculated by Kalman filter</TD> </TR>
<TR> <TD> TkrTopTot[tower] </TD> <TD>tot value at the top hit layer for each tower</TD> </TR> 
<TR> <TD> Tkr1ConvTot[tower] </TD> <TD>tot value at the layer of the first vertex</TD> </TR>
<TR> <TD> TkrTp[tower] </TD> <TD>TKR trigger primitive for each tower</TD> </TR>
<TR> <TD> TkrReq[tower][layer][view][end] </TD> <TD>trigger request. For example: TkrReq[8][7][0][0]=1 means trigger request was sent from tower 8, layer 7, measure X and lower end of the tray.</TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> CAL variable </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> CalEneSum </TD> <TD> sum of energies in each crystal </TD> </TR>
<TR> <TD> CalXEcentr </TD> <TD> x coordinate of centroid of CAL cluster </TD> </TR>
<TR> <TD> CalXEcentr </TD> <TD> x coordinate of centroid of CAL cluster </TD> </TR>
<TR> <TD> CalYEcentr </TD> <TD> y coordinate of centroid of CAL cluster </TD> </TR>
<TR> <TD> CalZEcentr </TD> <TD> z coordinate of centroid of CAL cluster </TD> </TR>
<TR> <TD> CalXtalEne[tower][layer][col] </TD> <TD> measured energy in a single crystal at each tower, layer and column </TD> </TR>
<TR> <TD> CalMaxEne </TD> <TD> maximal measured energy in a single crystal </TD> </TR>
<TR> <TD> CalNumHit[tower] </TD> <TD> number of crystals in each tower with measured energy larger than zero suppression threshold </TD> </TR>
<TR> <TD> CalTp[tower] </TD> <TD>CAL trigger primitive for each tower</TD> </TR>
<TR> <TD> CalReq[tower][layer][end] </TD> <TD>CAL trigger request. For example: CalReq[8][7][0]=1 means trigger request was sent from tower 8, layer 7 and end 0.</TD> </TR>
</TABLE>

*/
