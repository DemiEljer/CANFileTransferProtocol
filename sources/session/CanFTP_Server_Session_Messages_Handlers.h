#ifndef CANFTP_SERVER_SESSION_MESSAGES_HANDLERS_H_
#define CANFTP_SERVER_SESSION_MESSAGES_HANDLERS_H_

#include "CanFTP_Server_Session_HelpFunctions.h"


/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Server_Session_MessageRecieve_SessionControl(CanFTP_Server_Session_t* session, CanFTP_Message_Client_SessionControl_t* message);
/*
    Обработчик приема сообщения BlockControl
*/
void CanFTP_Server_Session_MessageRecieve_BlockControl(CanFTP_Server_Session_t* session, CanFTP_Message_Client_BlockControl_t* message);
/*
    Обработчик приема сообщения SubBlocksStatuses
*/
void CanFTP_Server_Session_MessageRecieve_SubBlocksStatuses(CanFTP_Server_Session_t* session, CanFTP_Message_Client_SubBlocksStatuses_t* message);
/*
    Обработчик приема сообщения BlockCRC
*/
void CanFTP_Server_Session_MessageRecieve_BlockCRC(CanFTP_Server_Session_t* session, CanFTP_Message_Client_BlockCRC_t* message);

/*
    Обработчик приема сообщения Registration
*/
void CanFTP_Server_Session_MessageSend_Registration(CanFTP_Server_Session_t* session);
/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Server_Session_MessageSend_SessionControl(CanFTP_Server_Session_t* session);
/*
    Обработчик приема сообщения BlockContro
*/
void CanFTP_Server_Session_MessageSend_BlockControl(CanFTP_Server_Session_t* session);
/*
    Обработчик приема сообщения DataFrame
*/
void CanFTP_Server_Session_MessageSend_DataFrame(CanFTP_Server_Session_t* session);
/*
    Отправить сообщение
*/
void CanFTP_Server_Session_MessageSend(CanFTP_Server_Session_t* session, CanFTP_CanMessage_t* message);

#endif // CANFTP_SERVER_SESSION_MESSAGES_HANDLERS_H_