
import os

# defaults for command-line args
runNumber = '1'
schemaFile = 'schema.xml' # no longer used
snapFile = 'snapshot.xml'
splitFile = 'splits.dat'
tarBall = 'configReport.tgz'

outFile = os.environ['configReportUrl']
version = os.environ['configReportVersion']

# register subfields and their descriptions
tables = {

    'ZERO_SUPP': ('GGLT/zero_suppress',
                  'CAL Zero Supression'),
    'FOUR_RANGE': ('GGLT/four_range_readout',
                   'CAL Four Range Readout'),
    
    'TKR_NR': ('GTEM/GTCC/GTRC/csr:7-12', # used to calc GTRC splits
               'Number of GTFEs to read'), 
    'TKR_MODE': ('GTEM/GTCC/GTRC/GTFE/mode', # used to calc GTRC splits
                 'TKR front end mode (L or R)'),
    'TKR_DAC': ('GTEM/GTCC/GTRC/GTFE/dac', # TKR DAC
                'TKR DAC'),

    'CAL_LAD': ('GTEM/GCCC/GCRC/GCFE/log_acpt',
                "CAL Log Accept Discriminator (zero supression)"), 
    'CAL_FHE': ('GTEM/GCCC/GCRC/GCFE/fhe_dac',
                "CAL High Energy Trigger Discriminator"), 
    'CAL_FLE': ('GTEM/GCCC/GCRC/GCFE/fle_dac',
                "CAL Low Energy Trigger Discriminator"), 
    'CAL_RNG': ('GTEM/GCCC/GCRC/GCFE/rng_uld_dac',
                "CAL Readout Range Select Discriminator"), 
    'CAL_REF': ('GTEM/GCCC/GCRC/GCFE/ref_dac',
                "CAL DAC for DC Reference"), 

    'CAL_DELAY': ('GTEM/GCCC/trg_alignment:0-7',
                  'Delay from CAL trigger discriminator to TEM trigger primitive formation'), 
    'TKR_DELAY': ('GTEM/GTCC/trg_alignment:0-7',
                  'Delay from TKR trigger discriminator to TEM trigger primitive formation'), 
    'ACD_DELAY': ('GAEM/GARC/veto_delay:0-7',
                  'Delay from ACD trigger discriminator to AEM trigger primitive formation'), 
    
    'CAL_WIDTH': ('GTEM/GCCC/trg_alignment:8-15',
                  'Stretch width of CAL trigger primitive'), 
    'ACD_WIDTH': ('GAEM/GARC/veto_width',
                  'Stretch width of ACD trigger primitive'), 
    
    'ACD_LATCH_DELAY': ('GAEM/GARC/hitmap_delay',
                        'Delay from ACD trigger primitive to AEM hitmap data latch'), 
    'ACD_LATCH_WIDTH': ('GAEM/GARC/hitmap_width',
                        'Stretch width of ACD trigger primitive to AEMXS hitmap data latch'), 
    
    'GEM_WIDTH': ('GGEM/GGEMW/window_width',
                  'Width of trigger window in GEM'), 
    
    'CAL_TRGSEQ': ('GTEM/cal_trgseq',
                   'Delay from trigger TACK to CAL shaper hold'), 
    'TKR_TRGSEQ': ('GTEM/tkr_trgseq',
                   'Delay from trigger TACK to TKR shaper hold'), 
    'ACD_TRGSEQ': ('GAEM/trgseq',
                   'Delay from trigger TACK to ACD shaper hold'),
    
    'CAL_DIAG': ('GTEM/GCCC/trg_alignment:16-23',
                 'Hold trigger primitive for TEM diagnostic latching of CAL trigger primitive'), 
    'TKR_DIAG': ('GTEM/GTCC/trg_alignment:16-23',
                 'Hold trigger primitive for TEM diagnostic latching of TKR trigger primitive'), 
    
    }

# logical values that apply to the whole LAT
globoLogicals = ['ZERO_SUPP', 'FOUR_RANGE']

# make TKR split tables this many towers wide
tkrSplitWidth = 4
# put this many tables of TKR FE settings acros the page
tkrTabWidth = 1 
# put this many tables of CAL FE settings acros the page
calTabWidth = 2 

# things to display from TKR front ends
tkrTags = ['TKR_DAC']
tkrAxisLabels = ('layer', 'front end')
tkrSimpleAxisLabels = ('GTCC,GTRC (digi layer, edge)', 'GTFE')

# things to display from CAL front ends
calTags = ['CAL_LAD', 'CAL_FHE', 'CAL_FLE', 'CAL_RNG', 'CAL_REF']
calAxisLabels = ('layer', 'crystal')

# cable delays
# cableDelays = ['CAL_DELAY', 'TKR_DELAY', 'ACD_DELAY', 'CAL_WIDTH', 'ACD_WIDTH', 'CAL_DIAG', 'TKR_DIAG', 'ACD_LATCH_DELAY', 'ACD_LATCH_WIDTH'] # if we had an ACD
cableDelays = ['CAL_DELAY', 'TKR_DELAY', 'CAL_WIDTH', 'CAL_DIAG', 'TKR_DIAG']
cableLabels = ('Tower', 'Cable') # but this won't work with the ACD

# TEM delays
# tackDelays = ['CAL_TRGSEQ', 'TKR_TRGSEQ', 'ACD_TRGSEQ'] # if we had an ACD
tackDelays = ['CAL_TRGSEQ', 'TKR_TRGSEQ']
tackDelayLabels = {'CAL_TRGSEQ': ('CAL (ticks (ns))', ('Tower', 'Delay')),
                   'TKR_TRGSEQ': ('TKR (ticks (ns))', ('Tower', 'Delay')),
                   'ACD_TRGSEQ': ('ACD (ticks (ns))', ('AEM', 'Delay'))}


# system clock rate and period
clock = 20e6
tick = 1.0 / clock

# units to report times in
timeScale = 1e9
timeUnits = 'ns'

# put this in empty table cells
absent = 'Absent'
