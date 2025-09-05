/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_MESSAGES_DEBUG_H_
#define CANFTP_MESSAGES_DEBUG_H_

#if (DEBUG_MESSAGES_CONTENT)

    #define DEBUG_MESSAGES_PRINTFIELD(messageName, fieldName, fieldValue) { \
        CANFTP_DEBUG_ARGS("Message \"%s\", field \"%s\" = \"%u\" \r\n", messageName, fieldName, fieldValue); \
    }

#else

    #define DEBUG_MESSAGES_PRINTFIELD(messageName, fieldName, fieldValue) { }

#endif

#endif // CANFTP_MESSAGES_DEBUG_H_
