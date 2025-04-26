#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 4096

int count_occurrences(const char *buffer, const char *word) {
    int count = 0;
    const char *pos = buffer;
    size_t word_len = strlen(word);

    while ((pos = strstr(pos, word)) != NULL) {
        count++;
        pos += word_len; 
    }
    return count;
}

void process_file(const char *filename, const char *word) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE + 1];
    int total_count = 0;

    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        buffer[bytes_read] = '\0'; 
        total_count += count_occurrences(buffer, word);
    }

    fclose(file);

    printf("%s - %d\n", filename, total_count);
    fflush(stdout); 
    exit(EXIT_SUCCESS); 
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <file1> <file2> [file3 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("Enter a word: ");
    fflush(stdout);
    char word[256];
    if (scanf("%255s", word) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Error: fork failed");
            return EXIT_FAILURE;
        } else if (pid == 0) {
            // Child process
            process_file(argv[i], word);
        }
    }

    for (int i = 1; i < argc; i++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
