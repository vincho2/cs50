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

// Default number of pixel in a neighborhood
const int grid_size = 9;

RGBTRIPLE get_blurry_pixel(RGBTRIPLE grid[grid_size], float average_factor);

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Store original image in another location as reference before the image starts to be modified
    RGBTRIPLE(*original_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original_image[i][j] = image[i][j];
        }
    }

    // Loop on each pixel to update the image pixel values with the average of its neighborhood

    // Define the local grid array (square of 3*3 pixels represented as a single array of 9 pixels)
    RGBTRIPLE local_grid[grid_size];

    // Define null pixel (assigned to pixels outside the image)
    RGBTRIPLE null_pixel = {0, 0, 0};

    // Loop on each pixel of the resulting image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Reset average factor to the grid size
            float average_factor = (float) grid_size;
            // Define local grid counter to 0
            int local_grid_counter = 0;

            // Build the local grid array for this pixel
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // If the current local grid pixel is outside the image
                    if (k < 0 || l < 0 || k >= height || l >= width)
                    {
                        // Assign the null pixel (will not be taken into account for the average)
                        local_grid[local_grid_counter] = null_pixel;
                        // decrease the total of pixels of the grid to compute the correct average
                        average_factor--;
                    }
                    // Else store the pixel values into the local grid array
                    else
                    {
                        local_grid[local_grid_counter] = original_image[k][l];
                    }
                    // Increment local grid counter to move to next pixel to store in the array
                    local_grid_counter++;
                }
            }
            // Update pixel
            image[i][j] = get_blurry_pixel(local_grid, average_factor);
        }
    }
    // After finishing looping on each pixels, free the memory allocated to the original image
    free(original_image);
}

//--------------------------------------------------------------------------------------------------
// Helper function to compute a blurry pixel value
//--------------------------------------------------------------------------------------------------
RGBTRIPLE get_blurry_pixel(RGBTRIPLE grid[grid_size], float average_factor)
{
    RGBTRIPLE resulting_pixel;
    int blue = 0;
    int green = 0;
    int red = 0;

    for (int i = 0; i < grid_size; i++)
    {
        blue += grid[i].rgbtBlue;
        green += grid[i].rgbtGreen;
        red += grid[i].rgbtRed;
    }
    resulting_pixel.rgbtBlue = (BYTE) round(blue / average_factor);
    resulting_pixel.rgbtGreen = (BYTE) round(green / average_factor);
    resulting_pixel.rgbtRed = (BYTE) round(red / average_factor);

    return resulting_pixel;
}

//--------------------------------------------------------------------------------------------------
// Detect EDGES
//--------------------------------------------------------------------------------------------------
RGBTRIPLE get_target_pixel_edge(RGBTRIPLE grid[grid_size]);

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Store original image in another location as reference before the image starts to be modified
    RGBTRIPLE(*original_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original_image[i][j] = image[i][j];
        }
    }

    // Loop on each pixel to update the image pixel values depending on its neighborhood

    // Define the local grid array (square of 3*3 pixels represented as a single array of 9 pixels)
    RGBTRIPLE local_grid[grid_size];

    // Define null pixel (assigned to pixels outside the image)
    RGBTRIPLE null_pixel = {0, 0, 0};

    // Loop on each pixel of the resulting image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Define local grid counter to 0
            int local_grid_counter = 0;

            // Build the local grid array for this pixel
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int l = j - 1; l <= j + 1; l++)
                {
                    // If the current local grid pixel is outside the image
                    if (k < 0 || l < 0 || k >= height || l >= width)
                    {
                        // Assign the null pixel (will not be taken into account for gradient)
                        local_grid[local_grid_counter] = null_pixel;
                    }
                    // Else store the pixel values into the local grid array
                    else
                    {
                        local_grid[local_grid_counter] = original_image[k][l];
                    }
                    // Increment local grid counter to move to next pixel to store in the array
                    local_grid_counter++;
                }
            }
            // Update pixel
            image[i][j] = get_target_pixel_edge(local_grid);
        }
    }
    // After finishing looping on each pixels, free the memory allocated to the original image
    free(original_image);
}

//--------------------------------------------------------------------------------------------------
// Helper function to compute target pixel value
//--------------------------------------------------------------------------------------------------
double max(double x, double y);

const double GX[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
const double GY[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

RGBTRIPLE get_target_pixel_edge(RGBTRIPLE grid[grid_size])
{
    RGBTRIPLE resulting_pixel;
    double gxb = 0;
    double gyb = 0;
    double tb = 0;
    BYTE tbb = 0;

    int green = 0;
    int red = 0;

    for (int i = 0; i < grid_size; i++)
    {
        gxb += grid[i].rgbtBlue * GX[i];
        gyb += grid[i].rgbtBlue * GY[i];
        tb = pow(pow(gxb, 2) + pow(gyb, 2), 0.5);
        tbb = round(max(tb, MAX_BYTE));






        green += grid[i].rgbtGreen;
        red += grid[i].rgbtRed;
    }
    resulting_pixel.rgbtBlue = (BYTE) round(blue / average_factor);
    resulting_pixel.rgbtGreen = (BYTE) round(green / average_factor);
    resulting_pixel.rgbtRed = (BYTE) round(red / average_factor);

    return resulting_pixel;


}
//--------------------------------------------------------------------------------------------------
// Helper function to get the target color byte value
//--------------------------------------------------------------------------------------------------
BYTE get_target_byte_edge(Color c, RGBTRIPLE pixel_input)
{
            gxb += grid[i].rgbtBlue * GX[i];
        gyb += grid[i].rgbtBlue * GY[i];
        tb = pow(pow(gxb, 2) + pow(gyb, 2), 0.5);
        tbb = round(max(tb, MAX_BYTE));



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
// Helper function to get the max of 2 doubles
//--------------------------------------------------------------------------------------------------
double max(double x, double y) {
    return (x > y) ? x : y;
}
