// (Special "header" just for doxygen)

/*! @mainpage  package EngineeringModelRoot

@author Xin Chen

@section intro Introduction

This package contains code to generate the SVAC ntuple for I&T/SVAC. The package includes the following executables/scripts:

<ul>
<li> RunRootAnalyzer.exe: It reads data from the 3 root files: mc, digi and recon. It produces 2 root files: *_svac.root contains the SVAC ntuple for I&T/SVAC, 
     *_hist.root contains histograms for I&T/SVAC. The names of the root files are contained in an option file. The executable uses its first argument as the name of 
     the option file; when there is no argument, it uses ../src/AnalyzerOption.dat as the option file</li>
<li> merge_raRoot.exe: It merges a list of SVAC and Merit ntuple files. </li>
<li> ../pl/RunRootAnalyzer.pl: It is used to run RunRootAnalyzer.exe in batch. </li>
<li> AnalyzeAcd.exe: A utility executable to process ACD digi alone. </li>
</ul>

@section def Definition of the SVAC ntuple

<TABLE>
<CAPTION ALIGN="TOP"> Run and Event variables </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> RunID </TD> <TD> Run number taken from DigiEvent.h </TD> </TR>
<TR> <TD> EventID </TD> <TD> Event number taken from DigiEvent.h</TD> </TR>
<TR> <TD> GltWord </TD> <TD> Trigger word: The definition of the bits can be found in enums/enums/TriggerBits.h. Not valid for EM1 data as there were no GASU, should be valid for LAT integration data. </TD> </TR>
<TR> <TD> EvtTime </TD> <TD> Time in seconds, since mission start, currently 1/1/2001. This is the time that is reported when doing simulations.</TD> </TR>
<TR> <TD> EvtSecond </TD> <TD> The number of seconds, since 1/1/1970, used in conjunction with getEbfTimeNanoSec for a measure of absolute time. </TD> </TR>
<TR> <TD> EvtNanoSecond </TD> <TD> The number of nano-seconds, since 1/1/1970, used in conjunction with getEbfTimeSec for a measure of absolute time. </TD> </TR>
<TR> <TD> EvtUpperTime </TD> <TD> The UpperPpcTimeBase word as stored in the LDF from real tests. Used in conjunction with EvtLowerTime (getEbfLowerPpcTimeBase), these words can be used to determine the spacing of real test events. </TD> </TR>
<TR> <TD> EvtLowerTime </TD> <TD> The LowerPpcTimeBase word stored in the LDF from real tests, used in conjunction with getEbfUpperPpcTimeBase, these words can be used to determine the spacing of real test events.</TD> </TR>
<TR> <TD> EvtTimeSeconds </TD> <TD> Uses the data words stored in the UpperPpcTimeBase and LowerPpcTimeBase to calculate seconds since power on. This time is used to determine the spacing of events - NOT as an absolute time. </TD> </TR>
<TR> <TD> EvtSummary </TD> <TD> Summary word for each event. For a detailed explaination, see the Online document at 
          http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf, Chapter 3.5</TD> </TR>
<TR> <TD> EventSequence </TD> <TD> Event sequence number: It comes from a 17 bits online counter and wraps around at 128k events. It may also not be continous or monotonically increasing because of prescaling.</TD> </TR>
<TR> <TD> EventFlags </TD> <TD>  Event quality flags: The definition of the bits can be found in enums/enums/EventFlags.h </TD> </TR>
<TR> <TD> GoodEvent </TD> <TD>  Decoded from EventFlags: '1' means a good event </TD> </TR>
<TR> <TD> TemLength[tower]      </TD> <TD> Size of the TEM event contribution              </TD> </TR>
<TR> <TD> GemLength             </TD> <TD> Size of the GEM event contribution (fixed size) </TD> </TR>
<TR> <TD> OswLength             </TD> <TD> Size of the OSW event contribution              </TD> </TR>
<TR> <TD> AemLength             </TD> <TD> Size of the AEM event contribution              </TD> </TR>
<TR> <TD> ErrLength             </TD> <TD> Size of the Error event contribution            </TD> </TR>
<TR> <TD> DiagLength            </TD> <TD> Size of the Diagnostics event contribution. Should always be 48.</TD> </TR>
<TR> <TD> TemError[tower]       </TD> <TD> TEM error contribution. For a detailed explanation, see section 4.4. in the Online document http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf </TD> </TR>
<TR> <TD> GemConditionsWord     </TD> <TD> GEM Conditions Summary word. The definition of the bits can be found in enums/enums/GemConditionSummary.h. For a detailed explanation of GEM quantities, see http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/GEM.pdf, Chapter 4      </TD> </TR>
<TR> <TD> GemTkrVector[tower]   </TD> <TD> GEM TKR vector                      </TD> </TR>
<TR> <TD> GemRoiVector[tower]   </TD> <TD> GEM ROI vector                      </TD> </TR>
<TR> <TD> GemCalLeVector[tower] </TD> <TD> GEM CAL LE vector                   </TD> </TR>
<TR> <TD> GemCalHeVector[tower] </TD> <TD> GEM CAL HE vector                   </TD> </TR>
<TR> <TD> GemCnoVector[12]      </TD> <TD> GEM CNO vector                      </TD> </TR>
<TR> <TD> GemLiveTime           </TD> <TD> GEM Live time                       </TD> </TR>
<TR> <TD> GemTriggerTime        </TD> <TD> GEM Trigger time                    </TD> </TR>
<TR> <TD> GemDeltaEventTime     </TD> <TD> GEM Delta event time                </TD> </TR>
<TR> <TD> GemOnePpsSeconds      </TD> <TD> GEM PPS Seconds                     </TD> </TR>
<TR> <TD> GemOnePpsTime         </TD> <TD> GEM PPS Time                        </TD> </TR>
<TR> <TD> GemPrescaled          </TD> <TD> GEM Prescaled counter               </TD> </TR>
<TR> <TD> GemDiscarded          </TD> <TD> GEM Discarded counter               </TD> </TR>
<TR> <TD> GemSent               </TD> <TD> GEM Sent counter. NB! Removed for now! (from EM v3r0407p13) </TD> </TR>

<TR> <TD> GemCondArrivalTimeWord  </TD> <TD> GEM Condition arrival times, complete word, p128 in the GEM document </TD> </TR>
<TR> <TD> GemCondArrivalTimeExt   </TD> <TD> GEM Condition arrival times, external trigger                    </TD> </TR>
<TR> <TD> GemCondArrivalTimeCno   </TD> <TD> GEM Condition arrival times, CNO                                 </TD> </TR>
<TR> <TD> GemCondArrivalTimeCalLe </TD> <TD> GEM Condition arrival times, Cal LE                              </TD> </TR>
<TR> <TD> GemCondArrivalTimeCalHe </TD> <TD> GEM Condition arrival times, Cal HE                              </TD> </TR>
<TR> <TD> GemCondArrivalTimeTkr   </TD> <TD> GEM Condition arrival times, TKR                                 </TD> </TR>
<TR> <TD> GemCondArrivalTimeRoi   </TD> <TD> GEM Condition arrival times, ROI                                 </TD> </TR>
<TR> <TD> GemDeltaWindowOpenTime  </TD> <TD> GEM Delta window open time, p130 in the GEM document                 </TD> </TR>

<TR> <TD> GemAcdTilesXzp        </TD> <TD> GEM ACD XZP tile list               </TD> </TR>
<TR> <TD> GemAcdTilesYzp        </TD> <TD> GEM ACD XZM tile list               </TD> </TR>
<TR> <TD> GemAcdTilesYzm        </TD> <TD> GEM ACD YZP tile list               </TD> </TR>
<TR> <TD> GemAcdTilesXy         </TD> <TD> GEM ACD YZM tile list               </TD> </TR>
<TR> <TD> GemAcdTilesRbn        </TD> <TD> GEM ACD RNB (Ribbons) tile list     </TD> </TR>
<TR> <TD> GemAcdTilesNa         </TD> <TD> GEM ACD NA (Not Assigned) tile list </TD> </TR>
</TABLE>



<TABLE>
<CAPTION ALIGN="TOP"> MC variables </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> McSeqNo </TD> <TD> Sequence number </TD> </TR>
<TR> <TD> McId </TD> <TD> PDG id for primary MC particle. For example: e-(11), e+(-11), gamma(22), mu-(13), mu+(-13) </TD> </TR>
<TR> <TD> McTotalEnergy </TD> <TD> Total energy of the particle including its mass </TD> </TR>
<TR> <TD> McX0 </TD> <TD> x coordinate of origin of the particle </TD> </TR>
<TR> <TD> McY0 </TD> <TD> y coordinate of origin of the particle </TD> </TR>
<TR> <TD> McZ0 </TD> <TD> z coordinate of origin of the particle </TD> </TR>
<TR> <TD> McXDir </TD> <TD> True x direction of the primary particle </TD> </TR>
<TR> <TD> McYDir </TD> <TD> True y direction of the primary particle </TD> </TR>
<TR> <TD> McZDir </TD> <TD> True z direction of the primary particle </TD> </TR>
<TR> <TD> McConvPointX </TD> <TD> x coordinate of photon conversion point </TD> </TR>
<TR> <TD> McConvPointY </TD> <TD> y coordinate of photon conversion point </TD> </TR>
<TR> <TD> McConvPointZ </TD> <TD> z coordinate of photon conversion point </TD> </TR>
<TR> <TD> McCalEneSum </TD> <TD> MC sum of energies deposited in each crystal </TD> </TR>
<TR> <TD> McTkr1Ene </TD> <TD> MC energy of first track if there is a pair production </TD> </TR>
<TR> <TD> McTkr2Ene </TD> <TD> MC energy of second track if there is a pair production </TD> </TR>
<TR> <TD> McConvAngle </TD> <TD> Opening angle of e+/e- pair if there is a pair production </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> Vertex variables </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> VtxX0 </TD> <TD> x coordinate of first (best) vertex </TD> </TR>
<TR> <TD> VtxY0 </TD> <TD> y coordinate of first (best) vertex </TD> </TR>
<TR> <TD> VtxZ0 </TD> <TD> z coordinate of first (best) vertex </TD> </TR>
<TR> <TD> VtxXDir </TD> <TD> x direction in first vertex. If there are two tracks associated with the vertex, then it is averged over the direction of the two tracks; Otherwise, it is just the direction of the track. </TD> </TR>
<TR> <TD> VtxYDir </TD> <TD> y direction in first vertex. If there are two tracks associated with the vertex, then it is averged over the direction of the two tracks; Otherwise, it is just the direction of the track. </TD> </TR>
<TR> <TD> VtxZDir </TD> <TD> z direction in first vertex. If there are two tracks associated with the vertex, then it is averged over the direction of the two tracks; Otherwise, it is just the direction of the track. </TD> </TR>
<TR> <TD> Vtx1NumTkrs </TD> <TD> Number of tracks associated with the first vertex </TD> </TR>
<TR> <TD> Vtx1Energy </TD> <TD> Energy stored in first vertex  </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> TKR variables </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> TkrNumDigis </TD> <TD> Number of TKR digis. Normally a digi is produced whenever there is a strip hit in a silicon plane. </TD> </TR>
<TR> <TD> TkrNumStrips[tower][layer][view] </TD> <TD> A 3 dimensional array which describes the number of strips in every tower, layer and view. View=0 refers to measure X while View=1 refers to measure Y </TD> </TR>
<TR> <TD> tot[tower][layer][view][end] </TD> <TD> A 4 dimensional array which describes tot value at every tower, layer, view and end. End=0 refers to low end with stripId from 0 to 768 while end=1 refers to high end with stripId from 768 to 1536. Normally division is at middle of the plane, however this could be changed during real data taking. </TD> </TR>
<TR> <TD> totCorrL[tower][layer][view][end] </TD> <TD> A 4 dimension array which describes corrected tot value at every tower, layer, view and end, using Hiro's linear correction formula. At the moment only valid for EM1 data. </TD> </TR>
<TR> <TD> totCorrQ[tower][layer][view][end] </TD> <TD> A 4 dimension array which describes corrected tot value at every tower, layer, view and end, using Hiro's quadratic correction formula. At the moment only valid for EM1 data. </TD> </TR>
<TR> <TD> TkrNumClusters[tower][layer][view] </TD> <TD> A 3 dimension array which describes number of clusters at every tower, layer and view. View=0 refers to measure X while View=1 refers to measure Y. </TD> </TR>
<TR> <TD> TkrNumTracks </TD> <TD> Number of reconstructed tracks</TD> </TR>
<TR> <TD> TkrNumVertices </TD> <TD> Number of reconstructed vertices</TD> </TR>
<TR> <TD> Tkr1NumHits </TD> <TD> Number of clusters in first track </TD> </TR>
<TR> <TD> Tkr2NumHits </TD> <TD> Number of clusters in second track </TD> </TR>
<TR> <TD> Tkr1Chisq </TD> <TD> Chi square of first track </TD> </TR>
<TR> <TD> Tkr2Chisq </TD> <TD> Chi square of second track </TD> </TR>
<TR> <TD> Tkr1ChisqS </TD> <TD> Smoothed chi square of first track </TD> </TR>
<TR> <TD> Tkr2ChisqS </TD> <TD> Smoothed chi square of second track </TD> </TR>
<TR> <TD> Tkr1Rms </TD> <TD> Rms value of first track </TD> </TR>
<TR> <TD> Tkr2Rms </TD> <TD> Rms value of second track </TD> </TR>
<TR> <TD> Tkr1KalThetaMs </TD> <TD> Multiple scattering angle of first track calculated by Kalman filter</TD> </TR>
<TR> <TD> Tkr2KalThetaMs </TD> <TD> Multiple scattering angle of second track calculated by Kalman filter</TD> </TR>
<TR> <TD> Tkr1KalEne </TD> <TD> Energy of first track calculated by Kalman filter</TD> </TR>
<TR> <TD> Tkr2KalEne </TD> <TD> Energy of second track calculated by Kalman filter</TD> </TR>
<TR> <TD> Tkr1EndPos[3] </TD> <TD> End-of-track position of track 1  </TD> </TR>
<TR> <TD> Tkr2EndPos[3] </TD> <TD> End-of-track position of track 2  </TD> </TR>
<TR> <TD> Tkr1EndDir[3] </TD> <TD> End-of-track direction of track 1 </TD> </TR>
<TR> <TD> Tkr2EndDir[3] </TD> <TD> End-of-track direction of track 2 </TD> </TR>
<TR> <TD> TkrTopTot[tower] </TD> <TD>A one dimension array which describes tot value at the top hit layer for each tower. The value is actually the maximum of 4 tot values at the biPlane.</TD> </TR> 
<TR> <TD> Tkr1ConvTot[tower] </TD> <TD>A one dimension array which describes tot value at the layer of the first vertex. The value is actually the maximum of 4 tot values at the biPlane.</TD> </TR>
<TR> <TD> TkrTp[tower][tp] </TD> <TD>A two dimension array which describes tracker trigger primitive for each tower. For detailed description, please see onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3</TD> </TR>
<TR> <TD> TkrReq[tower][layer][view][end] </TD> <TD>A 4 dimension array which describes tracker trigger request. For example: TkrReq[8][7][0][0]=1 means trigger request was sent from tower 8, layer 7, measure X and lower end of the tray.  End=0 refers to low end with stripId from 0 to 768 while end=1 refers to high end with stripId from 768 to 1536. Normally division is at middle of the plane, however this could be changed during real data taking.</TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> CAL variables </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> CalEneSum </TD> <TD> Sum of energies in each crystal </TD> </TR>
<TR> <TD> CalXEcentr </TD> <TD> x coordinate of centroid of CAL cluster </TD> </TR>
<TR> <TD> CalYEcentr </TD> <TD> y coordinate of centroid of CAL cluster </TD> </TR>
<TR> <TD> CalZEcentr </TD> <TD> z coordinate of centroid of CAL cluster </TD> </TR>
<TR> <TD> CalXtalEne[tower][layer][col][end] </TD> <TD> Measured energy in a single crystal at each tower, layer, column and end</TD> </TR>
<TR> <TD> CalMaxEne </TD> <TD> Maximal measured energy in a single crystal </TD> </TR>
<TR> <TD> CalNumHit[tower] </TD> <TD> A one dimension array which describes number of crystals in each tower with measured energy larger than zero suppression threshold </TD> </TR>
<TR> <TD> CalTp[tower][tp] </TD> <TD>A two dimension array which describes calorimeter trigger primitive for each tower.  For detailed description, please see onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3</TD> </TR>
<TR> <TD> CalReq[tower][layer][end] </TD> <TD>A 3 dimension array which describes calorimeter trigger request. For example: CalReq[8][7][0]=1 means trigger request was sent to low energy trigger from tower 8, layer 7 and end 0; =2 means the trigger request was sent to high energy trigger; =3 means the trigger request was sent to both trigger.  </TD> </TR>
<TR> <TD> CalReq[tower][layer][end] </TD> <TD>A 3 dimension array which describes calorimeter trigger request. For example: CalReq[8][7][0]=1 means trigger request was sent to low energy trigger from tower 8, layer 7 and end 0; =2 means the trigger request was sent to high energy trigger; =3 means the trigger request was sent to both trigger.  </TD> </TR>
<TR> <TD> CalLogAccepts[tower][layer][end]</TD> <TD>A 3 dimension array which describe log accepts contained in the CAL trigger diagnostic info.  For detailed description, please see onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3  </TD> </TR>
</TABLE>

@section jobOpt Example of the option file

@verbinclude AnalyzerOption.dat

*/
