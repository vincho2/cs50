#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    const BYTE BLACK = 0x00;
    const BYTE WHITE = 0xff;

    BYTE pixel_brightness;


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // Compute pixel brightness and assign the resulted value to each colour of the pixel
            pixel_brightness = (image.rgbtBlue + image.rgbtGreen + image.rgbtRed) / 3;
            image.rgbtBlue = pixel_brightness;
            image.rgbtGreen = pixel_brightness;
            image.rgbtRed = pixel_brightness;
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
