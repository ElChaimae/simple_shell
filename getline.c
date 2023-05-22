#include "main.h"
#include <unistd.h>
#define BUFFER_SIZE 1024

/**
 * my_getline - this function reads a line of text from a file descriptor.
 * @fd: file descriptor
 * Return: the line of text as a string, without the newline character
 * at the end.
 * If there is no more data in the file, it returns NULL.
 */
char *my_getline(int fd)
{
static char buffer[BUFFER_SIZE], line[BUFFER_SIZE];
static int buffer_pos, buffer_len, line_pos;
char c;

while (1)
{
if (buffer_pos == buffer_len)
{
buffer_len = read(fd, buffer, BUFFER_SIZE);
buffer_pos = 0;
}
if (buffer_len == 0)
{
if (line_pos > 0)
{
line[line_pos] = '\0'; /* add null terminator to line */
return (line);
}
else
return (NULL);
}
c = buffer[buffer_pos++];
if (c == '\n')
{
line[line_pos] = '\0'; /* add null terminator to line */
line_pos = 0; /* reset line position for next line */
return (line);
}
else
{
line[line_pos++] = c;
if (line_pos == BUFFER_SIZE)
{
line[line_pos] = '\0'; /* add null terminator to line */
line_pos = 0; /* reset line position for next line */
return (line);
}
}
}
}

