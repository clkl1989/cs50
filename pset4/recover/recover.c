#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int jpeg_start(BYTE buffer[]); //check if a buffer block makes the start of a JPEG

int main(int argc, char *argv[])
{
//open memory card
//repeat until end of card:
// 1. Read 512 bytes into a buffer (temp)
// 2. look at the 512 bytes block:
//a. if start of new JPEG:
//If first JPEG -> start writing to 000.JPEG,
//Else (if 2nd/3rd JPEG etc.) -> stop writing to the previous file and write to a new file 001 etc.
//b. if not start of new JPEG
//if JPEG found before -> keep writing to the existing JPEG gile
//if no JPEG found before -> look at the next block for the JPEG starting bytes
// 3. Reach the end?
//close all the remaining files



    if (argc == 2)
    {
        char *filename = argv[1];

        FILE *raw_file = fopen(filename, "r"); //open file and read

        if (raw_file == NULL)
        {
            printf("%p cannot be opened.\n", raw_file); //inform user that file cannot be opened
            return 1;
        }

        else
        {
            BYTE buffer[512]; //define buffer block
            char output_jpeg_name[8]; //naming an output jpeg file
            int count_of_output_jpeg = 0; //count how many JPEG has been fouond
            FILE *jpeg_outptr = NULL; //writing to an output file

            while (fread(buffer, 512, 1, raw_file) != 0)
            {
                if (jpeg_start(buffer) == 0) //if we found a JPEG in the buffer block, create a new output file and write into that file
                {
                    if (count_of_output_jpeg == 0) //if this is the first JPEG file found
                    {
                        sprintf(output_jpeg_name, "%03i.jpg", count_of_output_jpeg); //create an output file name
                        jpeg_outptr = fopen(output_jpeg_name, "w"); //write the buffer block into the output file
                        fwrite(buffer, 512, 1, jpeg_outptr);
                        count_of_output_jpeg++;
                    }

                    else //this is not the first JPEG file found, so stop writing to the previous output file and write to a new file
                    {
                        fclose(jpeg_outptr);
                        sprintf(output_jpeg_name, "%03i.jpg", count_of_output_jpeg);
                        jpeg_outptr = fopen(output_jpeg_name, "w");
                        fwrite(buffer, 512, 1, jpeg_outptr);
                        count_of_output_jpeg++;
                        
                    }
                }

                else
                {
                    if (count_of_output_jpeg > 0) //if a JPEG has been found before
                    {
                        fwrite(buffer, 512, 1, jpeg_outptr); //keep writing to the existing output file
                    }
                }
            }

        }

    }

    else if (argc != 2)
    {
        printf("Usage: ./recover image.\n"); //ask user to put in a proper command
        return 1;
    }
}

int jpeg_start(BYTE buffer[]) //function to check if the block of 512 bytes indicates start of a JPEG file
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return 0;
    }

    else
    {
        return 1;
    }
}