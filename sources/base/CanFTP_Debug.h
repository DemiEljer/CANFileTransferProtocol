/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_DEBUG_H_
#define CANFTP_DEBUG_H_

// Консольный вывод отладочной информации
#if (DEBUG_CONSOLE)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
    #if (DEBUG_CONSOLE)
        #include "stdio.h"
    #endif

    #define CANFTP_DEBUG_CONSOLE(logLine) { \
        printf(logLine);\
    }

    #define CANFTP_DEBUG_ARGS_CONSOLE(logLine, args...) { \
        printf(logLine, args);\
    }

#else

    #define CANFTP_DEBUG_CONSOLE(logLine) { }

    #define CANFTP_DEBUG_ARGS_CONSOLE(logLine, args...) { }

#endif

// Вывод отладочной строки
#define CANFTP_DEBUG(logLine) { \
    CANFTP_DEBUG_CONSOLE(logLine) \
}

// Вывод отладочной строки с аргументами
#define CANFTP_DEBUG_ARGS(logLine, args...) { \
    CANFTP_DEBUG_ARGS_CONSOLE(logLine, args) \
}

#endif // CANFTP_DEBUG_H_
