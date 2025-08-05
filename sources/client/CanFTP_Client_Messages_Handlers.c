#include "CanFTP_Client_Messages_Handlers.h"

/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_Ping(void* invoker, CanFTP_Message_Server_Ping_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);
    // Проверка версии протокола
    if (message->protocolVersion == CANFTP_PROTOCOL_VERSION)
    {
        // Подтверждение верификации версии протокола
        client->agents.pingController.statuses.isProtocolVersionVerified = CANFTP_TRUE;

        if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_IDLE)
        {
            if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_NOTERMINATION)
            {
                if (client->control.pingPermition == CANFTP_TRUE)
                {
                    // Запрос на переход в состояние ответа на запрос Ping
                    client->agents.pingController.requsts.requestPinging = CANFTP_TRUE;
                    // Запрос на блокирование логики
                    client->agents.logicLockController.requsts.requestToLockLogic = CANFTP_TRUE;
                }
            }
            else if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_TERMINATE)
            {
                if (client->control.pingPermition == CANFTP_TRUE)
                {
                    // Запрос на переход в состояние ответа на запрос Ping
                    client->agents.pingController.requsts.requestPinging = CANFTP_TRUE;
                }
            }
            CanFTP_TimeTrigger_Update(&(client->agents.pingController.coolingDownTrigger));
        }
        else if (CanFTP_Client_IsPinging(client))
        {
            if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_RELEASE)
            {
                // Запрос на прекращение процесса Ping
                client->agents.pingController.requsts.requestPinging = CANFTP_FALSE;
                // Снятие запроса на блокировку логики
                client->agents.logicLockController.requsts.requestToLockLogic = CANFTP_FALSE;
            }
            CanFTP_TimeTrigger_Update(&(client->agents.pingController.coolingDownTrigger));
        }
        // Проверка случая активной сессии
        else if (CanFTP_Client_IsInActiveState(client))
        {
            if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_RELEASE)
            {
                // Снятие запроса на блокировку логики
                client->agents.logicLockController.requsts.requestToLockLogic = CANFTP_FALSE;

                if (CanFTP_Client_IsInActiveSession(client))
                {
                    // Запрос на выключение сессии
                    client->agents.sessionController.requsts.requestSession = CANFTP_FALSE;
                }
            }
        }
        else
        {
            // Ничего не делаем
        }
    }
    else
    {
        client->agents.pingController.statuses.isProtocolVersionVerified = CANFTP_FALSE;
    }
}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_PingResponseAck(void* invoker, CanFTP_Message_Server_PingResponseAck_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);

    if (CanFTP_Client_IsPinging(client))
    {
        client->agents.pingController.pingResponsesAck[message->responseType] = CANFTP_TRUE;

        CanFTP_TimeTrigger_Update(&(client->agents.pingController.coolingDownTrigger));
    }
}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_Registration(void* invoker, CanFTP_Message_Server_Registration_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);
    // В случае, если совпадает серийный номер, переходим в активную сессию
    if (message->deviceSerial == client->devicveConfig.serialNumber
        && !CanFTP_Client_IsInActiveSession(client)
        && client->agents.sessionController.requsts.requestSession != CANFTP_TRUE
        && client->agents.pingController.statuses.isProtocolVersionVerified == CANFTP_TRUE
        && client->control.sessionStartPermition == CANFTP_TRUE)
    {
        client->agents.sessionController.requsts.requestSession = CANFTP_TRUE;
        client->agents.logicLockController.requsts.requestToLockLogic = CANFTP_TRUE;

        client->agents.sessionController.clientAssosiation.sessionCode = message->sessionCode;
        client->agents.sessionController.clientAssosiation.deviceCode = message->deviceCode;

        // Сброс счетчика количества повторений подтверждений приема
        CanFTP_IterationsHandler_Reset(&(client->agents.sessionController.repeateAckCounter));
    }
}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_SessionControl(void* invoker, CanFTP_Message_Server_SessionControl_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);
    // Проверка условий обработки данного сообшения
    if (CanFTP_Client_CheckIfMessageCorrespondingToActiveSession(client, message->sessionCode))
    {
        if (CanFTP_Client_GetState(client) != CANFTP_CLIENTSTATE_SESSION_FINISHED)
        {
            if (message->messageType == CANFT_MESSAGE_SERVER_SESSIONCONTROL_CONFIGURATION)
            {
                if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_REGISTRATED)
                {
                    // Инициализация параметров сессии
                    client->agents.sessionController.session.configuration.fileLength = message->configuration.fileLength;
                    client->agents.sessionController.session.configuration.pageIndex = message->configuration.pageIndex;
                    client->agents.sessionController.session.configuration.repeateAckCount = message->configuration.repeateAckCount;
                    client->agents.sessionController.session.configuration.repeateBlockCount = message->configuration.repeateBlockCount;
                    client->agents.sessionController.session.configuration.repeateInterval = message->configuration.repeateInterval;
                    // Выставление запроса на начало конфигурации
                    client->agents.sessionController.requsts.configurationRequest = CANFTP_TRUE;

                    // Сброс счетчика количества повторений подтверждений приема
                    CanFTP_IterationsHandler_Reset(&(client->agents.sessionController.repeateAckCounter));
                }
                // Ошибка посоедовательности сообщение
                else
                {
                    CanFTP_Client_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_WRONGSEQUENCE);
                }
            }
            else if (message->messageType == CANFT_MESSAGE_SERVER_SESSIONCONTROL_START)
            {
                if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_CONFIGURED)
                {
                    // Выставление запроса на начало сессии
                    client->agents.sessionController.requsts.startRequest = CANFTP_TRUE;

                    // Сброс счетчика количества повторений подтверждений приема
                    CanFTP_IterationsHandler_Reset(&(client->agents.sessionController.repeateAckCounter));
                }
                // Ошибка посоедовательности сообщение
                else
                {
                    CanFTP_Client_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_WRONGSEQUENCE);
                }
            }
            else if (message->messageType == CANFT_MESSAGE_SERVER_SESSIONCONTROL_FINISH)
            {
                if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY
                    || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_STARTED)
                {
                    // Выставление запроса на окончание сессии
                    client->agents.sessionController.requsts.stopRequest = CANFTP_TRUE;
                    CanFTP_SofwareVersion_Copy(&(client->agents.sessionController.newSoftVersion), &(message->finish.newSoftVersion));
                }
                // Ошибка посоедовательности сообщение
                else
                {
                    CanFTP_Client_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_WRONGSEQUENCE);
                }
            }
        }
    }
}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_BlockControl(void* invoker, CanFTP_Message_Server_BlockControl_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);

    // Проверка условий обработки данного сообшения
    if (CanFTP_Client_CheckIfMessageCorrespondingToActiveSession(client, message->sessionCode))
    {
        if (CanFTP_Client_GetState(client) != CANFTP_CLIENTSTATE_SESSION_FINISHED)
        {
            if (message->messageType == CANFT_MESSAGE_SERVER_BLOCKCONTROL_START)
            {
                if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_STARTED
                    || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY)
                {
                    // В случае нарущения последовательности индексов блоков, выставляется ошибка
                    if (message->finish.blockIndex != client->agents.sessionController.session.block.index
                        && (message->finish.blockIndex + 1) != client->agents.sessionController.session.block.index)
                    {
                        CanFTP_Client_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_BLOCKSEQUENCEFAILED);
                    }
                    // В случае, если передается следущий блок, при условии, что не обработан предыдущий 
                    else if ((message->finish.blockIndex + 1) == client->agents.sessionController.session.block.index
                             && client->agents.sessionController.statuses.blockHandlingStatus != CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKISRECIEVED)
                    {
                        CanFTP_Client_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_BLOCKUNFINISHED);
                    }
                    else
                    {
                        // Сброс статуса приема блока, если передается следующий блок
                        if ((message->finish.blockIndex + 1) == client->agents.sessionController.session.block.index)
                        {
                            client->agents.sessionController.statuses.blockHandlingStatus = CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKREPEAT;
                            client->agents.sessionController.statuses.newBlockIsHandling = CANFTP_TRUE;
                        }

                        client->agents.sessionController.requsts.startBlockRequest = CANFTP_TRUE;

                        CanFTP_Session_FileBlock_Configure(&(client->agents.sessionController.session.block)
                            , message->start.blockIndex
                            , message->start.blockLength);

                        // Сброс счетчика количества повторений подтверждений приема
                        CanFTP_IterationsHandler_Reset(&(client->agents.sessionController.repeateAckCounter));
                    }
                }
                // Ошибка посоедовательности сообщение
                else
                {
                    CanFTP_Client_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_WRONGSEQUENCE);
                }
            }
            else if (message->messageType == CANFT_MESSAGE_SERVER_BLOCKCONTROL_FINISH)
            {
                if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_BLOCK_RECIEVING)
                {
                    client->agents.sessionController.requsts.stopBlockRequest = CANFTP_TRUE;
                    // В случае несовпадения индексов блоков, выставляется ошибка
                    if (message->finish.blockIndex != client->agents.sessionController.session.block.index)
                    {
                        CanFTP_Client_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_BLOCKSEQUENCEFAILED);
                    }

                    // Сброс счетчика количества повторений подтверждений приема
                    CanFTP_IterationsHandler_Reset(&(client->agents.sessionController.repeateAckCounter));
                }
                // Ошибка посоедовательности сообщение
                else
                {
                    CanFTP_Client_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_WRONGSEQUENCE);
                }
            }
            else if (message->messageType == CANFT_MESSAGE_SERVER_BLOCKCONTROL_FEEDBACKACK)
            {
                if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_BLOCK_FINISHED)
                {
                    // Проверка, что ответ принадлежит данному клиенту
                    if (message->feedbackAck.deviceCode == client->agents.sessionController.clientAssosiation.deviceCode)
                    {
                        client->agents.sessionController.requsts.blockFinishAckRecieved = CANFTP_TRUE;
                        client->agents.sessionController.statuses.blockHandlingStatus = message->feedbackAck.blockHandlingStatus;
                    }
                }
                // Ошибка посоедовательности сообщение
                else
                {
                    CanFTP_Client_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_WRONGSEQUENCE);
                }
            }
        }
    }
}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_DataFrame(void* invoker, CanFTP_Message_Server_DataFrame_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);

    // Проверка условий обработки данного сообшения
    if (CanFTP_Client_CheckIfMessageCorrespondingToActiveSession(client, message->sessionCode))
    {
        if (CanFTP_Client_GetState(client) != CANFTP_CLIENTSTATE_SESSION_FINISHED)
        {
            if (client->agents.sessionController.statuses.blockHandlingStatus != CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKISRECIEVED)
            {
                client->agents.sessionController.requsts.recievingBlockRequest = CANFTP_TRUE;

                CanFTP_Session_FileBlock_SetFrame(&(client->agents.sessionController.session.block)
                    , message->frameIndex
                    , message->data);
            }
        }
    }
}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageSend_PingResponse(CanFTP_Client_t* client)
{
    CanFTP_Message_Client_PingResponse_t messageModel;
    // Обработка сообщения
    {
        // Инициализация кода устройства, полученного из серийного номера
        messageModel.deviceCode = (client->devicveConfig.serialNumber & 0xFFFF) + ((client->devicveConfig.serialNumber >> 8) & 0xFFFF);

        if (client->agents.pingController.requestedMessageIndex == 1)
        {
            messageModel.messageType = CANFT_MESSAGE_CLIENT_BLOCKCONTROL_RESPONSE1;

            messageModel.response1.deviceSerial = client->devicveConfig.serialNumber;
            messageModel.response1.deviceIdentifier = client->devicveConfig.identifier;
            messageModel.response1.deviceType = client->devicveConfig.type;
        }  
        else if (client->agents.pingController.requestedMessageIndex == 2)
        {
            messageModel.messageType = CANFT_MESSAGE_CLIENT_BLOCKCONTROL_RESPONSE2;

            messageModel.response2.deviceSerial = client->devicveConfig.serialNumber;
            messageModel.response2.deviceSoftVersion.lowerPart = client->devicveConfig.softVersion.lowerPart;
            messageModel.response2.deviceSoftVersion.middlePart = client->devicveConfig.softVersion.middlePart;
            messageModel.response2.deviceSoftVersion.higherPart = client->devicveConfig.softVersion.higherPart;
        }
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Client_PingResponse_Pack(&(messageModel), &(messageCan));
        CanFTP_Client_MessageSend(client, &(messageCan));
    }
}
/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Client_MessageSend_SessionControl(CanFTP_Client_t* client)
{
    CanFTP_Message_Client_SessionControl_t messageModel;
    // Обработка сообщения
    {
        // Инициализация параметров ассоциации клиента с сессией
        messageModel.sessionCode = client->agents.sessionController.clientAssosiation.sessionCode;
        messageModel.deviceCode = client->agents.sessionController.clientAssosiation.deviceCode;

        if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_REGISTRATED)
        {
            messageModel.messageType = CANFT_MESSAGE_CLIENT_SESSIONCONTROL_REGISTRATIONACK;

            messageModel.registrationAck.status = CANFTP_CLIENTSESSIONACKSTATUS_SUCCESS;
        }
        else if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_CONFIGURED)
        {
            messageModel.messageType = CANFT_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATIONACK;

            messageModel.configurationAck.status = CANFTP_CLIENTSESSIONACKSTATUS_SUCCESS;
            messageModel.configurationAck.maxBlockLength = CANFTP_FILEBLOCK_LENGTH;
        }
        else if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_STARTED)
        {
            messageModel.messageType = CANFT_MESSAGE_CLIENT_SESSIONCONTROL_STARTSESSIONACK;

            messageModel.startSessionAck.status = CANFTP_CLIENTSESSIONACKSTATUS_SUCCESS;
        }
        else if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_FINISHED)
        {
            messageModel.messageType = CANFT_MESSAGE_CLIENT_SESSIONCONTROL_FINISHSESSIONACK;
            // В случае, если выставлен статус ошибки, то выставляем флаг неуспешного окончания сессии
            if (client->agents.sessionController.statuses.sessionStatus != CANFTP_SESSIONSTATUS_OK)
            {
                messageModel.finishSessionAck.status = CANFTP_CLIENTSESSIONACKSTATUS_FAIL;
            }
            else
            {
                messageModel.finishSessionAck.status = CANFTP_CLIENTSESSIONACKSTATUS_SUCCESS;
            }
            messageModel.finishSessionAck.sessionStatus = client->agents.sessionController.statuses.sessionStatus;
        }
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Client_SessionControl_Pack(&(messageModel), &(messageCan));
        CanFTP_Client_MessageSend(client, &(messageCan));
    }
}
/*
    Обработчик приема сообщения BlockControl
*/
void CanFTP_Client_MessageSend_BlockControl(CanFTP_Client_t* client)
{
    CanFTP_Message_Client_BlockControl_t messageModel;
    // Обработка сообщения
    {
        messageModel.sessionCode = client->agents.sessionController.clientAssosiation.sessionCode;
        messageModel.deviceCode = client->agents.sessionController.clientAssosiation.deviceCode;

        if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_BLOCK_STARTED)
        {
            // Ничего не запроняем
        }
        else if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY)
        {
            messageModel.finishBlockAck.blockHandlingStatus = client->agents.sessionController.statuses.blockHandlingStatus;
        }
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Client_BlockControl_Pack(&(messageModel), &(messageCan));
        CanFTP_Client_MessageSend(client, &(messageCan));
    }
}
/*
    Обработчик приема сообщения SubBlocksStatuses
*/
void CanFTP_Client_MessageSend_SubBlocksStatuses(CanFTP_Client_t* client)
{
    CanFTP_Message_Client_SubBlocksStatuses_t messageModel;
    // Обработка сообщения
    {
        messageModel.sessionCode = client->agents.sessionController.clientAssosiation.sessionCode;
        messageModel.deviceCode = client->agents.sessionController.clientAssosiation.deviceCode;

        uint8_t i = 0;
        // Перенос флагов приема субблоков
        {
            for (i = 0; i < CANFTP_FILEBLOCK_SUBBLOCKSCOUNT; i++)
            {
                messageModel.subblocksReciecedFlags[i] = client->agents.sessionController.session.block.subblocksFlags[i];
            }
        }
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Client_SubBlocksStatuses_Pack(&(messageModel), &(messageCan));
        CanFTP_Client_MessageSend(client, &(messageCan));
    }
}
/*
    Обработчик приема сообщения BlockCRC
*/
void CanFTP_Client_MessageSend_BlockCRC(CanFTP_Client_t* client)
{
    CanFTP_Message_Client_BlockCRC_t messageModel;
    // Обработка сообщения
    {
        messageModel.sessionCode = client->agents.sessionController.clientAssosiation.sessionCode;
        messageModel.deviceCode = client->agents.sessionController.clientAssosiation.deviceCode;

        uint8_t i = 0;
        // Перенос значений CRC-суммы
        {
            for (i = 0; i < CANFTP_FILEBLOCK_CRCLENGTH; i++)
            {
                messageModel.crcElements[i] = client->agents.sessionController.statuses.blockCRC[i];
            }
        }
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Client_BlockCRC_Pack(&(messageModel), &(messageCan));
        CanFTP_Client_MessageSend(client, &(messageCan));
    }
}
/*
    Отправить сообщение
*/
void CanFTP_Client_MessageSend(CanFTP_Client_t* client, CanFTP_CanMessage_t* message)
{
    if (client->callbacks.sendMessageCallback != 0)
    {
        client->callbacks.sendMessageCallback(client, message);
    }
}
