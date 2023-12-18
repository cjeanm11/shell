#include "include/command_parser.h"
char** tokenize(char* line) {
    const char* delim = " \t\n";
    char** tokens = NULL;
    char* token = strtok(line, delim);
    int count = 0;

    while (token) {
        tokens = realloc(tokens, (count + 1) * sizeof(char*));
        tokens[count] = strdup(token);
        token = strtok(NULL, delim);
        count++;
    }

    tokens = realloc(tokens, (count + 1) * sizeof(char*));
    tokens[count] = NULL;
    return tokens;
}

struct Cmdline parse(char** tokens) {
    struct Cmdline cmd_line;
    cmd_line.is_background = false;

    int n = 1;
    for (int i = 0; tokens[i]; i++) {
        if (tokens[i][0] == '&' && (tokens[i][1] == '&' || !tokens[i][1])) {
            n++;
        } else if (tokens[i][0] == '|' && tokens[i][1] == '|') {
            n++;
        }
    }

    cmd_line.commands = malloc((n + 1) * sizeof(struct Command));
    if (!cmd_line.commands) {
        fprintf(stderr, "lack of memory\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        cmd_line.commands[i].type = NORMAL;
        cmd_line.commands[i].rnfn = '0';
        cmd_line.commands[i].n = 0;
    }

    int i, j, k;
    for (i = j = n = 0; tokens[i]; i++) {
        if ((cmd_line.commands[n].rnfn == 'f' || cmd_line.commands[n].rnfn == 'r') &&
            (k = strcspn(tokens[i], "()")) > 0) {
            tokens[i][k] = '\0';
        } else if (tokens[i][0] == '&') {
            if (tokens[i][1]) {
                cmd_line.commands[n].type = AND;
            } else {
                cmd_line.is_background = true;
            }
            cmd_line.commands[n++].argv = tokens + j;
            j = i;
            tokens[j++] = NULL;
        } else if (tokens[i][0] == '|' && tokens[i][1]) {
            cmd_line.commands[n].type = OR;
            cmd_line.commands[n++].argv = tokens + j;
            j = i;
            tokens[j++] = NULL;
        } else if ((i == 0 || !tokens[i - 1]) && (tokens[i][0] == 'r' || tokens[i][0] == 'f')) {
            k = 1;
            while (isdigit(tokens[i][k])) {
                k++;
            }
            if (tokens[i][k - 1] && tokens[i][k] == '(') {
                cmd_line.commands[n].rnfn = tokens[i][0];
                tokens[i][k] = '\0';
                cmd_line.commands[n].n = atoi(tokens[i] + 1);
                if (!tokens[i][k + 1]) {
                    tokens[i++] = NULL;
                } else {
                    tokens[i] += k + 1;
                }
                j = i;
            }
        }
    }

    if (!cmd_line.is_background) {
        cmd_line.commands[n++].argv = tokens + j;
    }

    cmd_line.commands[n].argv = NULL;
    return cmd_line;
}
