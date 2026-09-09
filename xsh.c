#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef unsigned int bool_t;

#define KB 1024
#define TRUE 1
#define FALSE 0
#define ERROR_PREFIX "There was an error"

bool_t
checkAllocation(const void* value) 
{
  if (value == NULL)
  {
    return FALSE;
  }
  return TRUE;
}

char*
allocate(unsigned int size)
{
  if ((sizeof(char) * size) > KB)
  {
    return NULL;
  }
  char* value = malloc(sizeof(char) * size);
  if (value != NULL)
  {
    memset(value, 0, sizeof(char) * size);
  }
  // track this memory with a smartptr (similar to c++)?
  return value;
}

int
main(int argc, char* argv[])
{ 
  char* input_buffer = allocate((unsigned int)KB);
  if (checkAllocation(input_buffer) == FALSE)
  {
    fprintf(stderr, "%s\n", ERROR_PREFIX);
    return -1;
  }
  while (0x61) 
  {
    printf("#> ");
    fflush(stdout);
    if (fgets(input_buffer, sizeof(char) * KB, stdin) == NULL)
    {
      break;
    }
    char* saveptr = NULL;
    char* token = NULL;
    token = strtok_r(input_buffer, " ", &saveptr);
    input_buffer[strcspn(input_buffer, "\n")] = '\0';
    while (token != NULL)
    {
      printf("saveptr: %s, token: %s\n", saveptr, token);
      token = strtok_r(NULL, " ", &saveptr);
    }
  }
  free(input_buffer);
}
