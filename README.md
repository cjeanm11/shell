<div class="center"></div>

#  Shell

This documentation describes the structure and functionality of a simple shell program developed as part of a university assignment. The shell is capable of parsing and executing commands with various features, including redirection and logical operators.

## Code Overview

The code consists of the following main components:

### Enum: CommandType

- `NORMAL`: Represents a normal command.
- `AND`: Represents a logical AND command (e.g., "command1 && command2").
- `OR`: Represents a logical OR command (e.g., "command1 || command2").

### Struct: Command

- Represents a single command along with its attributes.
- Members:
    - `char** argv`: An array of strings representing the command and its arguments.
    - `enum CommandType type`: The type of the command (NORMAL, AND, or OR).
    - `char rnfn`: The character indicating redirection ('r' or 'f') or '0' if none.
    - `int n`: The number of repetitions for the command (0 if not specified).

### Struct: Cmdline

- Represents a sequence of commands in a command line.
- Members:
    - `struct Command* commands`: An array of `Command` structures representing the commands.
    - `bool is_background`: A boolean indicating if the command line is to be run in the background.

## Usage

The provided code allows you to create and execute shell commands with various features such as logical operators (AND and OR) and command repetition. The `Command` and `Cmdline` structures are used to represent and manage command data.

### Example Usage

```c
struct Cmdline cmdLine;
// Populate cmdLine with commands and their attributes.

// Execute the command line.
int result = execute(cmdLine);

if (result < 0) {
    // Handle error.
} else {
    // Handle successful execution.
}
