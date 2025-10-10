
# Items & prices
MENU = {
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

total = 0.0

# Prompt the user with items as long as he does not press ctrl+D
try:
    while True:
        item = input('Item: ').title()
        # Get item price and add it to the sum (reprompt if item is not in the menu)
        if item in MENU:
            total += MENU[item]
            print(f'Total: ${total:.2f}')

# Stop program when user has finished the command
except EOFError:
    print('')
