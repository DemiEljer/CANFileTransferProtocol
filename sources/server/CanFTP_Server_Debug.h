#ifndef CANFTP_SERVER_DEBUG_H_
#define CANFTP_SERVER_DEBUG_H_

#if (DEBUG_SERVER_STATES)

    #define DEBUG_SERVER_PRINTSTATE(state) { \
        CANFTP_DEBUG_ARGS("Server enter state \"%s\"\r\n", state); \
    }

    #define DEBUG_SERVER_SESSION_PRINTSTATE(state, session) { \
        CANFTP_DEBUG_ARGS("Server enter state \"%s\", session \"%u\"\r\n", state, session); \
    }

#else

    #define DEBUG_SERVER_PRINTSTATE(state) { }

    #define DEBUG_SERVER_SESSION_PRINTSTATE(state, session) { }

#endif

#endif // CANFTP_SERVER_DEBUG_H_
