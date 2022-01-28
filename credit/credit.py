from cs50 import get_int, get_string


def main():
    # Get credit card number
    number = get_credit_number()
    # Determine if a valid credit card using Luhn’s algorithm
    product = get_product_sum(number)
    digit = last_digit(number, product)
    first, second = get_digits(number)
    # Print type of credit card or invalid
    print_credit_card(number, digit, first, second)


def get_credit_number():
    # Get positive credit number
    while True:
        num = get_int("Number: ")
        if num > 0:
            break
    return num


def get_product_sum(num):
    length = str(num)
    count = 0
    total = 0
    # Get each individual digit and count the digits
    for i in length:

        digit = int(num % 10)
        count += 1

        # Multiply every other digit
        if count % 2 == 0:

            product = digit * 2
            # Add the digits
            if product > 9:
                # Add the products and sum
                total += int(product % 10)
                product = int(product / 10)

            total += product

        num = num / 10

    return total


def last_digit(num, product):
    # Initialize Variables
    length = str(num)
    count = 0
    total = product

    # Get each individual digit and count the digits
    for i in length:

        digit = int(num % 10)
        count += 1

    # Add sum from previous function to other digits
        if count % 2 != 0:
            total = int(total + digit)

        num = num / 10

    last = int(total % 10)

    return last


def get_digits(num):
    # Change digits to a string and just obtain index to get values
    length = str(num)
    first = int(length[0])
    second = int(length[0] + length[1])
    return first, second


def print_credit_card(number, digit, first, second):
    num = str(number)
    length = len(num)

    # Validate credit card type
    if digit == 0:
        if length == 15 and second == 34 or length == 15 and second == 37:
            print("AMEX")
        elif length == 16 and second > 50 and second <= 55:
            print("MASTERCARD")
        elif length == 13 and first == 4 or length == 16 and first == 4:
            print("VISA")
        else:
            print("INVALID")

    else:
        print("INVALID")


main()
