/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Client_Agents.h"

/*
    Сброс контроллера процесса Ping
*/
void CanFTP_Client_Agent_PingControler_Reset(CanFTP_Client_Agent_PingControler_t *agent)
{
    uint8_t i = 0;
    for (i = 0; i < CANFT_MESSAGE_CLIENT_PINGRESPONSE_COUNT; i++)
    {
        agent->pingResponsesAck[i] = CANFTP_FALSE;
    }
    CanFTP_TimeTrigger_SetInterval(&(agent->reapeateSendingTrigger), CANFTP_CLIENT_PING_MININTERVAL);
    CanFTP_TimeTrigger_Reset(&(agent->reapeateSendingTrigger));
    CanFTP_TimeTrigger_SetInterval(&(agent->coolingDownTrigger), CANFTP_CLIENT_PING_TIMEOUT);
    CanFTP_TimeTrigger_Reset(&(agent->coolingDownTrigger));
    agent->requestedMessageIndex = 0x00;
    agent->requsts.requestPinging = CANFTP_FALSE;
}
/*
    Проверка, что были получены подтверждения на все запросы
*/
CanFTP_Logical_t CanFTP_Client_Agent_PingControler_AllAcksAreReceived(CanFTP_Client_Agent_PingControler_t *agent)
{
    uint8_t i = 0;
    for (i = 0; i < CANFT_MESSAGE_CLIENT_PINGRESPONSE_COUNT; i++)
    {
        if (agent->pingResponsesAck[i] != CANFTP_TRUE)
        {
            return CANFTP_FALSE;
        }
    }

    return CANFTP_TRUE;
}
/*
    Сброс контроллера процесса Ping
*/
void CanFTP_Client_Agent_LogicLockController_Reset(CanFTP_Client_Agent_LogicLockController_t *agent)
{
    agent->requsts.requestToLockLogic = CANFTP_FALSE;
    agent->statuses.isLocked = CANFTP_FALSE;
}
/*
    Сброс контроллера управления сессией
*/
void CanFTP_Client_Agent_SessionController_Reset(CanFTP_Client_Agent_SessionController_t *agent)
{
    uint8_t i = 0;

    agent->requsts.requestSession = CANFTP_FALSE;
    agent->requsts.configurationRequest = CANFTP_FALSE;
    agent->requsts.startRequest = CANFTP_FALSE;
    agent->requsts.stopRequest = CANFTP_FALSE;
    agent->requsts.startBlockRequest = CANFTP_FALSE;
    agent->requsts.recievingBlockRequest = CANFTP_FALSE;
    agent->requsts.stopBlockRequest = CANFTP_FALSE;
    agent->requsts.blockFinishAckRecieved = CANFTP_FALSE;
    agent->requsts.configurationPartIndex = CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART0;
    agent->statuses.sessionStatus = CANFTP_SESSIONSTATUS_OK;
    agent->statuses.sessionHasBeenVerified = CANFTP_FALSE;
    agent->statuses.allBlocksFramesWereRecieved = CANFTP_FALSE;
    agent->statuses.blockHandlingStatus = CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKREPEAT;
    agent->statuses.resultFileLength = 0;
    agent->statuses.newBlockIsHandling = CANFTP_TRUE;
    agent->statuses.clientHasBeenRegistrated = CANFTP_FALSE;
    // Сброс CRC-суммы
    {
        for (i = 0; i < CANFTP_FILEBLOCK_CRCLENGTH; i++)
        {
            agent->statuses.blockCRC[i] = 0;
        }
    }
    agent->clientAssosiation.deviceCode = 0;
    agent->clientAssosiation.sessionCode = 0;
    CanFTP_TimeTrigger_SetInterval(&(agent->repeateAckTrigger), CANFTP_CLIENT_SEESION_REPEATEACK_INTERVAL);
    CanFTP_TimeTrigger_Reset(&(agent->repeateAckTrigger));
    CanFTP_TimeTrigger_SetInterval(&(agent->lostConnectionTrigger), CANFTP_CLIENT_SEESION_LOSTCONNECTION_TIMEOUT);
    CanFTP_TimeTrigger_Reset(&(agent->lostConnectionTrigger));
    CanFTP_IterationsHandler_SetMaxCount(&(agent->repeateAckCounter), CANFTP_CLIENT_SEESION_REPEATEACK_COUNT);
    CanFTP_IterationsHandler_Reset(&(agent->repeateAckCounter));
    CanFTP_Client_Session_Reset(&(agent->session));
}
/*
    Сброс контроллера управления приемом блока
*/
void CanFTP_Client_Agent_SessionController_ResetBlock(CanFTP_Client_Agent_SessionController_t *agent)
{
    // Сброс флагов управления чтением блока
    agent->requsts.startBlockRequest = CANFTP_FALSE;
    agent->requsts.recievingBlockRequest = CANFTP_FALSE;
    agent->requsts.stopBlockRequest = CANFTP_FALSE;
    agent->requsts.blockFinishAckRecieved = CANFTP_FALSE;
}
/*
    Сброс контроллера управления приемом блоком при переходе к новому блоку
*/
void CanFTP_Client_Agent_SessionController_NewBlockReset(CanFTP_Client_Agent_SessionController_t *agent)
{
    uint8_t i = 0;

    agent->statuses.allBlocksFramesWereRecieved = CANFTP_FALSE;
    // Сброс CRC-суммы
    {
        for (i = 0; i < CANFTP_FILEBLOCK_CRCLENGTH; i++)
        {
            agent->statuses.blockCRC[i] = 0;
        }
    }

    CanFTP_Session_FileBlock_ResetFramesFlags(&(agent->session.block));
}
/*
    Установить статус состояния сессии
*/
void CanFTP_Client_Agent_SessionController_SetSessionStatus(CanFTP_Client_Agent_SessionController_t *agent, CanFTP_SessionStatus_t status)
{
    // Изменить статус в случае, если до этого сессия находилась в рабочем состоянии
    if (agent->statuses.sessionStatus == CANFTP_SESSIONSTATUS_OK)
    {
        agent->statuses.sessionStatus = status;
    }
    // В случае возникновения ошибки, убирается запрос на активацию сессии
    if (agent->statuses.sessionStatus != CANFTP_SESSIONSTATUS_OK)
    {
        agent->requsts.requestSession = CANFTP_FALSE;
    }
}
/*
    Сброс флагов управления при переходе в другое состояние
*/
void CanFTP_Client_Agent_SessionController_ResetBetweenStates(CanFTP_Client_Agent_SessionController_t *agent)
{
    // Сброс счетчика количества повторных отправок
    CanFTP_IterationsHandler_Reset(&(agent->repeateAckCounter));
    // Сброс метки времени повторной отправки
    CanFTP_TimeTrigger_Reset(&(agent->repeateAckTrigger));
}
/*
    Обновить параметры времени
*/
void CanFTP_Client_Agent_SessionController_UpdateTimeParams(CanFTP_Client_Agent_SessionController_t *agent, CanFTP_SendingRepeateInterval_t interval, CanFTP_SendingRepeate_t maxCount)
{
    // Установка максимального количества повторений
    CanFTP_IterationsHandler_SetMaxCount(&(agent->repeateAckCounter), maxCount);
    // Установка итервала времени повторной отправки
    CanFTP_TimeTrigger_SetInterval(&(agent->repeateAckTrigger), interval);
}
