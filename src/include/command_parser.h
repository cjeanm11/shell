#ifndef SHELL_COMMAND_PARSER_H
#define SHELL_COMMAND_PARSER_H
#include "shell.h"

/**
 * Tokenizes a null-terminated C string into individual tokens.
 *
 * @param line - The input string to be tokenized.
 * @return A dynamically allocated array of tokens (null-terminated C strings).
 *         The array is terminated with a NULL pointer.
 */
char** tokenize(char* line);

/**
 * Parses an array of tokens to build a structured representation of a command line.
 *
 * @param tokens - An array of tokens (null-terminated C strings) obtained from tokenize().
 * @return A structured representation of the parsed command line (struct Cmdline).
 */
struct Cmdline parse(char** tokens);
#endif //SHELL_COMMAND_PARSER_H
