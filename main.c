#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dll.h"
#include "test.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define FORMAT_STRING_LENGTH 30
#define INPUT_INCREMENT 10
#define MAX_COMMAND_LENGTH 100

void print_prompt(FILE* f) {
    fprintf(f, "\n> "); fflush(f);
}

data* read_data(char const* command) {
    int age;
    char name[NAME_LENGTH];

    // NOTE: this only has to done once
    char format[FORMAT_STRING_LENGTH];
    snprintf(format, FORMAT_STRING_LENGTH, "%%*s%%*[ \\t]%%3d%%*[ \\t]%%%ds", NAME_LENGTH - 1);

    if (sscanf(command, format, &age, name) != 2) {
        fprintf(stderr, "Expected arguments: <age> <name>\n");
        return NULL;
    }

    return data_new(age, name);
}

bool handle_command(FILE* printFile, dll* dll, char* command) {
    switch(*command) {
    case 'i': {
        data* data = read_data(command);
        if (data != NULL) {
            dll_insert(dll, data);
        }
        break;
    } case 'e': {
        data* data = read_data(command);
        if (data != NULL) {
            dll_erase(dll, data);
            free(data);
        }
        break;
    } case 'r':
        dll_reverse(dll);
        break;
    case 'p':
        dll_print(dll, printFile);
        break;
    case 'x':
        return true;
        break;
    case 't':
        test(printFile);
        break;
    default: {
        fprintf(printFile, "No such command: %s\n", command);
        break;
    }
    }
    return false;
}

char* read_command(FILE* in) {
    unsigned int inputMaxLength = 0;
    char* input = NULL;
    char* inputAt = NULL;

    unsigned int incr = INPUT_INCREMENT;

    inputMaxLength = incr;
    input = (char*)malloc(sizeof(char) * incr);
    inputAt = input;
    do {
        inputAt[incr - 1] = 'e';
        if(fgets(inputAt, incr, in) == NULL) return NULL;
        if(inputAt[incr - 1] != '\0' || inputAt[incr - 2] == '\n') {
            break;
        }
        if(inputMaxLength + incr >= MAX_COMMAND_LENGTH) {
            for (int c; (c = getchar()) != '\n' && c != EOF;); // flush rest of input
            break;
        }
        inputMaxLength += INPUT_INCREMENT;
        input = realloc(input, sizeof(char) * inputMaxLength);
        inputAt = input + inputMaxLength - INPUT_INCREMENT - 1;
        incr = MIN(INPUT_INCREMENT + 1, MAX_COMMAND_LENGTH - inputMaxLength);
    } while(1);
    size_t len = strlen(input);
    input[len-1] = '\0';
    return input;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    dll* dll = dll_new();

    while(1) {
        print_prompt(stdout);

        char* command = read_command(stdin);
        if(command == NULL) {
            break;
        }

        bool success = handle_command(stdout, dll, command);

        free(command);

        if(success) break;
    }

    dll_delete(dll);

    fprintf(stdout, "\nBye.\n");

}

