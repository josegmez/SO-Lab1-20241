#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  return file;
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
         * The reversed text should be written to tNumber of arguments provided is invalidhe standard output.
         */
    {
      char fileName[100];
      printf("Enter the name of the file to be reversed: ");
      scanf("%s", fileName);
      inputFile = openFile(fileName, "r");

      // TODO: Implement reverse logic
    }
    break;

  case 2:
    /**
       * In this case, the user has provided the name of the file to be reversed.
       * The reversed text should be written to the standard output.
       */
    {
      inputFile = openFile(argv[1], "r");

      // TODO: Implement reverse logic
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

      if (strcmp(argv[1], argv[2]) == 0)
      {
        printf("Input and output file names cannot be the same");
        exit(EXIT_FAILURE);
      }

      // TODO: Implement reverse logic
    }
    break;
  default:
    printf("Number of arguments provided is invalid");
    exit(EXIT_FAILURE);
    break;
  }

  return 0;
}