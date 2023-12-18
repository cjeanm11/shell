
#ifndef SHELL_COMMAND_EXECUTOR_H
#define SHELL_COMMAND_EXECUTOR_H
#include "shell.h"
/**
 * Executes a single command represented by the given Command structure.
 *
 * @param cmd - The Command structure representing the command to execute.
 * @return The exit status of the executed command. Returns a negative value
 *         in case of errors during execution or forking.
 */
int executeCmd(struct Command cmd);

/**
 * Executes a sequence of commands as specified in the Cmdline structure.
 *
 * @param cmdLine - The Cmdline structure representing the entire command line
 *                 with multiple commands and logical operators.
 * @return Returns 0 if all commands in the sequence were executed successfully,
 *         or a negative value in case of errors during execution or forking.
 */
int execute(struct Cmdline cmdLine);
#endif //SHELL_COMMAND_EXECUTOR_H
