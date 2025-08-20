#include "CanFTP_Server_Session_Messages_Handlers.h"

/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Server_Session_MessageRecieve_SessionControl(CanFTP_Server_Session_t* session, CanFTP_Message_Client_SessionControl_t* message)
{
    CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_CheckClientIsInSession(session, message->deviceCode);

    if (client != CANFTP_NULL)
    {
        if (message->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_REGISTRATIONACK)
        {
            if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_REGISTRATING)
            {
                if (message->registrationAck.status == CANFTP_CLIENTSESSIONACKSTATUS_SUCCESS)
                {
                    // Подтверждение регистрации
                    client->statuses.isRegistrated = CANFTP_TRUE;
                }
                else
                {
                    // Тут пока ничего не делаем
                }
            }
        }
        else if (message->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATIONACK)
        {
            if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_CONFIGURING)
            {
                if (message->configurationAck.status == CANFTP_CLIENTSESSIONACKSTATUS_SUCCESS)
                {
                    // Чтение ограничения на размер блока файла
                    CanFTP_Server_Session_FileConfiguration_InitMaxBlockLength(&(session->fileConfiguration), message->configurationAck.maxBlockLength);
                    // Подтверждение конфигурации сессии
                    client->statuses.isConfigurated = CANFTP_TRUE;
                }
                else
                {
                    // Тут пока ничего не делаем
                }
            }
        }
        else if (message->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_STARTSESSIONACK)
        {
            if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_STARTING)
            {
                if (message->startSessionAck.status == CANFTP_CLIENTSESSIONACKSTATUS_SUCCESS)
                {
                    // Подтверждение начала сессии
                    client->statuses.sessionIsStarted = CANFTP_TRUE;
                }
                else
                {
                    // Тут пока ничего не делаем
                }
            }
        }
        else if (message->messageType == CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_FINISHSESSIONACK)
        {
            // Подтверждение окончания сессии
            client->statuses.sessionIsFinished = CANFTP_TRUE;
            // Чтение статуса сессии
            CanFTP_Server_Session_Client_SetSessionStatus(client, message->finishSessionAck.sessionStatus);
        }
    }
}
/*
    Обработчик приема сообщения BlockControl
*/
void CanFTP_Server_Session_MessageRecieve_BlockControl(CanFTP_Server_Session_t* session, CanFTP_Message_Client_BlockControl_t* message)
{
    CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_CheckClientIsInSession(session, message->deviceCode);

    if (client != CANFTP_NULL)
    {
        if (message->messageType == CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_START)
        {
            if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_BLOCK_STARTING)
            {
                client->statuses.isBlockStarted = CANFTP_TRUE;
            }
        }
        else if (message->messageType == CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_FINISH)
        {
            if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_BLOCK_FINISHING)
            {
                client->statuses.isNextBlockReady = CANFTP_TRUE;
            }
        }
    }
}
/*
    Обработчик приема сообщения SubBlocksStatuses
*/
void CanFTP_Server_Session_MessageRecieve_SubBlocksStatuses(CanFTP_Server_Session_t* session, CanFTP_Message_Client_SubBlocksStatuses_t* message)
{
    CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_CheckClientIsInSession(session, message->deviceCode);

    if (client != CANFTP_NULL)
    {
        if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_BLOCK_FINISHING)
        {
            CanFTP_Session_FileBlock_MergeSubblocksFlags(&(session->agents.blockController.fileBlock), message->subblocksReciecedFlags);

            // Выставление статуса обработки блока
            client->statuses.blockStatus = CANFTP_CLIENTBLOCKHANDLINGSTATUS_SUBBLOCKESMISSING;

            // Отправка сообщения подтверждения
            CanFTP_Server_Session_MessageSend_BlockFeedbackAck(session, client);

            client->statuses.isBlockFinished = CANFTP_TRUE;
        }
    }
}
/*
    Обработчик приема сообщения BlockCRC
*/
void CanFTP_Server_Session_MessageRecieve_BlockCRC(CanFTP_Server_Session_t* session, CanFTP_Message_Client_BlockCRC_t* message)
{
    CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_CheckClientIsInSession(session, message->deviceCode);

    if (client != CANFTP_NULL)
    {
        if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_BLOCK_FINISHING)
        {
            if (CanFTP_Session_FileBlock_CompareCRC(session->agents.blockController.fileBlockCRC, message->crcElements))
            {
                // Выставление статуса обработки блока
                client->statuses.blockStatus = CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKISRECIEVED;
            }
            else
            {
                // Выставление статуса обработки блока
                client->statuses.blockStatus = CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKREPEAT;
                // Выставление запроса на сброс флагов обработки блока
                session->agents.blockController.requests.blockFramesFlagsResetRequst = CANFTP_TRUE;
            }
            // Отправка сообщения подтверждения
            CanFTP_Server_Session_MessageSend_BlockFeedbackAck(session, client);

            client->statuses.isBlockFinished = CANFTP_TRUE;
        }
    }
}

