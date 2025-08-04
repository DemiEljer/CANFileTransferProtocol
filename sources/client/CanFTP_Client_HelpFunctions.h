#ifndef CANFTP_CLIENT_HELPFUNCTIONS_H_
#define CANFTP_CLIENT_HELPFUNCTIONS_H_

#include "CanFTP_Client_Defines.h"

/*
    Проверить, находится ли клиент в состоянии активной сессии
*/
CanFTP_Logical_t CanFTP_Client_IsInActiveSession(CanFTP_Client_t* client);
/*
    Проверить условие, что конкретное сообщение относится к активной сессии клиента 
*/
CanFTP_Logical_t CanFTP_Client_CheckIfMessageCorrespondingToActiveSession(CanFTP_Client_t* client, CanFTP_SessionCode_t sessionCode);
/*
    Проверить, находится ли клиент в состоянии Ping
*/
CanFTP_Logical_t CanFTP_Client_IsPinging(CanFTP_Client_t* client);
/*
    Проверить, находится ли протокол в активном состоянии
*/
CanFTP_Logical_t CanFTP_Client_IsInActiveState(CanFTP_Client_t* client);
/*
    Получить состояние клиента
*/
CanFTP_ClientState_t CanFTP_Client_GetState(CanFTP_Client_t *client);

#endif // CANFTP_CLIENT_HELPFUNCTIONS_H_
