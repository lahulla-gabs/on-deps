#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_LENGTH 1024

void parse_line(const char *line, regex_t *regex) {
    regmatch_t matches[3];
    if (regexec(regex, line, 3, matches, 0) == 0) {
        char package_name[matches[1].rm_eo - matches[1].rm_so + 1];
        strncpy(package_name, line + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
        package_name[matches[1].rm_eo - matches[1].rm_so] = '\0';

        char dependencies[matches[2].rm_eo - matches[2].rm_so + 1];
        strncpy(dependencies, line + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
        dependencies[matches[2].rm_eo - matches[2].rm_so] = '\0';

        printf("Package: %s\n", package_name);
        char *token = strtok(dependencies, ", ");
        while (token != NULL) {
            printf("  Dependency: %s\n", token);
            token = strtok(NULL, ", ");
        }
    }
}

int main() {
    FILE *file = fopen("packages.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    regex_t regex;
    regcomp(&regex, "^([^:]+):\\s*(.*)$", REG_EXTENDED);

    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        parse_line(line, &regex);
    }

    fclose(file);
    regfree(&regex);

    return EXIT_SUCCESS;
}