/*
    Обработчик отправки сообщения Registration
*/
void CanFTP_Server_Session_MessageSend_Registration(CanFTP_Server_Session_t* session)
{
    CanFTP_Message_Server_Registration_t messageModel;
    // Обработка сообщения
    {
        CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_ClientsCollection_GetClientByIndex(&(session->clients), session->agents.registrationConrtoller.clientIndex);

        if (client != CANFTP_NULL)
        {
            messageModel.sessionCode = client->assosiation.sessionCode; 
            messageModel.deviceSerial = client->serverClient->configuration.serialNumber;
            messageModel.deviceCode = client->assosiation.deviceCode;  
        }
        else
        {
            CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);
        }
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Server_Registration_Pack(&(messageModel), &(messageCan));
        CanFTP_Server_Session_MessageSend(session, &(messageCan));
    }
}
/*
    Обработчик отправки сообщения SessionControl
*/
void CanFTP_Server_Session_MessageSend_SessionControl(CanFTP_Server_Session_t* session)
{
    CanFTP_Message_Server_SessionControl_t messageModel;
    // Обработка сообщения
    {
        messageModel.sessionCode = session->code;

        if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_CONFIGURING)
        {
            messageModel.messageType = CANFTP_MESSAGE_SERVER_SESSIONCONTROL_CONFIGURATION;

            messageModel.configuration.pageIndex = session->fileConfiguration.pageIndex;
            messageModel.configuration.fileLength = session->fileConfiguration.fileLength;
            messageModel.configuration.repeateAckCount = session->configuration.repeateAckCount;
            messageModel.configuration.repeateInterval = session->configuration.repeateAckInterval;
        }
        else if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_STARTING)
        {
            messageModel.messageType = CANFTP_MESSAGE_SERVER_SESSIONCONTROL_START;
        }
        else if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_FINISHING)
        {
            messageModel.messageType = CANFTP_MESSAGE_SERVER_SESSIONCONTROL_FINISH;

            messageModel.finish.sessionStatus = session->status;
            CanFTP_SoftwareVersion_Copy(&(messageModel.finish.newSoftVersion), &(session->fileConfiguration.newSoftVersion));
        }
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Server_SessionControl_Pack(&(messageModel), &(messageCan));
        CanFTP_Server_Session_MessageSend(session, &(messageCan));
    }
}
/*
    Обработчик отправки сообщения ClientDelete
*/
void CanFTP_Server_Session_MessageSend_DeleteClient(CanFTP_Server_Session_t* session, CanFTP_Server_Session_Client_t* client)
{
    CanFTP_Message_Server_SessionControl_t messageModel;
    // Обработка сообщения
    {
        messageModel.sessionCode = session->code;
        messageModel.messageType = CANFTP_MESSAGE_SERVER_SESSIONCONTROL_DELETECLIENT;

        messageModel.deleteClient.sessionStatus = client->statuses.sessionStatus;
        messageModel.deleteClient.deviceCode = client->assosiation.deviceCode;
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Server_SessionControl_Pack(&(messageModel), &(messageCan));
        CanFTP_Server_Session_MessageSend(session, &(messageCan));
    }
}
/*
    Обработчик отправки сообщения BlockControl
*/
void CanFTP_Server_Session_MessageSend_BlockControl(CanFTP_Server_Session_t* session)
{
    CanFTP_Message_Server_BlockControl_t messageModel;
    // Обработка сообщения
    {
        messageModel.sessionCode = session->code;

        if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_BLOCK_STARTING)
        {
            messageModel.messageType = CANFTP_MESSAGE_SERVER_BLOCKCONTROL_START;

            messageModel.start.blockIndex = session->agents.blockController.fileBlock.index;
            messageModel.start.blockLength = session->agents.blockController.fileBlock.length;
        }
        else if (CanFTP_Server_Session_GetState(session) == CANFTP_SESSIONSTATE_BLOCK_FINISHING)
        {
            messageModel.messageType = CANFTP_MESSAGE_SERVER_BLOCKCONTROL_FINISH;

            messageModel.finish.blockIndex = session->agents.blockController.fileBlock.index;
        }
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Server_BlockControl_Pack(&(messageModel), &(messageCan));
        CanFTP_Server_Session_MessageSend(session, &(messageCan));
    }
}
/*
    Обработчик отправки сообщения BlockFeedbackAck
*/
void CanFTP_Server_Session_MessageSend_BlockFeedbackAck(CanFTP_Server_Session_t* session, CanFTP_Server_Session_Client_t* client)
{
    CanFTP_Message_Server_BlockControl_t messageModel;
    // Обработка сообщения
    {
        messageModel.sessionCode = session->code;
        messageModel.messageType = CANFTP_MESSAGE_SERVER_BLOCKCONTROL_FEEDBACKACK;

        messageModel.feedbackAck.deviceCode = client->assosiation.deviceCode;
        messageModel.feedbackAck.blockHandlingStatus = client->statuses.blockStatus;
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Server_BlockControl_Pack(&(messageModel), &(messageCan));
        CanFTP_Server_Session_MessageSend(session, &(messageCan));
    }
}
/*
    Обработчик отправки сообщения DataFrame
*/
void CanFTP_Server_Session_MessageSend_DataFrame(CanFTP_Server_Session_t* session)
{
    CanFTP_Message_Server_DataFrame_t messageModel;
    // Обработка сообщения
    {
        messageModel.sessionCode = session->code;
        messageModel.frameIndex = session->agents.blockController.currentFrameIndex;
        CanFTP_Session_FileBlock_GetFrame(&(session->agents.blockController.fileBlock)
            , session->agents.blockController.currentFrameIndex
            , messageModel.data);
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Server_DataFrame_Pack(&(messageModel), &(messageCan));
        CanFTP_Server_Session_MessageSend(session, &(messageCan));
    }
}
/*
    Отправить сообщение
*/
void CanFTP_Server_Session_MessageSend(CanFTP_Server_Session_t* session, CanFTP_CanMessage_t* message)
{
    if (session->callbacks.sendMessageCallback != CANFTP_NULL
        && session->server != CANFTP_NULL)
    {
        session->callbacks.sendMessageCallback(session->server, message);
    }
}
