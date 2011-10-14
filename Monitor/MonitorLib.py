#$Id$
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['Monitor'])
    env.Tool('commonRootDataLib')
    env.Tool('digiRootDataLib')
    env.Tool('mcRootDataLib')
    env.Tool('reconRootDataLib')
    env.Tool('facilitiesLib')
    env.Tool('xmlBaseLib')
    env.Tool('configDataLib')
    env.Tool('calibUtilLib')
    env.Tool('identsLib')

def exists(env):
    return 1
