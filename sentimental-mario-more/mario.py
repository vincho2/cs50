from cs50 import get_int

height = 0

# Ask the user to provide a block height
while True:
    height = get_int("Height: ")
    if height in range(1, 9, 1):
        break

# Print the block
for i in range(height):
    print((height - i - 1) * " " + (i + 1) * "#")
