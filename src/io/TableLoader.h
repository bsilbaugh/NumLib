
#ifndef TABLE_LOADER_H
#define TABLE_LOADER_H

#include <fstream>
#include <sstream>
#include <vector>

#include "../base/numlib-config.h"
#include "string_utils.h"
#include "FileIOError.h"

namespace numlib{ namespace io{

class TableLoader
{
public:

	//! Default initialization (empty table)
	TableLoader();

	//! Loads table from ASCII file
	TableLoader(const String& file_name);

	//! Loads table from ASCII file
	void load(const String& file_name);

	//! Returns the number of data rows in the table
	const Size number_of_rows() const { return nrow; }

	//! Returns the number of data columns in the table
	const Size number_of_columns() const { return ncol; }

	//! Return the grid associated with table rows
	const Real abscissa(const Index i) const { return data[i+1][0]; }

	//! Returns the grid associated with table columns
	const Real ordinate(const Index j) const { return data[0][j]; }

	//! Returns the table data value associated with ith row and jth column
	const Real operator()(const Index i, const Index j) const { return data[i+1][j+1]; }

private:

	typedef std::vector< std::vector< Real > > Data;

	Size ncol;
	Size nrow;
	Data data;

};

}}//::numlib::io

#endif
