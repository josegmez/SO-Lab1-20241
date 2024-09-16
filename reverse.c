#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * This function take a file name and mode as input and opens the file in the specified mode.
 *
 * @param fileName Name of the file to be opened
 * @param mode Mode in which the file should be opened
 * @return The file pointer to the opened file
 */
FILE *openFile(char *fileName, char *mode)
{
  FILE *file = fopen(fileName, mode);
  if (file == NULL)
  {
    fprintf(stderr, "reverse: cannot open file '%s'\n", fileName);
    exit(EXIT_FAILURE);
  }
  return file;
}

void reverseText(FILE *input, FILE *output, int withOutput)
{
  char **lines = NULL;
  char *buffer = NULL;
  size_t line_count = 0;
  ssize_t read;

  // Read lines from input file into dynamically allocated memory
  while ((read = getline(&buffer, &read, input)) != -1)
  {
    lines = realloc(lines, (line_count + 1) * sizeof(char *));
    lines[line_count] = malloc(read);
    if (!lines)
    {
      fprintf(stderr, "malloc failed\n");
      exit(EXIT_FAILURE);
    }
    strcpy(lines[line_count], buffer);
    line_count++;
  }

  for (size_t i = line_count; i > 0; i--)
  {
    if (withOutput == 1)
    {
      fprintf(output, "%s", lines[i - 1]);
      free(lines[i - 1]);
    }
    else
    {
      fprintf(stdout, "%s", lines[i - 1]);
    }
  }

  free(lines);
  free(buffer);
}

int main(int argc, char *argv[])
{
  FILE *inputFile;
  FILE *outputFile;

  switch (argc)
  {
  case 1:
    /**
     * In this case, the user has not provided any arguments.
     * The program should prompt the user to enter the name of the file to be reversed.
     * The reversed text should be written to standard output.
     */
    {
      char fileName[100];
      printf("Enter the name of the file to be reversed: ");
      scanf("%s", fileName);
      inputFile = openFile(fileName, "r");

      reverseText(inputFile, NULL, 0);
    }
    break;

  case 2:
    /**
     * In this case, the user has provided the name of the file to be reversed.
     * The reversed text should be written to the standard output.
     */
    {
      inputFile = openFile(argv[1], "r");

      reverseText(inputFile, NULL, 0);
    }

    break;

  case 3:
    /**
     * In this case, the user has provided the name of the input file and the name of the output file.
     * The reversed text should be written to the output file.
     */
    {
      inputFile = openFile(argv[1], "r");
      outputFile = openFile(argv[2], "w");

      struct stat inputStat, outputStat;
      stat(argv[1], &inputStat);
      stat(argv[2], &outputStat);

      if (inputStat.st_ino == outputStat.st_ino)
      {
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(EXIT_FAILURE);
      }

      reverseText(inputFile, outputFile, 1);
    }
    break;
  default:
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(EXIT_FAILURE);
    break;
  }

  exit(EXIT_SUCCESS);
}