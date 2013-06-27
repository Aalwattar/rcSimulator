/*
 * rcsSimulator.c
 *
 *  Created on: Jun 24, 2013
 *      Author: aalwatta
 */
#include <stdio.h>
#include <stdlib.h>
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

static int TypeIndexMap[8]={
		 0,	ARCH_1,ARCH_2,ARCH_3,ARCH_4,ARCH_5,ARCH_6,ARCH_7} ;

void initPRRsConfigTime(unsigned int * prrTime, int noPRRs);



	int InitSimulator()
	{
		return 1;
	}

	int CleanSimulator()
	{

		return 1;
	}

	int RunSimulator(struct SimData *simData, struct SimResults *simResults)
	{
		struct node *dFG;
		int dFGsize = 0;
		struct PEs pEs;
		Queue ReadyQ;
		static struct Counts counters = { 0, 0, 0, 0, 0, 0 };
		int i = 0, w;


		CreateAllPEs(&pEs, NO_OF_PRRS, NO_OF_GPPS);
		initPRRsConfigTime(&PRRConfigValues[0][0], 5);
		ReadyQ = CreateQueue(MAX_QUEUE_TASKS);
		Init_TasksTypes();

		i = simData->dFGID;
		dFGsize = DFGArray[i].size;
		dFG = CreateDFG(dFGsize);

		if (dFGsize!=simData->noOfNodes)
		{
			fprintf(stderr,"The number of nodes does not match The DFG I am using !!!! \n ");
			exit(EXIT_FAILURE);
		}

		CopyDFG(dFG, DFGArray[i].dfg, dFGsize);
/* FIXME temporary measure till  Architecture get implemented by code  */
						int l;
						for (l = 0; l < dFGsize; l++) {
							SetNodeTaskType(dFG, l,( TypeIndexMap[GetNodeTaskType(dFG,l)-1]+ simData->typeData[l]));
						}


		InitProcessors(pEs.HWPE->pe, pEs.HWPE->size, TypeHW);
		InitProcessors(pEs.SWPE->pe, pEs.SWPE->size, TypeSW);
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
				 * TODO Cannot remember Why I have these three states!! Might be  duplicated
				 * code!! Double check if they are necessary and rewrite the code if necessary.
				 */
				switch (State) {
				case CfgDone:
#if  RCS_SCHED_I
					RunTaskSI(ReadyQ,&counters;
#elif RCS_SCHED_III
					RCSchedIII(ReadyQ, &counters, &pEs, dFG);
#elif RCS_SCHED_II
					RCSchedII(ReadyQ, &counters, &pEs,dFG);
#endif
					Ticker(&pEs, dFG);
					State = TaskDone;
					break;
					case TaskDone:
						AddTask2Queue(ReadyQ, dFG, dFGsize);

#if  RCS_SCHED_I
						RunTaskSI(ReadyQ,&counters);
#elif RCS_SCHED_III

						RCSchedIII(ReadyQ, &counters, &pEs, dFG);
#elif RCS_SCHED_II

						RCSchedII(ReadyQ, &counters, &pEs);
#endif
						Ticker(&pEs, dFG);
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

			//print_DFG(dFG);
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
		CleanAllPEs(&pEs);
		DisposeQueue(ReadyQ);
		return 0;
	}

void initPRRsConfigTime(unsigned int * prrTime, int noPRRs) {
		int i;
		for (i = 0; i < noPRRs; ++i) {

			InitPRRConfigTime(i, prrTime[i]);

		}
	}

