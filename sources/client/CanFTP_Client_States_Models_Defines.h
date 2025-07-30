#ifndef CANFTP_CLIENT_STATES_MODELS_DEFINES_H_
#define CANFTP_CLIENT_STATES_MODELS_DEFINES_H_

#include "CanFTP_TimeHandlers.h"

/*
    Структура параметров состояния на этапе PING
*/
typedef struct _CanFTP_Client_State_PING_Model
{
    // Флаги подтверждения приема сообщений Response 
    CanFTP_Logical_t pingResponsesAck[2];
    // Триггер повторной отправки сообщений в случае, если не был получен ответ
    CanFTP_TimeTrigger_t reapeateSendingTrigger;

} CanFTP_Client_State_PING_Model_t;



#endif // CANFTP_CLIENT_STATES_MODELS_DEFINES_H_
