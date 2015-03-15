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

  if(argc>2) // Si l'utilisateur renseigne au moins un argument en plus du ./poisson_exe
  	{
   
    	if(string(argv[1]).compare("-load")==0) 
    		{
      
      		if(argc>4 && string(argv[3]).compare("-save")==0)
      			{
							gaia=new Gaia(argv[4],argv[2]); // On souhaite exécuter une partie en mode load_et_save
      			}
      			
      		else
      			{
							gaia=new Gaia((char)0,argv[2]); // On souhaite exécuter une partie en mode load
						}
    		}
    		
    	if(string(argv[1]).compare("-save")==0)
    		{

      		if(argc>4 && string(argv[3]).compare("-load")==0)
      			{
							gaia=new Gaia(argv[2],argv[4]); // On souhaite exécuter une partie en mode load_et_save
      		 	}
      		 	
      		else
      			{
							gaia=new Gaia((char)1,argv[2]); // On souhaite exécuter une partie en mode save
						}
    		}
  	}
 else
 	{
    gaia=new Gaia(); // si aucun argument n'est renseigné on exécute une partie par défaut
  }
  
  gaia->commencer();
  
  delete gaia;

  exit( EXIT_SUCCESS );
}



// =======================================================================
//                         Define Miscellaneous Functions
// =======================================================================
