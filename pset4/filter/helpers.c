#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average_RGB = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0); //why when i put /3 then my code does not give the same results?
            image[i][j].rgbtBlue = average_RGB;
            image[i][j].rgbtGreen = average_RGB;
            image[i][j].rgbtRed = average_RGB;
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
            int ori_rgbtRed = image[i][j].rgbtRed;
            int ori_rgbtGreen = image[i][j].rgbtGreen;
            int ori_rgbtBlue = image[i][j].rgbtBlue;
            
            if (round(0.393 * ori_rgbtRed  + 0.769 * ori_rgbtGreen + 0.189 * ori_rgbtBlue) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            
            else
            {
                image[i][j].rgbtRed = round(0.393 * ori_rgbtRed  + 0.769 * ori_rgbtGreen + 0.189 * ori_rgbtBlue);
            }
            
            if (round(0.349 * ori_rgbtRed + 0.686 * ori_rgbtGreen + 0.168 * ori_rgbtBlue) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            
            else
            {
                image[i][j].rgbtGreen = round(0.349 * ori_rgbtRed + 0.686 * ori_rgbtGreen + 0.168 * ori_rgbtBlue);
            }
            
            if (round(0.272 * ori_rgbtRed + 0.534 * ori_rgbtGreen + 0.131 * ori_rgbtBlue) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            
            else
            {
                image[i][j].rgbtBlue = round(0.272 * ori_rgbtRed + 0.534 * ori_rgbtGreen + 0.131 * ori_rgbtBlue);
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (width % 2 == 0) //if width has even number
    {
        for (int i = 0; i < height; i++)
        {
            int center_point = width / 2.0;
        
            for (int j = 0; j < center_point; j++)  
            {
                RGBTRIPLE temp;
                temp   = image[i][j];
                image[i][j]   = image[i][width - 1 - j];
                image[i][width - 1 - j]   =  temp;
            }
        }
    }
    
    if (width % 2 == 1) //if width has odd number
    {
        for (int i = 0; i < height; i++)
        {
            int center_point = trunc(width / 2.0);
        
            for (int j = 0; j < center_point; j++)  
            {
                RGBTRIPLE temp;
                temp   = image[i][j];
                image[i][j]   = image[i][width - 1 - j];
                image[i][width - 1 - j]   =  temp;
            }
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    
    for (int i = 0; i < height; i++) //create a temp copy of the image with each original pixel color
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int m = i - 1, n = j - 1, p = i + 1, q = j + 1;
            
            if (i == 0)
            {
                if (j == 0) //top left pixel
                {
                    image[i][j].rgbtRed = round((temp[p][j].rgbtRed + temp[i][q].rgbtRed + temp[p][q].rgbtRed + temp[i][j].rgbtRed) / 4.0);
                    image[i][j].rgbtBlue = round((temp[p][j].rgbtBlue + temp[i][q].rgbtBlue + temp[p][q].rgbtBlue + temp[i][j].rgbtBlue) / 4.0);
                    image[i][j].rgbtGreen = round((temp[p][j].rgbtGreen + temp[i][q].rgbtGreen + temp[p][q].rgbtGreen + temp[i][j].rgbtGreen) / 4.0);
                }
            
                else if (j == width - 1) //top right pixel
                {
                    image[i][j].rgbtRed = round((temp[p][j].rgbtRed + temp[i][n].rgbtRed + temp[p][n].rgbtRed + temp[i][j].rgbtRed) / 4.0);
                    image[i][j].rgbtBlue = round((temp[p][j].rgbtBlue + temp[i][n].rgbtBlue + temp[p][n].rgbtBlue + temp[i][j].rgbtBlue) / 4.0);
                    image[i][j].rgbtGreen = round((temp[p][j].rgbtGreen + temp[i][n].rgbtGreen + temp[p][n].rgbtGreen + temp[i][j].rgbtGreen) / 4.0);
                }
                
                else //top row middle pixels
                {
                    image[i][j].rgbtRed = round((temp[p][j].rgbtRed + temp[i][q].rgbtRed + temp[p][q].rgbtRed + temp[i][n].rgbtRed + temp[p][n].rgbtRed + temp[i][j].rgbtRed) / 6.0);
                    image[i][j].rgbtBlue = round((temp[p][j].rgbtBlue + temp[i][q].rgbtBlue + temp[p][q].rgbtBlue + temp[i][n].rgbtBlue + temp[p][n].rgbtBlue + temp[i][j].rgbtBlue) / 6.0);
                    image[i][j].rgbtGreen = round((temp[p][j].rgbtGreen + temp[i][q].rgbtGreen + temp[p][q].rgbtGreen + temp[i][n].rgbtGreen + temp[p][n].rgbtGreen + temp[i][j].rgbtGreen) / 6.0);
                }
            }
                
            else if (i == height - 1) 
            {
                if (j == 0) //bottom left pixel
                {
                    image[i][j].rgbtRed = round((temp[m][j].rgbtRed + temp[i][q].rgbtRed + temp[m][q].rgbtRed + temp[i][j].rgbtRed) / 4.0);
                    image[i][j].rgbtBlue = round((temp[m][j].rgbtBlue + temp[i][q].rgbtBlue + temp[m][q].rgbtBlue + temp[i][j].rgbtBlue) / 4.0);
                    image[i][j].rgbtGreen = round((temp[m][j].rgbtGreen + temp[i][q].rgbtGreen + temp[m][q].rgbtGreen + temp[i][j].rgbtGreen) / 4.0);
                }
                
                else if (j == width - 1) //bottom right pixel
                {
                    image[i][j].rgbtRed = round((temp[m][j].rgbtRed + temp[i][n].rgbtRed + temp[m][n].rgbtRed + temp[i][j].rgbtRed) / 4.0);
                    image[i][j].rgbtBlue = round((temp[m][j].rgbtBlue + temp[i][n].rgbtBlue + temp[m][n].rgbtBlue + temp[i][j].rgbtBlue) / 4.0);
                    image[i][j].rgbtGreen = round((temp[m][j].rgbtGreen + temp[i][n].rgbtGreen + temp[m][n].rgbtGreen + temp[i][j].rgbtGreen) / 4.0);
                }
                
                else //bottom row middle pixels
                {
                    image[i][j].rgbtRed = round((temp[m][j].rgbtRed + temp[i][q].rgbtRed + temp[m][q].rgbtRed + temp[i][n].rgbtRed + temp[m][n].rgbtRed + temp[i][j].rgbtRed) / 6.0);
                    image[i][j].rgbtBlue = round((temp[m][j].rgbtBlue + temp[i][q].rgbtBlue + temp[m][q].rgbtBlue + temp[i][n].rgbtBlue + temp[m][n].rgbtBlue + temp[i][j].rgbtBlue) / 6.0);
                    image[i][j].rgbtGreen = round((temp[m][j].rgbtGreen + temp[i][q].rgbtGreen + temp[m][q].rgbtGreen + temp[i][n].rgbtGreen + temp[m][n].rgbtGreen + temp[i][j].rgbtGreen) / 6.0);
                }
            }
            
            else
            {
                if (j == 0) //left center pixels
                {
                    image[i][j].rgbtRed = round((temp[m][j].rgbtRed + temp[i][q].rgbtRed + temp[m][q].rgbtRed + temp[p][j].rgbtRed + temp[p][q].rgbtRed + temp[i][j].rgbtRed) / 6.0);
                    image[i][j].rgbtBlue = round((temp[m][j].rgbtBlue + temp[i][q].rgbtBlue + temp[m][q].rgbtBlue + temp[p][j].rgbtBlue + temp[p][q].rgbtBlue + temp[i][j].rgbtBlue) / 6.0);
                    image[i][j].rgbtGreen = round((temp[m][j].rgbtGreen + temp[i][q].rgbtGreen + temp[m][q].rgbtGreen + temp[p][j].rgbtGreen + temp[p][q].rgbtGreen + temp[i][j].rgbtGreen) / 6.0);
                }
                
                else if (j == width - 1) //right center pixels
                {
                    image[i][j].rgbtRed = round((temp[m][j].rgbtRed + temp[i][n].rgbtRed + temp[m][n].rgbtRed + temp[p][j].rgbtRed + temp[p][n].rgbtRed + temp[i][j].rgbtRed) / 6.0);
                    image[i][j].rgbtBlue = round((temp[m][j].rgbtBlue + temp[i][n].rgbtBlue + temp[m][n].rgbtBlue + temp[p][j].rgbtBlue + temp[p][n].rgbtBlue + temp[i][j].rgbtBlue) / 6.0);
                    image[i][j].rgbtGreen = round((temp[m][j].rgbtGreen + temp[i][n].rgbtGreen + temp[m][n].rgbtGreen + temp[p][j].rgbtGreen + temp[p][n].rgbtGreen + temp[i][j].rgbtGreen) / 6.0);
                }
                
                else //center pixels
                {
                    image[i][j].rgbtRed = round((temp[m][j].rgbtRed + temp[i][n].rgbtRed + temp[m][n].rgbtRed + temp[p][j].rgbtRed + temp[p][n].rgbtRed + temp[m][q].rgbtRed + temp[i][q].rgbtRed + temp[p][q].rgbtRed + temp[i][j].rgbtRed) / 9.0);
                    image[i][j].rgbtBlue = round((temp[m][j].rgbtBlue + temp[i][n].rgbtBlue + temp[m][n].rgbtBlue + temp[p][j].rgbtBlue + temp[p][n].rgbtBlue + temp[m][q].rgbtBlue + temp[i][q].rgbtBlue + temp[p][q].rgbtBlue + temp[i][j].rgbtBlue) / 9.0);
                    image[i][j].rgbtGreen = round((temp[m][j].rgbtGreen + temp[i][n].rgbtGreen + temp[m][n].rgbtGreen + temp[p][j].rgbtGreen + temp[p][n].rgbtGreen+ temp[m][q].rgbtGreen + temp[i][q].rgbtGreen + temp[p][q].rgbtGreen + temp[i][j].rgbtGreen) / 9.0);
                }
            }
            
        }
    }
    return;
}
