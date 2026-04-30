/*
 * cc3000_config.h
 *
 * Feature gate macros for CC3000 driver.
 * These are placeholders for phase 1 development; implementation
 * references them in future iterations.
 */

#ifndef CC3000_CONFIG_H_
#define CC3000_CONFIG_H_

#ifndef CC3K_DEBUG
#define CC3K_DEBUG 0
#endif

#ifndef CC3K_ASYNC
#define CC3K_ASYNC 0
#endif

#ifndef CC3K_RECONNECT
#define CC3K_RECONNECT 0
#endif

#ifndef CC3K_ZEROCOPY
#define CC3K_ZEROCOPY 0
#endif

#ifndef CC3K_SCAN
#define CC3K_SCAN 1
#endif

#ifndef CC3K_SMARTCONFIG
#define CC3K_SMARTCONFIG 0
#endif

#ifndef CC3K_MAX_SOCKETS
#define CC3K_MAX_SOCKETS 4
#endif

#ifndef CC3K_BUFFER_SIZE
#define CC3K_BUFFER_SIZE 256
#endif

#endif /* CC3000_CONFIG_H_ */
