#!/usr/bin/python

from distutils.core import setup
from distutils.core import Extension

boost_dir="/Users/silbaugh/CodeLib/Boost"
boost_dir="/usr/local"
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
inc_dirs.append(boost_dir+'/include')

libs = []
libs.append("boost_python")
libs.append("numlib_tensor")
libs.append("numlib_base")

dmacros = [('DEBUG', 1)]
undmacros = ['NDEBUG']
#arch = ['-arch', 'i386']
arch = None

boostpy_test = Extension('boostpy_test',['numlib/boostpy_test.cpp'],\
		define_macros=dmacros, \
		undef_macros=undmacros, \
		extra_compile_args=arch,\
		extra_link_args=arch,\
		include_dirs=inc_dirs,\
		library_dirs=lib_dirs, \
		libraries=libs \
		)

array = Extension('array/_array', ['numlib/array/array.cpp'],\
		define_macros=dmacros, \
		undef_macros=undmacros, \
		extra_compile_args=arch,\
		extra_link_args=arch,\
		include_dirs=inc_dirs,\
		library_dirs=lib_dirs,\
		libraries=libs
		)

tensor = Extension('tensor/_tensor', ['numlib/tensor/tensor.cpp'],\
		define_macros=dmacros, \
		undef_macros=undmacros, \
		extra_compile_args=arch,\
		extra_link_args=arch,\
		include_dirs=inc_dirs,\
		library_dirs=lib_dirs,\
		libraries=libs
		)

tensor_exp = Extension('tensor/_tensor_exp', ['numlib/tensor/tensor_exp.cpp'],\
		define_macros=dmacros, \
		undef_macros=undmacros, \
		extra_compile_args=arch,\
		extra_link_args=arch,\
		include_dirs=inc_dirs,\
		library_dirs=lib_dirs,\
		libraries=libs
		)

reconstruction = \
Extension('reconstruction/_reconstruction',\
		 ['numlib/reconstruction/reconstruction.cpp'],\
		 define_macros=dmacros, \
		 undef_macros=undmacros, \
		 extra_compile_args=arch,\
		 extra_link_args=arch,\
		 include_dirs=inc_dirs,\
		 library_dirs=lib_dirs,\
		 libraries=libs
		 )

mods = []
#mods.append(boostpy_test)
mods.append(array)
mods.append(tensor)
mods.append(tensor_exp)
mods.append(reconstruction)

setup(name='numlib',\
	  version='0.0',\
	  description='NumLib Python Interface',\
	  author='Benjamin Silbaugh',\
	  author_email='silbaugh@umd.edu',\
	  packages=['numlib'],\
	  ext_package='numlib',\
	  ext_modules=mods,\
	  )
