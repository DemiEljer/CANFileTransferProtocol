#include "CanFTP_Client_HelpFunctions.h"

/*
    Проверить, находится ли клиент в состоянии активной сессии
*/
CanFTP_Logical_t CanFTP_Client_IsInActiveSession(CanFTP_Client_t* client)
{
    return *(client->state) == CANFTP_CLIENTSTATE_SESSION_REGISTRATED
            || *(client->state) == CANFTP_CLIENTSTATE_SESSION_CONFIGURED
            || *(client->state) == CANFTP_CLIENTSTATE_SESSION_STARTED
            || *(client->state) == CANFTP_CLIENTSTATE_BLOCK_RECIEVING
            || *(client->state) == CANFTP_CLIENTSTATE_BLOCK_FINISHED
            || *(client->state) == CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY;
}
/*
    Проверить, находится ли клиент в состоянии Ping
*/
CanFTP_Logical_t CanFTP_Client_IsPinging(CanFTP_Client_t* client)
{
    return *(client->state) == CANFTP_CLIENTSTATE_PING_RESPONSING
            || *(client->state) == CANFTP_CLIENTSTATE_PING_FINISHED;
}
/*
    Проверить, находится ли протокол в активном состоянии
*/
CanFTP_Logical_t CanFTP_Client_IsInActiveState(CanFTP_Client_t* client)
{
    return CanFTP_Client_IsInActiveSession(client)
           || *(client->state) == CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE;
}
/*
    Получить состояние клиента
*/
CanFTP_ClientState_t CanFTP_Client_GetState(CanFTP_Client_t *client)
{
    return *(client->state);
}
