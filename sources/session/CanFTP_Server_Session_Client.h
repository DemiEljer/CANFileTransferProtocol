#ifndef CANFTP_SERVER_SESSION_CLIENT_H_
#define CANFTP_SERVER_SESSION_CLIENT_H_

#include "CanFTP_Server_Session_Client_Defines.h"

/*
    Инициализация клиента
*/
void CanFTP_Server_Session_Client_Init(CanFTP_Server_Session_Client_t *client
    // Код сессии
    , CanFTP_SessionCode_t sessionCode
    // Клиент на стороне сервера
    , CanFTP_Server_Client_t* serverClient
    // Код клиента
    , CanFTP_DeviceCode_t clientCode);
/*
    Подготовить клиента
*/
void CanFTP_Server_Session_Client_Prepare(CanFTP_Server_Session_Client_t *client);
/*
    Удаление клиента
*/
void CanFTP_Server_Session_Client_Dispose(CanFTP_Server_Session_Client_t *client);
/*
    Установить статус сессии клиенту
*/
void CanFTP_Server_Session_Client_SetSessionStatus(CanFTP_Server_Session_Client_t *client, CanFTP_SessionStatus_t status);
/*
    Получить статус сессии
*/
CanFTP_SessionStatus_t CanFTP_Server_Session_Client_GetSessionStatus(CanFTP_Server_Session_Client_t *client);
/*
    Обновить параметры отпавки сообщений управления
*/
void CanFTP_Server_Session_Client_UpdateControlSendingParams(CanFTP_Server_Session_Client_t *client
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount);
/*
    Обновить параметры отпавки сообщений удаления клиента из сессии
*/
void CanFTP_Server_Session_Client_UpdateDeletingSendingParams(CanFTP_Server_Session_Client_t *client
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount);
/*
    Проверить, что клиент активно участвует в сессии
*/
CanFTP_Logical_t CanFTP_Server_Session_Client_IsInSession(CanFTP_Server_Session_Client_t *client);
/*
    Проверить клиента
*/
CanFTP_Logical_t CanFTP_Server_Session_Client_Check(CanFTP_Server_Session_Client_t *client);
/*
    Сброс флагов при переходе к следующему блоку
*/
void CanFTP_Server_Session_Client_NextBlockReset(CanFTP_Server_Session_Client_t *client);


#endif // CANFTP_SERVER_SESSION_CLIENT_H_
