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
        if (CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_IDLE)
        {
            if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_NOTERMINATION)
            {
                // Запрос на переход в состояние ответа на запрос Ping
                client->agents.pingController.requsts.requestPinging = 0x01;
                // Запрос на блокирование логики
                client->agents.logicLockController.requsts.requestToLockLogic = 0x01;
            }
            else if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_TERMINATE)
            {
                // Запрос на переход в состояние ответа на запрос Ping
                client->agents.pingController.requsts.requestPinging = 0x01;
            }
        }
        else if (CanFTP_Client_IsPinging(client))
        {
            if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_RELEASE)
            {
                // Запрос на прекращение процесса Ping
                client->agents.pingController.requsts.requestPinging = 0x00;
                // Снятие запроса на блокировку логики
                client->agents.logicLockController.requsts.requestToLockLogic = 0x00;
            }
            CanFTP_TimeTrigger_Update(&(client->agents.pingController.coolingDownTrigger));
        }
        // Проверка случая активной сессии
        else if (CanFTP_Client_IsInActiveSession(client))
        {
            if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_RELEASE)
            {
                // Запрос на выключение сессии

                // Снятие запроса на блокировку логики
                client->agents.logicLockController.requsts.requestToLockLogic = 0x00;
            }
        }
        else
        {
            // Ничего не делаем
        }
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
        client->agents.pingController.pingResponsesAck[message->responseType] = 0x01;

        CanFTP_TimeTrigger_Update(&(client->agents.pingController.coolingDownTrigger));
    }
}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_Registration(void* invoker, CanFTP_Message_Server_Registration_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);


}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_SessionControl(void* invoker, CanFTP_Message_Server_SessionControl_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);


}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_BlockControl(void* invoker, CanFTP_Message_Server_BlockControl_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);


}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_DataFrame(void* invoker, CanFTP_Message_Server_DataFrame_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);


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
        client->callbacks.sendMessageCallback(message);
    }
}
