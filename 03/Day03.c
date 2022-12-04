#include <stdlib.h>
#include <stdio.h>

#define PATH "input"

int getline(char** buffer, int* capacity, FILE* fptr)
{
    if (*buffer == NULL)
    {
        (*buffer) = malloc(10);
        *capacity = 10;
        if (*buffer == NULL)
            exit(-1);
    }

    int n_read = 0;
    char c;
    while ((c = getc(fptr)) != EOF && c != '\n')
    {
        if (n_read == *capacity)
        {
            if (*capacity + 10 >= INT_MAX)
                exit(-1);
            *capacity = n_read + 10;
            char* temp = realloc(*buffer, (size_t)*capacity + 1);
            if (temp == NULL)
                exit(-1);
            *buffer = temp;
        }

        (*buffer)[n_read] = c;
        n_read++;
    }

    if (EOF == c && !n_read)
        return EOF;

    (*buffer)[n_read] = '\0';
    return n_read;
}

int get_priority(const char* line, const int size)
{
    int saved_values[('z' - 'a' + 1) + ('Z' - 'A' + 1)] = {NULL};

    for (int i = 0; i < size / 2; i++)
    {
        int value = line[i];
        value -= (value <= 'Z') ? 'A' - 26 : 'a';
        saved_values[value] |= 1;
    }
    for (int i = (size - 1); i > (size - 1) / 2; i--)
    {
        int value = line[i];
        value -= (value <= 'Z') ? 'A' - 26 : 'a';
        if (saved_values[value])
            return value + 1;
    }

    return -1;
}

int main()
{
    FILE* fptr;
    int a = sizeof(int);
    fopen_s(&fptr, PATH, "r");
    if (fptr == NULL) return -1;

    char* buffer = NULL;
    int capacity = 0;
    int added_priority = 0;
    int length;
    while ((length = getline(&buffer, &capacity, fptr)) != EOF)
    {
        added_priority += get_priority(buffer, length);
    }

    fclose(fptr);
    return 0;
}
