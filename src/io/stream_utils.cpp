/*! \file stream_utils.cpp
 */

#include "stream_utils.h"

namespace rodymol
{

std::ostream & operator<<(std::ostream & os, const Dict & dict)
{
	 Dict::const_iterator it;
	 for(it = dict.begin(); it != dict.end(); ++it)
		  os << "'" 
			 << (*it).first 
			 << "' = '"
			 << (*it).second
			 << "'\n";
	 return os;
}

std::ostream & operator<<(std::ostream & os, const RealList & list)
{
	 RealList::const_iterator it;
	 for(it=list.begin(); it!=list.end(); ++it)
		  os<<" "<<fmtReal<<(*it);
	 return os;
}

std::ostream & operator<<(std::ostream & os, const SizeList & list)
{
	 SizeList::const_iterator it;
	 for(it=list.begin(); it!=list.end(); ++it)
		  os<<" "<<(*it);
	 return os;
}

std::istream & operator>>(std::istream & is, TensorR1 & u)
{
	 is>>u(1);
	 is>>u(2);
	 is>>u(3);
	 return is;
}

std::istream & operator>>(std::istream & is, EulerParameterVector & u)
{
	 is>>u(1);
	 is>>u(2);
	 is>>u(3);
	 is>>u(4);
	 return is;
}

std::istream & operator>>(std::istream & is, TensorR2 & u)
{
	 is>>u(1,1)>>u(1,2)>>u(1,3);
	 is>>u(2,1)>>u(2,2)>>u(2,3);
	 is>>u(3,1)>>u(3,2)>>u(3,3);
	 return is;
}

void open(const String & fileName, std::ifstream & ifs)
{
	ifs.open(fileName.c_str());
	if(!ifs.is_open())
	{
		String error_msg("Failed to open file: ");
		error_msg += fileName;
		throw FileIOError(error_msg.c_str());
	}
}

void open(const String & fileName, std::ofstream & ofs)
{
	ofs.open(fileName.c_str());
}

void loadInputFileASCII(const String & fileName, StringStream & buff)
{

	 String line;

	 // Clear the output buffer...

	 buff.clear();
	 buff.str("");

	 // Obtain input file stream...

	 std::ifstream file;
	 open(fileName, file);

	 // Load input data into buffer...

	 while(!file.eof())
	 {

		  // Get next physical line in file...

		  getline(file, line);

		  // Strip comments...

		  stripComments(line);

		  // Strip whitespace...

		  stripWhiteSpace(line);

		  // If line non-empty input to buffer...

		  if(line.length() > 0)
		  {
			   DEBUG_PRINT_VAR(line);
			   buff<<"\n"<<line;
		  }

	 }

	 // Remove superflous leading newline character...

	 getline(buff, line);

	 // Close input file stream...

	 file.close();
}

void parseInputLine(const String & line, String & substr1, String & substr2, const char* delim)
{
	 Size pos1;
	 Size pos2;
	 Size len = strlen(delim);

	 pos1 = line.find(delim);
	 if(pos1 == String::npos) throw SyntaxError();

	 pos2 = pos1+len;

	 substr1 = line.substr(0,pos1);
	 substr2 = line.substr(pos2);
}

void parseInputStream(StringStream & buff, Dict & dict, const char* delim)
{

	 String line;
	 String substr1;
	 String substr2;

	 while(!buff.eof())
	 {

		  // Find start and end positions of delimeter...

		  getline(buff, line);
		  if(line.length() == 0) continue; /* skip blank lines */

		  // Extract variable name and value...

		  parseInputLine(line, substr1, substr2, delim);

		  // Populate variable dictionary...

		  dict[substr1] = substr2;

	 }

}

void parseCompModelNameList(StringStream & buff, CompModelNameList & nameList)
{

	 String line;
	 String substr1;
	 String substr2;
	 const char* delim = ":=";
	
	 typedef std::pair<String, String> ListElem;

	 while(!buff.eof())
	 {

		  // Find start and end positions of delimeter...

		  getline(buff, line);
		  if(line.length() == 0) continue; /* skip blank lines */

		  // Extract variable name and value...

		  parseInputLine(line, substr1, substr2, delim);

		  // Populate variable dictionary...

		  nameList.push_back( ListElem(substr1, substr2) );

	 }

}

void parseCompNameAndNodeIndex(const String & line, String & compModelName, Index & nodeIndex)
{
	 Index pos;
	 pos = line.find(':');
	 if(pos == String::npos) throw SyntaxError("Expected ':' ");

	 // Parse component model name...

	 compModelName = line.substr(0,pos);

	 // Parse node index value...

	 if( !fromString( nodeIndex, line.substr(pos+1) ) )
		  throw SyntaxError("Expected integer value for node index");
}

void parseConnInstInner(StringStream & buff, ConnInstSet & connInstSet)
{
	 String line;
	 String substrL;
	 String substrR;
	 Size pos;

	 /* Next line should be the left bracket '{' indicating the start of
		the connectivity statement list. */
	 
	 getline(buff, line);

	 if(line.compare("{")) throw SyntaxError("Expected '{' ");

	 // Read connectivity statement list until '}'...

	 getline(buff, line);
	 while(line.compare("}"))
	 {

		  DEBUG_PRINT_VAR( line );

		  pos = line.find("--");
		  if(pos == String::npos) throw SyntaxError("Expected '--' ");

		  substrL = line.substr(0,pos); /* displacement node statement */
		  substrR = line.substr(pos+2); /* force node statement */

		  ConnInst connInst;

		  parseCompNameAndNodeIndex(substrL, 
									connInst.disp.compModelName, 
									connInst.disp.nodeIndex);

		  parseCompNameAndNodeIndex(substrR,
									connInst.force.compModelName,
									connInst.force.nodeIndex);

		  DEBUG_PRINT_VAR( connInst.disp.compModelName );
		  DEBUG_PRINT_VAR( connInst.disp.nodeIndex );
		  DEBUG_PRINT_VAR( connInst.force.compModelName );
		  DEBUG_PRINT_VAR( connInst.force.nodeIndex );
		  
		  connInstSet.push_back(connInst);

		  getline(buff, line);
	 }
}

void parseConnInst(StringStream & buff,
				   ConnInstSet & cisPointLinear,
				   ConnInstSet & cisPointRotational,
	               ConnInstSet & cisCurveLinear,
				   ConnInstSet & cisCurveRotational)
{
	 /* We assume that all white space and comments have been removed by this
		point. */

	 String line;

	 while(!buff.eof())
	 {
		  getline(buff, line);

		  DEBUG_PRINT_VAR(line);

		  // parse topology type and motion type...

		  if( line.compare("point,linear") == 0 )
		  {
			   parseConnInstInner(buff, cisPointLinear);
		  }
		  else if( line.compare("point,rotational") == 0 )
		  {
			   parseConnInstInner(buff, cisPointRotational);
		  }
		  else if( line.compare("curve,linear") == 0 )
		  {
			   parseConnInstInner(buff, cisCurveLinear);
		  }
		  else if( line.compare("curve,rotational") == 0 )
		  {
			   parseConnInstInner(buff, cisCurveRotational);
		  }
		  else
		  {
			   throw SyntaxError("Error parsing connectivity file. Expected topology and motion type specification; e.g.\npoint, linear\n{\n\t...\n}\n");
		  }

	 }
}

}//::rodymol
