#ifndef CANFTP_SERVER_CLIENT_H_
#define CANFTP_SERVER_CLIENT_H_

#include "CanFTP_DeviceConfig.h"
#include "CanFTP_Message_Client_PingResponse.h"

/*
    Структура клиента на стороне сервера (allias)
*/
typedef struct _CanFTP_Server_Client_
{
    // Структура описания устройства
    CanFTP_DeviceConfig_t configuration;
    // Флаги получения описаний со стороны клиента
    CanFTP_Logical_t configurationMessagesAck[CANFT_MESSAGE_CLIENT_PINGRESPONSE_COUNT];
    // Флаг, что клиент вовлечен в сессию в данный момнет времени
    CanFTP_Logical_t isInSession;

} CanFTP_Server_Client_t;

/*
    Сбросить клиента
*/
void CanFTP_Server_Client_Reset(CanFTP_Server_Client_t *client);
/*
    Проверить, что клиент сконфигурирован
*/
CanFTP_Logical_t CanFTP_Server_Client_IsConfigured(CanFTP_Server_Client_t *client);
/*
    Проверить, что клиент вовлечен в сессию
*/
CanFTP_Logical_t CanFTP_Server_Client_IsInSession(CanFTP_Server_Client_t *client);

#endif // CANFTP_SERVER_CLIENT_H_
