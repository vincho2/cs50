#include "helpers.h"

BYTE *bptr;
BYTE *gptr;
BYTE *rptr;

//--------------------------------------------------------------------------------------------------
// Convert image to grayscale
//--------------------------------------------------------------------------------------------------
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
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

            // Compute pixel brightness
            pixel_brightness = (*bptr + *gptr + *rptr) / 3;
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

            // Compute pixel brightness
            pixel_brightness = (*bptr + *gptr + *rptr) / 3;
            // Assign the resulted brightness value to each color of the pixel
            *bptr = pixel_brightness;
            *gptr = pixel_brightness;
            *rptr = pixel_brightness;
        }
    }
}

//--------------------------------------------------------------------------------------------------
// Reflect image horizontally
//--------------------------------------------------------------------------------------------------
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

}

//--------------------------------------------------------------------------------------------------
// Blur image
//--------------------------------------------------------------------------------------------------
void blur(int height, int width, RGBTRIPLE image[height][width])
{

}
