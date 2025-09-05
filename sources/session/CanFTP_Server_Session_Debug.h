/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVER_SESSION_DEBUG_H_
#define CANFTP_SERVER_SESSION_DEBUG_H_

#if (DEBUG_SESSION_STATES)

    #define DEBUG_SESSION_PRINTSTATE(state, session) { \
        CANFTP_DEBUG_ARGS("Session \"%u\" enter state \"%s\"\r\n", session, state); \
    }

#else

    #define DEBUG_SESSION_PRINTSTATE(state, session) { }

#endif

#endif // CANFTP_SERVER_SESSION_DEBUG_H_
