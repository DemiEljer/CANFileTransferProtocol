#include "CanFTP_Server_Session_Messages_Handlers.h"

/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Server_Session_MessageRecieve_SessionControl(CanFTP_Server_Session_t* session, CanFTP_Message_Client_SessionControl_t* message)
{
    if (CanFTP_Server_Session_IsActive(session))
    {
        CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_ClientsCollection_GetClientByIndex(&(session->clients), message->deviceCode);

        if (client != CANFTP_NULL)
        {
            // Обновление метки времени потери связи с клиентом
            CanFTP_TimeTrigger_Update(&(client->lostConnectionTrigger));
        }
    }
}
/*
    Обработчик приема сообщения BlockControl
*/
void CanFTP_Server_Session_MessageRecieve_BlockControl(CanFTP_Server_Session_t* session, CanFTP_Message_Client_BlockControl_t* message)
{
    if (CanFTP_Server_Session_IsActive(session))
    {
        CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_ClientsCollection_GetClientByIndex(&(session->clients), message->deviceCode);

        if (client != CANFTP_NULL)
        {
            // Обновление метки времени потери связи с клиентом
            CanFTP_TimeTrigger_Update(&(client->lostConnectionTrigger));
        }
    }
}
/*
    Обработчик приема сообщения SubBlocksStatuses
*/
void CanFTP_Server_Session_MessageRecieve_SubBlocksStatuses(CanFTP_Server_Session_t* session, CanFTP_Message_Client_SubBlocksStatuses_t* message)
{
    if (CanFTP_Server_Session_IsActive(session))
    {
        CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_ClientsCollection_GetClientByIndex(&(session->clients), message->deviceCode);

        if (client != CANFTP_NULL)
        {
            // Обновление метки времени потери связи с клиентом
            CanFTP_TimeTrigger_Update(&(client->lostConnectionTrigger));
        }
    }
}
/*
    Обработчик приема сообщения BlockCRC
*/
void CanFTP_Server_Session_MessageRecieve_BlockCRC(CanFTP_Server_Session_t* session, CanFTP_Message_Client_BlockCRC_t* message)
{
    if (CanFTP_Server_Session_IsActive(session))
    {
        CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_ClientsCollection_GetClientByIndex(&(session->clients), message->deviceCode);

        if (client != CANFTP_NULL)
        {
            // Обновление метки времени потери связи с клиентом
            CanFTP_TimeTrigger_Update(&(client->lostConnectionTrigger));
        }
    }
}

/*
    Обработчик приема сообщения Registration
*/
void CanFTP_Server_Session_MessageSend_Registration(CanFTP_Server_Session_t* session)
{
    CanFTP_Message_Server_Registration_t messageModel;
    // Обработка сообщения
    {
        CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_ClientsCollection_GetClientByIndex(&(session->clients), session->agents.registrationConrtoller.clientIndex);

        if (client != CANFTP_NULL)
        {
            messageModel.deviceSerial = client->serverClient->configuration.serialNumber;
            messageModel.sessionCode = client->assosiation.sessionCode; 
            messageModel.deviceCode = client->assosiation.deviceCode;  
        }
        else
        {
            CanFTP_ThrowError();
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
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Server_Session_MessageSend_SessionControl(CanFTP_Server_Session_t* session)
{
    CanFTP_Message_Server_SessionControl_t messageModel;
    // Обработка сообщения
    {

    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Server_SessionControl_Pack(&(messageModel), &(messageCan));
        CanFTP_Server_Session_MessageSend(session, &(messageCan));
    }
}
/*
    Обработчик приема сообщения BlockContro
*/
void CanFTP_Server_Session_MessageSend_BlockControl(CanFTP_Server_Session_t* session)
{
    CanFTP_Message_Server_BlockControl_t messageModel;
    // Обработка сообщения
    {

    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Server_BlockControl_Pack(&(messageModel), &(messageCan));
        CanFTP_Server_Session_MessageSend(session, &(messageCan));
    }
}
/*
    Обработчик приема сообщения DataFrame
*/
void CanFTP_Server_Session_MessageSend_DataFrame(CanFTP_Server_Session_t* session)
{
    CanFTP_Message_Server_DataFrame_t messageModel;
    // Обработка сообщения
    {

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
