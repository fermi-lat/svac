
def findSnapshot(directory):
    prefixes = ("rsb", "rsa")
    for prefix in prefixes:
        filePattern = prefix + "*" + ".xml"
        fullPattern = os.path.join(directory, filePattern)
        files = glob.glob(fullPattern)
        if files:
            file = scalar(files)
            return file
        pass
    print "Couldn't find snapshot in directory %s." % directory
    sys.exit(3)
    return
    

def findSchema(directory):
    schema = scanRcReportDotOutForSchema(directory)
    if schema is None:
        schema = scanXmlForSchema(directory)
        pass
    return schema


def scanRcReportDotOutForSchema(directory):
    return


def scanXmlForSchema(directory):
    filePattern = "*" + ".xml"
    fullPattern = os.path.join(directory, filePattern)
    files = glob.glob(fullPattern)
    files = grep("<schema>", files, caseSen=0)
    if not files:
        print "Couldn't find a schema in directory %s." % directory
        sys.exit(4)
    file = scalar(files)
    return file

def grep(pattern, filenames, caseSen=1):
    flags = 0
    if not caseSen:
        flags |= re.IGNORECASE
    regex = re.compile(pattern, flags)
    matchers = []
    for filename in filenames:
        contents = file(filename, "rb").read()
        if regex.search(contents):
            matchers.append(filename)
            pass
        pass
    return matchers
