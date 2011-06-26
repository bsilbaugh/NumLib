
#include "TableLoader.h"

namespace numlib{ namespace io{

TableLoader::TableLoader():
	ncol(0), nrow(0), data(0)
{
}

TableLoader::TableLoader(const String& file_name):
	ncol(0), nrow(0), data(0)
{
	load(file_name);
}

void TableLoader::load(const String& file_name)
{
	data.resize(0);

	typedef std::vector<Real> Row;

	// Load table...

	std::ifstream ifile(file_name.c_str());
	if(!ifile.is_open())
		throw FileIOError( (file_name + " failed to open").c_str() );

	while(true)
	{
		String line;
		std::stringstream buff;

		getline(ifile, line);
		if(!ifile) break;
		if(line.size() == 0) continue;
		buff<<line;

		Real val;
		Row row(0);
		while(buff>>val)
			row.push_back(val);

		data.push_back(row);
	}

		ifile.close();

		// Get table size...
	
		nrow = data.size() - 1;
		ncol = data[0].size();

		// Check that all row are the same size...

		for(Index j=1; j<nrow; ++j)
			if(!(data[j].size() == ncol + 1))
				throw NumLibError("Table contains unequal columns");
}

}}//::namespace::io
