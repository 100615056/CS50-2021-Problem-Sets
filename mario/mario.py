from cs50 import get_int


def main():
    # Validate height choice
    h = valid_height()

    # Print Pyramid
    print_pyramid(h)


def valid_height():
    while True:
        # Ask for height
        height = get_int("Height: ")
        # Make height between 1 and 8 inclusive
        if height >= 1 and height <= 8:
            break
    return height


def calculate_spaces(height):
    # Calculate spaces needed
    space = height - 1
    return space


def calculate_hashes(n):
    # Calculate hash
    hashes = n
    return hashes


def print_pyramid(height):
    min_value = 1
    max_value = height

    # Calculate Spaces and Hashes
    for i in range(height):
        # Calculate spaces and hashes
        s = calculate_spaces(max_value)
        h = calculate_hashes(min_value)

        # Print Pyramid
        # Print Spaces
        for j in range(s):
            print(" ", end="")
        # Print left hashes
        for k in range(h):
            print("#", end="")
        # Print Gap
        print("  ", end="")
        # Print Right hashes
        for k in range(h):
            print("#", end="")
        print()

        # Change values for each row
        min_value += 1
        max_value -= 1


main()
