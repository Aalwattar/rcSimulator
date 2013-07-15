/*
 * main.c
 *
 *  Created on: Jun 24, 2013
 *      Author: aalwatta
 */

#include <stdio.h>
#include <stdlib.h>
#include <confuse.h>
#include  "rcsSimulator.h"
#include  "common_interfaces.h"
#include "architecture_library.h"
#include "hardware_library.h"
#include "dfg_library.h"
#include "argparse.h"


int main(int argc,  char* argv[] )
{
    Common_Interface input_data;
    Hardware hardware;
    struct ArgData argdata;
    InitArgdatar(&argdata);
	if (parseArgs(argc, argv, &argdata)) {
		fprintf(stderr, "Exiting..\n\n");
		exit(EXIT_FAILURE);
	}
    
    initArchLibrary(argdata.fnArch, &(input_data.archlib));
    initDFG(argdata.fnDFG, &(input_data.dfg));
    initHardwareLibrary(argdata.fnPRR, &hardware);
    
    input_data.setup = hardware.setups[argdata.PRRsSet];
    
	struct SimData simData={.typeData={0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0}};
	struct SimResults simResults;

	simData.noOfNodes=input_data.dfg.num_nodes;
	INIT_FLAGS(simData.flags);
    if (argdata.printDFG)
    {
    	SET_FLAG_VALUE(simData.flags,PRINT_DFG_DATA);
    }
	InitSimulator(&input_data);
	RunSimulator(&simData,&simResults);




	fprintf(stdout, "Process complete in {%d} cycles \n", simResults.totalTime);
	fprintf(stdout,
			"Number of configuration= %u SW Busy [%u] HW Busy [%u]\n",
			simResults.noOfConfiguration, simResults.noSWBusyCounter,
			simResults.noHWBusyCounter);
	fprintf(stdout,
			"SW2HW MIG [%u]  HW2SW Mig [%u] #of Reuse [%u]  #SW tasks [%u]\n",
			simResults.noSW2HWMigration, simResults.noHW2SWMigration, simResults.noOfReuse,
			simResults.noOfSWTasks);
	fprintf(stdout, "Total Power is {%d}  \n", simResults.power);
	fprintf(stdout,"_________________________________________________________________\n");
	RunSimulator(&simData,&simResults);

	fprintf(stdout, "Process complete in {%d} cycles \n", simResults.totalTime);
	fprintf(stdout,
			"Number of configuration= %u SW Busy [%u] HW Busy [%u]\n",
			simResults.noOfConfiguration, simResults.noSWBusyCounter,
			simResults.noHWBusyCounter);
	fprintf(stdout,
			"SW2HW MIG [%u]  HW2SW Mig [%u] #of Reuse [%u]  #SW tasks [%u]\n",
			simResults.noSW2HWMigration, simResults.noHW2SWMigration, simResults.noOfReuse,
			simResults.noOfSWTasks);
	fprintf(stdout, "Total Power is {%d}  \n", simResults.power);
	CleanSimulator();
    freeArchLibrary(&(input_data.archlib));
    freeDFG(&(input_data.dfg));
    freeHardwareLibrary(&hardware);

	return (EXIT_SUCCESS);
}
