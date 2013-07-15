/*
 * argparse.c
 *
 *  Created on: Jun 11, 2013
 *      Author: aalwatta
 */

#ifndef ARGPARSE_C_
#define ARGPARSE_C_


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "argparse.h"
#include "PlatformConfig.h"


void displayVersion()
{
	fprintf(stdout,"Scheduler Simulator Version [%s] \n ",VERSION_NUMBER);
	exit(EXIT_SUCCESS);
}

/*
	 * * FIXME  THIS FUNCTION NEED TO BE CHANGED COMPLETELY
	 * Does not check any error conditions,
	 * Does not check getting the right number of nodes,
	 * Need to be in this order..
	 * -n 10 -d 30 -p 33 -u 0 -s 233 -t 1 2 3 4 5
	 */

  int  parseArgs(int argc,  char *argv[],struct ArgData * argdatar){



	   int c;
	   opterr = 0;

	   while ((c = getopt(argc, argv, "d:a:p:s:vV")) != -1)
		   switch (c) {
		   case 'a':
			   strcpy( argdatar->fnArch,optarg);
			   break;
		   case 'd':
			  strcpy( argdatar->fnDFG,optarg);
			   break;

		   case 'p':
			   strcpy( argdatar->fnPRR,optarg);
			   break;
		   case 's':
			   argdatar->PRRsSet = atoi(optarg);
			   break;
		   case 'v':
			   argdatar->printDFG=1;
			   break;
		   case 'V':
			   displayVersion();
			   break;

		   case '?':
			   if (optopt == 'a' || optopt == 'd' || optopt == 'p'
					   || optopt == 's' )
				   fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			   else if (isprint (optopt))
				   fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			   else
				   fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
			   return 1;
		   default:
			   abort();
		   }



	   return 0;
   }

  void InitArgdatar(struct ArgData *arg)
  {
  	arg->PRRsSet=0;
  	strcpy(arg->fnArch,ARCH_FILE_NAME);
  	strcpy(arg->fnDFG,DFG_FILE_NAME);
  	strcpy(arg->fnPRR,PRR_FILE_NAME);
  	arg->printDFG=0;

  }

#endif /* ARGPARSE_C_ */
