
calTags = ["log_acpt", "fhe_dac", "fle_dac", "rng_uld_dac", "ref_dac"]

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

# pack this many tables across the output page
width = 4

version = "v0r0"
