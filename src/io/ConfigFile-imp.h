/*! \file ConfigFile-imp.h
 */

namespace numlib{ namespace io{

template<class T>
void ConfigFile::load(const String& name, T& val)
{

	Dictionary::iterator it = input_dict.find(name);

	if(it==input_dict.end())
	{
		String msg("Expected value for parameter '");
		msg += name;
		msg += "' but no value was given";
		throw SyntaxError(msg.c_str());
	}

	if(!fromString(val, it->second))
	{
		String msg("Type conversion failed for ");
		msg += name;
		throw SyntaxError(msg.c_str());
	}
}

template<class V>
void ConfigFile::loadVector(const String& name, V& val)
{

	Dictionary::iterator it = input_dict.find(name);

	if(it==input_dict.end())
	{
		String msg("Expected value for parameter '");
		msg += name;
		msg += "' but no value was given";
		throw SyntaxError(msg.c_str());
	}

	if((it->second)[0]!='[') 
	{
		String msg;
		msg = it->first;
		msg += " is a vector (1D array); expected opening bracket '['";
		throw SyntaxError(msg.c_str());
	}
	if((it->second)[(it->second).length()-1]!=']') 
	{
		String msg;
		msg = it->first;
		msg += " is a vector (1D array); expected closing bracket ']'";
		throw SyntaxError(msg.c_str());
	}

	std::stringstream buff;
	char c;
	typename V::value_type x;
  	buff<<it->second;
	buff>>c; /* purge opening bracket */
	do
	{
		buff>>x>>c;
		if(buff.fail())
		{
			String msg("Error while reading element values for vector '");
			msg+=it->first;
			msg+="'";
			throw SyntaxError(msg.c_str());
		}
		val.push_back(x);
	}while(c!=']');
}

}}//::numlib::io
