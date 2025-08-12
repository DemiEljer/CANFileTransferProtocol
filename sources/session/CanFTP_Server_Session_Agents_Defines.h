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
    CanFTP_IterationCounter_t sendMessageCounter;

} CanFTP_Server_Session_Agent_RegistrationConroller_t;

#endif // CANFTP_SERVER_SESSION_AGENTS_DEFINES_H_
