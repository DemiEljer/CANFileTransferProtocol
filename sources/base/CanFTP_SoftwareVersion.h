/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SOFTWAREVERSION_H_
#define CANFTP_SOFTWAREVERSION_H_

#include "CanFTP_BaseTypes_Defines.h"

/*
    Версия файла
*/
typedef struct _CanFTP_SoftwareVersion
{
    // Страршая часть версии
    CanFTP_DeviceSoftwareVersionPart_t higherPart;
    // Средняя часть версии
    CanFTP_DeviceSoftwareVersionPart_t middlePart;
    // Младшая часть версии
    CanFTP_DeviceSoftwareVersionPart_t lowerPart;

} CanFTP_SoftwareVersion_t;

/*
    Сбросить номер версии
*/
void CanFTP_SoftwareVersion_Reset(CanFTP_SoftwareVersion_t* version);
/*
    Скопировать номер версии
*/
void CanFTP_SoftwareVersion_Copy(CanFTP_SoftwareVersion_t* to, CanFTP_SoftwareVersion_t* from);
/*
    Скопировать номер версии, если он больше
*/
void CanFTP_SoftwareVersion_CopyIfBigger(CanFTP_SoftwareVersion_t* to, CanFTP_SoftwareVersion_t* from);

#endif // CANFTP_SOFTWAREVERSION_H_
