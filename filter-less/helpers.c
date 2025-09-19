#include "helpers.h"

const BYTE BLACK = 0x00;
const BYTE WHITE = 0xff;

RGBTRIPLE *pixel;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare brightness variable
    BYTE pixel_brightness;

    BYTE *blueptr;
    BYTE *greenptr;
    BYTE *redptr;

    // Loop on each row
    for (int i = 0; i < height; i++)
    {
        // Loop on each column
        for (int j = 0; j < width; j++)
        {
            // Initialize colors pointers
            blueptr = &image[i][j].rgbtBlue;
            greenptr = &image[i][j].rgbtGreen;
            redptr = &image[i][j].rgbtRed;

            // Compute pixel brightness
            pixel_brightness = (*blueptr + *greenptr + *redptr) / 3;
            // Assign the resulted brightness value to each color of the pixel
            *blueptr = pixel_brightness;
            *greenptr = pixel_brightness;
            *redptr = pixel_brightness;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

}
