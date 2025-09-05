/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVER_SESSION_CLIENTSCOLLECTION_H_
#define CANFTP_SERVER_SESSION_CLIENTSCOLLECTION_H_

#include "CanFTP_Server_Session_Client.h"

/*
    Структура коллекции клиентов сессии на стороне сервера
*/
typedef struct _CanFTP_Server_Session_ClientsCollection
{
    // Количество клиентов сессии
    CanFTP_DeviceCode_t clientsCount;
    // Массив клиентов сесси
    CanFTP_Server_Session_Client_t* clients;

} CanFTP_Server_Session_ClientsCollection_t;

/*
    Инициализация колекции клиентов сессии
*/
void CanFTP_Server_Session_ClientsCollection_Init(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Удаление колекции клиентов сессии
*/
void CanFTP_Server_Session_ClientsCollection_Dispose(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Инициализация клиентов сессии
*/
void CanFTP_Server_Session_ClientsCollection_InitClients(CanFTP_Server_Session_ClientsCollection_t* collection
    // Код сессии
    , CanFTP_SessionCode_t sessionCode
    // Количество клиентов
    , CanFTP_DeviceCode_t clientsCount
    // Массив указателей на клиентов сессии
    , CanFTP_Server_Client_t** serverClients);
/*
    Найти обобщенную версию программного обеспечения
*/    
void CanFTP_Server_Session_ClientsCollection_GetSoftVewrsion(CanFTP_Server_Session_ClientsCollection_t* collection, CanFTP_SoftwareVersion_t *softVersion);
/*
    Получить клиента по индексу
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_ClientsCollection_GetCount(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Получить клиента по индексу
*/
CanFTP_Server_Session_Client_t* CanFTP_Server_Session_ClientsCollection_GetClientByIndex(CanFTP_Server_Session_ClientsCollection_t* collection, CanFTP_DeviceCode_t index);
/*
    Подготовить клиентов перед запуском сессии
*/
void CanFTP_Server_Session_ClientsCollection_Prepare(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Обновить параметры отпавки сообщений управления
*/
void CanFTP_Server_Session_ClientsCollection_UpdateControlSendingParams(CanFTP_Server_Session_ClientsCollection_t *collection
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount);
/*
    Обновить параметры отпавки сообщений удапения клиентов
*/
void CanFTP_Server_Session_ClientsCollection_UpdateDeletingSendingParams(CanFTP_Server_Session_ClientsCollection_t *collection
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount);
/*
    Проверить клиентов на предмет выполнения условия нахождения в сессии
*/
void CanFTP_Server_Session_ClientsCollection_Check(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Получить количество ну удаленных клиентов
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_ClientsCollection_GetNotDisposedCount(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Проврить, что остались не удаленные клиенты
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckIsNotDisposedLeft(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Проврить, что все клиенты были зарегистрированы
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsRegistrationAndDelete(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Проврить, что все клиенты были сконфигурированы
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsConfiguration(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Удалить всех клиентов, не прошедших конфигурацию 
*/
void CanFTP_Server_Session_ClientsCollection_DeleteAllUnconfugured(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Проврить, что все клиенты готовы к началу сессии
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsSessionStarted(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Удалить всех клиентов, не начавших сессию
*/
void CanFTP_Server_Session_ClientsCollection_DeleteAllUnstarted(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Проврить, что все клиенты завершили сессию
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsSessionFinished(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Удалить всех клиентов, не закончившие сессию
*/
void CanFTP_Server_Session_ClientsCollection_DeleteAllUnfinished(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Сброс флагов при переходе к следующему блоку
*/
void CanFTP_Server_Session_ClientsCollection_NextBlockReset(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Проврить, что все клиенты начали чтение блока
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsBlockStarted(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Удалить всех клиентов, не начавших чтение блока
*/
void CanFTP_Server_Session_ClientsCollection_DeleteAllBlockUnstarted(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Проврить, что все клиенты окончили чтение блока
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsBlockFinished(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Удалить всех клиентов, не окончавших чтение блока
*/
void CanFTP_Server_Session_ClientsCollection_DeleteAllBlockUnfinished(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Удалить всех клиентов, не принявших блок
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_ClientsCollection_DeleteAllBlockUnrecieved(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Обновить метки времени потери связи с клиентами
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_ClientsCollection_UpdateLostConnectionTimeMarks(CanFTP_Server_Session_ClientsCollection_t* collection);


#endif // CANFTP_SERVER_SESSION_CLIENTSCOLLECTION_H_
