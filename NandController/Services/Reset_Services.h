/*
 *  Reset_Services.h
 *
 *  Created on: Feb 27, 2026
 *  Author: Henry
 */

#ifndef SERVICES_RESET_SERVICES_H_
#define SERVICES_RESET_SERVICES_H_

#include <stdbool.h>
#include "Nand_Dri_Reset.h"

bool DeviceReset_Services(void);
bool SoftwareReset_Service(void);

#endif /* SERVICES_RESET_SERVICES_H_ */
