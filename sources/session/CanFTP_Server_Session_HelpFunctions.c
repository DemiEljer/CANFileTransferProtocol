#include "CanFTP_Server_Session_HelpFunctions.h"

/*
    Получить состояние сессии
*/
CanFTP_SessionState_t CanFTP_Server_Session_GetState(CanFTP_Server_Session_t *session)
{
    return *(session->state);
}
