/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Client_Session_Configuration.h"

/*
    Сбросить конфигурацию сессии
*/
void CanFTP_Session_Configuratio_Reset(CanFTP_Client_Session_Configuration_t *configuration)
{
    // Индекс первой страницы записи
    configuration->firstPageIndex = 0;
    // Количество страниц записи
    configuration->pagesCount = 0;
    // Новая версия программного обеспечения
    CanFTP_SoftwareVersion_Reset(&(configuration->newSoftVersion));
    // Длина передаваемого файла
    configuration->fileLength = 0;
    // Количество повторных отправок сообщений подтверждения при управлении сессией
    configuration->sessionRepeateCount = 0;
    // Интервал времени повторной отправки сообщений подтверждения при управлении сессией
    configuration->sessionRepeateInterval = 0;
    // Количество повторных отправок сообщений подтверждения при передаче блока
    configuration->blockRepeateCount = 0;
    // Интервал времени повторной отправки сообщений подтверждения при передаче блока
    configuration->blockRepeateInterval = 0;
}
