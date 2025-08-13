#ifndef CANFTP_SERVER_SESSION_CLIENT_DEFINES_H_
#define CANFTP_SERVER_SESSION_CLIENT_DEFINES_H_

#include "CanFTP_Server_Session_Params.h"
#include "CanFTP_Session_ClientAssosiation.h"
#include "CanFTP_Session_FileBlock_Defines.h"
#include "CanFTP_Server_Client.h"
#include "CanFTP_SessionStatus.h"
#include "CanFTP_TimeHandlers.h"
#include "CanFTP_IterationsHandler.h"
#include "stdlib.h"

/*
    Струкутура клиента на стороне сервера
*/
typedef struct _CanFTP_Server_Session_Client
{
    // Клиент сервера
    CanFTP_Server_Client_t* serverClient;
    // Ассоциация клиента и сессии
    CanFTP_Session_ClientAssosiation_t assosiation;
    // Статусы клиента
    struct {
        // Флаг, что клиент был удален
        CanFTP_Logical_t isDisposed;
        // Подтверждение факта регистрации в сессии
        CanFTP_Logical_t isRegistrated;
        // Подтверждение факта конфигурации 
        CanFTP_Logical_t isConfigurated;
        // Подтверждение факта начала сессии
        CanFTP_Logical_t sessionIsStarted;
        // Подтверждение факта окончания сессии
        CanFTP_Logical_t sessionIsFinished;
        // Статус сессии со стороны клиента
        CanFTP_SessionStatus_t sessionStatus;
        // Подтверждение начала приема блока
        CanFTP_Logical_t isBlockStarted;
        // Подтверждение окончания приема блока
        CanFTP_Logical_t isBlockFinished;
        // Подтверждение готовности принимать следущий блок
        CanFTP_Logical_t isNextBlockReady;

    } statuses;
    // Триггер потери связи с клиентом
    CanFTP_TimeTrigger_t lostConnectionTrigger;
    // Триггер повторной отправки сообщений
    CanFTP_TimeTrigger_t repeateSendingTrigger;
    // Счетчик количества повторений отправки сообщений
    CanFTP_IterationsHandler_t repeateSendingCounter;
    // Флаг, что было вызвано событие освобождения клиента
    CanFTP_Logical_t isDisposeEventCalled;

} CanFTP_Server_Session_Client_t;

#endif // CANFTP_SERVER_SESSION_CLIENT_DEFINES_H_
