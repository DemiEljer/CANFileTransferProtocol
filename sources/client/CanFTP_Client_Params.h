/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_CLIENT_PARAMS_H_
#define CANFTP_CLIENT_PARAMS_H_

/*
    В процессе Ping каждый раз выбирается произвольный интервал ответа в заданном диапазоне
*/
// Минимальный интервал времени Ping
#define CANFTP_CLIENT_PING_MININTERVAL 20
// Максимальный интервал времени Ping
#define CANFTP_CLIENT_PING_MAXINTERVAL 100
// Продолжительность процесса Ping без повторной отправки запроса
#define CANFTP_CLIENT_PING_TIMEOUT 1000

// Интервал повтора ответа на запрос сервера
#define CANFTP_CLIENT_SEESION_REPEATEACK_INTERVAL 100
// Количество итераций повтора ответа на запрос сервера
#define CANFTP_CLIENT_SEESION_REPEATEACK_COUNT 10
// Интервал времени потери связи с сервером при отсуствии сообщений
#define CANFTP_CLIENT_SEESION_LOSTCONNECTION_TIMEOUT 10000

// Период отправки сообщений подтверждения выключения сессии в случае терминирования логики
#define CANFTP_CLIENT_SEESION_TERMINATIONACK_PERIOD 100
// Количество отправляемых сообщений подтверждений терминирования сессии
#define CANFTP_CLIENT_SEESION_TERMINATIONACK_COUNT 10



#endif // CANFTP_CLIENT_PARAMS_H_
