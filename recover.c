#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
    {
        return 1;
    }

    //memory space to store one block
    uint8_t buffer[512];
    //image counter
    int count = 0;
    //the existance of an output file
    FILE *output = NULL;
    //asking for enough space for filename
    char *filename = malloc(8 * sizeof(char));

    while (fread(buffer, sizeof(char), 512, input))
    {
        //if its a jpg file
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            //WHY MUST YOU CLOSE THE FILE HERE
            if (count > 0)
            {
                fclose(output);
            }
            //write jpg filename in previously asked memory space
            sprintf(filename, "%03i.jpg", count);
            //opening filename
            output = fopen(filename, "w");
            count++;
        }

        //copying the data over to output
        //WHY IS THIS NECESSARY
        if (output != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output);
            //data type FILE doesnt need to be allocated memory?
        }

    }
    free(filename);
    fclose(input);
    fclose(output);
    return 0;
}