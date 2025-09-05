/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_CLIENTSESSIONACKSTATUS_H_
#define CANFTP_CLIENTSESSIONACKSTATUS_H_

/*
    Статусы ответа на запросы сервера во время обработки сессии
*/
typedef enum _CanFTP_ClientSessionAckStatus
{
    // Запрос успешно обработан
    CANFTP_CLIENTSESSIONACKSTATUS_SUCCESS = 0,
    // Ошибка обработки запроса
    CANFTP_CLIENTSESSIONACKSTATUS_FAIL = 1,

} CanFTP_ClientSessionAckStatus_t; 

#endif // CANFTP_CLIENTSESSIONACKSTATUS_H_
