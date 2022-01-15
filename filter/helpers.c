#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculate average
            float average = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            //Round average to nearest integer value
            average = round(average);

            //Map new RGB values to ouput file
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
            //Calculate Sepia colour values
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            //Round Sepia values to nearest integer
            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

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

            //Map new RGB values to ouput file
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //int k = width;
    float tempRed = 0;
    float tempGreen = 0;
    float tempBlue = 0;

    for (int i = 0; i < height; i++)
    {
        //Defining the end of array
        int k = width - 1;

        for (int j = 0; j < k; j++)
        {
            //Storing pixel in temporary variables
            tempRed  = image[i][j].rgbtRed;
            tempGreen  = image[i][j].rgbtGreen;
            tempBlue  = image[i][j].rgbtBlue;

            //Moving last pixel to start of array
            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;

            //Moving first pixel to end of array
            image[i][k].rgbtRed = tempRed;
            image[i][k].rgbtGreen = tempGreen;
            image[i][k].rgbtBlue = tempBlue;

            k--;
        }

    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Initalize Variables
    float Redtotal = 0;
    float Greentotal = 0;
    float Bluetotal = 0;
    float counter = 0;

    float blurRed = 0;
    float blurGreen = 0;
    float blurBlue = 0;

    RGBTRIPLE tempArr[height][width]; //Make a temporary array to store calculates values

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempArr[i][j] = image[i][j];
        }
    }

    //Iterate through original array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Make 3 x 3 Pixel Box
            for (int k = -1; k < 2; k++) //Row
            {
                for (int l = -1; l < 2; l++) //Column
                {
                    //Validate pixel selection
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        //Calculate totals and increase pixel count
                        Redtotal += image[i + k][j + l].rgbtRed;
                        Greentotal += image[i + k][j + l].rgbtGreen;
                        Bluetotal += image[i + k][j + l].rgbtBlue;
                        counter += 1;
                    }
                }
            }

            //Calculate average
            blurRed = (float)(Redtotal / counter);
            blurGreen = (float)(Greentotal / counter);
            blurBlue = (float)(Bluetotal / counter);

            //Round average and store in temporary array
            tempArr[i][j].rgbtRed = round(blurRed);
            tempArr[i][j].rgbtGreen = round(blurGreen);
            tempArr[i][j].rgbtBlue = round(blurBlue);

            //Reset counter and total
            counter = 0;
            Redtotal = 0;
            Greentotal = 0;
            Bluetotal = 0;
        }
    }

    //Input temporary array values to original array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tempArr[i][j];
        }
    }
    return;
}
