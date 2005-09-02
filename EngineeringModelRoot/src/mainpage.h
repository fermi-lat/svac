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

Detailed explanations of some of these variables can be found in the following documents:

LAT-TD-00606: LAT Inter-module Communications - A Reference Manual, http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf
<br>
LAT-TD-00605: The Tower Electronics Module (TEM) - Programming ICD specification, http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf
<br>
LAT-TD-01545: The GLT Electronics Module (GEM) - Programming ICD specification, http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/GEM.pdf
<br>

<TABLE>
<CAPTION ALIGN="TOP"> Run and Event variables </CAPTION>

<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>

<TR> <TD> RunID </TD> <TD> Run number taken from DigiEvent.h. </TD> </TR> 

<TR> <TD> EventID </TD> <TD> Event number taken from DigiEvent.h. The event number comes from a 32 bit online counter. It is not always continous 
          (because of prescaling for example). For runs taken before the middle of April 2005 it came from a 17 bits online counter and wrapped around at 128k events 
          i.e. you could have multiple events with the same event sequence number. </TD> </TR>

<TR> <TD> EventSize </TD> <TD> Event size in bytes taken from the Fits file. It seems to be an 8 bytes offset with respect to the LDF event size (the FITS event size  
          being larger). </TD> </TR>

<TR> <TD> GltWord </TD> <TD> Trigger word made from digis: The definition of the bits can be found in enums/enums/TriggerBits.h and follows the definition of the 
          bits from the GltConditionsWord. The GltWord is the only trigger word available in the simulation as there is no GEM simulation.</TD> </TR>

<TR> <TD> EvtTime </TD> <TD> Time in seconds since mission start, currently 1/1/2001. This is the time that is reported when doing simulations. NB! For real data, 
          this time is from the event builder and is not the trigger time.</TD> </TR>

<TR> <TD> EvtSecond </TD> <TD> The number of seconds, since 1/1/1970, used in conjunction with getEbfTimeNanoSec for a measure of absolute time. NB! For real data, 
          this time is from the event builder and is not the trigger time.</TD> </TR>

<TR> <TD> EvtNanoSecond </TD> <TD> The number of nano-seconds, since 1/1/1970, used in conjunction with getEbfTimeSec for a measure of absolute time. NB! For real data, 
          this time is from the event builder and is not the time when the event triggered.</TD> </TR>

<TR> <TD> EvtUpperTime </TD> <TD> The UpperPpcTimeBase word as stored in the LDF from real data. Used in conjunction with EvtLowerTime (getEbfLowerPpcTimeBase), 
          these words can be used to determine the spacing of real test events. NB! This time is from the event builder and is not the time when 
          the event triggered.</TD> </TR>

<TR> <TD> EvtLowerTime </TD> <TD> The LowerPpcTimeBase word stored in the LDF from real data. Used in conjunction with getEbfUpperPpcTimeBase, these words can be 
          used to determine the spacing of real data events. NB! This time is from the event builder and is not the time when the event triggered.</TD> </TR>

<TR> <TD> EvtTimeSeconds </TD> <TD> Uses the data words stored in the UpperPpcTimeBase and LowerPpcTimeBase to calculate seconds since power on. This time is used to 
          determine the spacing of real data events - NOT as an absolute time. NB! This time is from the event builder and is not the time when the event triggered. 
          </TD> </TR>

<TR> <TD> EvtTicks </TD> <TD> Uses the data words stored in the GemTriggerTime, GemOnePpsSeconds, GemOnePpsTime, EvtSecond,
and EvtNanoSecond to calculate LAT ticks for each event. This time is used to determine the spacing of real data events 
- NOT as an absolute time.  The "zero point" is arbitrary.
NB! This is the time when the event triggered.
The values are integers, but are stored as doubles to portably get more than 32 bits.
          </TD> </TR>

<TR> <TD> EvtSummary </TD> <TD> Summary word for each event. For a detailed explaination, see the Online document  
          http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf, Chapter 3.5</TD> </TR>

<TR> <TD> EventFlags </TD> <TD>  Event quality flags: A bit is set if there is an error in TKR Recon, a Packet error, a Summary error or a Trigger parity error.  
          The definition of the bits can be found in enums/enums/EventFlags.h </TD> </TR>

