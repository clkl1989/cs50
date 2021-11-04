#include <cs50.h>
#include <stdio.h>

int main(void)
{
// ask user for height input get_int
// check if input is between 1-8
// if True, print blocks
// if height = X, start from row 1 to X, row i = [(8-i)*space] & [(i)*#] & [2*space] & [(i)*#]
// if F, get_int again
int height;
    do
    {
        height = get_int("Enter an integer between 1 to 8, both inclusive\n");
    }

    while (height > 8 || height < 1);

int r;
int space;
int lh;
int rh;

for (r = 1; r <= height; r++)
{
    for (space = height-r; space > 0; space--)
    {
        printf(" ");
    }

    for (lh = 1; lh <= r; lh++)
    {
        printf("#");
    }

    printf("  ");
    for (rh = 1; rh <= r; rh++)
    {
        printf("#");
    }

    printf("\n");
}
}