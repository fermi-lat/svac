
'GTEM/GCCC/GCRC/GCFE/log_acpt:*', "Log Accept Discriminator"
'GTEM/GCCC/GCRC/GCFE/fhe_dac:*', "High Energy Trigger Discriminator"
'GTEM/GCCC/GCRC/GCFE/fle_dac:*', "Low Energy Trigger Discriminator"
'GTEM/GCCC/GCRC/GCFE/rng_uld_dac:*', "Range Select Discriminator"
'GTEM/GCCC/GCRC/GCFE/ref_dac:*', "DAC for DC Reference"

'GTEM/GTCC/GTRC/csr:7-13', 'Number of GTFEs to read'
'GTEM/GTCC/GTRC/GTFE/mode:*', 'TKR front end mode (L or R)'

'GTEM/cal_trgseq:*', 'delay from trigger TACK to CAL shaper hold'
'GTEM/tkr_trgseq:*', 'delay from trigger TACK to TKR shaper hold'
'GAEM/trgseq:*', 'delay from trigger TACK to ACD shaper hold'
'GTEM/GCCC/trg_alignment:0-8', 'delay from CAL trigger discriminator to TEM trigger primitive formation'
'GTEM/GCCC/trg_alignment:8-16', 'stretch width of CAL trigger primitive'
'GTEM/GCCC/trg_alignment:16-24', 'hold trigger primitive for TEM diagnostic latching of CAL trigger primitive'
'GTEM/GTCC/trg_alignment:0-8', 'delay from TKR trigger discriminator to TEM trigger primitive formation'
'GTEM/GTCC/trg_alignment:16-24', 'hold trigger primitive for TEM diagnostic latching of TKR trigger primitive'
'GAEM/GARC/veto_delay:0-8', 'delay from ACD trigger discriminator to AEM trigger primitive formation'

'GAEM/GARC/veto_width:*', 'stretch width of ACD trigger primitive'
'GAEM/GARC/hitmap_delay:*', 'delay from ACD trigger primitive to AEM hitmap data latch'
'GAEM/GARC/hitmap_width:*', 'stretch width of ACD trigger primitive to AEMXS hitmap data latch'
'GGEM/GGEMW/window_width:*', 'width of trigger window in GEM'


outFile = os.environ['configReportUrl']
version = os.environ['configReportVersion']

# put this many tables of CAL settings acros the page
calTabWidth = 2 
