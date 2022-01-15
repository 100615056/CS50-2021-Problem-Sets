#include <stdio.h>

int main(void)
{
    int width = 4;
    int height = 4;
    int grid[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
        };

    
    

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        printf("%i ", grid[i+k][j+l]);
                    }
                }
            }
            printf("\n");
        }

    }

}