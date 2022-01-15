#include <stdio.h>
#include <cs50.h>

//Prototypes
long get_credit_number(void);
long get_product_sum(long num);
long last_digit(long num, long product);

int main(void)
{
    long c = get_credit_number();

    long p = get_product_sum(c);

    long digit = last_digit(c, p);

//Initialize Variables
    long n = 0;
    int count = 0;
    long first = 0;
    long second = 0;

//Get each indiviudal digit and count the digits
    while (c > 0)
    {
        n = c % 10;
        count++;
        if (c < 10)
        {
            first = n;
        }

        if (c > 10 && c < 100)
        {
            second = c % 100;
        }

        c = c / 10;
    }

//Determine credit card type based on conditions

//American Express
    if ((digit == 0 & count == 15 & second == 34) || digit == 0 & count == 15 & second == 37)
    {
        printf("AMEX\n");
    }

//MasterCard
    else if (digit == 0 & count == 16 & second > 50 & second <= 55)
    {
        printf("MASTERCARD\n");
    }

//VISA
    else if ((digit == 0 & count == 13 & first == 4) || (digit == 0 & count == 16 & first == 4))
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }

}

long get_credit_number(void)
{
    long c;
//Prompt user for input
    do
    {
        c = get_long("Number: ");
    }
    while (c <= 0);
    return c;
}

long get_product_sum(long num)
{
//Initialize Variables
    long digit = 0;
    int n = 0;
    long product = 0;
    long sum = 0;
//Get each indiviudal digit and count the digits
    while (num > 0)
    {
        digit = num % 10;
        n++;

//Multiply every other digit
        if (n % 2 == 0)
        {
            product = (digit * 2);
//Add the digits
            if (product > 9)
            {
                sum = sum + product % 10;
                product = product / 10;
            }
            sum = sum + product;
        }
        num = num / 10;
    }
    
    return sum;
}

long last_digit(long num, long product)
{
//Initialize Variables
    long digit = 0;
    int n = 0;
    int sum = product;
    long last;

//Get each indiviudal digit and count the digits
    while (num > 0)
    {
        digit = num % 10;
        n++;

//Add sum from previous function to other digits
        if (n % 2 != 0)
        {
            sum = sum + digit;
        }
        num = num / 10;
    }

    last = sum % 10;
    return last;
}