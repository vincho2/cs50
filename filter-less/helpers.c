#include "helpers.h"

const BYTE BLACK = 0x00;
const BYTE WHITE = 0xff;

RGBTRIPLE *pixel;

// Convert image to grayscale
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
            // Initialize pixel variable
            pixel = &image[i][j];
            // Compute pixel brightness
            pixel_brightness = (*pixel.rgbtBlue + *pixel.rgbtGreen + *pixel.rgbtRed) / 3;
            // Assign the resulted brightness value to each color of the pixel
            *pixel.rgbtBlue = pixel_brightness;
            *pixel.rgbtGreen = pixel_brightness;
            *pixel.rgbtRed = pixel_brightness;
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
