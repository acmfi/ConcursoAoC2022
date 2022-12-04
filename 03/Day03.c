// El código más sucio, menos seguro, complicado y lioso
// que se haya visto jamás. No tiene ni una sola comprobación
// de ningún tipo de errores, y sólo sirve exclusivamente para
// el caso muy particular del enunciado.

#include <stdlib.h>
#include <stdio.h>

#define PATH "input"
typedef unsigned int uint;

uint getline(char** buffer, FILE* fptr)
{
	(*buffer) = malloc(10);
	size_t capacity = 10;

	int n_read = 0;
	char c;
	while ((c = getc(fptr)) != EOF && c != '\n')
	{
		if (n_read == capacity)
		{
			capacity = n_read + 10;
			char* temp = realloc(*buffer, capacity + 1);
			*buffer = temp;
		}

		(*buffer)[n_read] = c;
		n_read++;
	}

	if (EOF == c)
		return EOF;

	(*buffer)[n_read] = '\0';
	return n_read;
}

uint char_to_priority(const char a) {
	return (a - ((a <= 'Z') ? 'A' - 26 : 'a'));
}

int get_priority(const char* line, const int size)
{
	uint saved_values[52] = { NULL };

	for (uint i = 0; i < size / 2; i++)
	{
		saved_values[char_to_priority(line[i])] |= 1;
	}
	for (uint i = (size - 1); i > (size - 1) / 2; i--)
	{
		uint value = char_to_priority(line[i]);
		if (saved_values[value])
			return value + 1;
	}
}

uint get_across_group(const char* lineOne, const char* lineTwo, const char* lineThree) {
	int saved_values[52] = { 0 };
	int c;

	for (int i = 0; (c = lineOne[i]) != '\0'; i++)
		saved_values[char_to_priority(c)] |= 0b01;
	for (int i = 0; (c = lineTwo[i]) != '\0'; i++)
		saved_values[char_to_priority(c)] |= 0b10;

	uint value;
	for (int i = 0; (c = lineThree[i]) != '\0'; i++)
	{
		value = char_to_priority(c);
		if (saved_values[value] == 0b11)
			return value + 1;
	}
}

uint part_one()
{
	FILE* fptr;
	int a = sizeof(int);
	fopen_s(&fptr, PATH, "r");

	char* buffer = NULL;
	int length;

	uint added_priority = 0;

	while ((length = getline(&buffer, fptr)) != EOF)
	{
		added_priority += get_priority(buffer, length);
	}
	fclose(fptr);

	return added_priority;
}

uint part_two()
{
	FILE* fptr;
	int a = sizeof(int);
	fopen_s(&fptr, PATH, "r");

	char* buffer1 = NULL;
	char* buffer2 = NULL;
	char* buffer3 = NULL;
	int capacity = 0;

	uint added_priority = 0;

	while (getline(&buffer1, fptr) != EOF)
	{
		getline(&buffer2, fptr);
		getline(&buffer3, fptr);
		added_priority += get_across_group(buffer1, buffer2, buffer3);
	}
	fclose(fptr);

	return added_priority;
}

int main()
{
	printf("1 - El valor de la suma de los elementos duplicados es %u\n", part_one());
	printf("2 - El valor de la suma de las insignias es %u\n", part_two());

	return 0;
}
