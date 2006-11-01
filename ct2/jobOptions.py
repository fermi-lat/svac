
import os

import mappings

# defaults for command-line args
runNumber = '1'
schemaFile = 'schema.xml' # no longer used
snapFile = 'snapshot.xml'
splitFile = 'splits.dat'
tarBall = 'configReport.tgz'

outFile = os.environ['configReportUrl']
version = os.environ['configReportVersion']

licosMode = 'licos'
latteMode = 'latte'
modes = {
    u'algorithm': licosMode,
    u'configuration': latteMode,
    }
mode = 'bogus'


# register subfields and their descriptions
tables = {

    'ZERO_SUPP_GLT': ('GLT/zero_suppress',
                      'CAL Zero Suppression'),
    'FOUR_RANGE_GLT': ('GLT/four_range_readout',
                       'CAL Four Range Readout'),

    'ZERO_SUPP': ('GEM/GEMMG/engine_*:21',
                  'CAL 0 Suppression'),
    'FOUR_RANGE': ('GEM/GEMMG/engine_*:20',
                   'CAL 4 Range Readout'),
    'PRESCALE': ('GEM/GEMMG/engine_*:0-7',
                 'Prescale'),
    'INHIBIT': ('GEM/GEMMG/engine_*:15',
                'Inhibit'),

    'CONDITION': ('GEM/GEMSC/conditions_*',
                  'Trigger Condition -> Message engine lookup table'),

    'TEM_DIAG': ('TEM/data_masks:12',
                 'TEM Diagnostics'),
    
    'TKR_NR': ('TEM/TCC/TRC/csr:7-11', # used to calc GTRC splits
               'Number of GTFEs to read'), 
    'TKR_MODE': ('TEM/TCC/TRC/TFE/mode', # used to calc GTRC splits
                 'TKR front end mode (L or R)'),
    'TKR_DAC': ('TEM/TCC/TRC/TFE/dac', # TKR DAC
                'TKR DAC (range,<B>threshhold</B>)'),

    'TKR_OR_STRETCH': ('TEM/TCC/TRC/csr:12-16', 
                       'TKR OR_STRETCH'),

    'CAL_LAD': ('TEM/CCC/CRC/CFE/log_acpt',
                "CAL Log Accept Discriminator (zero suppression)"), 
    'CAL_FHE': ('TEM/CCC/CRC/CFE/fhe_dac',
                "CAL High Energy Trigger Discriminator"), 
    'CAL_FLE': ('TEM/CCC/CRC/CFE/fle_dac',
                "CAL Low Energy Trigger Discriminator"), 
    'CAL_RNG': ('TEM/CCC/CRC/CFE/rng_uld_dac',
                "CAL Readout Range Select Discriminator"), 
    'CAL_REF': ('TEM/CCC/CRC/CFE/ref_dac',
                "CAL DAC for DC Reference"), 

    'CAL_DELAY': ('TEM/CCC/trg_alignment:0-7',
                  'Delay from CAL trigger discriminator to TEM trigger primitive formation'), 
    'TKR_DELAY': ('TEM/TCC/trg_alignment:0-7',
                  'Delay from TKR trigger discriminator to TEM trigger primitive formation'), 
    'ACD_DELAY': ('AEM/ARC/veto_delay',
                  'Delay from ACD trigger discriminator to AEM trigger primitive formation'), 
    
    'CAL_WIDTH': ('TEM/CCC/trg_alignment:8-15',
                  'Stretch width of CAL trigger primitive'), 
    'ACD_WIDTH': ('AEM/ARC/veto_width',
                  'Stretch width of ACD trigger primitive'), 
    
    'ACD_LATCH_DELAY': ('AEM/ARC/hitmap_delay',
                        'Delay from ACD trigger primitive to AEM hitmap data latch'), 
    'ACD_LATCH_WIDTH': ('AEM/ARC/hitmap_width',
                        'Stretch width of ACD trigger primitive to AEMXS hitmap data latch'), 
    'ACD_HITMAP_DEADTIME': ('AEM/ARC/hitmap_deadtime',
                            'Time added to hitmap signals'),
    'ACD_HOLD_DELAY': ('AEM/ARC/hold_delay',
                       'Delay from trigger to hold'),
    'ACD_ADC_TACQ': ('AEM/ARC/adc_tacq',
                     'ADC acquisition time'),
   
    'GEM_WIDTH': ('GEM/GEMW/window_width',
                  'Width of trigger window in GEM'), 
    
    'CAL_TRGSEQ': ('TEM/cal_trgseq',
                   'Delay from trigger TACK to CAL shaper hold'), 
    'TKR_TRGSEQ': ('TEM/tkr_trgseq',
                   'Delay from trigger TACK to TKR shaper hold'), 
    'ACD_TRGSEQ': ('AEM/trgseq',
                   'Delay from trigger TACK to ACD shaper hold'),

    'DELAY_1': ('TEM/CCC/CRC/delay_1',
                'CAL Range Decision Time (nominal=31)'),
    'DELAY_2': ('TEM/CCC/CRC/delay_2',
                'CAL Time After Range Decision Until ADC Readout Time (nominal=53)'),
    'DELAY_3': ('TEM/CCC/CRC/delay_3',
                'CAL ADC Readout Time (nominal=133)'),
    
    'CAL_DIAG': ('TEM/CCC/trg_alignment:16-23',
                 'Hold trigger primitive for TEM diagnostic latching of CAL trigger primitive'), 
    'TKR_DIAG': ('TEM/TCC/trg_alignment:16-23',
                 'Hold trigger primitive for TEM diagnostic latching of TKR trigger primitive'), 


    'ACD_HVBS': ('AEM/ARC/hvbs',
                 'Requested High Voltage (HV) for normal operation'),
    'ACD_SAA': ('AEM/ARC/saa',
                'Requested High Voltage (HV) for SAA operation'),
    'ACD_USE_HV_NORMAL': ('AEM/ARC/use_hv_normal',
                          'Current High Voltage (HV) for normal operation'),
    'ACD_USE_HV_SAA': ('AEM/ARC/use_hv_saa',
                       'Current High Voltage (HV) for SAA operation'),

    'ACD_MODE': ('AEM/ARC/mode',
                 'Various bit fields for mode settings'),
    'ACD_STATUS': ('AEM/ARC/status',
                   'Status'),

    'ACD_CONFIG_REG': ('AEM/ARC/AFE/configuration',
                       'Configuration setup'),
    'ACD_VETO_DAC': ('AEM/ARC/AFE/veto_dac',
                     'Set VETO threshold (coarse)'),
    'ACD_VETO_VERNIER': ('AEM/ARC/AFE/veto_vernier',
                         'Set VETO threshold (fine)'),
    'ACD_HLD_DAC': ('AEM/ARC/AFE/hld_dac',
                    'Set HLD threshold'),
    'ACD_BIAS_DAC': ('AEM/ARC/AFE/bias_dac',
                     'Set bias value'),

    '': ('',
         ''),
    
    }

