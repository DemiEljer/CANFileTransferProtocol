#ifndef CANFTP_CLIENT_H_
#define CANFTP_CLIENT_H_

#include "CanFTP_Client_Defines.h"

/*
    Инициализация клиента
*/
void CanFTP_Client_Init(CanFTP_Client_t *client);
/*
    Вызов логики обработки клиента
*/
void CanFTP_Client_Invoke(CanFTP_Client_t *client);
/*
    Обработка получения сообщений
*/
void CanFTP_Client_RecieveCanMessage(CanFTP_Client_t *client, CanFTP_CanMessage_t* canMessage);
/*
    Проинициализировать функцию генерации случайных значений
*/
void CanFTP_Client_InitRanmod(CanFTP_Client_t *client);
/*
    Принудительно остановить сессию
*/
void CanFTP_Client_TerminateSession(CanFTP_Client_t *client);
/*
    Заблокировать логику
*/
void CanFTP_Client_LockLogic(CanFTP_Client_t *client);
/*
    Разблокировать логику
*/
void CanFTP_Client_UnlockLogic(CanFTP_Client_t *client);
/*
    Проверить, находится ли клиент в состоянии Ping
*/
CanFTP_Logical_t CanFTP_Client_CheckIsPinging(CanFTP_Client_t *client);
/*
    Проверить, находится ли клиент сотоянии активной сессии
*/
CanFTP_Logical_t CanFTP_Client_CheckIsInSession(CanFTP_Client_t *client);

#endif // CANFTP_CLIENT_H_