#include "CanFTP_Server_Client.h"

/*
    Сбросить клиента
*/
void CanFTP_Server_Client_Reset(CanFTP_Server_Client_t *client)
{
    uint8_t i = 0;
    for (i = 0; i < CANFT_MESSAGE_CLIENT_PINGRESPONSE_COUNT; i++)
    {
        client->configurationMessagesAck[i] = CANFTP_FALSE;
    }
    CanFTP_DeviceConfig_Reset(&(client->configuration));
}
/*
    Проверить, что клиент сконфигурирован
*/
CanFTP_Logical_t CanFTP_Server_Client_IsConfigured(CanFTP_Server_Client_t *client)
{
    uint8_t i = 0;
    for (i = 0; i < CANFT_MESSAGE_CLIENT_PINGRESPONSE_COUNT; i++)
    {
        if (client->configurationMessagesAck[i] != CANFTP_TRUE)
        {
            return CANFTP_FALSE;
        }
    }

    return CANFTP_TRUE;
}
