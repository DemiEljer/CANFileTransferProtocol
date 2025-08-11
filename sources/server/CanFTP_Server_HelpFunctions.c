#include "CanFTP_Server_HelpFunctions.h"

/*
    Получить состояние сервера
*/
CanFTP_ServerState_t CanFTP_Server_GetState(CanFTP_Server_t *server)
{
    return *(server->state);
}
/*
    Проверить, что в данный момент разрешено начать процесс Ping
*/
CanFTP_Logical_t CanFTP_Server_PingPermition(CanFTP_Server_t *server)
{
    return CanFTP_Server_GetState(server) == CANFTP_SERVERSTATE_IDLE
           || CanFTP_Server_GetState(server) == CANFTP_SERVERSTATE_PING;
}
/*
    Проверить, что в данный момент разрешено создать сессию
*/
CanFTP_Logical_t CanFTP_Server_CreateSessionPermition(CanFTP_Server_t *server)
{
    return CanFTP_Server_GetState(server) == CANFTP_SERVERSTATE_IDLE;
}