<TR> <TD> TemLength[tower] </TD> <TD> Size in bytes of the TEM event contribution, per tower. Variable length. </TD> </TR>
<TR> <TD> GemLength        </TD> <TD> Size in bytes of the GEM event contribution. Fixed size: 64 bytes        </TD> </TR>
<TR> <TD> OswLength        </TD> <TD> Size in bytes of the OSW event contribution. Fixed size: 32 bytes        </TD> </TR>
<TR> <TD> AemLength        </TD> <TD> Size in bytes of the AEM event contribution.                             </TD> </TR>
<TR> <TD> ErrLength        </TD> <TD> Size in bytes of the Error event contribution. Variable lenght.          </TD> </TR>
<TR> <TD> DiagLength       </TD> <TD> Size in bytes of the Diagnostics event contribution. Fixed size: 48 bytes (if the TEM diagnostics are enabled)</TD> </TR>

<TR> <TD> GemConditionsWord  </TD> <TD> GEM Conditions Summary word. The definition of the bits can be found in enums/enums/GemConditionSummary.h. 
          For a detailed explanation, see http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/GEM.pdf, Chapter 4 </TD> </TR>

<TR> <TD> GemTkrVector[16]   </TD> <TD> GEM TKR vector: 16 bits, one bit per tower. The bit is set if the TKR trigger was asserted at least once in the trigger window. 
          </TD> </TR>
<TR> <TD> GemRoiVector[16]   </TD> <TD> GEM ROI vector: 16 bits - the meaning depends on whether the ROI was used as a trigger or a veto. The bit is set if a ROI was 
          asserted at least once in the trigger window. </TD> </TR> 
<TR> <TD> GemCalLeVector[16] </TD> <TD> GEM CAL LE vector: 16 bits, one bit per tower. The bit is set if the CAL LE trigger was asserted at least once in the trigger 
          window. </TD> </TR>
<TR> <TD> GemCalHeVector[16] </TD> <TD> GEM CAL HE vector: 16 bits, one bit per tower. The bit is set if the CAL HE trigger was asserted at least once in the trigger 
          window. </TD> </TR>
<TR> <TD> GemCnoVector[12]      </TD> <TD> GEM CNO vector: 12 bits. The bit is set if the CNO trigger was asserted at least once in the trigger window. </TD> </TR>

<TR> <TD> GemLiveTime           </TD> <TD> GEM Live time counter in ticks of 50 ns. Wraps around. </TD> </TR>
<TR> <TD> GemTriggerTime        </TD> <TD> GEM Trigger time counter in ticks of 50 ns. Wraps around. </TD> </TR>
<TR> <TD> GemDeltaEventTime     </TD> <TD> GEM Delta event time counter in ticks of 50 ns. Saturates at 3.3 ms </TD> </TR>
<TR> <TD> GemOnePpsSeconds      </TD> <TD> GEM PPS Seconds: Number of seconds since the GEM was reset. Wraps around. </TD> </TR>
<TR> <TD> GemOnePpsTime         </TD> <TD> GEM PPS Time in units of 50 ns. Wraps around. </TD> </TR>
<TR> <TD> GemPrescaled          </TD> <TD> GEM Prescaled counter: Increments when an event is lost due to prescaling Wraps around. </TD> </TR>
<TR> <TD> GemDiscarded          </TD> <TD> GEM Discarded counter. Increments when an event is lost due to LAT busy. Wraps around. </TD> </TR>

<TR> <TD> GemCondArrivalTimeWord  </TD> <TD> GEM Condition arrival times: The complete word, see section 4.13 in the GEM document for a detailed description.</TD> </TR>

<TR> <TD> GemCondArrivalTimeTkr   </TD> <TD> GEM Condition arrival times in 50 ns ticks for the TKR trigger: Tells us when the TKR trigger arrived with respect to the 
          trigger window opening. A value of 0 means the TKR trigger opened the trigger window. The arrival time can be between 0 and 30, but you need to take the actual 
          width of the trigger window into account (usually 5 or 12 ticks). A value of 31 means that either the TKR trigger did not participate in the trigger (i.e. 
          the event was triggered by something else), or that the TKR trigger line was already high when the trigger window opened. This can happen if the TKR triggered 
          the previous event and that event was discarded. </TD> </TR>

<TR> <TD> GemCondArrivalTimeExt   </TD> <TD> GEM Condition arrival times in 50 ns ticks for the external trigger  </TD> </TR>
<TR> <TD> GemCondArrivalTimeCno   </TD> <TD> GEM Condition arrival times in 50 ns ticks for the CNO trigger       </TD> </TR>
<TR> <TD> GemCondArrivalTimeCalLe </TD> <TD> GEM Condition arrival times in 50 ns ticks for the CAL LE trigger    </TD> </TR>
<TR> <TD> GemCondArrivalTimeCalHe </TD> <TD> GEM Condition arrival times in 50 ns for the CAL HE trigger          </TD> </TR>
<TR> <TD> GemCondArrivalTimeRoi   </TD> <TD> GEM Condition arrival times in 50 ns ticks for the ROI               </TD> </TR>

