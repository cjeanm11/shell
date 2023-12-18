#include "include/command_executor.h"

int executeCmd(struct Command cmd) {
    int childCode = 0;
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "could not fork process\n");
        return -1;
    } else if (pid == 0) {
        childCode = execvp(cmd.argv[0], cmd.argv);
        fprintf(stderr, "%s: command not found\n", cmd.argv[0]);
        exit(childCode);
    } else {
        waitpid(pid, &childCode, 0);
        childCode = WEXITSTATUS(childCode);
    }
    return childCode;
}

int execute(struct Cmdline cmdLine) {
    int ret;
    struct Command* commands = cmdLine.commands;

    if (cmdLine.is_background) {
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "could not fork process\n");
            return -1;
        } else if (pid != 0) {
            return 0;
        }
    }

    for (int i = 0; commands[i].argv; i++) {
        if (commands[i].rnfn == 'r' || commands[i].rnfn == 'f') {
            for (int n = 0; n < commands[i].n; n++) {
                ret = (commands[i].rnfn == 'f') ? 0 : executeCmd(commands[i]);
                if (ret < 0) {
                    return -1;
                }
            }
        } else {
            ret = executeCmd(commands[i]);
            if (ret < 0) {
                return -1;
            }
        }

        if (ret == 0) {
            if (commands[i].type == OR) {
                while (commands[i].argv && commands[i].type != AND) {
                    i++;
                }
                if (!commands[i].argv) {
                    break;
                }
            }
        } else {
            if (commands[i].type == AND) {
                while (commands[i].argv && commands[i].type != OR) {
                    i++;
                }
                if (!commands[i].argv) {
                    break;
                }
            }
        }
    }

    return 0;
}
