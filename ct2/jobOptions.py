
import os

outFile = os.environ['configReportUrl']
version = os.environ['configReportVersion']

# register subfields and their descriptions
tables = {

    'GGLT/zero_suppress:*':('GGLT/zero_suppress:*',
                            'Zero Supression'),
    'GGLT/four_range_readout:*':('GGLT/four_range_readout:*'
                                 'Four Range Readout'),
    
    'TKR_NR': ('GTEM/GTCC/GTRC/csr:7-13', # used to calc GTRC splits
               'Number of GTFEs to read'), 
    'TKR_MODE': ('GTEM/GTCC/GTRC/GTFE/mode:*', # used to calc GTRC splits
                 'TKR front end mode (L or R)'), 

    'CAL_LAD': ('GTEM/GCCC/GCRC/GCFE/log_acpt:*',
                "CAL Log Accept Discriminator (zero supression)"), 
    'CAL_FHE': ('GTEM/GCCC/GCRC/GCFE/fhe_dac:*',
                "CAL High Energy Trigger Discriminator"), 
    'CAL_FLE': ('GTEM/GCCC/GCRC/GCFE/fle_dac:*',
                "CAL Low Energy Trigger Discriminator"), 
    'CAL_RNG': ('GTEM/GCCC/GCRC/GCFE/rng_uld_dac:*',
                "CAL Range Select Discriminator"), 
    'CAL_REF': ('GTEM/GCCC/GCRC/GCFE/ref_dac:*',
                "CAL DAC for DC Reference"), 

    'CAL_DELAY': ('GTEM/GCCC/trg_alignment:0-8',
                  'delay from CAL trigger discriminator to TEM trigger primitive formation'), 
    'TKR_DELAY': ('GTEM/GTCC/trg_alignment:0-8',
                  'delay from TKR trigger discriminator to TEM trigger primitive formation'), 
    'ACD_DELAY': ('GAEM/GARC/veto_delay:0-8',
                  'delay from ACD trigger discriminator to AEM trigger primitive formation'), 
    
    'CAL_WIDTH': ('GTEM/GCCC/trg_alignment:8-16',
                  'stretch width of CAL trigger primitive'), 
    'ACD_WIDTH': ('GAEM/GARC/veto_width:*',
                  'stretch width of ACD trigger primitive'), 
    
    'ACD_LATCH_DELAY': ('GAEM/GARC/hitmap_delay:*',
                        'delay from ACD trigger primitive to AEM hitmap data latch'), 
    'ACD_LATCH_WIDTH': ('GAEM/GARC/hitmap_width:*',
                        'stretch width of ACD trigger primitive to AEMXS hitmap data latch'), 
    
    'GEM_WIDTH': ('GGEM/GGEMW/window_width:*',
                  'width of trigger window in GEM'), 
    
    'CAL_TRGSEQ': ('GTEM/cal_trgseq:*',
                   'delay from trigger TACK to CAL shaper hold'), 
    'TKR_TRGSEQ': ('GTEM/tkr_trgseq:*',
                   'delay from trigger TACK to TKR shaper hold'), 
    'ACD_TRGSEQ': ('GAEM/trgseq:*',
                   'delay from trigger TACK to ACD shaper hold'),
    
    'CAL_DIAG': ('GTEM/GCCC/trg_alignment:16-24',
                 'hold trigger primitive for TEM diagnostic latching of CAL trigger primitive'), 
    'TKR_DIAG': ('GTEM/GTCC/trg_alignment:16-24',
                 'hold trigger primitive for TEM diagnostic latching of TKR trigger primitive'), 
    
    }

# things to display from CAL front ends
calTags = ['CAL_LAD', 'CAL_FHE', 'CAL_FLE', 'CAL_RNG', 'CAL_REF']
calAxisLabels = ('layer', 'crystal')

# make TKR split tables this many towers wide
tkrSplitWidth = 4
# put this many tables of CAL FE settings acros the page
calTabWidth = 2 


# put this in empty table cells
absent = 'Absent'
