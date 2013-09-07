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

  int k[5000];	// Key array
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

  // ****************************************************************************************

  // You must record how much time it takes to open and load key.pc.db, and to then determine the presence or absence of each si.
  GetLocalTime( &beg );

  // Copy Keys values from database to k[5000] array
  fp.open( "key.pc.db", ios::in | ios::binary);

  fp.read( (char *) &val, (int) sizeof(int));

  i = 0;
  while( !fp.eof())
  {
	  k[i++] = val;
	  fp.read( (char *) &val, (int) sizeof(int));
  }

  fp.close();

  // ****************************************** Check if key exists**********************************************

  for(i = 0; i < 10000; i++)
  {
	  temp = s[i];

	  j = 0;
	  while(j < 5000)
	  {
		  if(temp == k[j++])
		  {
			  hit[i] = 1;
			  break;
		  }
		  else
		  {
			  hit[i] = 0;
		  }
	  }
  }

  GetLocalTime( &end );

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