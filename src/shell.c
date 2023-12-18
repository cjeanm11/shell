#include "include/shell.h"
#include "include/command_parser.h"
#include "include/command_executor.h"

char* readLine() {
    char* line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, stdin);
    if (read == -1) {
        free(line);
        return NULL;
    }
    return line;
}



int shell(void) {
    int ret;
    char* line;
    char** tokens;
    struct Cmdline cmdLine;

    while (1) {
        line = readLine();
        if (line) {
            tokens = tokenize(line);
            cmdLine = parse(tokens);
            if (!cmdLine.commands) {
                free(tokens);
                free(line);
                exit(1);
            } else {
                ret = execute(cmdLine);
                free(cmdLine.commands);
                free(tokens);
                free(line);
                if (ret < 0) {
                    exit(1);
                }
            }
        }
        line = NULL;
    }
}

int main () {
    shell();
    return 0;
}
