#include "tinycli-config.h"

#define TINYCLI_ERROR_NOCMD     -1
#define TINYCLI_ERROR_NUMARGS   -2
#define TINYCLI_ERROR_NOSIG     -3

// TODO: X-macro style
#define tinycli_register(cmd, func) _Generic((func),                                        \
int(*)(TINYCLI_ARGTYPE_):   tinycli_register_sig(cmd, (int(*)(void))func, TINYCLI_SIG_),    \
int(*)(TINYCLI_ARGTYPE_I):  tinycli_register_sig(cmd, (int(*)(void))func, TINYCLI_SIG_I),   \
int(*)(TINYCLI_ARGTYPE_D):  tinycli_register_sig(cmd, (int(*)(void))func, TINYCLI_SIG_D),   \
int(*)(TINYCLI_ARGTYPE_II): tinycli_register_sig(cmd, (int(*)(void))func, TINYCLI_SIG_II),  \
int(*)(TINYCLI_ARGTYPE_ID): tinycli_register_sig(cmd, (int(*)(void))func, TINYCLI_SIG_ID),  \
int(*)(TINYCLI_ARGTYPE_DI): tinycli_register_sig(cmd, (int(*)(void))func, TINYCLI_SIG_DI),  \
int(*)(TINYCLI_ARGTYPE_DD): tinycli_register_sig(cmd, (int(*)(void))func, TINYCLI_SIG_DD)   )

// TODO: non-gneric helper functions
// tinycli_register_v(.....)
// tinycli_register_ii(.....)
// etc



void tinycli_register_sig(const char* cmd, int (*f)(void), int sig);
int  tinycli_call(int argc, char* argv[]);
int  tinycli_process(void);
void tinycli_putc(char c);
void tinycli_puts(char* str);
