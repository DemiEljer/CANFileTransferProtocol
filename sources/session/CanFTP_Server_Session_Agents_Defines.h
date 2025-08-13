#ifndef CANFTP_SERVER_SESSION_AGENTS_DEFINES_H_
#define CANFTP_SERVER_SESSION_AGENTS_DEFINES_H_

#include "CanFTP_TimeHandlers.h"
#include "CanFTP_IterationsHandler.h"
#include "CanFTP_Server_Session_Params.h"

/*
    Контроллер регистрации клиентов
*/
typedef struct _CanFTP_Server_Session_Agent_RegistrationConroller
{
    // Индекс регистрируемого клиента
    CanFTP_DeviceCode_t clientIndex;
    // Интервал времени отправки сообщения регистрации
    CanFTP_TimeTrigger_t sendMessageTrigger;
    // Счетчик повторной отправки сообщения регистрации
    CanFTP_IterationsHandler_t sendMessageCounter;

} CanFTP_Server_Session_Agent_RegistrationConroller_t;
/*
    Контроллер отправки сообщений управления сессией
*/
typedef struct _CanFTP_Server_Session_Agent_SessionConroller
{
    // Интервал времени отправки сообщения регистрации
    CanFTP_TimeTrigger_t sendMessageTrigger;
    // Счетчик повторной отправки сообщения регистрации
    CanFTP_IterationsHandler_t sendMessageCounter;

} CanFTP_Server_Session_Agent_SessionConroller_t;
/*
    Контроллер отправки сообщений блока файла
*/
typedef struct _CanFTP_Server_Session_Agent_BlockConroller
{
    // Интервал времени отправки сообщения регистрации
    CanFTP_TimeTrigger_t sendMessageTrigger;
    // Счетчик повторной отправки сообщения регистрации
    CanFTP_IterationsHandler_t sendMessageCounter;

} CanFTP_Server_Session_Agent_BlockConroller_t;

#endif // CANFTP_SERVER_SESSION_AGENTS_DEFINES_H_
