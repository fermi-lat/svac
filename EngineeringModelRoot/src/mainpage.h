// (Special "header" just for doxygen)

/*! @mainpage  Package svac/EngineeringModelRoot

@author Xin Chen 

@section current Current maintainer: Anders W. Borgland

@section intro Introduction

This package contains code to generate the SVAC ntuple for I&T/SVAC in addition to some histograms useful for the TKR group. The package includes the following executables and scripts:

<ul>
<li> RunRootAnalyzer.exe: It reads data from the 3 root files: mc, digi and recon. It produces 2 root files: *_svac.root contains the SVAC ntuple for I&T/SVAC, 
     *_hist.root contains histograms for I&T/SVAC. The names of the root files are contained in an option file. The executable uses its first argument as the name of 
     the option file; when there is no argument, it uses ../src/AnalyzerOption.dat as the option file</li>
<li> mergeNtuple.exe: It merges a list of SVAC and Merit ntuple files. </li>
<li> mergeRoot.exe and mergeRoot_mc.exe: Merges digi.root/recon.root and mc.root files.
<li> ../pl/RunRootAnalyzer.pl: It is used to run RunRootAnalyzer.exe in batch. </li>
</ul>

@section def Definition of the SVAC ntuple

Detailed explanations of some of these variables can be found in the following documents:

LAT-TD-00606: LAT Inter-module Communications - A Reference Manual, http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf
<br>
LAT-TD-00605: The Tower Electronics Module (TEM) - Programming ICD specification, http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf
<br>
LAT-TD-01545: The GLT Electronics Module (GEM) - Programming ICD specification, http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/GEM.pdf
<br>
LAT-TD-05601: DataFlow Public Interface (DFI), http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/DFI.pdf
<br> 

<TABLE>
<CAPTION ALIGN="TOP"> Run and Event variables </CAPTION>

<TR> <TH> Variable name </TH> <TH> Type </TH> <TH>Meaning  </TH> </TR>

<TR> <TD> RunID </TD> <TD> UInt </TD>  <TD> Run number </TD> </TR> 

<TR> <TD> EventID </TD> <TD> UInt </TD>  <TD> Event number: For Flight Software Runs this is really UInt64_t, but is currently stored as an UInt. The full event ID is stored in ContextGemScalersSequence 
          variable. For LATTE the event number comes from a 
          32 bit online counter. The event numbers are always contigous, i.e. no gaps, except for runs taken with software prescaling. For runs taken before the middle of April 2005 
          it came from a 17 bits online counter and wrapped around at 128k events i.e. you could have multiple events with the same event sequence number. </TD> </TR>

<TR> <TD> EventSize </TD> <TD> Int </TD>  <TD> Event size in bytes taken from the Fits file. It seems to be an 8 bytes offset with respect to the LDF event size (the FITS event size  
          being larger). </TD> </TR>

<TR> <TD> GltWord </TD> <TD> Int </TD> <TD> Trigger word made from digis: The definition of the bits can be found in enums/enums/TriggerBits.h and follows the definition of the 
          bits from the GltConditionsWord. The GltWord is the only trigger word available in the simulation as there is no GEM simulation.</TD> </TR>

<TR> <TD> EvtTime </TD> <TD> Double </TD> <TD> Time in seconds since mission start, currently 1/1/2001. This is the time that is reported when doing simulations. NB! For real data taken with LATTE, 
          this time is from the event builder and is not the trigger time. For Flight Software runs this used to be the time of the creation of the datagram but it's now the real timestamp of the 
          event. </TD> </TR>

<TR> <TD> EvtTicks </TD> <TD> Double </TD> <TD> Uses the data words stored in the GemTriggerTime, GemOnePpsSeconds, GemOnePpsTime, EvtSecond, and EvtNanoSecond to calculate LAT ticks for each event. 
          This time is used to determine the spacing of real data events - NOT as an absolute time.  The "zero point" is arbitrary.
          NB! This is the time when the event triggered. The values are integers, but are stored as doubles to portably get more than 32 bits. Do not use with Flight Software Runs!
          </TD> </TR>

<TR> <TD> EvtMCLiveTime </TD> <TD> Double </TD> <TD> MC livetime. </TD> </TR>

<TR> <TD> EvtSummary </TD> <TD> Int </TD> <TD> Summary word for each event. For a detailed explaination, see the Online document  
          http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf Chapter 3.5</TD> </TR>

<TR> <TD> EventFlags </TD> <TD> Int </TD> <TD>  Event quality flags: A bit is set if there is an error in TKR Recon, a Packet error, a Summary error or a Trigger parity error.  
          The definition of the bits can be found in enums/enums/EventFlags.h </TD> </TR>

<TR> <TD> EventBadEventSequence </TD> <TD> Int </TD> <TD> Set if the event sequence is not monotonically increasing. </TD> </TR>
<TR> <TD> EventBadTkrRecon      </TD> <TD> Int </TD> <TD> Set if there are too many TKR hits in the event. If so, TKR recon will not run on the event. </TD> </TR>
<TR> <TD> EventPacketError      </TD> <TD> Int </TD> <TD> Set if there is a packet error in the event. </TD> </TR> 
<TR> <TD> EventTemError         </TD> <TD> Int </TD> <TD> Set if there is a TEM error in the event. </TD> </TR> 
<TR> <TD> EventTrgParityError   </TD> <TD> Int </TD> <TD> Set if there is a trigger parity error in the event. </TD> </TR> 
<TR> <TD> EventBadLdfStatus     </TD> <TD> Int </TD> <TD> Set if there is an LDF parser problem in the event. </TD> </TR>
<TR> <TD> EventGtrcPhase        </TD> <TD> Int </TD> <TD> Set if there is a GTRC phase error in the event. </TD> </TR> 
<TR> <TD> EventGtfePhase        </TD> <TD> Int </TD> <TD> Set if there is a GTFE phase error in the event. </TD> </TR> 
<TR> <TD> EventGtccFifo         </TD> <TD> Int </TD> <TD> Set if there is a GTCC FIFO (full) error in the event. </TD> </TR>
<TR> <TD> EventGtccHdrParity    </TD> <TD> Int </TD> <TD> Set if there is a GTCC Header parity error in the event. </TD> </TR> 
<TR> <TD> EventGtccWcParity     </TD> <TD> Int </TD> <TD> Set if there is a GTCC Word count parity error in the event. </TD> </TR>
<TR> <TD> EventGtrcSummary      </TD> <TD> Int </TD> <TD> Set if there is a GTRC summary error in the event. </TD> </TR>
<TR> <TD> EventGtccDataParity   </TD> <TD> Int </TD> <TD> Set if there is a GTCC Data parity error in the event. </TD> </TR>   
<TR> <TD> EventGtccTimeout      </TD> <TD> Int </TD> <TD> Set if there is a GTCC timeout error in the event. </TD> </TR> 
<TR> <TD> EventGtccError        </TD> <TD> Int </TD> <TD> Set if there is a GTCC error in the event. </TD> </TR>
<TR> <TD> EventGcccError        </TD> <TD> Int </TD> <TD> Set if there is a GCCC error in the event. </TD> </TR>
<TR> <TD> EventPhaseError       </TD> <TD> Int </TD> <TD> Set if there is an event phase error in the event. </TD> </TR>
<TR> <TD> EventTimeoutError     </TD> <TD> Int </TD> <TD> Set if there is an event timeout error in the event. </TD> </TR> 

<TR> <TD> EventReadout4      </TD> <TD> Int </TD> <TD> 4-range readout - see Chapter 3 in http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf </TD> </TR>    
<TR> <TD> EventZeroSuppress  </TD> <TD> Int </TD> <TD> Zero-suppressed readout - see Chapter 3 in http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf </TD> </TR>
<TR> <TD> EventMarker        </TD> <TD> Int </TD> <TD> Marker - see Chapter 3 in http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf </TD> </TR> 
<TR> <TD> EventCalStrobe     </TD> <TD> Int </TD> <TD> Calstrobe - see Chapter 3 in http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf </TD> </TR>
<TR> <TD> EventTag           </TD> <TD> Int </TD> <TD> Tag - see Chapter 3 in http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf </TD> </TR>
<TR> <TD> EventTACK          </TD> <TD> Int </TD> <TD> TACK - see Chapter 3 in http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/LATcom.pdf </TD> </TR>

<TR> <TD> CCSDSTime  </TD> <TD> Double </TD> <TD> CCSDS Time from packet secondary header. It's also known as the datagram creation time even though it's really the time when the datagram was flsuhed.
This means that this time will be later than the time of any event time. </TD> </TR>
<TR> <TD> CCSDSapID  </TD> <TD> Int    </TD> <TD> CCSDS AP ID </TD> </TR>
<TR> <TD> CCSDSscID  </TD> <TD> Int    </TD> <TD> CCSDS SC ID </TD> </TR>


<TR> <TD> TemLength[tower] </TD> <TD> Int </TD> <TD> Size in bytes of the TEM event contribution, per tower. Variable length. </TD> </TR>
<TR> <TD> GemLength        </TD> <TD> Int </TD> <TD> Size in bytes of the GEM event contribution. Fixed size: 64 bytes        </TD> </TR>
<TR> <TD> OswLength        </TD> <TD> Int </TD> <TD> Size in bytes of the OSW event contribution. Fixed size: 32 bytes        </TD> </TR>
<TR> <TD> AemLength        </TD> <TD> Int </TD> <TD> Size in bytes of the AEM event contribution.                             </TD> </TR>
<TR> <TD> ErrLength        </TD> <TD> Int </TD> <TD> Size in bytes of the Error event contribution. Variable lenght.          </TD> </TR>
<TR> <TD> DiagLength       </TD> <TD> Int </TD> <TD> Size in bytes of the Diagnostics event contribution. Fixed size: 48 bytes (if the TEM diagnostics are enabled)</TD> </TR>

<TR> <TD> GemConditionsWord  </TD> <TD> Int </TD> <TD> GEM Conditions Summary word. The definition of the bits can be found in enums/enums/GemConditionSummary.h. 
          For a detailed explanation, see http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/GEM.pdf Chapter 4 </TD> </TR>

<TR> <TD> TrgEngineGlt </TD> <TD> Int </TD> <TD> Trigger engine calculated based on the GltWord. </TD> </TR>
<TR> <TD> TrgEngineGem </TD> <TD> Int </TD> <TD> Trigger engine calculated based on the GemConditionsWord. </TD> </TR>

<TR> <TD> GemTkrVector[16]   </TD> <TD> Int </TD> <TD> GEM TKR vector: 16 bits, one bit per tower. The bit is set if the TKR trigger was asserted at least once in the trigger window. 
          </TD> </TR>
<TR> <TD> GemRoiVector[16]   </TD> <TD> Int </TD> <TD> GEM ROI vector: 16 bits - the meaning depends on whether the ROI was used as a trigger or a veto. The bit is set if a ROI was 
          asserted at least once in the trigger window. </TD> </TR> 
<TR> <TD> GemCalLeVector[16] </TD> <TD> Int </TD> <TD> GEM CAL LE vector: 16 bits, one bit per tower. The bit is set if the CAL LE trigger was asserted at least once in the trigger 
          window. </TD> </TR>
<TR> <TD> GemCalHeVector[16] </TD> <TD> Int </TD> <TD> GEM CAL HE vector: 16 bits, one bit per tower. The bit is set if the CAL HE trigger was asserted at least once in the trigger 
          window. </TD> </TR>
<TR> <TD> GemCnoVector[12]      </TD> <TD> Int </TD> <TD> GEM CNO vector: 12 bits. The bit is set if the CNO trigger was asserted at least once in the trigger window. </TD> </TR>

<TR> <TD> GemLiveTime           </TD> <TD> Int </TD> <TD> GEM Live time counter in ticks of 50 ns. Wraps around. </TD> </TR>
<TR> <TD> GemTriggerTime        </TD> <TD> Int </TD> <TD> GEM Trigger time counter in ticks of 50 ns. Wraps around. </TD> </TR>
<TR> <TD> GemDeltaEventTime     </TD> <TD> Int </TD> <TD> GEM Delta event time counter in ticks of 50 ns. Saturates at 3.3 ms </TD> </TR>
<TR> <TD> GemOnePpsSeconds      </TD> <TD> Int </TD> <TD> GEM PPS Seconds: Number of seconds since the GEM was reset. Wraps around. </TD> </TR>
<TR> <TD> GemOnePpsTime         </TD> <TD> Int </TD> <TD> GEM PPS Time in units of 50 ns. Wraps around. </TD> </TR>
<TR> <TD> GemPrescaled          </TD> <TD> Int </TD> <TD> GEM Prescaled counter: Increments when an event is lost due to prescaling Wraps around. </TD> </TR>
<TR> <TD> GemDiscarded          </TD> <TD> Int </TD> <TD> GEM Discarded counter. Increments when an event is lost due to LAT busy. Wraps around. </TD> </TR>

<TR> <TD> GemCondArrivalTimeWord  </TD> <TD> Int </TD> <TD> GEM Condition arrival times: The complete word, see section 4.13 in the GEM document for a detailed description.</TD> </TR>

<TR> <TD> GemCondArrivalTimeTkr   </TD> <TD> Int </TD> <TD> GEM Condition arrival times in 50 ns ticks for the TKR trigger: Tells us when the TKR trigger arrived with respect to the 
          trigger window opening. A value of 0 means the TKR trigger opened the trigger window. The arrival time can be between 0 and 30, but you need to take the actual 
          width of the trigger window into account (usually 5 or 12 ticks). A value of 31 means that either the TKR trigger did not participate in the trigger (i.e. 
          the event was triggered by something else), or that the TKR trigger line was already high when the trigger window opened. This can happen if the TKR triggered 
          the previous event and that event was discarded. </TD> </TR>

<TR> <TD> GemCondArrivalTimeExt   </TD> <TD> Int </TD> <TD> GEM Condition arrival times in 50 ns ticks for the external trigger  </TD> </TR>
<TR> <TD> GemCondArrivalTimeCno   </TD> <TD> Int </TD> <TD> GEM Condition arrival times in 50 ns ticks for the CNO trigger       </TD> </TR>
<TR> <TD> GemCondArrivalTimeCalLe </TD> <TD> Int </TD> <TD> GEM Condition arrival times in 50 ns ticks for the CAL LE trigger    </TD> </TR>
<TR> <TD> GemCondArrivalTimeCalHe </TD> <TD> Int </TD> <TD> GEM Condition arrival times in 50 ns for the CAL HE trigger          </TD> </TR>
<TR> <TD> GemCondArrivalTimeRoi   </TD> <TD> Int </TD> <TD> GEM Condition arrival times in 50 ns ticks for the ROI               </TD> </TR>

<TR> <TD> GemDeltaWindowOpenTime  </TD> <TD> Int </TD> <TD> GEM Delta window open time counter: Number of 50 ns ticks between the opening of the trigger window between the previous event 
          and this event. Wraps around. </TD> </TR>

<TR> <TD> GemDeadZone </TD> <TD> Int </TD> <TD> GEM Dead zone counter: It takes a minimum of 2 clock ticks for the GEM to recover from forming one trigger window and opening the 
          next one. If a trigger window opening was requested in this 'dead zone' this counter increments. </TD> </TR>      

<TR> <TD> GemAcdTilesXzp        </TD> <TD> Int </TD> <TD> GEM ACD XZP tile list: See section 4.9 in the GEM document for details. </TD> </TR>
<TR> <TD> GemAcdTilesYzp        </TD> <TD> Int </TD> <TD> GEM ACD XZM tile list: See section 4.9 in the GEM document for details. </TD> </TR>
<TR> <TD> GemAcdTilesYzm        </TD> <TD> Int </TD> <TD> GEM ACD YZP tile list: See section 4.9 in the GEM document for details. </TD> </TR>
<TR> <TD> GemAcdTilesXy         </TD> <TD> Int </TD> <TD> GEM ACD YZM tile list: See section 4.9 in the GEM document for details. </TD> </TR>
<TR> <TD> GemAcdTilesRbn        </TD> <TD> Int </TD> <TD> GEM ACD RNB (Ribbons) tile list: See section 4.9 in the GEM document for details.      </TD> </TR>
<TR> <TD> GemAcdTilesNa         </TD> <TD> Int </TD> <TD> GEM ACD NA (Not Assigned) tile list:  See section 4.9 in the GEM document for details. </TD> </TR>

<TR> <TD> DigiTriRowBits[tower]        </TD> <TD> Int </TD> <TD> 3-in-a-row trigger bits made from TKR digis </TD> </TR>
<TR> <TD> TrgReqTriRowBits[tower]      </TD> <TD> Int </TD> <TD> 3-in-a-row trigger bits made from the real trigger requests (trigger primitives) </TD> </TR>  
</TABLE>




<TABLE>
<CAPTION ALIGN="TOP"> Context information from Flight Software </CAPTION>
<TR> <TH> Variable name </TH> <TH> Type </TH> <TH>Meaning  </TH> </TR>

<TR> <TD> ContextRunInfoPlatform   </TD> <TD> Int  </TD> <TD> The platform type this run was taken on (No platform, LAT, Testbead or Host (software simulation)) - See enums/enums/Lsf.h </TD> </TR> 
<TR> <TD> ContextRunInfoDataOrigin </TD> <TD> Int  </TD> <TD> The type of data from this run (No origin, Orbit, MC, ground) - See enums/enums/Lsf.h  </TD> </TR>
<TR> <TD> ContextRunInfoID         </TD> <TD> UInt </TD> <TD> The ground based ID of this run. This is usually defined on the ground, but if the LAT DAQ reboots on-orbit, the Ground ID can be reset. </TD> </TR>
<TR> <TD> ContextRunInfoStartTime  </TD> <TD> UInt </TD> <TD> The start time of this run: This is the number of seconds since GLAST epoch start when the run started. </TD> </TR>

<TR> <TD> ContextDataGramInfoModeChanges </TD> <TD> UInt </TD> <TD> The number of times the mode changed since the start of the run.                </TD> </TR>
<TR> <TD> ContextDataGramInfoDatagrams   </TD> <TD> UInt </TD> <TD> The datagram sequence number within this run.                                   </TD> </TR>
<TR> <TD> ContextDataGramInfoOpenAction  </TD> <TD> Int  </TD> <TD> The action that caused the datagram to be opened (Start, Resume, Continue, Unspecified) - See enums/enums/Lsf.h</TD> </TR>
<TR> <TD> ContextDataGramInfoOpenReason  </TD> <TD> Int  </TD> <TD> The reason why the datagram was opened (Operator, ModeChange, TimedOut, CountedOut, Full, Unknown) - See enums/enums/Lsf.h </TD> </TR>
<TR> <TD> ContextDataGramInfoCrate       </TD> <TD> Int  </TD> <TD> Which cpu the event was handled by (No crate, Epu0, Epu1, Epu2, Siu0, Siu1, Aux, Mixed) - See enums/enums/Lsf.h  </TD> </TR>
<TR> <TD> ContextDataGramInfoMode        </TD> <TD> Int  </TD> <TD> The operating mode of the LAT when these data were accquired (Normal, TOO, GRB0, GRB1, GRB2, Solar, Calibration, Diagnostic) 
                                                                    - See enums/enums/Lsf.h </TD> </TR>
<TR> <TD> ContextDataGramInfoCloseAction </TD> <TD> Int  </TD> <TD> The action that caused the datagram to be closed (Stop, Abort, Pause, Continue, Unspecified) - See enums/enums/Lsf.h</TD> </TR>
<TR> <TD> ContextDataGramInfoCloseReason </TD> <TD> Int  </TD> <TD> The reason why the datagram was closed (Operator, ModeChange, TimedOut, CountedOut, Full, Unknown) - See enums/enums/Lsf.h</TD> </TR>

<TR> <TD> ContextGemScalersElapsed   </TD> <TD> ULong64 </TD> <TD> The number of system clock ticks (nominally 50ns) since the counters were reset i.e. use it to find the time between any two events, 
          not for an absolute time!. Not reset at begin run!                                                                                                                    </TD> </TR>
<TR> <TD> ContextGemScalersLivetime  </TD> <TD> ULong64 </TD> <TD> The number of system clock ticks (nominally 50ns) that the LAT was alive. Not reset at begin run!            </TD> </TR>
<TR> <TD> ContextGemScalersPrescaled </TD> <TD> ULong64 </TD> <TD> The total number of events prescaled away up to this point. Not reset at begin run!                          </TD> </TR>
<TR> <TD> ContextGemScalersDiscarded </TD> <TD> ULong64 </TD> <TD> The total number of event discarded due to deadtime. Not reset at begin run!                                 </TD> </TR>
<TR> <TD> ContextGemScalersSequence  </TD> <TD> ULong64 </TD> <TD> The sequence number of the event within the run as seen by the Gem. Not reset at begin run!                  </TD> </TR>
<TR> <TD> ContextGemScalersDeadzone  </TD> <TD> ULong64 </TD> <TD> The total number of event discarded b/c they arrived during the 2 tick Gem deadzone. Not reset at begin run!  </TD> </TR>

<TR> <TD> ContextLsfTimeTimeToneCurrentIncomplete      </TD> <TD> UInt </TD> <TD> Current timetone: If this is non-zero part of the time tone is missing. Check the status bits.  </TD> </TR>
<TR> <TD> ContextLsfTimeTimeToneCurrentTimeSecs        </TD> <TD> UInt </TD> <TD> Current timetone: Number of seconds since Epoch start (01.01.2001) at most recent time hack.    </TD> </TR>
<TR> <TD> ContextLsfTimeTimeToneCurrentFlywheeling     </TD> <TD> UInt </TD> <TD> Current timetone: Number of time tones since last complete time tone.                           </TD> </TR>
<TR> <TD> ContextLsfTimeTimeToneCurrentFlagsValid      </TD> <TD> Int  </TD> <TD> Current timetone: Make sure that the flags are valid.                                           </TD> </TR>
<TR> <TD> ContextLsfTimeTimeToneCurrentIsSourceGps     </TD> <TD> Int  </TD> <TD> Current timetone: Is the source GPS?                                                            </TD> </TR>
<TR> <TD> ContextLsfTimeTimeToneCurrentMissingCpuPps   </TD> <TD> Int  </TD> <TD> Current timetone: No 1-PPS signal at the CPU level.                                             </TD> </TR>
<TR> <TD> ContextLsfTimeTimeToneCurrentMissingLatPps   </TD> <TD> Int  </TD> <TD> Current timetone: No 1-PPS signal at the LAT level.                                             </TD> </TR>
<TR> <TD> ContextLsfTimeTimeToneCurrentMissingTimeTone </TD> <TD> Int  </TD> <TD> Current timetone: No 1-PPS signal at the Spacecraft.                                            </TD> </TR>
<TR> <TD> ContextLsfTimeTimeToneCurrentEarlyEvent      </TD> <TD> Int  </TD> <TD> Current timetone: Event arrived close to 1-PPS.                                                 </TD> </TR>
<TR> <TD> ContextLsfTimeTimeToneCurrentGemTimeHacks    </TD> <TD> UInt </TD> <TD> Current timetone: The value of the GemTime registers at the time tone: Nnumber of 1-PPS time hacks. This counter wraps around at 127. </TD> </TR>
<TR> <TD> ContextLsfTimeTimeToneCurrentGemTimeTicks    </TD> <TD> UInt </TD> <TD> Current timetone: The value of the GemTime registers at the time tone: Value of the LAT system clock at the last 1-PPS time hack. </TD> </TR>

<TR> <TD> ContextLsfTimeTimeTonePreviousIncomplete      </TD> <TD> UInt </TD> <TD> Previous timetone: If this is non-zero part of the time tone is missing. Check the status bits.  </TD> </TR>
<TR> <TD> ContextLsfTimeTimeTonePreviousTimeSecs        </TD> <TD> UInt </TD> <TD> Previous timetone: Number of seconds since Epoch start (01.01.2001) at most recent time hack.    </TD> </TR>
<TR> <TD> ContextLsfTimeTimeTonePreviousFlywheeling     </TD> <TD> UInt </TD> <TD> Previous timetone: Number of time tones since last complete time tone.                           </TD> </TR>
<TR> <TD> ContextLsfTimeTimeTonePreviousFlagsValid      </TD> <TD> Int  </TD> <TD> Previous timetone: Make sure that the flags are valid.                                           </TD> </TR>
<TR> <TD> ContextLsfTimeTimeTonePreviousIsSourceGp      </TD> <TD> Int  </TD> <TD> Previous timetone: Is the source GPS?                                                            </TD> </TR>
<TR> <TD> ContextLsfTimeTimeTonePreviousMissingCpuPps   </TD> <TD> Int  </TD> <TD> Previous timetone: No 1-PPS signal at the CPU level.                                             </TD> </TR>
<TR> <TD> ContextLsfTimeTimeTonePreviousMissingLatPps   </TD> <TD> Int  </TD> <TD> Previous timetone: No 1-PPS signal at the LAT level.                                             </TD> </TR>
<TR> <TD> ContextLsfTimeTimeTonePreviousMissingTimeTone </TD> <TD> Int  </TD> <TD> Previous timetone: No 1-PPS signal at the Spacecraft.                                            </TD> </TR>
<TR> <TD> ContextLsfTimeTimeTonePreviousEarlyEvent      </TD> <TD> Int  </TD> <TD> Previous timetone: Event arrived close to 1-PPS.                                                 </TD> </TR><TR> 
<TD> ContextLsfTimeTimeTonePreviousGemTimeHacks    </TD> <TD> UInt </TD> <TD> Previous timetone: The value of the GemTime registers at the time tone: Nnumber of 1-PPS time hacks. This counter wraps around at 127. </TD> </TR>
<TR> <TD> ContextLsfTimeTimeTonePreviousGemTimeTicks    </TD> <TD> UInt </TD> <TD> Previous timetone: The value of the GemTime registers at the time tone: Value of the LAT system clock at the last 1-PPS time hack. </TD> </TR>


<TR> <TD> ContextLsfTimeTimeTicks </TD> <TD> UInt </TD> <TD> The number of system clock ticks (nominally 50ns) since last the last time hack.  </TD> </TR>

<TR> <TD>  ContextLsfTimeHackHacks </TD> <TD> UInt </TD> <TD> The number of 1-PPS time hacks.  This counter wraps around at 127. </TD> </TR>  
<TR> <TD>  ContextLsfTimeHackTicks </TD> <TD> UInt </TD> <TD> The value of the LAT system clock at the last 1-PPS time hack. </TD> </TR>  

<TR> <TD> ContextRunType </TD> <TD> Int  </TD> <TD> Which type of run was this, particle data or charge injection. </TD> </TR>

</TABLE>


<TABLE>
<CAPTION ALIGN="TOP"> Onboard Filter (Offline version)  </CAPTION>
<TR> <TH> Variable name </TH> <TH> Type </TH> <TH>Meaning  </TH> </TR>

<TR> <TD> ObfPassedGAMMA   </TD> <TD> Int  </TD> <TD> Variable equal to 1 if the event passed the GAMMA-filter and 0 if it didn't. </TD> </TR> 
<TR> <TD> ObfPassedMIP     </TD> <TD> Int  </TD> <TD> Variable equal to 1 if the event passed the MIP-filter and 0 if it didn't. </TD> </TR> 
<TR> <TD> ObfPassedHIP     </TD> <TD> Int  </TD> <TD> Variable equal to 1 if the event passed the HIP (Heavy ion filter) and 0 if it didn't. </TD> </TR> 
<TR> <TD> ObfPassedDGN     </TD> <TD> Int  </TD> <TD> Variable equal to 1 if the event passed the DGN (Diagnostic filter) and 0 if it didn't. </TD> </TR> 
</TABLE>



<TABLE>
<CAPTION ALIGN="TOP"> MC variables </CAPTION>
<TR> <TH> Variable name </TH> <TH> Type </TH> <TH>Meaning  </TH> </TR>

<TR> <TD> McSeqNo       </TD> <TD> Int   </TD> <TD> Sequence number </TD> </TR>
<TR> <TD> McId          </TD> <TD> Int   </TD> <TD> PDG id for primary MC particle. For example: e-(11), e+(-11), gamma(22), mu-(13), mu+(-13) </TD> </TR>
<TR> <TD> McTotalEnergy </TD> <TD> Float </TD> <TD> Total energy (in MeV) of the particle including its mass </TD> </TR>
<TR> <TD> McX0          </TD> <TD> Float </TD> <TD> x coordinate (in mm) of origin of the particle </TD> </TR>
<TR> <TD> McY0          </TD> <TD> Float </TD> <TD> y coordinate (in mm) of origin of the particle </TD> </TR>
<TR> <TD> McZ0          </TD> <TD> Float </TD> <TD> z coordinate (in mm) of origin of the particle </TD> </TR>
<TR> <TD> McXDir        </TD> <TD> Float </TD> <TD> True x direction (in radian) of the primary particle </TD> </TR>
<TR> <TD> McYDir        </TD> <TD> Float </TD> <TD> True y direction (in radian) of the primary particle </TD> </TR>
<TR> <TD> McZDir        </TD> <TD> Float </TD> <TD> True z direction (in radian) of the primary particle </TD> </TR>
<TR> <TD> McConvPointX  </TD> <TD> Float </TD> <TD> x coordinate (in mm) of photon conversion point </TD> </TR>
<TR> <TD> McConvPointY  </TD> <TD> Float </TD> <TD> y coordinate (in mm) of photon conversion point </TD> </TR>
<TR> <TD> McConvPointZ  </TD> <TD> Float </TD> <TD> z coordinate (in mm) of photon conversion point </TD> </TR>
<TR> <TD> McCalEneSum   </TD> <TD> Float </TD> <TD> MC sum of energies (in MeV) deposited in each crystal </TD> </TR>
<TR> <TD> McTkr1Ene     </TD> <TD> Float </TD> <TD> MC energy of first track (in MeV) if there is a pair production </TD> </TR>
<TR> <TD> McTkr2Ene     </TD> <TD> Float </TD> <TD> MC energy of second track (in MeV) if there is a pair production </TD> </TR>
<TR> <TD> McConvAngle   </TD> <TD> Float </TD> <TD> Opening angle (in radian) of e+/e- pair if there is a pair production </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> Vertex variables </CAPTION>
<TR> <TH> Variable name </TH> <TH> Type </TH> <TH>Meaning  </TH> </TR>

<TR> <TD> VtxX0       </TD> <TD> Float </TD> <TD> x coordinate (in mm) of first (best) vertex </TD> </TR>
<TR> <TD> VtxY0       </TD> <TD> Float </TD> <TD> y coordinate (in mm) of first (best) vertex </TD> </TR>
<TR> <TD> VtxZ0       </TD> <TD> Float </TD> <TD> z coordinate (in mm) of first (best) vertex </TD> </TR>

<TR> <TD> VtxXDir     </TD> <TD> Float </TD> <TD> x direction (in radian) in first vertex. If there are two tracks associated with the vertex, 
          then it is averged over the direction of the two tracks; Otherwise, it is just the direction of the track. </TD> </TR>
<TR> <TD> VtxYDir     </TD> <TD> Float </TD> <TD> y direction (in radian) in first vertex. If there are two tracks associated with the vertex, 
          then it is averged over the direction of the two tracks; Otherwise, it is just the direction of the track. </TD> </TR>
<TR> <TD> VtxZDir     </TD> <TD> Float </TD> <TD> z direction (in radian) in first vertex. If there are two tracks associated with the vertex, 
          then it is averged over the direction of the two tracks; Otherwise, it is just the direction of the track. </TD> </TR>

<TR> <TD> Vtx1NumTkrs </TD> <TD> Int   </TD> <TD> Number of tracks associated with the first vertex </TD> </TR>
<TR> <TD> Vtx1Energy  </TD> <TD> Float </TD> <TD> Energy (in MeV) stored in first vertex  </TD> </TR>
</TABLE>

<TABLE>
<CAPTION ALIGN="TOP"> TKR variables </CAPTION>
<TR> <TH> Variable name </TH> <TH> Type </TH> <TH>Meaning  </TH> </TR>

<TR> <TD> TkrNumDigis                        </TD> <TD> Int </TD> <TD> Number of TKR digis. A digi is produced whenever there is at least one strip hit in a silicon plane. </TD> </TR>
<TR> <TD> TkrNumStrips[tower][layer][view]   </TD> <TD> Int </TD> <TD> A 3 dimensional array which describes the number of strips in every tower, layer and view. 
           View=0 refers to measure X while View=1 refers to measure Y </TD> </TR>

<TR> <TD> tot[tower][layer][view][end]       </TD> <TD> Int </TD> <TD> A 4 dimensional array which describes tot value at every tower, layer, view and end. 
          End=0 refers to low end with stripId from 0 to 768 while end=1 refers to high end with stripId from 768 to 1536. Normally division is at middle of the plane. 
          However this could be changed during real data taking. Please check the configuration report to find out whether the devision is really in the middle</TD> </TR>

<TR> <TD> TkrNumClusters[tower][layer][view] </TD> <TD> Int </TD> <TD> A 3 dimension array which describes the number of clusters at every tower, layer and view. 
           View=0 refers to measure X while View=1 refers to measure Y. </TD> </TR>

<TR> <TD> TkrDepositEne[tower][layer][view] </TD> <TD> Float </TD> <TD> A 3 dimension array containing, for each tower, the true deposited energy in each layer and view. For MC only. </TD> </TR>

<TR> <TD> TkrNumTracks   </TD> <TD> Int </TD> <TD> Number of reconstructed tracks. Currently recon allows maximum of 10 tracks.</TD> </TR>
<TR> <TD> TkrNumVertices </TD> <TD> Int </TD> <TD> Number of reconstructed vertices</TD> </TR>
<TR> <TD> Tkr1NumHits    </TD> <TD> Int </TD> <TD> Number of clusters in first track </TD> </TR>
<TR> <TD> Tkr2NumHits    </TD> <TD> Int </TD> <TD> Number of clusters in second track </TD> </TR>

<TR> <TD> Tkr1Chisq      </TD> <TD> Float </TD> <TD> Chi square of first track. Note that the Merit variable Tkr1Chisq is the smooth chi2 which here is called Tkr1ChisqS. </TD> </TR>
<TR> <TD> Tkr2Chisq      </TD> <TD> Float </TD> <TD> Chi square of second track. Note that the Merit variable Tkr2Chisq is the smooth chi2 which here is called Tkr2ChisqS.  </TD> </TR>
<TR> <TD> Tkr1ChisqS     </TD> <TD> Float </TD> <TD> Smoothed chi square of first track </TD> </TR>
<TR> <TD> Tkr2ChisqS     </TD> <TD> Float </TD> <TD> Smoothed chi square of second track </TD> </TR>
<TR> <TD> Tkr1Rms        </TD> <TD> Float </TD> <TD> Rms value of first track </TD> </TR>
<TR> <TD> Tkr2Rms        </TD> <TD> Float </TD> <TD> Rms value of second track </TD> </TR>
<TR> <TD> Tkr1KalThetaMs </TD> <TD> Float </TD> <TD> Multiple scattering angle of first track calculated by the Kalman filter</TD> </TR>
<TR> <TD> Tkr2KalThetaMs </TD> <TD> Float </TD> <TD> Multiple scattering angle of second track calculated by the Kalman filter</TD> </TR>
<TR> <TD> Tkr1KalEne     </TD> <TD> Float </TD> <TD> Energy (in MeV) of first track calculated by the Kalman filter</TD> </TR>
<TR> <TD> Tkr2KalEne     </TD> <TD> Float </TD> <TD> Energy (in MeV) of second track calculated by the Kalman filter</TD> </TR>
<TR> <TD> Tkr1EndPos[3]  </TD> <TD> Float </TD> <TD> End-of-track position (in mm) of track 1  </TD> </TR>
<TR> <TD> Tkr2EndPos[3]  </TD> <TD> Float </TD> <TD> End-of-track position (in mm) of track 2  </TD> </TR>
<TR> <TD> Tkr1EndDir[3]  </TD> <TD> Float </TD> <TD> End-of-track direction (in mm) of track 1 </TD> </TR>
<TR> <TD> Tkr2EndDir[3]  </TD> <TD> Float </TD> <TD> End-of-track direction (in mm) of track 2 </TD> </TR>

<TR> <TD> TkrTopTot[tower]   </TD> <TD> Int </TD> <TD>A one dimensional array which describes tot value at the top hit layer for each tower. 
          The value is actually the maximum of 4 tot values at the biPlane.</TD> </TR> 
<TR> <TD> Tkr1ConvTot[tower] </TD> <TD> Int </TD> <TD>A one dimensional array which describes tot value at the layer of the first vertex. 
          The value is actually the maximum of 4 tot values at the biPlane.</TD> </TR>
<TR> <TD> TkrTp[tower][tp]   </TD> <TD> Int </TD> <TD>A two dimensional array which describes tracker trigger primitive for each tower. 
          For a more detailed description, please see the onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3</TD> </TR>

<TR> <TD> TkrReq[tower][layer][view][end] </TD> <TD> Int </TD> <TD>A 4 dimensional array which describes tracker trigger request. For example: TkrReq[8][7][0][0]=1 means a 
          trigger request was sent from tower 8, layer 7, measure X and lower end of the tray.  End=0 refers to low end with stripId from 0 to 768 while end=1 refers to high 
          end with stripId from 768 to 1536. Normally division is at middle of the plane, however this could be changed during real data taking.</TD> </TR>

<TR> <TD> TkrTotalHits[tower]     </TD> <TD> Int </TD> <TD>Total number of strip hits in each tower.</TD> </TR>
<TR> <TD> TkrTotalClusters[tower] </TD> <TD> Int </TD> <TD>Total number of clusters in each tower.</TD> </TR>
</TABLE>


<TABLE>
<CAPTION ALIGN="TOP"> CAL variables </CAPTION>
<TR> <TH> Variable name </TH> <TH> Type </TH> <TH>Meaning  </TH> </TR>

<TR> <TD> CalEneSum  </TD> <TD> Float </TD> <TD> Sum of energies (in MeV) in each crystal. This is the same as the Merit variable CalEnergyRaw. </TD> </TR>
<TR> <TD> CalXEcentr </TD> <TD> Float </TD> <TD> x coordinate (in mm) of centroid of the CAL cluster </TD> </TR>
<TR> <TD> CalYEcentr </TD> <TD> Float </TD> <TD> y coordinate (in mm) of centroid of the CAL cluster </TD> </TR>
<TR> <TD> CalZEcentr </TD> <TD> Float </TD> <TD> z coordinate (in mm) of centroid of the CAL cluster </TD> </TR>

<TR> <TD> CalXtalEne[tower][layer][col] </TD> <TD> Float </TD> <TD> Measured energy (in MeV) in a single crystal at each tower, layer and column. To get the log end energies you need to look at the CAL ntuple. Note that prior to October 2007 this array also contained '[end]'. This is no longer the case as it was unnecessary.</TD> </TR>

<TR> <TD> CalMaxEne </TD> <TD> Float </TD> <TD> Maximal measured energy (in MeV) in a single crystal </TD> </TR>

<TR> <TD> CalNumHit[tower] </TD> <TD> Int </TD> <TD> A one dimensional array which describes number of crystals in each tower with measured energy larger than zero suppression threshold </TD> </TR>

<TR> <TD> CalTp[tower][tp] </TD> <TD> Int </TD> <TD>A two dimensional array which describes the calorimeter trigger primitive for each tower.  
          For a more detailed description, please see the onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3. (For experts only.)</TD> </TR>

<TR> <TD> CalReq[tower][layer][end] </TD> <TD> Int </TD> <TD>A 3 dimensional array which describes calorimeter trigger request. For example: CalReq[8][7][0]=1 means a trigger request 
          was sent to the low energy trigger from tower 8, layer 7 and end 0; =2 means the trigger request was sent to the high energy trigger; =3 means the trigger request was sent 
          to both triggera.  </TD> </TR>

<TR> <TD> CalLogAccepts[tower][layer][end]</TD> <TD> Int </TD> <TD>A 3 dimensional array which describe the log accepts contained in the CAL trigger diagnostic information.  
          For a more detailed description, please see the onLine document at http://www-glast.slac.stanford.edu/IntegrationTest/ONLINE/docs/TEM.pdf, chapter 4.3  </TD> </TR>

<TR> <TD> CalXtalPos[tower][layer][col][coord] </TD> <TD> Float </TD> <TD>A 3 dimensional array which describes fit position in each CAL crystal: coord=0 means fitted X coordinate, 
          coord=1 means fitted Y coordinate and coord=2 means fitted Z coodinate. (For experts only.) </TD> </TR>


<TR> <TD> CalMipNum       </TD> <TD> Int   </TD> <TD> Total number of MIPs from the CAL MIP finder  </TD> </TR> 
<TR> <TD> CalMip1Pos[0-2] </TD> <TD> Float </TD> <TD> A 3 dimensional array which describes the CAL MIP track position centroid coordinates for the best MIP: 0=X, 1=Y and 2=Z. </TD> </TR> 
<TR> <TD> CalMip1Dir[0-2] </TD> <TD> Float </TD> <TD> A 3 dimensional array which describes the CAL MIP track direction for the best MIP: 0=X, 1=Y and 2=Z. </TD> </TR>
<TR> <TD> CalMip1Chi2     </TD> <TD> Float </TD> <TD> Chi2 of the direction fit (combination of least squares in XZ and YZ planes) for the best MIP. </TD> </TR>
<TR> <TD> CalMip1D2edge   </TD> <TD> Float </TD> <TD> Best track distance to CAL closest edge (mm) for the best MIP. </TD> </TR> 
<TR> <TD> CalMip1ArcLen   </TD> <TD> Float </TD> <TD> Track length (mm) of the best MIP. </TD> </TR>
<TR> <TD> CalMip1Ecor     </TD> <TD> Float </TD> <TD> Mean vertical-equivalent energy (MeV), obtained by averaging path-length corrected energies on a layer basis for the best MIP. </TD> </TR>
<TR> <TD> CalMip1EcorRms  </TD> <TD> Float </TD> <TD> Track RMS of the above corrected energie for the best MIP. </TD> </TR> 
<TR> <TD> CalMip1Erm      </TD> <TD> Float </TD> <TD> Total energy (MeV) contained in a cylinder of 1 Moliere radius around the best MIP. </TD> </TR>                    


<TR> <TD> CalMip2Pos[0-2] </TD> <TD> Float </TD> <TD> A 3 dimensional array which describes the CAL MIP track position centroid coordinates for the second best MIP: 0=X, 1=Y and 2=Z. </TD> </TR> 
<TR> <TD> CalMip2Dir[0-2] </TD> <TD> Float </TD> <TD> A 3 dimensional array which describes the CAL MIP track direction for the second best MIP 2: 0=X, 1=Y and 2=Z. </TD> </TR>            
<TR> <TD> CalMip2Chi2     </TD> <TD> Float </TD> <TD> Chi2 of the direction fit (combination of least squares in XZ and YZ planes) for the second best MIP. </TD> </TR>
<TR> <TD> CalMip2D2edge   </TD> <TD> Float </TD> <TD> Best track distance to CAL closest edge (mm) for the second best MIP. </TD> </TR> 
<TR> <TD> CalMip2ArcLen   </TD> <TD> Float </TD> <TD> Track length (mm) of the second best MIP. </TD> </TR>
<TR> <TD> CalMip2Ecor     </TD> <TD> Float </TD> <TD> Mean vertical-equivalent energy (MeV), obtained by averaging path-length corrected energies on a layer basis for the second best MIP. </TD> </TR>
<TR> <TD> CalMip2EcorRms  </TD> <TD> Float </TD> <TD> Track RMS of the above corrected energie for the second best MIP. </TD> </TR> 
<TR> <TD> CalMip2Erm      </TD> <TD> Float </TD> <TD> Total energy (MeV) contained in a cylinder of 1 Moliere radius around the second best MIP. </TD> </TR>                    

</TABLE>


<TABLE>
<CAPTION ALIGN="TOP"> ACD variables </CAPTION>
<TR> <TH> Variable name </TH> <TH> Type </TH> <TH>Meaning </TH> </TR>
<TR> <TD> AcdNumDigis                           </TD> <TD> Int   </TD> <TD> Number of ACD digis. This includes both attached and non-attached tiles (unless the non-attached were masked off). </TD> </TR>
<TR> <TD> Acd10Ids[10]                          </TD> <TD> Int   </TD> <TD> The tile IDs for the first 10 ACD digis. </TD> </TR>
<TR> <TD> AcdPha[tileID:0-603][2]               </TD> <TD> Int   </TD> <TD> Pulse Hight Analysis for the specified attached tile/ribbon and PMT (A or B). </TD> </TR>

<TR> <TD> AcdMips[tileID:0-603][2]              </TD> <TD> Float </TD> <TD> Calibrated PHA in MIPs by tileID, pmt</TD> </TR>
<TR> <TD> AcdMipsPha[tileID:0-603][2]           </TD> <TD> Int   </TD> <TD> PHA value by tileID, pmt, for now this is the same as AcdPha</TD> </TR>

<TR> <TD> AcdMipsFlag[tileID:0-603][2]          </TD> <TD> Int   </TD> <TD> Flag for calibrated Pha values. The bits are: PMT_ACCEPT_BIT = 0 (channel is above zero suppresion threshold (applied to digital data)), PMT_VETO_BIT = 1 (channel fired veto discriminator (applied to analog data)), PMT_RANGE_BIT = 2 (channel was read out in high range), PMT_RESERVED_BIT = 3 (just a trick to split the errors into the higher byte), PMT_ODD_PARITY_ERROR_BIT = 4 (PHA data transmission had parity error), PMT_HEADER_PARITY_ERROR_BIT = 5 (header data transmission had parity error - this should _never_happen!), PMT_DEAD_BIT = 6 (PMT was flagged as dead by offline calibration), PMT_HOT_BIT = 7 (PMT was flagged as hot by offline calibration). </TD> </TR>

<TR> <TD> AcdMipsMax                            </TD> <TD> Float </TD> <TD> Maximum calibrated signal in MIPs of all the PMTs</TD> </TR>
<TR> <TD> AcdMipsMaxTileID                      </TD> <TD> Int   </TD> <TD> Tile ID of tile with the maximum calibrated signal in MIPs. </TD> </TR> 
<TR> <TD> AcdMipsMaxPmt                         </TD> <TD> Int   </TD> <TD> PMT of tile with the maximum calibrated signal in MIPs. </TD> </TR>
<TR> <TD> AcdMipsSum                            </TD> <TD> Float </TD> <TD> Sum of calibrated PHA in MIPs (average of the two PMTs, or a single PMT if the other PMT is missing).</TD> </TR> 

<TR> <TD> AcdHitMap[tileID:0-603][2]            </TD> <TD> Int   </TD> <TD> Veto discriminator set or not for the specified attached tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdRange[tileID:0-603][2]             </TD> <TD> Int   </TD> <TD> Range for the specified attached tile/ribbon and PMT (A or B).</TD> </TR>
<TR> <TD> AcdOddParityError[tileID:0-603][2]    </TD> <TD> Int   </TD> <TD> Odd parity error bit for the specified attached tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdHeaderParityError[tileID:0-603][2] </TD> <TD> Int   </TD> <TD> Header parity error bit for the specified attached tile/ribbon and PMT (A or B). This bit should _never_ be set!</TD> </TR>
<TR> <TD> AcdLowDisc[tileID:0-603][2]           </TD> <TD> Int   </TD> <TD> Low discriminator set or not for the specified attached tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdTileNumber[tileID:0-603]           </TD> <TD> Int   </TD> <TD> Tile ID in dense notation.</TD> </TR> 

<TR> <TD> AcdNaPha[NA0-NA10:0-10][2]            </TD> <TD> Int </TD> <TD> Pulse Hight Analysis for the specified non-attached tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdNaHitMap[NA0-NA10:0-10][2]         </TD> <TD> Int </TD> <TD> Veto discriminator set or not for the specified non-attached tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdNaRange[NA0-NA10:0-10][2]          </TD> <TD> Int </TD> <TD> Range for the specified non-attached tile/ribbon and PMT (A or B).</TD> </TR>
<TR> <TD> AcdNaOddParityError[NA0-NA10:0-10][2] </TD> <TD> Int </TD> <TD> Odd parity error bit for the specified non-attached tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdNaHeaderParityError[NA0-NA10:0-10][2] </TD> <TD> Int </TD> <TD> Header parity error bit for the specified non-attached tile/ribbon and PMT (A or B). </TD> </TR>
<TR> <TD> AcdNaLowDisc[NA0-Na10:0-10][2]        </TD> <TD> Int </TD> <TD> Low discriminator set or not for the specified non-attached tile/ribbon and PMT (A or B). </TD> </TR>

<TR> <TD> AcdMCEnergy[tileID:0-603] </TD> <TD> Float </TD> <TD> The amount of Monte Carlo energy (in MeV) deposited in this detector element. </TD> </TR>

<TR> <TD> AcdTileMCEnergy        </TD> <TD> Float </TD> <TD> Total amount of Monte Carlo energy (in MeV) deposited in the ACD. </TD> </TR> 
<TR> <TD> AcdTileCount           </TD> <TD> Int   </TD> <TD> Total number of ACD tiles with the accept bit set (above the low threshold).  </TD> </TR> 
<TR> <TD> AcdDoca                </TD> <TD> Float </TD> <TD> The minimal Distance of Closest Approach (DOCA) wrt the center of the tile. </TD> </TR>
<TR> <TD> AcdMinDocaId           </TD> <TD> Float </TD> <TD> The ID of the Acd Tile associated with the minimum DOCA. </TD> </TR> 
<TR> <TD> AcdCornerDoca          </TD> <TD> Float </TD> <TD> Measure DOCA to rays along corner side gaps. </TD> </TR>
<TR> <TD> AcdActiveDist          </TD> <TD> Float </TD> <TD> Returns the maximum Active Distance for all tracks and ACD tiles. </TD> </TR>
<TR> <TD> AcdMaxActiveDistId     </TD> <TD> Int   </TD> <TD> The tile ID of the ACD tile associated with the maximum active distance.  </TD> </TR>

<TR> <TD> AcdRibbonMCEnergy      </TD> <TD> Float </TD> <TD> The amount of Monte Carlo energy (MeV) deposited in the ribbons.</TD> </TR>  </TD> </TR>
<TR> <TD> AcdRibbonCount         </TD> <TD> Int   </TD> <TD> Total number of ACD ribbons with the accept bit set (above the low threshold). </TD> </TR>
<TR> <TD> AcdRibbonActiveDist    </TD> <TD> Float </TD> <TD> The maximum Active Distance for all tracks and ACD ribbons. </TD> </TR>
<TR> <TD> AcdRibbonActiveDistId  </TD> <TD> Int   </TD> <TD> The ribbon ID of the ACD ribbon associated with the maximum Active Distance. </TD> </TR>

<TR> <TD>                                                 </TD> <TD>       </TD> <TD>                                                                      </TD> </TR>
<TR> <TD> AcdTkrIntersection variables: Information about the expected intersection of a track with the ACD. </TD> <TD>       </TD> <TD>                                                                      </TD> </TR>
<TR> <TD> AcdNumTkrIntSec                                 </TD> <TD> Int   </TD> <TD> Total number of ACD-TKR intersections.</TD> </TR>
<TR> <TD> AcdTkrIntSecTileId[iTkrIntSec:0-19]             </TD> <TD> Int   </TD> <TD> The tile/ribbon ID of the ACD tile/ribbon intersected by the track. </TD> </TR>
<TR> <TD> AcdTkrIntSecTkrIndex[iTkrIntSec:0-19]           </TD> <TD> Int   </TD> <TD> The track index of the intersecting track.  </TD> </TR>
<TR> <TD> AcdTkrIntSecGlobalX[iTkrIntSec:0-19]            </TD> <TD> Float </TD> <TD> Global X-coordinate of the hit position.  </TD> </TR>
<TR> <TD> AcdTkrIntSecGlobalY[iTkrIntSec:0-19]            </TD> <TD> Float </TD> <TD> Global Y-coordinate of the hit position.  </TD> </TR>
<TR> <TD> AcdTkrIntSecGlobalZ[iTkrIntSec:0-19]            </TD> <TD> Float </TD> <TD> Global Z-coordinate of the hit position.  </TD> </TR>
<TR> <TD> AcdTkrIntSecLocalX[iTkrIntSec:0-19]             </TD> <TD> Float </TD> <TD> Local X-coordinate of hit (in tile coordinates). </TD> </TR>
<TR> <TD> AcdTkrIntSecLocalY[iTkrIntSec:0-19]             </TD> <TD> Float </TD> <TD> Local Y-coordinate of hit (in tile coordinates). </TD> </TR>
<TR> <TD> AcdTkrIntSecLocalXXCov[iTkrIntSec:0-19]         </TD> <TD> Float </TD> <TD> Covariance matrix element XX of hit (in tile coordinates). </TD> </TR>
<TR> <TD> AcdTkrIntSecLocalYYCov[iTkrIntSec:0-19]         </TD> <TD> Float </TD> <TD> Covariance matrix element YY of hit (in tile coordinates). </TD> </TR>
<TR> <TD> AcdTkrIntSecLocalXYCov[iTkrIntSec:0-19]         </TD> <TD> Float </TD> <TD> Covariance matrix element XY of hit (in tile coordinates). </TD> </TR>
<TR> <TD> AcdTkrIntSecArcLengthToIntSec[iTkrIntSec:0-19]  </TD> <TD> Float </TD> <TD> Distance along track from first hit to tile intersection. </TD> </TR>
<TR> <TD> AcdTkrIntSecPathLengthInTile[iTkrIntSec:0-19]   </TD> <TD> Float </TD> <TD> Path length of track through tile. </TD> </TR>
<TR> <TD> AcdTkrIntSecTileHit[iTkrIntSec:0-19]            </TD> <TD> Int   </TD> <TD> Greater than zero if intersected tile/ribbon is hit. It is the sum of the values 1, 2, 4, 8, 16, and 32 which are set if 
          the signal in the tile passed the accept threshold for PMT A, the accept threshold for PMT B, the Veto threshold for PMT A, the Veto threshold for PMT B, the CNO threshold for PMT A and the 
          CNO threshold for PMT B respectively. </TD> </TR>



<TR> <TD>  </TD> <TD>       </TD> <TD> </TD> </TR>
<TR> <TD> AcdTkrPoca variables: Information about the Point of Closest Approach (POCA) between an extrapolated track and a hit Acd element 
          (tile or ribbon). This POCA is calculated in 3D.  The doca is defined to be positive if the track goes inside the active distance and negative otherwise </TD> <TD>       </TD> <TD> </TD> </TR> 
<TR> <TD> AcdPocaNbrTrack1                                </TD> <TD> Int   </TD> <TD>  Total number of hit tiles for track 1. NB! May be larger than 5! </TD> </TR>
<TR> <TD> AcdPocaNbrTrack2                                </TD> <TD> Int   </TD> <TD>  Total number of hit tiles for track 2. NB! May be larger than 5! </TD> </TR>
<TR> <TD> AcdPocaAcdTrackID[TrackIndex:0-1][Tile:0-6]     </TD> <TD> Float </TD> <TD>  Track index of intersecting track. Only information for the first two tracks are stored. </TD> </TR> 
<TR> <TD> AcdPocaAcdTileID[TrackIndex:0-1][Tile:0-6]      </TD> <TD> Float </TD> <TD>  Tile ID of the tile the track intersects. </TD> </TR>
<TR> <TD> AcdPocaDoca[TrackIndex:0-1][Tile:0-6]           </TD> <TD> Float </TD> <TD>  Distance of closet approach (DOCA) - calculated in 3D. </TD> </TR>
<TR> <TD> AcdPocaDocaErr[TrackIndex:0-1][Tile:0-6]        </TD> <TD> Float </TD> <TD>  Error on DOCA. This is calculated using the full Kalman Filter propagation of the track to the POCA 
          and the projection of the propagated covarience matrix along the line of the DOCA. </TD> </TR>
<TR> <TD> AcdPocaDocaRegion[TrackIndex:0-1][Tile:0-6]     </TD> <TD> Float </TD> <TD>  Returns a code showing which region of the tile or ribbon the POCA occured in. </TD> </TR>
<TR> <TD> AcdPocaX[TrackIndex:0-1][Tile:0-6]              </TD> <TD> Float </TD> <TD>  Global X-coordinate of POCA.  This point occurs along the track trajectory.</TD> </TR> 
<TR> <TD> AcdPocaY[TrackIndex:0-1][Tile:0-6]              </TD> <TD> Float </TD> <TD>  Global Y-coordinate of POCA.  This point occurs along the track trajectory.</TD> </TR> 
<TR> <TD> AcdPocaZ[TrackIndex:0-1][Tile:0-6]              </TD> <TD> Float </TD> <TD>  Global Z-coordinate of POCA.  This point occurs along the track trajectory.</TD> </TR> 
<TR> <TD> AcdPocaDirX[TrackIndex:0-1][Tile:0-6]           </TD> <TD> Float </TD> <TD>  X-component of vector from POCA to the detector element.  AcdPoca-AcdPocaDir gives the point on the detector element closest to the track.</TD> </TR> 
<TR> <TD> AcdPocaDirY[TrackIndex:0-1][Tile:0-6]           </TD> <TD> Float </TD> <TD>  Y-component of vector from POCA to the detector element.  AcdPoca-AcdPocaDir gives the point on the detector element closest to the track.</TD> </TR> 
<TR> <TD> AcdPocaDirZ[TrackIndex:0-1][Tile:0-6]           </TD> <TD> Float </TD> <TD>  Z-component of vector from POCA to the detector element.  AcdPoca-AcdPocaDir gives the point on the detector element closest to the track.</TD> </TR> 


<TR> <TD>  </TD> <TD>       </TD> <TD> </TD> </TR>
<TR> <TD> AcdGapPoca variables:Information about the Point of Closest Approach (POCA) between an extrapolated track and a gap between tiles in the ACD.  This POCA is calculated in 3D.  The doca is defined to be positive if the track goes into the gap and negative otherwise </TD> <TD> </TD> </TR>
<TR> <TD> AcdGapPocaNbrTrack1                             </TD> <TD> Int   </TD> <TD>  Total number of relevent gaps for track 1.</TD> </TR>
<TR> <TD> AcdGApPocaNbrTrack2                             </TD> <TD> Int   </TD> <TD>  Total number of relevent gaps for track 2.</TD> </TR>
<TR> <TD> AcdGapPocaTrackID[TrackIndex:0-1][Tile:0-3]     </TD> <TD> Float </TD> <TD>  Track index of intersecting track. Only information for the first two tracks are stored. </TD> </TR> 
<TR> <TD> AcdGapPocaTileID[TrackIndex:0-1][Tile:0-3]      </TD> <TD> Float </TD> <TD>  GAP ID of the tile the track intersects.  Exprssed as a bit mask.  GapType[0xF000] | GapNumber[0x0E00] | Face[0x01C0] | Row[0x0038] | Col[0x0007]</TD> </TR>
<TR> <TD> AcdGapPocaDoca[TrackIndex:0-1][Tile:0-3]        </TD> <TD> Float </TD> <TD>  Distance of closet approach (DOCA) - calculated in 2D. </TD> </TR>
<TR> <TD> AcdGapPocaGapIndex[TrackIndex:0-1][Tile:0-3]    </TD> <TD> Int   </TD> <TD>  Index saying which gap the DOCA is being calculated with respect to. </TD> </TR>
<TR> <TD> AcdGapPocaGapType[TrackIndex:0-1][Tile:0-3]     </TD> <TD> Int   </TD> <TD>  What type of gap we are talking about: X_RibbonSide = 1, Y_RibbonSide = 2, Y_RibbonTop = 3, CornerRay = 4, TopCornerEdge = 5, TileHole = 6. </TD> </TR> 


<TR> <TD>  </TD> <TD>       </TD> <TD> </TD> </TR>
<TR> <TD> AcdTkrPoint variables: Information about the point where the track leaves the nominal ACD volume.  This does not account for the complexities of the geometry, but does give a good estimate of where the track hit the ACD </TD> <TD> </TD> </TR>
<TR> <TD> AcdTkrPointX[up,down:0,1]                       </TD> <TD> Float </TD> <TD>  X-component of point where track struck ACD</TD> </TR>
<TR> <TD> AcdTkrPointY[up,down:0,1]                       </TD> <TD> Float </TD> <TD>  Y-component of point where track struck ACD</TD> </TR>
<TR> <TD> AcdTkrPointZ[up,down:0,1]                       </TD> <TD> Float </TD> <TD>  Z-component of point where track struck ACD</TD> </TR>
<TR> <TD> AcdTkrFace[up,down:0,1]                         </TD> <TD> Int </TD> <TD>  Face of ACD struck by track 0=top, 1,3 = +- X, 2,4 = +- Y, 5 =bottom</TD> </TR>

</TABLE>

*/
