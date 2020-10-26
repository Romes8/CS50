#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float values;

    for (int i = 0; i < height; i++)
    {
        for (int u = 0; u < width; u++)
        {
            values = round((image[i][u].rgbtRed +  image[i][u].rgbtGreen + image[i][u].rgbtBlue) / 3.000);

            image[i][u].rgbtRed = values;
            image[i][u].rgbtGreen = values;
            image[i][u].rgbtBlue = values;

        }
    }
}


void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int u = 0; u < width; u++)
        {
            float sepiared = image[i][u].rgbtRed * .393 + image[i][u].rgbtGreen * .769 + image[i][u].rgbtBlue * .189;
            float sepiagreen = (image[i][u].rgbtRed * .349) + (image[i][u].rgbtGreen * .686) + (image[i][u].rgbtBlue * .168);
            float sepiablue = (image[i][u].rgbtRed * .272) + (image[i][u].rgbtGreen * .534) + (image[i][u].rgbtBlue * .131);

            int newRed = round(sepiared);
            int newGreen = round(sepiagreen);
            int newBlue = round(sepiablue);


            if (newRed > 255)
            {
                newRed = 255;
            }

            if (newGreen > 255)
            {
                newGreen = 255;
            }

            if (newBlue > 255)
            {
                newBlue = 255;
            }

            image[i][u].rgbtRed = newRed;
            image[i][u].rgbtGreen = newGreen;
            image[i][u].rgbtBlue = newBlue;

        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int temp[3];
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width / 2; i++)
        {
            temp[0] = image[j][i].rgbtBlue;
            temp[1] = image[j][i].rgbtGreen;
            temp[2] = image[j][i].rgbtRed;

            image[j][i].rgbtBlue = image[j][width - i - 1].rgbtBlue;
            image[j][i].rgbtGreen = image[j][width - i - 1].rgbtGreen;
            image[j][i].rgbtRed = image[j][width - i - 1].rgbtRed;

            image[j][width - i - 1].rgbtBlue = temp[0];
            image[j][width - i - 1].rgbtGreen = temp[1];
            image[j][width - i - 1].rgbtRed = temp[2];
        }
    }
}


void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int blue;
    int green;
    int red;

    float count;

    RGBTRIPLE temp[height][width];

    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {

            red = 0;
            blue = 0;
            green = 0;
            count = 0.00;

            for (int l = -1; l < 2; l++)
            {
                if (i + l < 0 || j + l > height - 1)
                {
                    continue;
                }

                for (int k = -1; k < 2; k++)
                {
                    if (j + k < 0 || j + k > width - 1)
                    {
                        continue;
                    }

                    blue += image[i + l][j + k].rgbtBlue;
                    green += image[i + l][j + k].rgbtGreen;
                    red += image[i + l][j + k].rgbtRed;
                    count++;
                }
            }

            temp[i][j].rgbtBlue = round(blue / count);
            temp[i][j].rgbtGreen = round(green / count);
            temp[i][j].rgbtRed = round(red / count);

        }
    }

    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
}


