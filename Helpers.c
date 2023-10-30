#include "helpers.h"
#include <math.h>
#include <stdio.h>

#define RED 0
#define GREEN 1
#define BLUE 2
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // covert int colours to float
            float originalRed = image[i][j].rgbtRed;
            float originalBlue = image[i][j].rgbtBlue;
            float originalGreen = image[i][j].rgbtGreen;

            // Calculate the average and round up to whole number
            int average = round((originalRed + originalBlue + originalGreen) / 3.0);

            // convert colour to the average
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)

        {
            // convert values to float
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            // Calculating the sepia values for Red Green and blue
            int sepiaRed = round((originalRed * 0.393) + (originalGreen * 0.769) + (originalBlue * 0.189));
            int sepiaGreen = round((originalRed * 0.349) + (originalGreen * 0.686) + (originalBlue * 0.168));
            int sepiaBlue = round((originalRed * 0.272) + (originalGreen * 0.534) + (originalBlue * 0.131));

            // Ensuring the colour values doesnt exceed 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Convert colours to their sepia value
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}
// get blur function that returns an integer value
int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int colour_position)
{
    int sum = 0;
    float counter = 0;
    for (int row = i - 1; row <= (i + 1); row++)
    {
        for (int column = j - 1; column <= (j + 1); column++)
        {
            if (row < 0 || row >= height || column < 0 || column >= width)
            {
                continue;
            }
            else if (colour_position == RED)
            {
                sum += image[row][column].rgbtRed;
            }
            else if (colour_position == GREEN)
            {
                sum += image[row][column].rgbtGreen;
            }
            else if (colour_position == BLUE)
            {
                sum += image[row][column].rgbtBlue;
            }
            counter++;
        }
    }
    return round(sum / counter);
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy the RGTriple color
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // use the getblur function
            image[i][j].rgbtRed = getBlur(i, j, height, width, copy, RED);
            image[i][j].rgbtGreen = getBlur(i, j, height, width, copy, GREEN);
            image[i][j].rgbtBlue = getBlur(i, j, height, width, copy, BLUE);
        }
    }
    return;
}
