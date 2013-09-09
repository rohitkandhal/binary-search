#include <windows.h>
#include <iostream>
#include <fstream>

using std::ifstream;

using std::ios;
using std::cout;

#include <stdio.h>
#include <time.h>

int main( int argc, char *argv[] )
{
  SYSTEMTIME  beg;      // Start time
  SYSTEMTIME  end;		// End Time

  ifstream    fp;       // Input file stream
  
  int         val;      // Current input value
  int		  i, kfirst, kmid, klast;		// Index variables for keys
  int		  key;		// temporary variable

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

  // ****************************************** Check if key exists**********************************************

  i = 0;
  
  GetLocalTime( &beg );

  fp.open( "key.pc.db", ios::in | ios::binary);

  // Loop through all seek keys
  for(i = 0; i < 10000; i++)
  {
	  key = s[i];
	  
	  // Initially set hit to false, if element found then set it to true.
	  hit[i] = 0;

	  kfirst = 0;
	  klast = 4999;		
	  
	  //printf("\n******************************\n");
	  while(kfirst <= klast)
	  {
		  kmid = (kfirst + klast)/2;

		  // Read specific element.
		  fp.seekg( kmid *(int) sizeof( int ), ios::beg );
		  fp.read( (char *) &val, (int) sizeof(int));
		  
		  // printf("\n\t%d-%d-%d: %d\t", kfirst, kmid,klast, val);
		  if(val < key)
		  {
			  // Search Right side of array
			  kfirst = kmid + 1;
		  }
		  else if(val > key)
		  {
			  // Search Left side of array
			  klast = kmid - 1;
		  }
		  else
		  {
			  // Found the element
			  hit[i] = 1;
			  break;
		  }
	  }
  }

  GetLocalTime( &end );

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