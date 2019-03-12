#include <stdlib.h>
#include <string.h>

#include "tinycli.h"

#define TINYCLI_ENTER  '\n'

/* Return value
 */
int tinycli_result;



/* An array of command structures for
 * storing info needed for calling a
 * function for a specific command.  */
static struct {
    const char* text;
    int(*fun)(void);
    int sig;
    int nargs;
} cmds[TINYCLI_MAXCMDS];


/* The number of commands that
 * have been registered. This cannot
 * exceed TINYCLI_MAXCMDS. */
static int numCmds = 0;


/*
 * Tokenize a string into argc/argv format
 *
 * Params:
 *   str  = a NULL terminated string to tokenize
 *   argv = a char** for holding tokens. Each entry
 *          in argv will be filled with a pointer to
 *          the token in str. Thus argv is only valid
 *          as long as str is valid.
 *
 * Returns:
 *   the number of tokens copied into argv
 *
 * Note:
 *   In the case that str contains more tokens than MAX_ARGC, then only
 *   the first MAX_ARGC number will be copied into argv.
 */
int tokenize(char* str, char* argv[]) {
    int argc = 0;
    argv[argc] = strtok(str, " \n");
    while (++argc < TINYCLI_MAXARGC && (argv[argc] = strtok(NULL, " ")));
    return argc;
}


/* Find the index of the command given
 * by the string at argv[0].  */
static int findCmd(int argc, char* argv[]) {
    for (int i = 0; i < numCmds; i++) {
        if (!strcmp(argv[0], cmds[i].text)) return i;
    }
    return -1;
}


/* Register a command
 *
 * If you don't want to specify the specific TINYCLI_SIG_?? macro,
 * you can instead call the helper functions: tincli_regiser_??().
 *
 * Params:
 *    text = a string literal of the text that will trigger this command.
 *           This should be a single word with no surrounding whitespace.
 *    fun  = the function to call when this command is encountered but
 *           cast to an int(*)(void) signature.
 *    sig  = the true signature of the callback function as defined in
 *           the TINYCLI_SIG_?? macros.
 */
void tinycli_register_sig(const char* text, int (*fun)(void), int sig, int nargs) {
    if (numCmds >= TINYCLI_MAXCMDS) return;
    cmds[numCmds].text  = text;
    cmds[numCmds].fun   = fun;
    cmds[numCmds].sig   = sig;
    cmds[numCmds].nargs = nargs;
    numCmds++;
}

/*
 *
 */
#define tinycli_cmd(s) void tinycli_register_##s (const char* cmd, int (*f)(tinycli_params(s))) { tinycli_register_sig(cmd, (int(*)(void)) f, tinycli_sig(s), tinycli_nargs(s)); }
#include "tinycli-funs.h"
#undef tinycli_cmd

/*
 *
 */
int tinycli_stoi(const char* c) {
    return strtol(c, NULL, 0);
}

/*
 *
 */
double tinycli_stod(const char* c) {
    return strtod(c, NULL);
}


/* Call a registered callback based on the entered text
 *
 * Params:
 *    argc = the size of argv.
 *    argv = an array containing the text of the command
 *           and the arguments. The command is at index 0
 *           with arguments following.
 *
 * Returns: the result of callback function of a negative
 *          error code if the given command is not found
 *          or if the arguments converted incorrectedly.
 */
int tinycli_call(int argc, char* argv[]) {
    
    // Get command index
    int cmdIndex = findCmd(argc, argv);
    if (cmdIndex < 0) return TINYCLI_ERROR_NOCMD;
    if (argc != cmds[cmdIndex].nargs+1) return TINYCLI_ERROR_NUMARGS;
    switch (cmds[cmdIndex].sig) {
        #define tinycli_cmd(s)  case tinycli_sig(s): return ((int(*)(tinycli_params(s))) cmds[cmdIndex].fun)(tinycli_args(s));
        #include "tinycli-funs.h"
        #undef tinycli_cmd
    }
    return TINYCLI_ERROR_NOSIG;
}


/* Add char to tinycli buffer
 *
 * Will trigger a command if the
 * char matches the TINYCLI_ENTER
 * character.
 *
 * Params:
 *     c = the character to append
 */
void tinycli_putc(char c) {

    static int  top = 0;
    static char buffer[TINYCLI_MAXBUFFER];
    static char*  argv[TINYCLI_MAXARGC];

    // Ignore carriage return
    if (c == '\r') return;

    // Handle backspace
    if (c == '\b') {
        top--;
        return;
    }

    // Save char
    buffer[top++] = c;

    // Call stuff
    if (c == TINYCLI_ENTER) {
        // Parse command into argv and argc
        int argc = tokenize(buffer, argv);

        // Try to call function
        tinycli_result = tinycli_call(argc, argv);
        top = 0;
    }
}


/* Add string to tinycli buffer
 *
 * Will trigger a command if the char
 * matches the TINYCLI_ENTER character.
 * This can possibly happen more that
 * once if there are multiple lines of
 * commands to execute.
 *
 * Params:
 *     s = the null terminated string to append
 *     n = a maximum number of characters to append
 */
void tinycli_putsn(char* s, int n) {
    for (int i = 0; i < n; i++) {
        if (s[i] == '\0') break;  // Stop at NULL char
        tinycli_putc(s[i]);
    }
}


