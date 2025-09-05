/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Server_Session_Agents.h"

/*
    Сбросить контроллер регистрации
*/
void CanFTP_Server_Session_Agent_RegistrationConroller_Reset(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent)
{
    agent->clientIndex = 0;
    CanFTP_TimeTrigger_SetInterval(&(agent->sendMessageTrigger), CANFTP_SERVER_SESSION_REGISTRATION_INTERVAL);
    CanFTP_TimeTrigger_Reset(&(agent->sendMessageTrigger));
    CanFTP_IterationsHandler_SetMaxCount(&(agent->sendMessageCounter), CANFTP_SERVER_SESSION_REGISTRATION_COUNT);
    CanFTP_IterationsHandler_Reset(&(agent->sendMessageCounter));
}
/*
    Перейти к следующему клиенту
*/
CanFTP_Logical_t CanFTP_Server_Session_Agent_RegistrationConroller_MoveToNextClient(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent, CanFTP_DeviceCode_t clientsCount)
{
    CanFTP_IterationsHandler_Reset(&(agent->sendMessageCounter));

    agent->clientIndex++;

    return CanFTP_Server_Session_Agent_RegistrationConroller_CheckIfClientsLeft(agent, clientsCount);
}
/*
    Проверить, остались ли клиенты для регистрации
*/
CanFTP_Logical_t CanFTP_Server_Session_Agent_RegistrationConroller_CheckIfClientsLeft(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent, CanFTP_DeviceCode_t clientsCount)
{
    return agent->clientIndex < clientsCount;
}
/*
    Сброисть контроллер управления сессией
*/
void CanFTP_Server_Session_Agent_SessionConroller_Reset(CanFTP_Server_Session_Agent_SessionConroller_t* agent)
{
    CanFTP_TimeTrigger_Reset(&(agent->sendMessageTrigger));
    CanFTP_IterationsHandler_Reset(&(agent->sendMessageCounter));
}
/*
    Обновить параметры отправки соообщений
*/
void CanFTP_Server_Session_Agent_SessionConroller_UpdateSendingParams(CanFTP_Server_Session_Agent_SessionConroller_t* agent
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount)
{
    CanFTP_TimeTrigger_SetInterval(&(agent->sendMessageTrigger), interval);
    CanFTP_TimeTrigger_Update(&(agent->sendMessageTrigger));
    CanFTP_IterationsHandler_SetMaxCount(&(agent->sendMessageCounter), maxCount);
    CanFTP_IterationsHandler_Reset(&(agent->sendMessageCounter));
}
/*
    Сбросить контроллер блока
*/
void CanFTP_Server_Session_Agent_BlockConroller_Reset(CanFTP_Server_Session_Agent_BlockConroller_t* agent)
{
    // Сбпрос запросов
    {
        agent->requests.blockFramesFlagsResetRequst = CANFTP_FALSE;
    }
    // Сброс статусов
    {
        agent->statuses.newBlockIsHanling = CANFTP_TRUE;
    }
    CanFTP_TimeTrigger_Reset(&(agent->sendControlMessageTrigger));
    CanFTP_IterationsHandler_Reset(&(agent->sendControlMessageCounter));
    CanFTP_TimeTrigger_Reset(&(agent->sendDataMessageTrigger));
    CanFTP_IterationsHandler_Reset(&(agent->sendBlockCounter));
    agent->firstBlockByteIndex = 0;
    agent->currentFrameIndex = 0;
    agent->currentBlockIndex = 0;
    CanFTP_Session_FileBlock_Reset(&(agent->fileBlock));
    CanFTP_Session_FileBlock_ClearCRC(agent->fileBlockCRC);
}
/*
    Обновить параметры отправки соообщений
*/
void CanFTP_Server_Session_Agent_BlockConroller_UpdateSendingParams(CanFTP_Server_Session_Agent_BlockConroller_t* agent
    // Интервал времени отправки
    , CanFTP_TimeInterval_t controlInterval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t controlMaxCount
    // Интервал времени отправки
    , CanFTP_TimeInterval_t dataInterval
    // Максимальное количество итераций отправки блока
    , CanFTP_IterationCounter_t blockMaxCount)
{
    CanFTP_TimeTrigger_SetInterval(&(agent->sendControlMessageTrigger), controlInterval);
    CanFTP_TimeTrigger_Update(&(agent->sendControlMessageTrigger));
    CanFTP_IterationsHandler_SetMaxCount(&(agent->sendControlMessageCounter), controlMaxCount);
    CanFTP_IterationsHandler_Reset(&(agent->sendControlMessageCounter));
    CanFTP_TimeTrigger_SetInterval(&(agent->sendDataMessageTrigger), dataInterval);
    CanFTP_TimeTrigger_Update(&(agent->sendDataMessageTrigger));
    CanFTP_IterationsHandler_SetMaxCount(&(agent->sendBlockCounter), blockMaxCount);
}
/*
    Сбросить флаги обработки блока, если запрошено
*/
void CanFTP_Server_Session_Agent_BlockConroller_ResetBlockFlagsIfRequested(CanFTP_Server_Session_Agent_BlockConroller_t* agent)
{
    if (agent->requests.blockFramesFlagsResetRequst == CANFTP_TRUE)
    {
        CanFTP_Session_FileBlock_ResetFramesFlags(&(agent->fileBlock));
    }

    agent->requests.blockFramesFlagsResetRequst = CANFTP_FALSE;
}
/*
    Сбросить контроллер перед отправкой блока
*/
void CanFTP_Server_Session_Agent_BlockConroller_ResetBeforeBlockStart(CanFTP_Server_Session_Agent_BlockConroller_t* agent)
{
    CanFTP_FrameIndex_t frameIndex = 0;

    if (CanFTP_Session_FileBlock_GetFirstUnandledFrameIndex(&(agent->fileBlock), &(frameIndex)))
    {
        agent->currentFrameIndex = frameIndex;
    }
    else
    {   
        // В случае отработки данной логики, как минимум один кадр должен быть не обработан
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_BLOCKERROR);
    }
}
/*
    Сбросить контроллер перед отправкой нового блока
*/
CanFTP_FileLength_t CanFTP_Server_Session_Agent_BlockConroller_NextBlock(CanFTP_Server_Session_Agent_BlockConroller_t* agent)
{
    agent->requests.blockFramesFlagsResetRequst = CANFTP_FALSE;
    agent->statuses.newBlockIsHanling = CANFTP_TRUE;
    CanFTP_Session_FileBlock_ResetFramesFlags(&(agent->fileBlock));

    agent->firstBlockByteIndex += agent->fileBlock.length;
    agent->currentBlockIndex++;

    return agent->firstBlockByteIndex;
}
