/*
 * tmpInitData.h
 *
 *  Created on: Jun 18, 2013
 *      Author: aalwatta
 */

#ifndef TMPINITDATA_H_
#define TMPINITDATA_H_
#include "data.h"
#include  "PlatformConfig.h"
/*
 * TODO this file need to be deleted and replaced with external
 * Configuration files.
 *
 */

void setTaskTypeDataHWDelay(int id, unsigned int value);
 void setTaskTypeDataSWDelay(int id, unsigned int value);
 unsigned int getTaskTypeDataHWDelay(int id);
 unsigned int getTaskTypeDataSWDelay(int id);

 void setTaskTypeDataConfTime(int id, unsigned int value);
 void setTaskTypeDataTaskType(int id, unsigned int value);
 unsigned int getTaskTypeDataConfTime(int id);
 unsigned int getTaskTypeDataTaskType(int id);
 void setTaskTypeDataArchNo(int id, unsigned int value);
 unsigned int getTaskTypeDataArchNo(int id);

#endif /* TMPINITDATA_H_ */
