#ifndef CANFTP_DEBUG_H_
#define CANFTP_DEBUG_H_

#if (DEBUG_CONSOLE)

    #include "stdio.h"

    #define CANFTP_DEBUG_PRINT(logLine) { printf(logLine); }

    #define CANFTP_DEBUG_PRINT_ARGS(logLine, args...) { printf(logLine, args); }

#else

    #define CANFTP_DEBUG_PRINT(logLine) { }

    #define CANFTP_DEBUG_PRINT_ARGS(logLine, args...) { }

#endif

#endif // CANFTP_DEBUG_H_
