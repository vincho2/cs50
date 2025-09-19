#include "helpers.h"
#include <math.h>

BYTE set_sepia_color(Color c, BYTE *pixptr);

BYTE *bptr;
BYTE *gptr;
BYTE *rptr;

typedef enum
{
    BLUE,
    GREEN,
    RED
} Color;

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
    BYTE sepiaRed;
    BYTE sepiaGreen;
    BYTE sepiaBlue;

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

            sepiaBlue = set_sepia_color(BLUE, &image[i][j]);

            sepiaBlue = (BYTE) fmax(.272 * (*rptr) + .534 * (*gptr) + .131 * (*bptr), 255);
            sepiaGreen = (BYTE) fmax(.349 * (*rptr) + .686 * (*gptr) + .168 * (*bptr), 255);
            sepiaRed = (BYTE) fmax(.393 * (*rptr) + .769 * (*gptr) + .189 * (*bptr), 255);



            // Compute pixel brightness
            pixel_brightness = (*bptr + *gptr + *rptr) / 3;
            // Assign the resulted brightness value to each color of the pixel
            *bptr = sepiaRed;
            *gptr = sepiaGreen;
            *rptr = sepiaRed;
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

//--------------------------------------------------------------------------------------------------
// Helper function to set the Sepia color value
//--------------------------------------------------------------------------------------------------
BYTE set_sepia_color(Color c, BYTE *pixptr)
{

    // Initialize colors pointers
    bptr = pixptr.rgbtBlue;
    gptr = pixptr.rgbtGreen;
    rptr = pixptr.rgbtRed;

    switch(c)
    {
        case BLUE:
            sepiaBlue = (BYTE) fmax(.272 * (*rptr) + .534 * (*gptr) + .131 * (*bptr), 255);
            break;


    }


}
