
outFile = "ConfigTables.html"

calTags = ["log_acpt", "fhe_dac", "fle_dac", "rng_uld_dac", "ref_dac"]

delayTags = ["GLAT/GTEM/cal_trgseq", "GLAT/GTEM/tkr_trgseq", "GLAT/GAEM/trgseq",
             "GLAT/GTEM/GCCC/alignment", "GLAT/GTEM/GTCC/alignment",
             "GLAT/GAEM/veto_delay"
             ]
stretchTags = ["GLAT/GTEM/GCCC/alignment", "GLAT/GTEM/GCCC/alignment",
               "GLAT/GTEM/GTCC/alignment", "GLAT/GAEM/GARC/veto_width",
               "GLAT/GAEM/GARC/hitmap_delay", "GLAT/GAEM/GARC/hitmap_width",
               "GLAT/GGEM/GGEMW/window_width", 
               ]

schemaTag = "schema"

# These are things for which the schema should define allowed values for
# ID attribute
shapeTags = ["GTWR",
             "GTEM",
             "GCCC", "GCRC", "GCFE",
             "GTCC", "GTRC", "GTFE",
             "GARC", "GAFE",
             ]
maxShape = {"GTWR": 16,
            "GTEM": 16,
            "GCCC": 4, "GCRC": 4, "GCFE": 12,
            "GTCC": 8, "GTRC": 9, "GTFE": 24,
            "GARC": 12, "GAFE": 18,            
            } 

# pack this many tables across the output page
width = 4

version = "v0r0"
