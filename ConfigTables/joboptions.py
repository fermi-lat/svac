
runDir = "/nfs/slac/g/svac/focke/ConfigTables/rawData/139000001"
outFile = "tables.html"
outDir = "."

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

# special value used by schema to broadcast over all values of ID
broadcast = 255

# pack this many table across the output page
width = 2
