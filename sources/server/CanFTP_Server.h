/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVER_H_
#define CANFTP_SERVER_H_

#include "CanFTP_Server_Defines.h"

/*
    Инициализация сервера
*/
void CanFTP_Server_Init(CanFTP_Server_t *server);
/*
    Вызов логики обработки клиента
*/
void CanFTP_Server_Invoke(CanFTP_Server_t *server);
/*
    Обработка получения сообщений
*/
void CanFTP_Server_RecieveCanMessage(CanFTP_Server_t *server, CanFTP_CanMessage_t* canMessage);
/*
    Запустить процесс Ping
*/
CanFTP_Logical_t CanFTP_Server_StartPing(CanFTP_Server_t *server, CanFTP_Logical_t requestLogicLocking);
/*
    Запустить процесс разблокировки логик клиентов
*/
void CanFTP_Server_StartRelease(CanFTP_Server_t *server);
/*
    Остановить процесс Ping
*/
void CanFTP_Server_StopPing(CanFTP_Server_t *server);
/*
    Получить количество клиентов
*/
CanFTP_LinkedList_ElementsCount_t CanFTP_Server_GetClientsCount(CanFTP_Server_t *server);
/*
    Получить клиента по индексу
*/
CanFTP_Server_Client_t* CanFTP_Server_GetClientByIndex(CanFTP_Server_t *server, CanFTP_LinkedList_ElementsCount_t clientIndex);
/*
    Создать экземпляр сессии
*/
CanFTP_Server_Session_t* CanFTP_Server_CreateNewSession(CanFTP_Server_t *server);
/*
    Получить количество активных сессий
*/
CanFTP_SessionCode_t CanFTP_Server_GetActiveSessionsCount(CanFTP_Server_t *server);
/*
    Получить активную сессию по иднексу
*/
CanFTP_Server_Session_t* CanFTP_Server_GetActiveSessionByIndex(CanFTP_Server_t *server, CanFTP_SessionCode_t index);


#endif // CANFTP_SERVER_H_
