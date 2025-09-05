/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_SoftwareVersion.h"

/*
    Сбросить номер версии
*/
void CanFTP_SoftwareVersion_Reset(CanFTP_SoftwareVersion_t* version)
{
    version->lowerPart = 0;
    version->middlePart = 0;
    version->higherPart = 0;
}
/*
    Скопировать номер версии
*/
void CanFTP_SoftwareVersion_Copy(CanFTP_SoftwareVersion_t* to, CanFTP_SoftwareVersion_t* from)
{
    to->lowerPart = from->lowerPart;
    to->middlePart = from->middlePart;
    to->higherPart = from->higherPart;
}
/*
    Скопировать номер версии, если он больше
*/
void CanFTP_SoftwareVersion_CopyIfBigger(CanFTP_SoftwareVersion_t* to, CanFTP_SoftwareVersion_t* from)
{
    if (from->higherPart > to->higherPart)
    {
        CanFTP_SoftwareVersion_Copy(to, from);
    }
    else if (from->higherPart == to->higherPart
             && from->middlePart > to->middlePart)
    {
        CanFTP_SoftwareVersion_Copy(to, from);
    }
    else if (from->higherPart == to->higherPart
             && from->middlePart == to->middlePart
             && from->lowerPart > to->lowerPart)
    {
        CanFTP_SoftwareVersion_Copy(to, from);
    }
}
