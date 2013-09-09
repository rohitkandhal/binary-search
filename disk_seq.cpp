#include <windows.h>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;	// To print output to a text file.
using std::ios;
using std::cout;

#include <stdio.h>
#include <time.h>

int main( int argc, char *argv[] )
{
  SYSTEMTIME  beg;      // Start time
  SYSTEMTIME  end;		// End Time

  ifstream    fp;       // Input file stream
  ofstream	  op;
  
  int         val;      // Current input value
  int		  i,j;		// Index variables
  int		  temp;		// temporary variable

  int s[10000];	// Seek array
  int hit[10000];	// Hit array

  // ****************************************************************************************
  
  // Open file. IN: Open for reading, Binary: Operations in binary mode rather than text.
  fp.open( "seek.pc.db", ios::in | ios::binary );

  // Copy Seek values to s[10000] array
  fp.read( (char *) &val, (int) sizeof(int));
  
  i = 0;
  while( !fp.eof())
  {
	  s[i] = val;
	  i++;
	  fp.read( (char *) &val, (int) sizeof(int));
  }

  fp.close();

  GetLocalTime( &beg );

  // ****************************************** Check if key exists**********************************************

  fp.open( "key.pc.db", ios::in | ios::binary);

  for(i = 0; i < 10000; i++)
  {
	  temp = s[i];

	  j = 0;

	  hit[i] = 0;

	  while(j < 5000)
	  {
		  // seekg: Sets the position of the next character to be extracted from the input stream.
		  fp.seekg( j *(int) sizeof( int ), ios::beg );
		  //printf( "seekg( %d INT, begin ), pos=%d\n",i, (int) fp.tellg() );
		  fp.read( (char *) &val, (int) sizeof(int));
		  //printf( "val=%d\n\n", val );

		  j++;

		  if(temp == val)
		  {
			  hit[i] = 1;
			  break;
		  }
	  }
  }

  GetLocalTime( &end );

  // Time taken to close file stream should not be included in comparison.
  fp.close();

  // ************************************** Print Output **************************************************

  printf( "%02d:%02d:%02d:%06d\n", beg.wHour,
    beg.wMinute, beg.wSecond, beg.wMilliseconds * 1000 );
  
  printf( "%02d:%02d:%02d:%06d\n", end.wHour,
    end.wMinute, end.wSecond, end.wMilliseconds * 1000 );

  i = 0;
  while ( i < 10000)
  {
	  printf( "%6d: %d\n", s[i], hit[i]);
	  i++;
  }

  return 1;
}