<TR> <TD> GemDeltaWindowOpenTime  </TD> <TD> GEM Delta window open time counter: Number of 50 ns ticks between the opening of the trigger window between the previous event 
          and this event. Wraps around. </TD> </TR>

<TR> <TD> GemDeadZone </TD> <TD> GEM Dead zone counter: It takes a minimum of 2 clock ticks for the GEM to recover from forming one trigger window and opening the 
          next one. If a trigger window opening was requested in this 'dead zone' this counter increments. </TD> </TR>      

<TR> <TD> GemAcdTilesXzp        </TD> <TD> GEM ACD XZP tile list: See section 4.9 in the GEM document for details. </TD> </TR>
<TR> <TD> GemAcdTilesYzp        </TD> <TD> GEM ACD XZM tile list: See section 4.9 in the GEM document for details. </TD> </TR>
<TR> <TD> GemAcdTilesYzm        </TD> <TD> GEM ACD YZP tile list: See section 4.9 in the GEM document for details. </TD> </TR>
<TR> <TD> GemAcdTilesXy         </TD> <TD> GEM ACD YZM tile list: See section 4.9 in the GEM document for details. </TD> </TR>
<TR> <TD> GemAcdTilesRbn        </TD> <TD> GEM ACD RNB (Ribbons) tile list: See section 4.9 in the GEM document for details.      </TD> </TR>
<TR> <TD> GemAcdTilesNa         </TD> <TD> GEM ACD NA (Not Assigned) tile list:  See section 4.9 in the GEM document for details. </TD> </TR>

<TR> <TD> DigiTriRowBits[tower]        </TD> <TD> 3-in-a-row trigger bits made from TKR digis </TD> </TR>
<TR> <TD> TrgReqTriRowBits[tower]      </TD> <TD> 3-in-a-row trigger bits made from the real trigger requests (trigger primitives) </TD> </TR>  
</TABLE>



