/*
 * TempInitData.c
 *
 *  Created on: Jun 18, 2013
 *      Author: aalwatta
 */
#include "PlatformConfig.h"
#include "tmpInitData.h"
#include "data.h"
#include <stdlib.h>
#include <stdio.h>
struct architcture
{
	unsigned int HWdelay;
	unsigned int SWdelay;
	int tasktype;
	int archno;
	enum Mode mode;
	unsigned int confTime;


};


static  struct architcture TaskTypeData[BUFFER_SIZE];
//                                      =
//
//                                    {
//
//        {.HWdelay=0 , .SWdelay=0}, /* Dummy Data  should never be used*/
//
//        {.HWdelay=5 , .SWdelay=50},
//		{.HWdelay=10 , .SWdelay=50}, /* Task 1 */
//		{.HWdelay=10 , .SWdelay=50},
//
//		{.HWdelay=5 , .SWdelay=50},/* Task 2 */
//		{.HWdelay=20 , .SWdelay=50},
//		{.HWdelay=10 , .SWdelay=50}, /* 6 */
//		{.HWdelay=15 , .SWdelay=50},
//
//
//		{.HWdelay=15 , .SWdelay=50},/* Task 3 */
//		{.HWdelay=75 , .SWdelay=50},
//		{.HWdelay=20 , .SWdelay=50},/* 10 */
//		{.HWdelay=30 , .SWdelay=50},
//		{.HWdelay=20 , .SWdelay=50},
//
//		{.HWdelay=40 , .SWdelay=50},/* Task 4 */
//		{.HWdelay=60 , .SWdelay=50},
//
//		{.HWdelay=5 , .SWdelay=50},/* Task 5 */
//		{.HWdelay=10 , .SWdelay=50}, /* 16 */
//		{.HWdelay=10 , .SWdelay=50},
//
//		{.HWdelay=15 , .SWdelay=50}, /* Task 6 */
//		{.HWdelay=30 , .SWdelay=50},
//		{.HWdelay=20 , .SWdelay=50}, /* 20 */
//
//		{.HWdelay=20 , .SWdelay=50}, /* Task 7 */
//		{.HWdelay=40 , .SWdelay=50},
//
//		{.HWdelay=20 , .SWdelay=50}, /* Task 8 */
//		{.HWdelay=30 , .SWdelay=50}
//                                    };

 void setTaskTypeDataHWDelay(int id, unsigned int value)
 {
	 if (0>value)
	 {
		 fprintf(stderr,"ERROR[setTaskTypeDataHWDelay] can't assign negative number \n");
		 exit(EXIT_FAILURE);
	 }

	 TaskTypeData[id].HWdelay=value;

 }
 void setTaskTypeDataSWDelay(int id, unsigned int value)
 {
	 if (0>value)
	 {
		 fprintf(stderr,"ERROR[setTaskTypeDataSWDelay] can't assign negative number \n");
		 exit(EXIT_FAILURE);
	 }

	 TaskTypeData[id].SWdelay=value;

 }

 unsigned int getTaskTypeDataHWDelay(int id)
 {
	 if (0>id )
	 {
		 fprintf(stderr,"ERROR[getTaskTypeDataHWDelay] can't assign negative number %d -> %d\n",id,TaskTypeData[id].HWdelay);
		 exit(EXIT_FAILURE);
	 }

	 return TaskTypeData[id].HWdelay;

 }
 unsigned int getTaskTypeDataSWDelay(int id)
 {
	 if (0>id )
	 {
		 fprintf(stderr,"ERROR[getTaskTypeDataSWDelay] can't assign negative number \n");
		 exit(EXIT_FAILURE);
	 }

	return TaskTypeData[id].SWdelay;

 }


 void setTaskTypeDataConfTime(int id, unsigned int value)
 {
	 if (0>value)
	 {
		 fprintf(stderr,"ERROR[setTaskTypeDataConfTime] can't assign negative number \n");
		 exit(EXIT_FAILURE);
	 }

	 TaskTypeData[id].confTime=value;

 }
 void setTaskTypeDataTaskType(int id, unsigned int value)
 {
	 if (0>value)
	 {
		 fprintf(stderr,"ERROR[setTaskTypeDataTaskType] can't assign negative number \n");
		 exit(EXIT_FAILURE);
	 }

	 TaskTypeData[id].tasktype=value;

 }

 unsigned int getTaskTypeDataConfTime(int id)
 {
	 if (0>id )
	 {
		 fprintf(stderr,"ERROR[getTaskTypeDataConfTime] can't assign negative number %d -> %d\n",id,TaskTypeData[id].HWdelay);
		 exit(EXIT_FAILURE);
	 }

	 return TaskTypeData[id].confTime;

 }
 unsigned int getTaskTypeDataTaskType(int id)
 {
	 if (0>id )
	 {
		 fprintf(stderr,"ERROR[getTaskTypeDataTaskType] can't assign negative number \n");
		 exit(EXIT_FAILURE);
	 }

	return TaskTypeData[id].tasktype;

 }

 void setTaskTypeDataArchNo(int id, unsigned int value)
 {
	 if (0>value)
	 {
		 fprintf(stderr,"ERROR[setTaskTypeDataArchNo] can't assign negative number \n");
		 exit(EXIT_FAILURE);
	 }

	 TaskTypeData[id].archno=value;

 }

 unsigned int getTaskTypeDataArchNo(int id)
 {
	 if (0>id )
	 {
		 fprintf(stderr,"ERROR[getTaskTypeDataArchNo] can't assign negative number %d -> %d\n",id,TaskTypeData[id].HWdelay);
		 exit(EXIT_FAILURE);
	 }

	 return TaskTypeData[id].archno;

 }
