	

#include <windows.h>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::ios;

#include <stdio.h>
#include <time.h>

int main( int argc, char *argv[] )
{
  SYSTEMTIME  beg;      // Start time
  ifstream    fp;       // Input file stream
  ofstream		op;
  int         val;      // Current input value
  int			i;
  GetLocalTime( &beg );

  printf( "%02d:%02d:%02d:%06d\n", beg.wHour,
    beg.wMinute, beg.wSecond, beg.wMilliseconds * 1000 );
  
  op.open("sample.txt", ios::out);

  // Open file. IN: Open for reading, Binary: Operations in binary mode rather than text.
  fp.open( "seek.pc.db", ios::in | ios::binary );

  for(i = 1; i< 50; i++)
  {
	  // The result of the sizeof operator is of type size_t	 
	  // seekg: Sets the position of the next character to be extracted from the input stream.
	  fp.seekg( i * (int) sizeof( int ), ios::beg );
	  // tellg: Returns the position of the current character in the input stream.
	  printf( "seekg( %d INT, begin ), pos=%d\n",i, (int) fp.tellg() );

	  // istream& read (char* s, streamsize n);
	  // Extracts n characters from the stream and stores them in the array pointed by by s.
	  fp.read( (char *) &val, (int) sizeof( int ) );
	  printf( "val=%d\n\n", val );

	  // Note: Use \r\n to add line break.
	  op << i << ":" << val << "\r\n";
  }
  fp.seekg( -2 * (int) sizeof( int ), ios::end );
  printf( "seekg( -2 INT, end ), pos=%d\n", (int) fp.tellg() );

  fp.read( (char *) &val, (int) sizeof( int ) );
  printf( "val=%d\n", val );

  fp.close();  

  return 1;
}