mappers = {'TKR_DAC': mappings.mapTkrDac}

# logical values that apply to the whole LAT
globoLogicals = ('ZERO_SUPP_GLT', 'FOUR_RANGE_GLT')

globalDBKeys = ('NoOfTowers', 'CAL_SER_NO', 'TKR_SER_NO', 'RELEASE')
globalDBStringLabels = {'NoOfTowers': 'Number of Towers',
                        'TKR_SER_NO': 'TKR Serial #s',
                        'CAL_SER_NO': 'CAL Serial #s',
                        'RELEASE': 'LICOS/LATTE Release',
                        }

# GEM stuff
# # stuff to display from message engines
messageEngineColumns = ('INHIBIT', 'ZERO_SUPP', 'FOUR_RANGE', 'PRESCALE')
# # label message engines, and use to expand wildcard in engine_* registers
messageEngineRowLabels = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']

conditionTag = 'CONDITION'
# # use to expand wildcard in conditions_* registers
conditionStrings = ['%x%x_%x%x' % (msn, lsn, msn, lsn+7) for msn in range(16) for lsn in (0, 8)]
# # use to pull individual table entries from registers
conditionFields = ['%d-%d' % (4*entry, 4*entry+3) for entry in range(8)]
conditionAxes = ('MSN', 'LSN')

# values that apply per-TEM
perTem = ('TEM_DIAG',)
# and column labels for those tables
perTemColumns = ('Tower', 'Value')

# make TKR split tables this many towers wide
tkrSplitWidth = 4
# put this many tables of TKR FE settings acros the page
tkrTabWidth = 1 
# put this many tables of CAL FE settings acros the page
calTabWidth = 2
# put this many g?rc tables across page
rcWidth = 2

# # ACD stuff ####################################

garcLabels = ('GARC', 'Value')
gafeLabels = ('GARC', 'GAFE')

# HV info
acdHvTags = ('ACD_HVBS', 'ACD_USE_HV_NORMAL', 'ACD_SAA', 'ACD_USE_HV_SAA')

