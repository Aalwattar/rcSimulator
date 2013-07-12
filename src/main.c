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


int main()
{
    Common_Interface input_data;
    Hardware hardware;
    
    initArchLibrary("/export/home/shares/sharegroup1/common_interfaces/src/conf/arch.conf", &(input_data.archlib));
    initDFG("/export/home/shares/sharegroup1/conf/B1_dfgTemplate10_5_2.conf", &(input_data.dfg));
//    initDFG("/export/home/shares/sharegroup1/conf/B1_dfgTemplate25_10_2.conf", &(input_data.dfg));

    initHardwareLibrary("/export/home/shares/sharegroup1/common_interfaces/src/conf/prr.conf", &hardware);
    
    input_data.setup = hardware.setups[2];
    
	struct SimData simData={.typeData={0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0}};
	struct SimResults simResults;


	simData.noOfNodes=10;
    
	InitSimulator(&input_data);
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
    
    
    freeArchLibrary(&(input_data.archlib));
    freeDFG(&(input_data.dfg));
    freeHardwareLibrary(&hardware);

	return (EXIT_SUCCESS);
}
