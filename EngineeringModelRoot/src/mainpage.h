// (Special "header" just for doxygen)

/*! @mainpage  package EngineeringModelRoot

@author Xin Chen

@section intro Introduction

This package contains codes to generate ntuple for I&T/SVAC. The package includes following executables/scripts

<ul>
<li> RunRootAnalyzer.exe. It read data from 3 root files: mc, digi and recon. It produce 2 root files: *_svac.root contains ntuple for I&T/SVAC, *_hist.root contains histograms for I&T/SVAC. Names of the root files are contained in a option file. The exe uses its first argument as name of the option file; when there is no argument, it uses ../src/AnalyzerOption.dat as the option file</li>
<li> merge_raRoot.exe. It merges a list of SVAC and merit ntuple files. </li>
<li> ../pl/RunRootAnalyzer.pl. It is used to run RunRootAnalyzer.exe at batch. </li>
<li> AnalyzeAcd.exe. A utility exe to process ACD digi alone. </li>
</ul>

@section def Definition of SVAC ntuple

<TABLE>
<CAPTION ALIGN="TOP"> Run and Event variable </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> Run </TD> <TD> run number taken from DigiEvent.h </TD> </TR>
<TR> <TD> Event </TD> <TD> event number taken from DigiEvent.h</TD> </TR>
<TR> <TD> GltWord </TD> <TD> trigger word. Not valid for EM1 data as there were no GASU, should be valid for LAT integration data</TD> </TR>
<TR> <TD> EvtTime </TD> <TD> Time stamp taken from DigiEvent.h, this may change when new LDF definition is available. </TD> </TR>
<TR> <TD> EvtSecond </TD> <TD> event time </TD> </TR>
<TR> <TD> EvtNanoSecond </TD> <TD> event time </TD> </TR>
<TR> <TD> EvtUpperTime </TD> <TD> event time (this will change)</TD> </TR>
<TR> <TD> EvtLowerTime </TD> <TD> event time (this will change)</TD> </TR>
<TR> <TD> EvtSummary </TD> <TD> summary word for each event. For detailed explaination, see onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf, Chapter 3.5</TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> MC variable </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> McSeqNo </TD> <TD> sequence number </TD> </TR>
<TR> <TD> McId </TD> <TD> PDG id for primary MC particle. For example: e-(11), e+(-11), gamma(22), mu-(13), mu+(-13) </TD> </TR>
<TR> <TD> McTotalEnergy </TD> <TD> total energy of the particle including it's mass </TD> </TR>
<TR> <TD> McX0 </TD> <TD> x coordinate of origin of the particle </TD> </TR>
<TR> <TD> McY0 </TD> <TD> y coordinate of origin of the particle </TD> </TR>
<TR> <TD> McZ0 </TD> <TD> z coordinate of origin of the particle </TD> </TR>
<TR> <TD> McXDir </TD> <TD> true x direction of the primary particle </TD> </TR>
<TR> <TD> McYDir </TD> <TD> true y direction of the primary particle </TD> </TR>
<TR> <TD> McZDir </TD> <TD> true z direction of the primary particle </TD> </TR>
<TR> <TD> McConvPointX </TD> <TD> x coordinate of photon conversion point </TD> </TR>
<TR> <TD> McConvPointY </TD> <TD> y coordinate of photon conversion point </TD> </TR>
<TR> <TD> McConvPointZ </TD> <TD> z coordinate of photon conversion point </TD> </TR>
<TR> <TD> McCalEneSum </TD> <TD> MC sum of energies deposited in each crystal </TD> </TR>
<TR> <TD> McTkr1Ene </TD> <TD> MC energy of first track if there is a pair production </TD> </TR>
<TR> <TD> McTkr2Ene </TD> <TD> MC energy of second track if there is a pair production </TD> </TR>
<TR> <TD> McConvAngle </TD> <TD> Opening angle of e+/e- pair if there is a pair production </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> Vertex variable </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> VtxX0 </TD> <TD> x coordinate of first(best) vertex </TD> </TR>
<TR> <TD> VtxY0 </TD> <TD> y coordinate of first(best) vertex </TD> </TR>
<TR> <TD> VtxZ0 </TD> <TD> z coordinate of first(best) vertex </TD> </TR>
<TR> <TD> VtxXDir </TD> <TD> x direction in first vertex. If there are two tracks associated with the vertex, then it is averged over direction of the two tracks; Otherwise, it is just direction of the track. </TD> </TR>
<TR> <TD> VtxYDir </TD> <TD> y direction in first vertex. If there are two tracks associated with the vertex, then it is averged over direction of the two tracks; Otherwise, it is just direction of the track. </TD> </TR>
<TR> <TD> VtxZDir </TD> <TD> z direction in first vertex. If there are two tracks associated with the vertex, then it is averged over direction of the two tracks; Otherwise, it is just direction of the track. </TD> </TR>
<TR> <TD> Vtx1NumTkrs </TD> <TD> number of tracks associated with first vertex </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> TKR variable </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> TkrNumDigis </TD> <TD> number of TKR digis. Normally a digi is produced whenver there is a strip hit in a silicon plane. </TD> </TR>
<TR> <TD> TkrNumStrips[tower][layer][view] </TD> <TD> A 3 dimension array which describes number of strips in every tower, layer and view. View=0 refers to measure X while View=1 refers to measure Y </TD> </TR>
<TR> <TD> tot[tower][layer][view][end] </TD> <TD> A 4 dimension array which describes tot value at every tower, layer, view and end. End=0 refers to low end with stripId from 0 to 768 while end=1 refers to high end with stripId from 768 to 1536. Normally division is at middle of the plane, however this could be changed during real data taking. </TD> </TR>
<TR> <TD> totCorrL[tower][layer][view][end] </TD> <TD> A 4 dimension array which describes corrected tot value at every tower, layer, view and end, using Hiro's linear correction formula. At the moment only valid for EM1 data. </TD> </TR>
<TR> <TD> totCorrQ[tower][layer][view][end] </TD> <TD> A 4 dimension array which describes corrected tot value at every tower, layer, view and end, using Hiro's quadratic correction formula. At the moment only valid for EM1 data. </TD> </TR>
<TR> <TD> TkrNumClusters[tower][layer][view] </TD> <TD> A 3 dimension array which describes number of clusters at every tower, layer and view. View=0 refers to measure X while View=1 refers to measure Y. </TD> </TR>
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
<TR> <TD> TkrTopTot[tower] </TD> <TD>A one dimension array which describes tot value at the top hit layer for each tower. The value is actually the maximum of 4 tot values at the biPlane.</TD> </TR> 
<TR> <TD> Tkr1ConvTot[tower] </TD> <TD>A one dimension array which describes tot value at the layer of the first vertex. The value is actually the maximum of 4 tot values at the biPlane.</TD> </TR>
<TR> <TD> TkrTp[tower] </TD> <TD>A one dimension array which describes tracker trigger primitive for each tower. For detailed description, please see onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3</TD> </TR>
<TR> <TD> TkrReq[tower][layer][view][end] </TD> <TD>A 4 dimension array which describes tracker trigger request. For example: TkrReq[8][7][0][0]=1 means trigger request was sent from tower 8, layer 7, measure X and lower end of the tray.  End=0 refers to low end with stripId from 0 to 768 while end=1 refers to high end with stripId from 768 to 1536. Normally division is at middle of the plane, however this could be changed during real data taking.</TD> </TR>
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
<TR> <TD> CalNumHit[tower] </TD> <TD> A one dimension array which describes number of crystals in each tower with measured energy larger than zero suppression threshold </TD> </TR>
<TR> <TD> CalTp[tower] </TD> <TD>A one dimension array which describes calorimeter trigger primitive for each tower.  For detailed description, please see onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3</TD> </TR>
<TR> <TD> CalReq[tower][layer][end] </TD> <TD>A 4 dimension array which describes calorimeter trigger request. For example: CalReq[8][7][0]=1 means trigger request was sent from tower 8, layer 7 and end 0.  End=0 refers to low end with stripId from 0 to 768 while end=1 refers to high end with stripId from 768 to 1536. Normally division is at middle of the plane, however this could be changed during real data taking.</TD> </TR>
</TABLE>

*/
