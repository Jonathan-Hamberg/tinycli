#ifndef  __TINYCLI_CONFIG_H__
#define __TINYCLI_CONFIG_H__

/*
 *
 */
#define TINYCLI_DEFINE(t) TINYCLI_SIG_##t,
enum {
#include "tinycli-funs.h"
};
#undef TINYCLI_DEFINE


#define TINYCLI_ARGTYPE_    void
#define TINYCLI_ARGTYPE_I   int
#define TINYCLI_ARGTYPE_D   double
#define TINYCLI_ARGTYPE_II  int,int
#define TINYCLI_ARGTYPE_ID  int,double
#define TINYCLI_ARGTYPE_DI  double,int
#define TINYCLI_ARGTYPE_DD  double,double

#define TINYCLI_ARGS_
#define TINYCLI_ARGS_I   tinycli_stoi(argv[1])
#define TINYCLI_ARGS_D   tinycli_stod(argv[1])
#define TINYCLI_ARGS_II  tinycli_stoi(argv[1]), tinycli_stoi(argv[2])
#define TINYCLI_ARGS_ID  tinycli_stoi(argv[1]), tinycli_stod(argv[2])
#define TINYCLI_ARGS_DI  tinycli_stod(argv[1]), tinycli_stoi(argv[2])
#define TINYCLI_ARGS_DD  tinycli_stod(argv[1]), tinycli_stod(argv[2])

#define TINYCLI_MAXCMDS    14
#define TINYCLI_MAXARGC    14
#define TINYCLI_MAXBUFFER  100


/* Check that MAX_ARGC is at least the minimum
 * values required for functionality.  */
#if (TINYCLI_MAXARGC < 1)
    #error "MAX_ARGC must be at least 1"
#endif

#endif // __TINYCLI_CONFIG_H__
