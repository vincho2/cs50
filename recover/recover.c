#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t BYTE;
const int block_size = 512;
const BYTE INIT_3_BYTES[] = {0xff, 0xd8, 0xff};
const BYTE BYTE4_MIN = 0xe0;
const BYTE BYTE4_MAX = 0xef;

int build_new_jpg_file_name(int counter, char file_name[8]);

int main(int argc, char *argv[])
{
    // Command line should accept 1 and only 1 argument
    if (argc != 2)
    {
        printf("Usage: ./recover file.raw");
        return 1;
    }

    // If input file does not exist or cannot be open, return an error
    char *input_file = argv[1];
    FILE *inptr = fopen(input_file, "r");

    if (inptr == NULL)
    {
        printf("Could not open file named %s", input_file);
        return 1;
    }

    // Initialize block array of 512 bytes
    BYTE block[block_size];


    // Initialize jpg file name and pointer
    char output_file[8];
    int jpg_counter = 0;
    build_new_jpg_file_name(jpg_counter, output_file);
    FILE *output_file_ptr = NULL;

    // Loop over each block in the input file
    while (fread(block, block_size * sizeof(BYTE), 1, inptr))
    {
        // Identify JPG pattern
        if (memcmp(block, INIT_3_BYTES, 3) == 0 && block[4] <= BYTE4_MIN && block[4] <= BYTE4_MAX)
        {
            // Close previous file if it exists
            if (output_file_ptr != NULL)
            {
                fclose(output_file_ptr);
            }

            // Initialize new JPG file name
            build_new_jpg_file_name(jpg_counter, output_file);
            // Open new output file
            output_file_ptr = fopen(output_file, "w");
            if (output_file_ptr == NULL)
            {
                printf("Could not open output file %s", output_file);
                return 1;
            }

            // Increment counter and keep file open
            jpg_counter++;
        }

        // Assume that if jpg counter is not zéro then a jpg file is opened and we should write
        // the block into it (end of jpg series is not specified in the exercize)
        if (jpg_counter != 0)
        {
            // Put the whole block in the currently opened JPG file
            fwrite(block, block_size * sizeof(BYTE), 1, output_file_ptr);
        }
    }

    // At the end of the input raw file, close the last jpg file
    if (output_file_ptr != NULL)
    {
        fclose(output_file_ptr);
    }
}

// -------------------------------------------------------------------------------------------------
// Helper function to set output jpg file name
// -------------------------------------------------------------------------------------------------
char *build_new_jpg_file_name(int counter)
{
    const char *ext = ".jpg";
    char *result;

    if (counter > 999)
    {
        printf("too many files");
        return "999.jpg";
    }
    if (counter < 10)
    {
        sprintf(result, "00%i%s", counter, ext);
    }
    else if (counter < 100)
    {
        sprintf(result, "0%i%s", counter, ext);
    }
    else
    {
        sprintf(result, "%i%s", counter, ext);
    }
    return result;
}
