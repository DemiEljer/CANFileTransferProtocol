#ifndef CANFTP_SERVER_SESSION_DEBUG_H_
#define CANFTP_SERVER_SESSION_DEBUG_H_

#if (DEBUG_SESSION_STATES)

    #define DEBUG_SESSION_PRINTSTATE(state, session) { \
        CANFTP_DEBUG_ARGS("Server enter state \"%s\", session \"%u\"\r\n", state, session); \
    }

#else

    #define DEBUG_SESSION_PRINTSTATE(state, session) { }

#endif

#endif // CANFTP_SERVER_SESSION_DEBUG_H_
