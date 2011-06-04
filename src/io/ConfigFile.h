/*! \file ConfigFile.h
 */

#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include "../base/debug_tools.h"
#include "../base/numlib-config.h"
#include "FileIOError.h"
#include "SyntaxError.h"
#include "string_utils.h"
#include <map>
#include <sstream>
#include <fstream>

namespace numlib{ namespace io{

//! Loads and parses a configuration file
/*!
 *	A common problem in developing a numerical model is that
 *	of mapping an configuration file (i.e. input file) to a
 *	set of parameters which are needed to setup and run the
 *	simulation. This class seeks to solve this problem by
 *	defining a simple, matlab-like, syntax for defining
 *	named scalars and arrays in an ASCII formatted file.
 *	To make the configuration files more human readable,
 *	comments (denoted by '#') are allowed. The result is
 *	something similar to that of a namelist common to Fortran
 *	programs. Thus, developers of numerical models need to
 *	simply define which variables is requires in its 
 *	documentation and delagate the work of parsing the user
 *	created configuration files to this class.
 *
 *	The template parameter 'V' specifies the container template type
 *	to use for vectors or 1D arrays. The type 'V' is assumed to either 
 *	be an STL container (e.g. vector, list, deque) or implement the 
 *	same container protocals as STL containers. The containers,
 *	numlib::array::Array1D and numlib::linalg::Vector are not currently 
 *	supported as they do not implement STL protocals. The template function 
 *	numlib::io::fromString is used to handle the type conversion; thus, the 
 *	element type must be a type understood by numlib::io::fromString.
 *	The following element types are known to work for both scalar and
 *	vector inputs: double, float, int, std::string.
 *
 *  \todo Remove some of the code duplication between load and loadVector
 *	\todo Enable support of multi-dimensional arrays
 *	\todo Enable support of NumLib arrays and vectors
 *	\todo Enable custom string converters for user defined numeric types
 */
class ConfigFile
{
public:

	//! Loads and parses configuration file
	ConfigFile(const String& file_name);

	~ConfigFile();

	//! Loads scalar types
	template<class T>
	void load(const String& name, T& val);

	//! Loads vector types (i.e. 1D arrays of arbitrary size)
	template<class V>
	void loadVector(const String& name, V& val);

private:

	typedef std::map<String,String> Dictionary;

	Dictionary input_dict;

};

}}//::numlib::io

#include "ConfigFile-imp.h"

#endif
