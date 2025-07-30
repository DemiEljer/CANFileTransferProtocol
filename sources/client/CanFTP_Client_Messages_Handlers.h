#ifndef CANFTP_CLIENT_MESSAGES_HANDLERS_H_
#define CANFTP_CLIENT_MESSAGES_HANDLERS_H_

#include "CanFTP_Client_Defines.h"

/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_Ping(void* invoker, CanFTP_Message_Server_Ping_t* message);
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_PingResponseAck(void* invoker, CanFTP_Message_Server_PingResponseAck_t* message);
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_Registration(void* invoker, CanFTP_Message_Server_Registration_t* message);
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_SessionControl(void* invoker, CanFTP_Message_Server_SessionControl_t* message);
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_BlockControl(void* invoker, CanFTP_Message_Server_BlockControl_t* message);
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_DataFrame(void* invoker, CanFTP_Message_Server_DataFrame_t* message);


/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageSend_PingResponse(CanFTP_Client_t* client);
/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Client_MessageSend_SessionControl(CanFTP_Client_t* client);
/*
    Обработчик приема сообщения BlockControl
*/
void CanFTP_Client_MessageSend_BlockControl(CanFTP_Client_t* client);
/*
    Обработчик приема сообщения SubBlocksStatuses
*/
void CanFTP_Client_MessageSend_SubBlocksStatuses(CanFTP_Client_t* client);
/*
    Обработчик приема сообщения BlockCRC
*/
void CanFTP_Client_MessageSend_BlockCRC(CanFTP_Client_t* client);
/*
    Отправить сообщение
*/
void CanFTP_Client_MessageSend(CanFTP_Client_t* client, CanFTP_CanMessage_t* message);

#endif