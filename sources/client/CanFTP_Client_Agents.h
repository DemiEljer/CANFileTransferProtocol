#ifndef CANFTP_CLIENT_AGENTS_H_
#define CANFTP_CLIENT_AGENTS_H_

#include "CanFTP_Client_Agents_Defines.h"

/*
    Сброс контроллера процесса Ping
*/
void CanFTP_Client_Agent_PingControler_Reset(CanFTP_Client_Agent_PingControler_t *agent);
/*
    Проверка, что были получены подтверждения на все запросы
*/
CanFTP_Logical_t CanFTP_Client_Agent_PingControler_AllAcksAreReceived(CanFTP_Client_Agent_PingControler_t *agent);
/*
    Сброс контроллера процесса Ping
*/
void CanFTP_Client_LogicLockController_Reset(CanFTP_Client_LogicLockController_t *agent);

#endif // CANFTP_CLIENT_AGENTS_H_
