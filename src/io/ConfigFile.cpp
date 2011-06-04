
#include "ConfigFile.h"

namespace numlib{ namespace io{

ConfigFile::ConfigFile(const String& file_name):
	input_dict()
{
	// Open input file stream...
	std::ifstream file(file_name.c_str());
	if(!file.is_open())
	{
		String msg("Failed to open file: ");
		msg+=file_name;
		throw FileIOError(msg.c_str());
	}

	// Load file into buffer while parsing comments and white space...
	std::stringstream buff;
	String line;
	while(!file.eof())
	{
		// Load the next line...
		getline(file,line);

		// Strip superfluous characters...
		stripComments(line);
		stripWhiteSpace(line);

		// Append non-blank line to buffer...
		if(line.length() > 0) buff<<"\n"<<line;
	}
	getline(buff,line);

	// Close file stream...
	file.close();

	// If any array inputs with wrapped lines, unwrap them...
	std::stringstream buff2;
	while(!buff.eof())
	{
		getline(buff, line);

		DEBUG_PRINT_VAR( line );

		buff2<<"\n"<<line;

		if(line.find('[') < String::npos)
		{
			while(!(line.find(']') < String::npos))
			{
				getline(buff, line);
				DEBUG_PRINT_VAR( line );
				buff2<<line;
			}
		}
	}
	getline(buff2,line);

	// Parse key value pairs...
	String key;
	String val;
	while(!buff2.eof())
	{
		getline(buff2, line);
		if(split(line, key, val, "="))
		{
			String msg;
			msg = "Failed to parse line '";
			msg += line;
			msg += "'";
			throw SyntaxError(msg.c_str());
		}

		std::pair<Dictionary::iterator,bool> ret=input_dict.insert(std::pair<String,String>(key,val));
		if(ret.second==false)
		{
			String msg;
			msg = "Value for parameter '";
			msg += key;
			msg += "' already given as '";
			msg += ret.first->second;
			msg += "'";
			throw SyntaxError(msg.c_str());
		}
	}
}

ConfigFile::~ConfigFile()
{
	/* all auto delete */
}

}}//::numlib::io
