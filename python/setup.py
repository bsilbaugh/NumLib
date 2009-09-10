#!/usr/bin/python

from distutils.core import setup
from distutils.core import Extension

boost_dir="/Users/silbaugh/CodeLib/Boost"
numlib_dir='..'

# *** NOTE: WE'RE EXPLICITLY SPECIFYING THE BOOST PYTHON LIBRARY
#     PATH AND EXTENSION. DEFAULT LINKAGE CHOOSES THE DYNAMIC
#     LIBRARY WHICH FAILS WHEN TRYING TO IMPORT THE MODULE INTO
#     PYTHON. A MORE PORTABLE SOLUTION SHOULD BE FOUND BEFORE
#     DISTRIBUTING THIS CODE TO OTHERS!!!!  

#boostlink = "/usr/local/lib/libboost_python-xgcc40-mt.a"
#boostlink = "/Users/silbaugh/CodeLib/Boost/lib/libboost_python.a"

lib_dirs = []
lib_dirs.append(numlib_dir+'/lib')
lib_dirs.append(boost_dir+'/lib')

inc_dirs = []
inc_dirs.append(numlib_dir+'/include')
inc_dirs.append(boost_dir+'/include ')

libs = []
libs.append("boost_python")
libs.append("numlib_tensor")

boostpy_test = Extension('boostpy_test',['numlib/boostpy_test.cpp'],\
		include_dirs=inc_dirs,\
		library_dirs=lib_dirs, \
		libraries=libs \
		)

array = Extension('array/_array', ['numlib/array/array.cpp'],\
		include_dirs=inc_dirs,\
		library_dirs=lib_dirs,\
		libraries=libs
		)

tensor = Extension('tensor/_tensor', ['numlib/tensor/tensor.cpp'],\
		include_dirs=inc_dirs,\
		library_dirs=lib_dirs,\
		libraries=libs
		)

tensor_exp = Extension('tensor/_tensor_exp', ['numlib/tensor/tensor_exp.cpp'],\
		include_dirs=inc_dirs,\
		library_dirs=lib_dirs,\
		libraries=libs
		)

mods = []
#mods.append(boostpy_test)
#mods.append(array)
mods.append(tensor)
mods.append(tensor_exp)

setup(name='numlib',\
	  version='0.0',\
	  description='NumLib Python Interface',\
	  author='Benjamin Silbaugh',\
	  author_email='silbaugh@umd.edu',\
	  packages=['numlib'],\
	  ext_package='numlib',\
	  ext_modules=mods,\
	  )
