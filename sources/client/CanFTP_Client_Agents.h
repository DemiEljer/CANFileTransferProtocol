/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

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
void CanFTP_Client_Agent_LogicLockController_Reset(CanFTP_Client_Agent_LogicLockController_t *agent);
/*
    Сброс контроллера управления сессией
*/
void CanFTP_Client_Agent_SessionController_Reset(CanFTP_Client_Agent_SessionController_t *agent);
/*
    Сброс контроллера управления приемом блока
*/
void CanFTP_Client_Agent_SessionController_ResetBlock(CanFTP_Client_Agent_SessionController_t *agent);
/*
    Сброс контроллера управления приемом блоком при переходе к новому блоку
*/
void CanFTP_Client_Agent_SessionController_NewBlockReset(CanFTP_Client_Agent_SessionController_t *agent);
/*
    Установить статус состояния сессии
*/
void CanFTP_Client_Agent_SessionController_SetSessionStatus(CanFTP_Client_Agent_SessionController_t *agent, CanFTP_SessionStatus_t status);
/*
    Сброс флагов управления при переходе в другое состояние
*/
void CanFTP_Client_Agent_SessionController_ResetBetweenStates(CanFTP_Client_Agent_SessionController_t *agent);

#endif // CANFTP_CLIENT_AGENTS_H_
