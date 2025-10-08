

PRICES = {
    "Baja Taco": 4.25,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

total = 0

# Prompt the user with items
try:
    while True:
        item = input('Item: ').title()
        if item in PRICES:
            total += PRICES[item]
            print('Total: $' + str(total))

# Stop program when user has finished the command
except EOFError:
    print('')
