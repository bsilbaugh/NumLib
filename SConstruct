################################################################################
#
#                            SCons Build Script
#
# General Scons notes:
#
# 1. Always remember that an SCons script is declarative not imperitive;
# 	 thus, SCons load this entire script before actually building anything.
#	 Forgetting this may cause unexepected behaviors, particularly when
#	 trying to implement ad-hoc replacement of environment variables for
#	 certain source file(s); the last replace command will always "win"
#	 and be used for all builds in that environment.
#
# 2. By default, Scons does not use the same PATH defined in the shell
#	 environment that Scons was executed in. This design choice is to
#    ensure consistent builds.
#
# 3. Most Scons arguments which expect a list also accept a string when
#    only one element needs to be passed.
#
# 4. Generally speaking, all paths are taken as relative to the
#    local (or subsidiary) SConstruct file. Paths may be taken relative to the 
# 	 top level SConstruct file by prepending the path with '#'.
#
################################################################################

# Setup contruction environment(s)...

env = Environment()

# Explicity set path...

path = ['/usr/local/bin', '/bin', '/usr/bin']
env['ENV']['PATH'] = path

# Set installation location (will assume local install only for now)...

prefix = '#'

# env.Decider('MD5') # Default rule
env.Decider('timestamp-newer') # Makefile-like rule

# Create some 'help' info...

Help("""
You are very smart. I'm sure you'll figure this out.
""")

#Define libraries to build...

libs = (
	'base', 
	'array',
	'integration',
	'linalg',
	'optimization',
	'reconstruction',
	'tensor',
	'solvers',
	'nnet'
)

# Define subsidiary SConstruct files...

SConscript(['src/%s/SConstruct' %z for z in libs], exports='env prefix')
