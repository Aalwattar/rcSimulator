/*
 * main.c
 *
 *  Created on: Jun 24, 2013
 *      Author: aalwatta
 */

#include <stdio.h>
#include <stdlib.h>
#include  "rcsSimulator.h"
int main()
{
	struct SimData simData={.typeData={1,1,1,1,1,1,1,1,1,1}};
	struct SimResults simResults;

	simData.dFGID=0;
	simData.noGPP=0;
	simData.noPRR=5;
	simData.noOfNodes=10;

	InitSimulator();
	RunSimulator(&simData,&simResults);
	CleanSimulator();


	fprintf(stdout, "Process complete in {%d} cycles \n", simResults.totalTime);
	fprintf(stdout,
			"Number of configuration= %u SW Busy [%u] HW Busy [%u]\n",
			simResults.noOfConfiguration, simResults.noSWBusyCounter,
			simResults.noHWBusyCounter);
	fprintf(stdout,
			"SW2HW MIG [%u]  HW2SW Mig [%u] #of Reuse [%u]  #SW tasks [%u]\n",
			simResults.noSW2HWMigration, simResults.noHW2SWMigration, simResults.noOfReuse,
			simResults.noOfSWTasks);

	return (EXIT_SUCCESS);
}


