#ifndef CANFTP_SESSION_CONFIGURATION_H_
#define CANFTP_SESSION_CONFIGURATION_H_

#include "CanFTP_BaseTypes_Defines.h"

/*
    Структура конфигурации сессии
*/
typedef struct _CanFTP_Session_Configuration
{
    // Индекс страницы записи
    CanFTP_PageIndex_t pageIndex;
    // Длина передаваемого файла
    CanFTP_FileLength_t fileLength;
    // Количество повторных отправок блока файла
    CanFTP_SendingRepeate_t repeateBlockCount;
    // Количество повторных отправок сообщений подтверждения
    CanFTP_SendingRepeate_t repeateAckCount;
    // Интервал времени повторной отправки
    CanFTP_SendingRepeateInterval_t repeateInterval;
    
} CanFTP_Session_Configuration_t;

/*
    Сбросить конфигурацию сессии
*/
void CanFTP_Session_Configuratio_Reset(CanFTP_Session_Configuration_t *configuration);

#endif // CANFTP_SESSION_CONFIGURATION_H_
