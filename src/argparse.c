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
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include "argparse.h"
#include "PlatformConfig.h"


void displayVersion()
{
	fprintf(stdout,"Scheduler Simulator Version [%s] \n ",VERSION_NUMBER);
	exit(EXIT_SUCCESS);
}

char displaymsg []={" usage  %s  [options] prog-and-args\n\n"
		"tool-selection option, with default in [ ]:\n\n"
		"-h --help \t\t show this message\n"
		"-V --version \t\t display version \n"
		"-v --verbose \t\t show node execution details  \n"
		"-d --dfg-file  \t\t followed by the DFG file to be processed [dfg.conf]\n"
		"-a --arch-file \t\t followed by architecture file to be processed [arch.conf]\n"
		"-p --prr-file  \t\t followed by PRR files (contains PRR combination) [prr.conf]\n"
		"-s --prr-set \t\t integer to pick which PRR set to use from the PRR file [0]\n\n"};

void displayHelp(char *programName)
{
	fprintf(stdout, displaymsg,programName);
}
/*
	 * * FIXME  THIS FUNCTION NEED TO BE CHANGED COMPLETELY
	 * Does not check any error conditions,
	 * Does not check getting the right number of nodes,
	 * Need to be in this order..
	 * -n 10 -d 30 -p 33 -u 0 -s 233 -t 1 2 3 4 5
	 */

static struct option long_options[] = {
     {"dfg-file",   required_argument,   	 	  0,  'd' },
     {"arch-file",	required_argument,     		  0,  'a' },
     {"prr-file",  required_argument,			  0,  'p' },
     {"prr-set",   required_argument, 				  0,  's' },
     {"verbose",   no_argument,						  0,  'v' },
     {"version",   no_argument, 					  0,  'V' },
     {"help",      no_argument, 					  0,  'h' },
     {0,           0,                 0,  0   }
 };

  int  parseArgs(int argc,  char *argv[],struct ArgData * argdatar){



	   int c;
	   opterr = 0;
	int long_index=0;
	   while ((c = getopt_long(argc, argv, "d:a:p:s:vV",
			   	   long_options,&long_index)) != -1)
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
		   case 'h':
			   displayHelp(argv[0]);
			   exit(EXIT_SUCCESS);
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
