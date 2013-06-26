/*
 * TempInitData.c
 *
 *  Created on: Jun 18, 2013
 *      Author: aalwatta
 */
#include "PlatformConfig.h"
#include "tmpInitData.h"
#include "data.h"

unsigned int PRRConfigValues [][50]={
		{ PRR_0_CONFIG_TIME,  PRR_1_CONFIG_TIME,
				PRR_2_CONFIG_TIME, PRR_3_CONFIG_TIME, PRR_4_CONFIG_TIME },
		{5,10,20,30,40},
		{40,40},
		{10,10,15,15,20,20},
		{10,10,15,15,20,20}
};

const struct Emulation TaskTypeData[MAX_TASKS_TYPES]=
                                    {

        {.HWdelay=0 , .SWdelay=0}, /* Dummy Data  should never be used*/

        {.HWdelay=5 , .SWdelay=50},
		{.HWdelay=10 , .SWdelay=50}, /* Task 1 */
		{.HWdelay=10 , .SWdelay=50},

		{.HWdelay=5 , .SWdelay=50},/* Task 2 */
		{.HWdelay=20 , .SWdelay=50},
		{.HWdelay=10 , .SWdelay=50}, /* 6 */
		{.HWdelay=15 , .SWdelay=50},


		{.HWdelay=15 , .SWdelay=50},/* Task 3 */
		{.HWdelay=75 , .SWdelay=50},
		{.HWdelay=20 , .SWdelay=50},/* 10 */
		{.HWdelay=30 , .SWdelay=50},
		{.HWdelay=20 , .SWdelay=50},

		{.HWdelay=40 , .SWdelay=50},/* Task 4 */
		{.HWdelay=60 , .SWdelay=50},

		{.HWdelay=5 , .SWdelay=50},/* Task 5 */
		{.HWdelay=10 , .SWdelay=50}, /* 16 */
		{.HWdelay=10 , .SWdelay=50},

		{.HWdelay=15 , .SWdelay=50}, /* Task 6 */
		{.HWdelay=30 , .SWdelay=50},
		{.HWdelay=20 , .SWdelay=50}, /* 20 */

		{.HWdelay=20 , .SWdelay=50}, /* Task 7 */
		{.HWdelay=40 , .SWdelay=50},

		{.HWdelay=20 , .SWdelay=50}, /* Task 8 */
		{.HWdelay=30 , .SWdelay=50}
                                    };

