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

#endif // CANFTP_CLIENT_H_