#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
// ask user for credit card number (long) - done
//check if length of credit card number is 13, 15 or 16? if N -> invalid number - done
//check if number fulfills checksum criteria? if N -> invalid number
//checksum logic:
//#1: identify digits to multiply by 2 (second last onwards)
//#2: get product of 2xdigit
//#3: add all prod as sumprod
//#4: add all nonmultiplydigit and sumprod to get checksum
//#5: checksum divide by 10, if remainder == 0, valid CC number
//check if number starts with 34 or 37 -> American Express
//check if number starts with 4 -> VISA
//check if number starts with 51, 52, 53, 54, 55 -> Mastercard
//otherwise -> invalid number

    long cc;
    int length;

    do
    {
        cc = get_long("Enter credit card number\n");
    }

    while (cc <= 0);

    length = log10(cc) + 1;

    if (length < 13 || length == 14 || length > 16)

    {
        printf("INVALID\n");
    }

    else
    {
        // int d1r = cc%10/1; here i = 10
        // int d2r2 = 2*(cc%100)/10; here i = 100, logvalue = 2
        // int d3r = (cc%1000)/100; here i = 1000
        // int d4r2 = 2*(cc%10000)/1000; i = 10000
        // int d5r = (cc%100000)/10000;
        // int d6r2 = 2*(cc%1000000)/100000;
        // int d7r = (cc%10000000)/1000000;
        // int d8r2 = 2*(cc%100000000)/10000000;
        // int d9r = (cc%1000000000)/100000000;
        // int d10r2 = 2*(cc%10000000000)/1000000000;
        // int d11r = (cc%100000000000)/10000000000;
        // int d12r2 = 2*(cc%1000000000000)/100000000000;
        // int d13r = (cc%10000000000000)/1000000000000;
        // int d14r2 = 2*(cc%100000000000000)/10000000000000;
        // int d15r = (cc%1000000000000000)/100000000000000;
        // int d16r2 = 2*(cc%10000000000000000)/1000000000000000;

        long i;
        int logvalue, sum = 0, numtoadd, n ;

        for (i = 10; i < 100000000000000000; i = i * 10)
        {
            logvalue = log10(i);

            //printf("i is %ld\n",i);
            //printf("logvalue is %d\n", logvalue);

            if (logvalue % 2 == 0) // if logvalue is even
            {
                numtoadd = 2 * ((cc % i) / (i / 10));

                if (numtoadd >= 10) //if 2*digit is >10, then need to break up the number into 2 digits to sum them together
                {
                    sum = sum + (numtoadd % 10 + numtoadd / 10);
                    //printf("long number to add is %d\n", numtoadd);
                }

                else
                {
                    sum = sum + numtoadd;
                    //printf("2*number to add is %d\n", numtoadd);
                }

            }

            else
            {
                sum = sum + ((cc % i) / (i / 10));
                //printf("single number to add is %ld\n",(cc%i)/(i/10));
            }

            //printf("sum is now %d\n\n", sum);
        }

        if (sum % 10 != 0)
        {
            printf("INVALID\n");
        }

        else
        {
            int firstd, first2d;

            //printf("%ld\n", cc);
            //printf("%d\n", length);
            //printf("%f\n", pow(10, length-1));

            firstd = cc / pow(10, length - 1);
            //printf("%d\n", firstd);

            first2d = cc / pow(10, length - 2);
            //printf("%d\n", first2d);

            if (firstd == 4)
            {
                printf("VISA\n");
            }

            else
            {
                if (first2d == 34 | first2d == 37)
                {
                    printf("AMEX\n");
                }

                else
                {
                    if (first2d > 50 && first2d < 56)
                    {
                        printf("MASTERCARD\n");
                    }

                    else
                    {
                        printf("INVALID\n"); //this actually may be other cards that are not in the scope of this problem
                    }
                }
            }
        }

    }

}