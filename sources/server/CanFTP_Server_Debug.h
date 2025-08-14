#ifndef CANFTP_SERVER_DEBUG_H_
#define CANFTP_SERVER_DEBUG_H_

#if (DEBUG_SERVER_STATES)

    #define DEBUG_SERVER_PRINTSTATE(state) { \
        CANFTP_DEBUG_ARGS("Server enter state \"%s\"\r\n", state); \
    }

#else

    #define DEBUG_SERVER_PRINTSTATE(state) { }

#endif

#endif // CANFTP_SERVER_DEBUG_H_
