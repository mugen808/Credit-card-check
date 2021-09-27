#include <cs50.h>
#include <stdio.h>
#include <math.h>

string luhncheck(int array[], int digits, int array2[]);
int array(long long n);

int main(void)
{
    //Prompt user for card number
    long long cardnumber = get_long_long("Credit card number: ");

    //Sets n as the number of digits in the card
    int n = array(cardnumber);

    //Array creation with the correct number of slots (n)
    int cardcheck[n];
    int cardcheck2[n];

    //Variable needed to further calculation of items in each array
    long long remaining2 = 0;

    //Dividing factors to different number of card digits
    double divisor = pow(10, (n - 1));
    //Assign each number number of the card separately into an array (n digits)
    for (int i = 0; i < n; i++)
    {
        long long remaining = cardnumber / divisor;

        if (i == 0)
        {
            cardcheck[i] = remaining;
            remaining2 = remaining;
            divisor = divisor / 10;
            cardcheck2[i] = cardcheck[i];
            printf("Array [0]: %i\n", cardcheck[i]);
        }

        else if (i > 0)
        {
            remaining = cardnumber / divisor;
            cardcheck[i] = remaining - (remaining2 * 10);
            remaining2 = remaining;
            divisor = divisor / 10;
            cardcheck2[i] = cardcheck[i];
            printf("Array [%i]: %i\n", i, cardcheck[i]);
        }

    }


    //Using Luhn's Check for validation
    printf("Luhns number: %s\n", luhncheck(cardcheck, n, cardcheck2));



}

//Calculates the array size according to number of digits in the card.
int array(long long n)
{
    int digits = 1;
    do
    {
        n = n / 10;
        digits = digits + 1;
    }
    while (n > 10);
    return digits;
}

//Luhn's Algorithm testing
string luhncheck(int array[], int digits, int array2[])
{
    int sum = 1;
    int multipliers = 2;
    int multisum = 0;
    string validation;

    //Multiply every other item from second to last and store in each array
    for (int j = 0; j < digits; j += 2)
    {
        array[(digits - multipliers)] = (array[(digits - multipliers)] * 2);

        //If an element is greater than 10, we add its digits
        if (array[(digits - multipliers)] > 10)
        {
            int x = array[(digits - multipliers)] % 10;
            int y = array[(digits - multipliers)] / 10;
            array[(digits - multipliers)] = x + y;
        }
        multipliers = multipliers + 2;
    }

    //Sum of the elements in the array once previously multiplied
    for (int m = 0; m < digits; m++)
    {
        multisum = array[m] + multisum;
    }


    //Return the resolution by the card type/validation
    int factor = multisum % 10;
    printf("FACTOR: %i\n", factor);
    if (factor != 0)
    {
        printf("(FUNCTION) INVALID! | %i\n", multisum);
        validation = "INVALID!\n";
    }
    else if (factor == 0)
        {
        if (array2[0] == 4)
        {
            printf("(FUNCTION) VISA\n");
            validation = "VISA\n";
        }
        else if (array2[0] == 5)
        {
            printf("(FUNCTION) MASTERCARD\n");
            validation = "MASTERCARD\n";
        }
        else if (array2[0] == 3)
        {
            printf("(FUNCTION) AMEX\n");
            validation = "MASTERCARD\n";
        }
        else
        {
            printf("(FUNCTION ELSE1)\n");
            validation = "INVALID!\n";
        }
    }
    else
    {
        printf("(FUNCTION) ELSE FALSE\n");
        validation = "INVALID!\n";
    }
    return validation;
}
