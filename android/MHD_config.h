/* MHD_config.h for Android */
/* Created manually. */

/* *** Basic OS/compiler information *** */

/* This is a Linux system */
#define LINUX 1

#define HAVE_PTHREAD_H 1
#define MHD_USE_POSIX_THREADS 1

#define HAVE_POLL_H 1
#define HAVE_POLL 1

#define HAVE_SYS_SOCKET_H 1

#define HAVE_NETINET_TCP_H 1

/* Define to 1 if your C compiler supports inline functions. */
#define INLINE_FUNC 1

#define HAVE_SYS_TIME_H 1

#define HAVE_NETDB_H 1

#define HAVE_NET_IF_H 1

#define HAVE_NETINET_IN_H 1

#define HAVE_SYS_SELECT_H 1

#define HAVE_UNISTD_H 1

#define EPOLL_SUPPORT 1


/* Define to prefix which will be used with MHD inline functions. */
#define _MHD_static_inline static inline

/* *** MHD configuration *** */
/* Undef to disable feature */

/* Enable basic Auth support */
#define BAUTH_SUPPORT 1

/* Enable digest Auth support */
#define DAUTH_SUPPORT 1

/* Enable postprocessor.c */
#define HAVE_POSTPROCESSOR 1

/* Enable error messages */
#define HAVE_MESSAGES 1

/* Enable HTTP Upgrade support. */
#define UPGRADE_SUPPORT 1

/* *** OS features *** */

/* Provides IPv6 headers */
#define HAVE_INET6 1

/* Define to use socketpair for inter-thread communication */
#define _MHD_ITC_SOCKETPAIR 1


/* Define to 1 if you have the `_lseeki64' function. */
#define HAVE___LSEEKI64 1

/* Define to 1 if you have the `gmtime_s' function in W32 form. */
//#define HAVE_W32_GMTIME_S 1

/* Define to 1 if you have the usable `calloc' function. */
#define HAVE_CALLOC 1

#define HAVE_SNPRINTF 1

#define HAVE_INTTYPES_H 1


/* *** Headers information *** */
/* Not really important as not used by code currently */

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the <math.h> header file. */
#define HAVE_MATH_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

#define HAVE_STDBOOL_H 1

/* *** Other useful staff *** */

#define _GNU_SOURCE  1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1


/* End of MHD_config.h */
