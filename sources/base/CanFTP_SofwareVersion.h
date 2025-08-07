#ifndef CANFTP_SOFWAREVERSION_H_
#define CANFTP_SOFWAREVERSION_H_

#include "CanFTP_BaseTypes_Defines.h"

/*
    Версия файла
*/
typedef struct _CanFTP_SofwareVersion
{
    // Страршая часть версии
    CanFTP_DeviceSoftwareVersionPart_t higherPart;
    // Средняя часть версии
    CanFTP_DeviceSoftwareVersionPart_t middlePart;
    // Младшая часть версии
    CanFTP_DeviceSoftwareVersionPart_t lowerPart;

} CanFTP_SofwareVersion_t;

/*
    Сбросить номер версии
*/
void CanFTP_SofwareVersion_Reset(CanFTP_SofwareVersion_t* version);
/*
    Скопировать номер версии
*/
void CanFTP_SofwareVersion_Copy(CanFTP_SofwareVersion_t* to, CanFTP_SofwareVersion_t* from);

#endif // CANFTP_SOFWAREVERSION_H_
