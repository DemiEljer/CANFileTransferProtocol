#ifndef CANFTP_SERVER_MESSAGES_HANDLERS_H_
#define CANFTP_SERVER_MESSAGES_HANDLERS_H_

#include "CanFTP_Server_HelpFunctions.h"

/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Server_MessageRecieve_PingResponse(void* invoker, CanFTP_Message_Client_PingResponse_t* message);
/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Server_MessageRecieve_SessionControl(void* invoker, CanFTP_Message_Client_SessionControl_t* message);
/*
    Обработчик приема сообщения BlockControl
*/
void CanFTP_Server_MessageRecieve_BlockControl(void* invoker, CanFTP_Message_Client_BlockControl_t* message);
/*
    Обработчик приема сообщения SubBlocksStatuses
*/
void CanFTP_Server_MessageRecieve_SubBlocksStatuses(void* invoker, CanFTP_Message_Client_SubBlocksStatuses_t* message);
/*
    Обработчик приема сообщения BlockCRC
*/
void CanFTP_Server_MessageRecieve_BlockCRC(void* invoker, CanFTP_Message_Client_BlockCRC_t* message);

/*
    Обработчик приема сообщения Ping
*/
void CanFTP_Server_MessageSend_Ping(CanFTP_Server_t* server);
/*
    Обработчик приема сообщения PingResponseAck
*/
void CanFTP_Server_MessageSend_PingResponseAck(CanFTP_Server_t* server);
/*
    Обработчик приема сообщения Registration
*/
void CanFTP_Server_MessageSend_Registration(CanFTP_Server_t* server, CanFTP_Server_Session_t* session);
/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Server_MessageSend_SessionControl(CanFTP_Server_t* server, CanFTP_Server_Session_t* session);
/*
    Обработчик приема сообщения BlockContro
*/
void CanFTP_Server_MessageSend_BlockControl(CanFTP_Server_t* server, CanFTP_Server_Session_t* session);
/*
    Обработчик приема сообщения DataFrame
*/
void CanFTP_Server_MessageSend_DataFrame(CanFTP_Server_t* server, CanFTP_Server_Session_t* session);
/*
    Отправить сообщение
*/
void CanFTP_Server_MessageSend(CanFTP_Server_t* server, CanFTP_CanMessage_t* message);

#endif // CANFTP_SERVER_MESSAGES_HANDLERS_H_