acdMaskRegs = {'PHA': ('AEM/ARC/pha_en_0', 'AEM/GARC/pha_en_1'),
               'veto': ('AEM/ARC/veto_en_0', 'AEM/GARC/veto_en_1')}
acdGarcRandom = ('ACD_MODE', 'ACD_STATUS')

acdGafeHex = ('ACD_CONFIG_REG', )
acdGafe = ('ACD_VETO_DAC', 'ACD_VETO_VERNIER', 'ACD_HLD_DAC', 'ACD_BIAS_DAC')

# # TKR stuff ####################################

# stuff from TKR readout controllers
gtrcTags = ('TKR_NR', 'TKR_OR_STRETCH')
gtrcLabels = ('GTCC', 'GTRC')

# things to display from TKR front ends
tkrTags = ('TKR_MODE', 'TKR_DAC', )
tkrAxisLabels = ('layer', 'front end')
tkrSimpleAxisLabels = ('GTCC,GTRC (digi layer, edge)', 'GTFE')


# # CAL ##########################################

# things to display from CAL front ends
calTags = ('CAL_LAD', 'CAL_FHE', 'CAL_FLE', 'CAL_RNG', 'CAL_REF')
calAxisLabels = ('layer', 'crystal')

# # delays #######################################

# cable delays
cableDelays = ('CAL_DELAY', 'TKR_DELAY', 'CAL_WIDTH', 'CAL_DIAG', 'TKR_DIAG')
cableLabels = ('Tower', 'Cable')

garcDelays = ('ACD_DELAY', 'ACD_WIDTH', 'ACD_ADC_TACQ', 'ACD_LATCH_DELAY',
              'ACD_LATCH_WIDTH', 'ACD_HITMAP_DEADTIME', 'ACD_HOLD_DELAY')


# TEM delays
# tackDelays = ('CAL_TRGSEQ', 'TKR_TRGSEQ', 'ACD_TRGSEQ') # if we had an ACD
tackDelays = ('CAL_TRGSEQ', 'TKR_TRGSEQ')
tackDelayLabels = {'CAL_TRGSEQ': ('CAL (ticks (ns))', ('Tower', 'Delay')),
                   'TKR_TRGSEQ': ('TKR (ticks (ns))', ('Tower', 'Delay')),
                   'ACD_TRGSEQ': ('ACD (ticks (ns))', ('AEM', 'Delay'))}

# CAL delays
calDelays = ('DELAY_1', 'DELAY_2', 'DELAY_3')
gcrcLabels = ('GCCC', 'GCRC')

# system clock rate and period
clock = 20e6
tick = 1.0 / clock

# units to report times in
timeScale = 1e9
timeUnits = 'ns'

timeLabel = ' (ticks (%s))' % timeUnits
timeMap = (mappings.displayTime, timeLabel)


# voltage scale
maxVolts = 1500.0
voltRegMax = 1 << 12 - 1
vScale = maxVolts / voltRegMax
voltUnit = 'V'
voltLabel = ' (steps (%s))' % voltUnit
voltMap = (mappings.displayHv, voltLabel)

hexMap = (mappings.displayHex, '')

# put this in empty table cells
absent = 'Broadcast'

# These are tags that we use to determine if various subsystems are present
presenceTags = {
    'TEM': 'TEM',
    'TKR': 'TFE',
    'CAL': 'CFE',
    'GEM': 'GEM',
    'GLT': 'GLT',
    'ACD': 'AFE',
    }

# Shapes of register tables for the whole LAT
shapes = {
    'TEM': (16,),
    'AEM': (12,),
    'ARC': (12, 1),
    'CCC': (16, 4),
    'TCC': (16, 8),
    'CRC': (16, 4, 4),
    'TRC': (16, 8, 9),
    'AFE': (12, 1, 18),
    'CFE': (16, 4, 4, 12),
    'TFE': (16, 8, 9, 24),
    '': (),
    }

# Modify various strings to switch from LICOS to LATTE mode
def toLatte():
    global absent
    dictToLatte(tables)
    dictToLatte(acdMaskRegs)
    tagsToLatte(presenceTags)
    absent = 'Absent'
    return

def regToLatte(oldPath):
    tags = oldPath.split('/')
    tags[:-1] = ['G' + tag for tag in tags[:-1]]
    newPath = '/'.join(tags)
    return newPath

def dictToLatte(regDict):
    for key, (path, label) in regDict.items():
        path = regToLatte(path)
        regDict[key] = (path, label)
        pass
    return

def tagsToLatte(tagDict):
    for key, value in tagDict.items():
        tagDict[key] = 'G' + value
    return
