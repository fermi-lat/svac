
runDir = "/nfs/farm/g/glast/u01/EM2/rawData"
outFile = "ConfigTables.html"
outDir = "/nfs/farm/g/glast/u01/EM2/rootData"
reportDir = "config"

registerTag = "log_acpt"
calTags = ["log_acpt", "fhe_dac", "fle_dac", "rng_uld_dac", "ref_dac"]

snapshotPrefix = "rsa"
exten = ".xml"

schemaFile = "MiniCaland4LayerTkr.xml"
schemaTag = "schema"

# These are things for which the schema should define allowed values for
# ID attribute
shapeTags = ["GTWR",
             "GTEM",
             "GCCC", "GCRC", "GCFE",
             "GTCC", "GTRC", "GTFE",
             ]
maxShape = {"GTWR": 16,
            "GTEM": 16,
            "GCCC": 4, "GCRC": 4, "GCFE": 12,
            "GTCC": 8, "GTRC": 9, "GTFE": 24,
            } 

# special value used by schema to broadcast over all values of ID
broadcast = 255

# pack this many table across the output page
width = 2
