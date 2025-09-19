// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
const int MAX_16_BITS_VALUE = 65535;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open input file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "a");
    if (output == NULL)
    {
        fclose(input);
        printf("Could not open output file.\n");
        return 1;
    }

    float factor = atof(argv[3]);


    //----------------------------------------------------------------------------------------------
    // Copy header from input file to output file
    //----------------------------------------------------------------------------------------------

    // Initialize buffer used for the header
    char *input_header = malloc(HEADER_SIZE);

    // Make sure memory allocation is done properly, otherwise close files and stop the programme
    if (input_header == NULL)
    {
        printf("No memory allocated for header");
        fclose(input);
        fclose(output);
        return 2;
    }

    // Get header from input
    fread(input_header, sizeof(char), HEADER_SIZE, input);
    // Paste header in output
    fwrite(input_header, sizeof(char), HEADER_SIZE, output);
    // Free the memory
    free(input_header);

    //----------------------------------------------------------------------------------------------
    // TODO: Read samples from input file and write updated data to output file
    //----------------------------------------------------------------------------------------------

    // Initialize the sample pointer
    uint16_t *input_sample = malloc(sizeof(uint16_t));
    uint16_t *output_sample = malloc(sizeof(uint16_t));

    // Append the amplified samples to the output file
    while (fread(input_sample, sizeof(uint16_t), 1, input))
    {
        float output_sample_float_value = *input_sample * factor;

        // To avoid overflow, the output is capped to the maximum value of a 16 bytes number
        if (output_sample_float_value > MAX_16_BITS_VALUE)
        {
            *output_sample = (uint16_t) MAX_16_BITS_VALUE;
        }
        else
        {
            *output_sample = (uint16_t) output_sample_float_value;
        }
        fwrite(output_sample, sizeof(uint16_t), 1, output);
    }

    // Free memory and close files
    free(input_sample);
    free(output_sample);
    fclose(input);
    fclose(output);
}
