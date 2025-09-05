/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVER_SESSION_PARAMS_H_
#define CANFTP_SERVER_SESSION_PARAMS_H_

// Интервал отправки сообщений при регистрации клиентов
#define CANFTP_SERVER_SESSION_REGISTRATION_INTERVAL 100
// Количество попыток регистрации клиентов
#define CANFTP_SERVER_SESSION_REGISTRATION_COUNT 10
// Интервал отправки сообщений управления сессией
#define CANFTP_SERVER_SESSION_SESSIONCONTROL_INTERVAL 100
// Количество попыток отправок сообщений управления сессией
#define CANFTP_SERVER_SESSION_SESSIONCONTROL_COUNT 10
// Количество попыток отправки блока файла
#define CANFTP_SERVER_SESSION_BLOCKREPEATE_COUNT 10
// Интервал времени отправки сообщений управления отправкой блока
#define CANFTP_SERVER_SESSION_BLCOCKCONTROL_INTERVAL 100
// Количество попыток отправки сообщений при управлении отправкой блока
#define CANFTP_SERVER_SESSION_BLOCKCONTROL_COUNT 10
// Интервал времени при отправке фрейма блока файла
#define CANFTP_SERVER_SESSION_FRAMESENDING_INTERVAL 1
// Интервел времени отправки подтверждений со стороны клиентов
#define CANFTP_SERVER_SESSION_ACKREPEATE_INTERVAL 100
// Количество попыток отправки подтверждений со стороны клиента
#define CANFTP_SERVER_SESSION_ACKREPEATE_COUNT 10
// Интервал времени для отслеживания потери связи с клиентом
#define CANFTP_SERVER_SESSION_LOSTCONNECTION_TIMEOUT 10000

#endif // CANFTP_SERVER_SESSION_PARAMS_H_
