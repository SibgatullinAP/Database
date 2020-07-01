#include "dataBase.h"

int main(void)
{
    char inputBuff[INPUT_BUFF_LEN];

    printf("Please, enter Hash_Size of search structure for phone (more the better): ");
    int hashSize = 1;
    if(fgets(inputBuff, INPUT_BUFF_LEN, stdin) == nullptr || !(hashSize = atoi(inputBuff)))
    {
	printf("\nError: Incorrect input values\n"
	       "Hash_Size must be integer > 0.\n");
	return -1;
    }

    printf("Please, enter name or absolute path to initialization file: ");
    char initFileName[INPUT_BUFF_LEN] = {0};
    if(fgets(inputBuff, INPUT_BUFF_LEN, stdin) == nullptr || sscanf(inputBuff, "%s", initFileName) != 1)
    {
       printf("\nError: Incorrect input values.\n");
       return -1;
    }

    FILE* initFile = fopen(initFileName, "r");
    if(initFile == nullptr)
    {
	printf("Error: Can't open %s.\n", initFileName);
	return -2;
    }

    DataBase students (hashSize);

    double timeRead = clock();
    printf("\nReading...\n");
    int ret = students.read(initFile);
    timeRead = (clock() - timeRead) / CLOCKS_PER_SEC;

    if(ret < 0)
    {
	switch (ret)
	{
	    case ERROR_CANNOT_READ_INPUT_FILE:
		printf("Error: Can not read from %s.\n", initFileName);
		break;
	    default:
		printf("Error: Unknown error, error_value = %d.\n", ret);
		break;
	}
	fclose(initFile);
	return -3;
    }
    fclose(initFile);
    printf("Read time : %0.5lf\n", timeRead);

    double timeExecution = clock();
    printf("\nReady to use. Enter command: \n");
    students.run();
    timeExecution = (clock() - timeExecution) / CLOCKS_PER_SEC;

    printf("Operation time : %0.5lf\n", timeExecution);

    return 0;
}