<TABLE>
<CAPTION ALIGN="TOP"> MC variables </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> McSeqNo </TD> <TD> Sequence number </TD> </TR>
<TR> <TD> McId </TD> <TD> PDG id for primary MC particle. For example: e-(11), e+(-11), gamma(22), mu-(13), mu+(-13) </TD> </TR>
<TR> <TD> McTotalEnergy </TD> <TD> Total energy (in MeV) of the particle including its mass </TD> </TR>
<TR> <TD> McX0 </TD> <TD> x coordinate (in mm) of origin of the particle </TD> </TR>
<TR> <TD> McY0 </TD> <TD> y coordinate (in mm) of origin of the particle </TD> </TR>
<TR> <TD> McZ0 </TD> <TD> z coordinate (in mm) of origin of the particle </TD> </TR>
<TR> <TD> McXDir </TD> <TD> True x direction (in radian) of the primary particle </TD> </TR>
<TR> <TD> McYDir </TD> <TD> True y direction (in radian) of the primary particle </TD> </TR>
<TR> <TD> McZDir </TD> <TD> True z direction (in radian) of the primary particle </TD> </TR>
<TR> <TD> McConvPointX </TD> <TD> x coordinate (in mm) of photon conversion point </TD> </TR>
<TR> <TD> McConvPointY </TD> <TD> y coordinate (in mm) of photon conversion point </TD> </TR>
<TR> <TD> McConvPointZ </TD> <TD> z coordinate (in mm) of photon conversion point </TD> </TR>
<TR> <TD> McCalEneSum </TD> <TD> MC sum of energies (in MeV) deposited in each crystal </TD> </TR>
<TR> <TD> McTkr1Ene </TD> <TD> MC energy of first track (in MeV) if there is a pair production </TD> </TR>
<TR> <TD> McTkr2Ene </TD> <TD> MC energy of second track (in MeV) if there is a pair production </TD> </TR>
<TR> <TD> McConvAngle </TD> <TD> Opening angle (in radian) of e+/e- pair if there is a pair production </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> Vertex variables </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> VtxX0 </TD> <TD> x coordinate (in mm) of first (best) vertex </TD> </TR>
<TR> <TD> VtxY0 </TD> <TD> y coordinate (in mm) of first (best) vertex </TD> </TR>
<TR> <TD> VtxZ0 </TD> <TD> z coordinate (in mm) of first (best) vertex </TD> </TR>
<TR> <TD> VtxXDir </TD> <TD> x direction (in radian) in first vertex. If there are two tracks associated with the vertex, then it is averged over the direction of the two tracks; Otherwise, it is just the direction of the track. </TD> </TR>
<TR> <TD> VtxYDir </TD> <TD> y direction (in radian) in first vertex. If there are two tracks associated with the vertex, then it is averged over the direction of the two tracks; Otherwise, it is just the direction of the track. </TD> </TR>
<TR> <TD> VtxZDir </TD> <TD> z direction (in radian) in first vertex. If there are two tracks associated with the vertex, then it is averged over the direction of the two tracks; Otherwise, it is just the direction of the track. </TD> </TR>
<TR> <TD> Vtx1NumTkrs </TD> <TD> Number of tracks associated with the first vertex </TD> </TR>
<TR> <TD> Vtx1Energy </TD> <TD> Energy (in MeV) stored in first vertex  </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> TKR variables </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> TkrNumDigis </TD> <TD> Number of TKR digis. A digi is produced whenever there is at least one strip hit in a silicon plane. </TD> </TR>
<TR> <TD> TkrNumStrips[tower][layer][view] </TD> <TD> A 3 dimensional array which describes the number of strips in every tower, layer and view. View=0 refers to measure X while View=1 refers to measure Y </TD> </TR>
<TR> <TD> tot[tower][layer][view][end] </TD> <TD> A 4 dimensional array which describes tot value at every tower, layer, view and end. End=0 refers to low end with stripId from 0 to 768 while end=1 refers to high end with stripId from 768 to 1536. Normally division is at middle of the plane, however this could be changed during real data taking. Please check configuration report to find out whether the devision is really in the middle</TD> </TR>
<TR> <TD> totCorrL[tower][layer][view][end] </TD> <TD> A 4 dimension array which describes corrected tot value at every tower, layer, view and end, using Hiro's linear correction formula. At the moment only valid for EM1 data. </TD> </TR>
<TR> <TD> totCorrQ[tower][layer][view][end] </TD> <TD> A 4 dimension array which describes corrected tot value at every tower, layer, view and end, using Hiro's quadratic correction formula. At the moment only valid for EM1 data. </TD> </TR>
<TR> <TD> TkrNumClusters[tower][layer][view] </TD> <TD> A 3 dimension array which describes number of clusters at every tower, layer and view. View=0 refers to measure X while View=1 refers to measure Y. </TD> </TR>
<TR> <TD> TkrNumTracks </TD> <TD> Number of reconstructed tracks. Currently recon allows maximum of 10 tracks.</TD> </TR>
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
<TR> <TD> Tkr1EndPos[3] </TD> <TD> End-of-track position (in mm) of track 1  </TD> </TR>
<TR> <TD> Tkr2EndPos[3] </TD> <TD> End-of-track position (in mm) of track 2  </TD> </TR>
<TR> <TD> Tkr1EndDir[3] </TD> <TD> End-of-track direction (in mm) of track 1 </TD> </TR>
<TR> <TD> Tkr2EndDir[3] </TD> <TD> End-of-track direction (in mm) of track 2 </TD> </TR>
<TR> <TD> TkrTopTot[tower] </TD> <TD>A one dimension array which describes tot value at the top hit layer for each tower. The value is actually the maximum of 4 tot values at the biPlane.</TD> </TR> 
<TR> <TD> Tkr1ConvTot[tower] </TD> <TD>A one dimension array which describes tot value at the layer of the first vertex. The value is actually the maximum of 4 tot values at the biPlane.</TD> </TR>
<TR> <TD> TkrTp[tower][tp] </TD> <TD>A two dimension array which describes tracker trigger primitive for each tower. For detailed description, please see onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3</TD> </TR>
<TR> <TD> TkrReq[tower][layer][view][end] </TD> <TD>A 4 dimension array which describes tracker trigger request. For example: TkrReq[8][7][0][0]=1 means trigger request was sent from tower 8, layer 7, measure X and lower end of the tray.  End=0 refers to low end with stripId from 0 to 768 while end=1 refers to high end with stripId from 768 to 1536. Normally division is at middle of the plane, however this could be changed during real data taking.</TD> </TR>
<TR> <TD> TkrTotalHits[tower] </TD> <TD>Total number of strip hits in each tower.</TD> </TR>
<TR> <TD> TkrTotalClusters[tower] </TD> <TD>Total number of clusters in each tower.</TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> CAL variables </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> CalEneSum </TD> <TD> Sum of energies (in MeV) in each crystal </TD> </TR>
<TR> <TD> CalXEcentr </TD> <TD> x coordinate (in mm) of centroid of CAL cluster </TD> </TR>
<TR> <TD> CalYEcentr </TD> <TD> y coordinate (in mm) of centroid of CAL cluster </TD> </TR>
<TR> <TD> CalZEcentr </TD> <TD> z coordinate (in mm) of centroid of CAL cluster </TD> </TR>
<TR> <TD> CalXtalEne[tower][layer][col][end] </TD> <TD> Measured energy (in MeV) in a single crystal at each tower, layer, column (and end). Currently both ends contain the best total energy 
          estimate i.e. use either [end=0] or [end=1], but not both. To get the end energies you need to look at the CAL ntuple.</TD> </TR>
