/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_DeviceConfig.h"

/*
    Сбросить конфигурацию
*/
void CanFTP_DeviceConfig_Reset(CanFTP_DeviceConfig_t* configuration)
{
    configuration->identifier = 0;
    configuration->serialNumber = 0;
    configuration->type = 0;
    CanFTP_SoftwareVersion_Reset(&(configuration->softVersion));
}
