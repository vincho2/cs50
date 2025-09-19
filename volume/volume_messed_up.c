// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
const int16_t MAX_16_BITS_VALUE = 65535;
const int16_t MIN_16_BITS_VALUE = 65535;

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

    FILE *output = fopen(argv[2], "w");
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
    uint8_t input_header[HEADER_SIZE];

    // Get header from input
    fread(input_header, HEADER_SIZE, 1, input);
    // Paste header in output
    fwrite(input_header, HEADER_SIZE, 1, output);

    //----------------------------------------------------------------------------------------------
    // TODO: Read samples from input file and write updated data to output file
    //----------------------------------------------------------------------------------------------

    // Initialize the sample pointer
    int integer_result;
    uint16_t input_sample;
    uint16_t output_sample;
    uint16_t offset = 1;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    // Append the amplified samples to the output file
    while (fread(&input_sample, sizeof(uint16_t), 1, input))
    {

        i++;
        integer_result = (int) input_sample *  (int) factor;

        output_sample = (uint16_t) (input_sample * factor);

        printf("---- Sample %i -------------------- %i negative --- %i overflows --- small %i\n", i, j, k, l);
        printf("input sample: %u\noutput sample: %f\ninput * factor: %u\n", input_sample, factor, output_sample);

        // To avoid overflow, the output is capped to the maximum value of a 16 bytes number
        if (integer_result > (int) MAX_16_BITS_VALUE)
        {
            output_sample = MAX_16_BITS_VALUE;
            k++;
        }
        // To avoid underflow, the output is floored to the minimum value of a 16 bytes number
        else if (integer_result < 0)
        {
            output_sample = (uint16_t) 0;
            j++;
        }
        // avoid 0 in output
        else if (input_sample == (uint16_t) 1)
        {
            output_sample = input_sample;
            l++;
        }

        printf("output sample after logic: %u\n", output_sample);
        printf("negative: %i - ", j);
        printf("small: %i - ", l);
        printf("overflow: %i\n\n", k);

        if (l == 100)
        {
            fclose(input);
            fclose(output);
            return 1;
        }

        fwrite(&output_sample, sizeof(uint16_t), 1, output);
    }

    // Free memory and close files
    fclose(input);
    fclose(output);
}
