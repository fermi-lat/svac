
import os

tables = {
'CAL_LAD': ('GTEM/GCCC/GCRC/GCFE/log_acpt:*', "Log Accept Discriminator (zero supression)"), 
'CAL_FHE': ('GTEM/GCCC/GCRC/GCFE/fhe_dac:*', "High Energy Trigger Discriminator"), 
'CAL_FLE': ('GTEM/GCCC/GCRC/GCFE/fle_dac:*', "Low Energy Trigger Discriminator"), 
'CAL_RNG': ('GTEM/GCCC/GCRC/GCFE/rng_uld_dac:*', "Range Select Discriminator"), 
'CAL_REF': ('GTEM/GCCC/GCRC/GCFE/ref_dac:*', "DAC for DC Reference"), 

'CAL_TRGSEQ': ('GTEM/cal_trgseq:*', 'delay from trigger TACK to CAL shaper hold'), 
'TKR_TRGSEQ': ('GTEM/tkr_trgseq:*', 'delay from trigger TACK to TKR shaper hold'), 
'ACD_TRGSEQ': ('GAEM/trgseq:*', 'delay from trigger TACK to ACD shaper hold'), 
'CAL_DELAY': ('GTEM/GCCC/trg_alignment:0-8', 'delay from CAL trigger discriminator to TEM trigger primitive formation'), 
'CAL_WIDTH': ('GTEM/GCCC/trg_alignment:8-16', 'stretch width of CAL trigger primitive'), 
'CAL_DIAG': ('GTEM/GCCC/trg_alignment:16-24', 'hold trigger primitive for TEM diagnostic latching of CAL trigger primitive'), 
'TKR_DELAY': ('GTEM/GTCC/trg_alignment:0-8', 'delay from TKR trigger discriminator to TEM trigger primitive formation'), 
'TKR_DIAG': ('GTEM/GTCC/trg_alignment:16-24', 'hold trigger primitive for TEM diagnostic latching of TKR trigger primitive'), 
'ACD_DELAY': ('GAEM/GARC/veto_delay:0-8', 'delay from ACD trigger discriminator to AEM trigger primitive formation'), 

'ACD_WIDTH': ('GAEM/GARC/veto_width:*', 'stretch width of ACD trigger primitive'), 
'ACD_LATCH_DELAY': ('GAEM/GARC/hitmap_delay:*', 'delay from ACD trigger primitive to AEM hitmap data latch'), 
'ACD_LATCH_WIDTH': ('GAEM/GARC/hitmap_width:*', 'stretch width of ACD trigger primitive to AEMXS hitmap data latch'), 
'GEM_WIDTH': ('GGEM/GGEMW/window_width:*', 'width of trigger window in GEM'), 

'TKR_NR': ('GTEM/GTCC/GTRC/csr:7-13', 'Number of GTFEs to read'), 
'TKR_MODE': ('GTEM/GTCC/GTRC/GTFE/mode:*', 'TKR front end mode (L or R)'), 
}

calTags = ['CAL_LAD', 'CAL_FHE', 'CAL_FLE', 'CAL_RNG', 'CAL_REF']
calAxisLabels = ('layer', 'crystal')

outFile = os.environ['configReportUrl']
version = os.environ['configReportVersion']

# put this many tables of CAL settings acros the page
calTabWidth = 2 
