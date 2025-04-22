#include "files.h"
#include <stdio.h>

FILE *open_file(const char *filepath, const char *mode)
{
  FILE *file = NULL;
  file = fopen(filepath, mode);

  if (file == NULL)
  {
    perror(filepath);
    exit(1);
  }

  return file;
}

void close_file(FILE *file)
{
  if (fclose(file) == EOF)
  {
    perror("Cannot close file");
    exit(2);
  }
}

void reset_file(const char *filepath)
{
  FILE *file = open_file(filepath, "w");
  close_file(file);
}
