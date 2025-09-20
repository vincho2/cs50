#include "helpers.h"
#include <math.h>
#include <stdio.h>

const int MAX_BYTE = 255;

BYTE *bptr;
BYTE *gptr;
BYTE *rptr;

typedef enum { BLUE, GREEN, RED } Color;

BYTE set_sepia_color(Color c, BYTE b_input, BYTE g_input, BYTE r_input);

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
// Convert image to sepia
//--------------------------------------------------------------------------------------------------
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
// Reflect image horizontally
//--------------------------------------------------------------------------------------------------
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE *rrptr[width];
    RGBTRIPLE reflected_row[width];
    // Loop on each row
    for (int i = 0; i < height; i++)
    {
        // Loop on each column to populate the reflected row array
        for (int j = 0; j < width; j++)
        {
            reflected_row[j] = image[i][width - j - 1];
        }
        // Loop again on each column to populate the image array with the reflected array content
        for (int j = 0; j < width; j++)
        {
            image[i][j] = reflected_row[j];
        }
    }
}

//--------------------------------------------------------------------------------------------------
// Blur image
//--------------------------------------------------------------------------------------------------
void blur(int height, int width, RGBTRIPLE image[height][width]) {







}

//--------------------------------------------------------------------------------------------------
// Helper function to set the Sepia color value
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
