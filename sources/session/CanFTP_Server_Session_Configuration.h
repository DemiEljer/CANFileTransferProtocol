#ifndef CANFTP_SERVER_SESSION_CONFIGURATION_H_
#define CANFTP_SERVER_SESSION_CONFIGURATION_H_

#include "CanFTP_TimeHandlers.h"
#include "CanFTP_IterationsHandler.h"

/*
    Структура конфигурации сессии на стороне сервера
*/
typedef struct _CanFTP_Server_Session_Configuration
{
    // Интервалы времени отправки сообщений при регистрации клиентов
    CanFTP_TimeInterval_t registrationInterval;
    // Количество повторений отправки сообщений при регистрации клиентов
    CanFTP_IterationCounter_t registrationRepeateCount;
    // Интервалы времени отправки сообщений при управлении сессией
    CanFTP_TimeInterval_t sessionControlInterval;
    // Количество повторений отправки сообщений при управлении сессей
    CanFTP_IterationCounter_t sessionControlRepeateCount;
    // Количество повторений отправки блока
    CanFTP_SendingRepeate_t repeateBlockCount;
    // Интервалы времени отправки сообщений при управлении процессом отправки блока
    CanFTP_TimeInterval_t blockControlInterval;
    // Количество повторений отправки сообщений при управлении процессом отправки блока
    CanFTP_IterationCounter_t blockControlRepeateCount;
    // Интервалы времени отправки кадров блока
    CanFTP_TimeInterval_t frameSendingInterval;
    // Интервалы времени отправки подтверждений со стороны клиента
    CanFTP_SendingRepeateInterval_t repeateAckInterval;
    // Количество повторений отправки сообщений от клиентов
    CanFTP_SendingRepeate_t repeateAckCount;

} CanFTP_Server_Session_Configuration_t;

/*
    Сбросить конфигурацию
*/
void CanFTP_Server_Session_Configuration_Reset(CanFTP_Server_Session_Configuration_t* configuration);
/*
    Скопировать конфигурацию
*/
void CanFTP_Server_Session_Configuration_Copy(CanFTP_Server_Session_Configuration_t* to, CanFTP_Server_Session_Configuration_t* from);

#endif // CANFTP_SERVER_SESSION_CONFIGURATION_H_
