#ifndef CANFTP_CLIENT_DEBUG_H_
#define CANFTP_CLIENT_DEBUG_H_

#if (DEBUG_CLIENT_STATES)

    #define DEBUG_CLIENT_PRINTSTATE(state, serial) { \
        CANFTP_DEBUG_ARGS("Client enter state \"%s\", serial \"%u\"\r\n", state, serial); \
    }

#else

    #define DEBUG_CLIENT_PRINTSTATE(state, serial) { }

#endif



#endif // CANFTP_CLIENT_DEBUG_H_
