//************************************************************************
//
//
//
//************************************************************************
 
 
 
 
// =======================================================================
//                               Include Libraries
// =======================================================================
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>

#include "Gaia.h"
#include "Population.h"
#include "Agent.h"



// =======================================================================
//                             Include Project Files
// =======================================================================



// =======================================================================
//                         Declare Miscellaneous Functions
// =======================================================================





int main( int argc, char* argv[] )
{
  srand(time(NULL));
  Gaia* gaia;

  if(argc>2)
  	{
   
    	if(string(argv[1]).compare("-load")==0)
    		{
      
      		if(argc>4 && string(argv[3]).compare("-save")==0)
      			{
							gaia=new Gaia(argv[4],argv[2]);
      			}
      			
      		else
      			{
							gaia=new Gaia((char)0,argv[2]);
						}
    		}
    		
    	if(string(argv[1]).compare("-save")==0)
    		{

      		if(argc>4 && string(argv[3]).compare("-load")==0)
      			{
							printf("load: %s\n",argv[4]);
							gaia=new Gaia(argv[2],argv[4]);
      		 	}
      		 	
      		else
      			{
							gaia=new Gaia((char)1,argv[2]);
						}
    		}
  	}
 else
 	{
    gaia=new Gaia();
  }
  
  gaia->commencer();
  delete gaia;

  exit( EXIT_SUCCESS );
}



// =======================================================================
//                         Define Miscellaneous Functions
// =======================================================================
