#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

#define true 1
#define false 0
#define bool int


/**
 * Enum representing the type of a command.
 */
enum CommandType {
    NORMAL, ///< Normal command
    AND,    ///< Logical AND command (e.g., "command1 && command2")
    OR      ///< Logical OR command (e.g., "command1 || command2")
};

/**
 * Structure representing a single command along with its attributes.
 */
struct Command {
    char** argv;           ///< An array of strings representing the command and its arguments
    enum CommandType type; ///< The type of the command (NORMAL, AND, or OR)
    char rnfn;             ///< The character indicating redirection ('r' or 'f') or '0' if none
    int n;                 ///< The number of repetitions for the command (0 if not specified)
};

/**
 * Structure representing a sequence of commands in a command line.
 */
struct Cmdline {
    struct Command* commands; ///< An array of Command structures representing the commands
    bool is_background;       ///< A boolean indicating if the command line is to be run in the background
};


#endif /* SHELL_H */