<TR> <TD> CalMaxEne </TD> <TD> Maximal measured energy (in MeV) in a single crystal </TD> </TR>
<TR> <TD> CalNumHit[tower] </TD> <TD> A one dimension array which describes number of crystals in each tower with measured energy larger than zero suppression threshold </TD> </TR>
<TR> <TD> CalTp[tower][tp] </TD> <TD>A two dimension array which describes calorimeter trigger primitive for each tower.  For detailed description, please see onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3. (For experts only.)</TD> </TR>
<TR> <TD> CalReq[tower][layer][end] </TD> <TD>A 3 dimension array which describes calorimeter trigger request. For example: CalReq[8][7][0]=1 means trigger request was sent to low energy trigger from tower 8, layer 7 and end 0; =2 means the trigger request was sent to high energy trigger; =3 means the trigger request was sent to both trigger.  </TD> </TR>
<TR> <TD> CalReq[tower][layer][end] </TD> <TD>A 3 dimension array which describes calorimeter trigger request. For example: CalReq[8][7][0]=1 means trigger request was sent to low energy trigger from tower 8, layer 7 and end 0; =2 means the trigger request was sent to high energy trigger; =3 means the trigger request was sent to both trigger.  </TD> </TR>
<TR> <TD> CalLogAccepts[tower][layer][end]</TD> <TD>A 3 dimension array which describe log accepts contained in the CAL trigger diagnostic info.  For detailed description, please see onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3  </TD> </TR>
<TR> <TD> CalXtalPos[tower][layer][col][coord] </TD> <TD>A three dimension array which describes fit position in each CAL crystal, coord=0 means fitted X coordinate, coord=1 means fitted Y coordinate and coord=2 means fitted Z coodinate.(For experts only.)</TD> </TR>
</TABLE>


<TABLE>
<CAPTION ALIGN="TOP"> ACD variables </CAPTION>
<TR> <TH> Variable name </TH> <TH>Meaning  </TH> </TR>
<TR> <TD> AcdNumDigis               </TD> <TD> Number of ACD digis </TD> </TR>
<TR> <TD> AcdPha[tileID][2]         </TD> <TD> Pulse Hight Analysis for the specified tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdHitMap[tileID][2]      </TD> <TD> Veto discriminator set or not for the specified tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdRange[tileID][2]       </TD> <TD> Range for the specified tile/ribbon and PMT (A or B).</TD> </TR>
<TR> <TD> AcdParityError[tileID][2] </TD> <TD> Parity error bit for the specified tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdLowDisc[tileID][2]     </TD> <TD> Low discriminator set or not for the specified tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdHighDisc[tileID][2]    </TD> <TD> High (CNO) discriminator set or not for the specified tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdTileNumber[tileID]     </TD> <TD> Tile number in dense notation. </TD> </TR> 
<TR> <TD> AcdMCEnergy[tileID]       </TD> <TD> The amount of Monte Carlo energy (MeV) deposited in this detector. Only useful for simulated data. </TD> </TR>
<TR> <TD> AcdEnergy                 </TD> <TD> Total energy deposited in the ACD system. </TD> </TR> 
<TR> <TD> AcdTileCount              </TD> <TD> Total number of ACD tiles above veto threshold.  </TD> </TR> 
<TR> <TD> AcdDoca                   </TD> <TD> The minimal Distance of Closest Approach (DOCA) wrt the center of the tile. </TD> </TR>
<TR> <TD> AcdMinDocaId              </TD> <TD> The ID of the Acd Tile associated with the minimum DOCA. </TD> </TR> 
<TR> <TD> AcdGammaDoca              </TD> <TD> The minimal Distance of Closest Approach (DOCA) of the photon wrt the center of the tile. </TD> </TR>
<TR> <TD> AcdActiveDist             </TD> <TD> Minimum Active Distance for all tracks and ACD tiles above veto threshol. </TD> </TR>
<TR> <TD> Acd10Ids[10]              </TD> <TD> The tile IDs for the first 10 tiles above veto threshol. </TD> </TR>
</TABLE>

@section jobOpt Example of the option file

@verbinclude AnalyzerOption.dat

*/
