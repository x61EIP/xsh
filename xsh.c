#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h> // resume here 

typedef unsigned int bool_t;

#define KB 1024
#define TRUE 1
#define FALSE 0
#define ERROR_PREFIX "There was an error"


struct
menuItem
{
  unsigned int id;
  char* name;
  void (*fn)(const char*);
};

// This function name will probably change.
// The idea here is to create a list of structs that contain 
// the menu options available to the user. 
// [{ item0, ..., itemN }] where item is a struct menuItem.
void
_printDescription(const char* msg)
{
  printf("%s\n", msg);
}

void
displayMenu()
{
  struct menuItem item = { 
    .id = 1, 
    .name = "first item", 
    .fn = _printDescription
  };
  printf("***xsh****\n");
  item.fn("constraint = less than 44 characters");
}

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
  displayMenu();
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
