/*
 * rcsSimulato+1r.c
 *
 *  Created on: Jun 24, 2013
 *      Author: aalwatta
 */
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "data.h"
#include "processors.h"
#include "reconfiguration.h"
#include "PlatformConfig.h"
#include "queue.h"
#include "schedulers.h"
#include "displayResults.h"
#include "drawTaskAllocation.h"
#include "argparse.h"
#include "tmpInitData.h"
#include "rcsSimulator.h"
#include "common_interfaces.h"
#include "io.h"

//static int TypeIndexMap[8] = { 0, ARCH_1, ARCH_2, ARCH_3, ARCH_4, ARCH_5,
//                               ARCH_6, ARCH_7
//                             };

struct global_rcsSimualator {
	int noPRRs;
	int noGPPs;
	struct PEs pEs;
	struct node *dFG;
	int dfgSize;
	Architecture_Library *arch;
	int tableIndexMap[BUFFER_SIZE];

};

static struct global_rcsSimualator Global_local;
void CalculateTaskIndex(Common_Interface*);





int InitSimulator(Common_Interface *mn) { /*FIXME fix tmprrval */


	unsigned int *pRRConfigValues;
	Global_local.dfgSize = mn->dfg.num_nodes;
	Global_local.noGPPs = mn->setup.num_gpps;
	Global_local.noPRRs = mn->setup.num_prrs;
	Global_local.arch = &mn->archlib;

   unsigned int tmpprrval[100];
   int i;
	for (i = 0; i < Global_local.noPRRs; i++) {
		tmpprrval[i] = mn->setup.prr_config_time[i];
	}

	CalculateTaskIndex(mn);
	initTaskTypeData(mn);
	Global_local.dFG = CreateDFG(Global_local.dfgSize);
	convertDFG(Global_local.dFG, &(mn->dfg));
	pRRConfigValues = init_pRRrConfigValues(tmpprrval, Global_local.noPRRs);
	//qsort(pRRConfigValues, Global_local.noPRRs, sizeof(unsigned int), cmpfunc);
	sortDecend (pRRConfigValues, Global_local.noPRRs );
	CreateAllPEs(&Global_local.pEs, Global_local.noPRRs, Global_local.noGPPs);
	initPRRsConfigTime(pRRConfigValues, Global_local.noPRRs);

	free(pRRConfigValues);
	return 1;
}

int CleanSimulator() {
	CleanAllPEs(&Global_local.pEs);
	/*TODO Clear Global_local.dfg*/

	return 1;
}

int RunSimulator(struct SimData *simData, struct SimResults *simResults) {

	struct node *dFG;
	int dFGsize = 0;

	Queue ReadyQ;
	static struct Counts counters = { 0, 0, 0, 0, 0, 0 };
	int w;

	ReadyQ = CreateQueue(MAX_QUEUE_TASKS);
	Init_TasksTypes(Global_local.arch->num_tasks, Global_local.noPRRs);

	// i = simData->dFGID;
	//  dFGsize = DFGArray[i].size;
	dFGsize = Global_local.dfgSize;
	dFG = CreateDFG(dFGsize);

	if (dFGsize != simData->noOfNodes) {
		fprintf(stderr,
				"The number of nodes does not match The DFG I am using !!!! \n");
		exit(EXIT_FAILURE);
	}

	CopyDFG(dFG, Global_local.dFG, dFGsize);
	/* FIXME temporary measure till  Architecture get implemented by code
	 * Can Run must be implemented here  */
	int l;
	for (l = 0; l < dFGsize; l++) {
		SetNodeTaskType(dFG, l,
				(Global_local.tableIndexMap[GetNodeTaskType(dFG, l) - 1]
						+ simData->typeData[l]));
	}

	updateCanRun(dFG,dFGsize,Global_local.noPRRs);

	InitProcessors(Global_local.pEs.HWPE->pe, Global_local.pEs.HWPE->size,
			TypeHW);
	InitProcessors(Global_local.pEs.SWPE->pe, Global_local.pEs.SWPE->size,
			TypeSW);
	RstCounters(&counters);

	for (w = 0; w < NO_OF_DFG_REP; w++) {
#if  SCHED_I_EN
		Init_Rand_Prr(AVAILABLE_PRR);
#endif

#if DEBUG_PRINT
		fprintf(stdout, "Processing: DFG[%d] with [%d] nodes ITERATION [%d] \n",
				i, dFGsize, w);
#endif
		/*
		 * Reset Things before every DFG
		 */

		MakeEmpty(ReadyQ);
		/* Reset Configuration Counter */
		ResetConfigCount();
		setTaskCounter(dFGsize);
		reinitTasksTable(dFGsize);
		ResetTimer();
		RstCounters(&counters);

		/*
		 * Start Processing DFG
		 */

		do {
			/*
			 * TODO Cannot remember Why I have these three states!! Might be
			 * duplicated code!! Double check if they are necessary and rewrite
			 * the code if necessary.
			 */
			switch (State) {
			case CfgDone:
#if  RCS_SCHED_I
				RunTaskSI(ReadyQ,&counters;
#elif RCS_SCHED_III
				RCSchedIII(ReadyQ, &counters, &Global_local.pEs, dFG);
#elif RCS_SCHED_II
				RCSchedII(ReadyQ, &counters, &pEs,dFG);
#endif
				Ticker(&Global_local.pEs, dFG);
				State = TaskDone;
				break;
			case TaskDone:
				AddTask2Queue(ReadyQ, dFG, dFGsize);

#if  RCS_SCHED_I
				RunTaskSI(ReadyQ,&counters);
#elif RCS_SCHED_III

				RCSchedIII(ReadyQ, &counters, &Global_local.pEs, dFG);
#elif RCS_SCHED_II

				RCSchedII(ReadyQ, &counters, &pEs);
#endif
				Ticker(&Global_local.pEs, dFG);
				State = TaskDone;
				break;
			case Start:
				AddTask2Queue(ReadyQ, dFG, dFGsize);

				State = TaskDone;
				break;
			case None:
				break;
			default:
				fprintf(stderr, "ERROR: Unknown state ...\n");
				break;
			}

		} while (getTaskCounter());

		print_DFG(dFG, Global_local.noPRRs);
		simResults->noHW2SWMigration = counters.HW2SWMig;
		simResults->noHWBusyCounter = counters.busyCounterHW;
		simResults->noOfConfiguration = GetConfigCount();
		simResults->noOfReuse = counters.ReuseCounter;
		simResults->noOfSWTasks = counters.SWTasksCounter;
		simResults->noSW2HWMigration = counters.SW2HWMig;
		simResults->noSWBusyCounter = counters.busyCounterSW;
		simResults->totalTime = GetTimer();

	}
	CleanDFG(dFG);
	CleanTasksTable();

	DisposeQueue(ReadyQ);
	return 0;
}

void CalculateTaskIndex(Common_Interface* mn) {
	int i;
	int sum = 0;
	for (i = 0; i < mn->archlib.num_tasks; ++i) {

		Global_local.tableIndexMap[i] = sum;
		sum += mn->archlib.task[i].num_impl;
	//	fprintf(stderr, "\t\tarchlib[%d]\n", Global_local.tableIndexMap[i]);
	}

}
