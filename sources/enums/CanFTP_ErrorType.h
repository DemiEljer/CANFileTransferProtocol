/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_ERRORTYPE_H_
#define CANFTP_ERRORTYPE_H_

/*
    Тип ошибки
*/
typedef enum _CanFTP_ErrorType
{
    // Ошибка выхода за пределы размера списка
    CANFTP_ERROR_LIST_OUTOFRANGE = 1,
    // Ошибка не принадлежности элемента списку
    CANFTP_ERROR_LIST_STRANGERELEMENT = 2,
    // Ошибка отсутствия обработчика получения текущего времени
    CANFTP_ERROR_TIME_NOTTIMEGETTER = 3,
    // Ошибка метки времени
    CANFTP_ERROR_TIME_TIMEMARK = 4,
    // Ошибка отсутствия ссылки на клиента
    CANFTP_ERROR_CLIENT_NULL = 5,
    // Ошибка отсуствия обработчика тела состояния конечного автомата
    CANFTP_ERROR_FMS_NOBODYHANLER = 6,
    // Ошибка выхода за переделы коллекции состояний конечного автомата
    CANFTP_ERROR_FMS_OUTOFHANDLERS = 7,
    // Ошибка типа сообщения
    CANFTP_ERROR_MESSAGES_WRONGTYPE = 8,
    // Ошибка параметров сообщения
    CANFTP_ERROR_MESSAGES_WRONGPARAMS = 9,
    // Выход за пределы коллекции клиентов
    CANFTP_ERROR_CLIENTSCOLLECTION_OUTOFRANGE = 10,
    // Выход за пределы коллекции сессий
    CANFTP_ERROR_SESSIONSCOLLECTION_OUTOFRANGE = 11,
    // Ошибка отсутствия ссылки на сервер
    CANFTP_ERROR_SERVER_NULL = 12,
    // Ошибка обработки блока файла
    CANFTP_ERROR_SESSION_BLOCKERROR = 13,
    // Ошибка попытки добавления в сессию клиента, который уже находится в сессии
    CANFTP_ERROR_CLIENT_ALREADYINSESSION = 14,
    // Ошибка отсутствия ссылки на сессию
    CANFTP_ERROR_SESSION_NULL = 15,
    // Ошибка выхода за пределы блока файла
    CANFTP_ERROR_FILEBLOCK_OUTOFRANGE = 16,
    // Ошибка выхода за пределы коллекции конфигурационных сообщений
    CANFTP_ERROR_SESSION_CONFIGURATION_PARTINDEXOUTOFRANGE = 17,
    // Ошибка отсутствия обработчика отправки CAN-сообщений
    CANFTP_ERROR_CALLBACKS_NOMESSAGESENDER = 18,
    // Ошибка отсутствия обработчика приема блока файла
    CANFTP_ERROR_CALLBACKS_NOBLOCKHANDLER = 19,

} CanFTP_ErrorType_t;

#endif // CANFTP_ERRORTYPE_H_
