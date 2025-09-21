#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const int MAX_BYTE = 255;

BYTE *bptr;
BYTE *gptr;
BYTE *rptr;

typedef enum { BLUE, GREEN, RED } Color;



//--------------------------------------------------------------------------------------------------
// Convert image to grayscale
//--------------------------------------------------------------------------------------------------
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare original color variables
    BYTE original_blue;
    BYTE original_green;
    BYTE original_red;

    // Declare brightness variable
    BYTE pixel_brightness;

    // Loop on each row
    for (int i = 0; i < height; i++)
    {
        // Loop on each column
        for (int j = 0; j < width; j++)
        {
            // Initialize colors pointers
            bptr = &image[i][j].rgbtBlue;
            gptr = &image[i][j].rgbtGreen;
            rptr = &image[i][j].rgbtRed;

            original_blue = *bptr;
            original_green = *gptr;
            original_red = *rptr;

            // Compute pixel brightness
            pixel_brightness = (BYTE) round((original_blue + original_green + original_red) / 3.0);
            // Assign the resulted brightness value to each color of the pixel
            *bptr = pixel_brightness;
            *gptr = pixel_brightness;
            *rptr = pixel_brightness;
        }
    }
}

//--------------------------------------------------------------------------------------------------
// Convert image to SEPIA
//--------------------------------------------------------------------------------------------------
BYTE set_sepia_color(Color c, BYTE b_input, BYTE g_input, BYTE r_input);

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare original color variables
    BYTE original_blue;
    BYTE original_green;
    BYTE original_red;

    // Loop on each row
    for (int i = 0; i < height; i++)
    {
        // Loop on each column
        for (int j = 0; j < width; j++)
        {
            // Initialize colors pointers
            bptr = &image[i][j].rgbtBlue;
            gptr = &image[i][j].rgbtGreen;
            rptr = &image[i][j].rgbtRed;

            original_blue = *bptr;
            original_green = *gptr;
            original_red = *rptr;

            // Assign the resulted brightness value to each color of the pixel
            *bptr = set_sepia_color(BLUE, original_blue, original_green, original_red);
            *gptr = set_sepia_color(GREEN, original_blue, original_green, original_red);
            *rptr = set_sepia_color(RED, original_blue, original_green, original_red);
        }
    }
}

//--------------------------------------------------------------------------------------------------
// Helper function to set the SEPIA color value
//--------------------------------------------------------------------------------------------------
BYTE set_sepia_color(Color c, BYTE b_input, BYTE g_input, BYTE r_input)
{
    // Initialize factors by color
    float b_factor;
    float g_factor;
    float r_factor;

    // Set factors depending on the input color to convert
    switch (c)
    {
        case BLUE:
            b_factor = .131;
            g_factor = .534;
            r_factor = .272;
            break;

        case GREEN:
            b_factor = .168;
            g_factor = .686;
            r_factor = .349;
            break;

        case RED:
            b_factor = .189;
            g_factor = .769;
            r_factor = .393;
            break;
    }

    // Compute resulting sepia color
    int int_result =
        (int) round(fmin(MAX_BYTE, b_factor * b_input + g_factor * g_input + r_factor * r_input));

    // return result as a byte type
    return (BYTE) int_result;
}

//--------------------------------------------------------------------------------------------------
// REFLECT image horizontally
//--------------------------------------------------------------------------------------------------
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *rrptr = calloc(width, sizeof(RGBTRIPLE));
    if (rrptr == NULL)
    {
        printf("No memory in the heap to create row of pixel, it will crash");
        return;
    }

    // Loop on each row
    for (int i = 0; i < height; i++)
    {
        // Loop on each column to populate the reflected row array
        for (int j = 0; j < width; j++)
        {
            rrptr[j] = image[i][width - j - 1];
        }
        // Loop again on each column to populate the image array with the reflected array content
        for (int j = 0; j < width; j++)
        {
            image[i][j] = rrptr[j];
        }
    }
    free(rrptr);
}

//--------------------------------------------------------------------------------------------------
// BLUR image
//--------------------------------------------------------------------------------------------------
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Define null pixel
    RGBTRIPLE null_pixel = {0, 0, 0};

    // Store original image in another location as reference
    RGBTRIPLE (*original_image)[width] = calloc(height * width, sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original_image[i][j] = image[i][j];
        }
    }

    // Loop on each pixel to update the pixel value with the average of its neighborhood

    // Default number of pixel in a neighborhood
    const int grid_size = 9;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset neighbor count to the grid size
            int neighbor_count = grid_size;
            // Define the local grid array
            RGBTRIPLE local_grid[grid_size];
            int m = 0;

            for (int k = i - 1; k < i + 1; k++)
            {
                for (int l = j - 1; l < j + 1; l++)
                {

                    if (k = 0 || j = 0 || k = height || j = width)
                    {
                        local_grid[m] = null_pixel;
                        neighbor_count--;
                    }
                    else
                    {
                        local_grid[m] = image[k][l];
                    }
                    m++;
                }
                if (m != grid_size)
                {
                    printf("%i should be %i", m, grid_size);
                }
                image[i][j] = get_blurry_inner_pixel(local_grid, neighbor_count);
            }
        }
    }
    free(original_image);
}

//--------------------------------------------------------------------------------------------------
// Helper function to compute an inner blurry pixel value
//--------------------------------------------------------------------------------------------------
RGBTRIPLE get_blurry_inner_pixel(RGBTRIPLE grid[grid_size], int average_factor)
{


}


