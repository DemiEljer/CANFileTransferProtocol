#ifndef CANFTP_SOFWAREVERSION_H_
#define CANFTP_SOFWAREVERSION_H_

#include "CanFTP_BaseTypes_Defines.h"

typedef struct _CanFTP_SofwareVersion
{
    // Страршая часть версии
    CanFTP_DeviceSoftwareVersionPart_t higherPart;
    // Средняя часть версии
    CanFTP_DeviceSoftwareVersionPart_t middlePart;
    // Младшая часть версии
    CanFTP_DeviceSoftwareVersionPart_t lowerPart;

} CanFTP_SofwareVersion_t;

#endif // CANFTP_SOFWAREVERSION_H_
