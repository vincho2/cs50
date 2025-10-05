from pyfiglet import Figlet
import sys
import argparse
from random import choice

# --------------------------------------------------------------------------------------------------
# Generic invalid usage function
# --------------------------------------------------------------------------------------------------
def return_exit():
    print('Invalid usage')
    sys.exit(1)

# --------------------------------------------------------------------------------------------------
# Main code
# --------------------------------------------------------------------------------------------------

# Get fonts into a list
figlet = Figlet()
font_list = figlet.getFonts()

# Customize argument parser to display a generic message when exiting on error
class MyArgumentParser(argparse.ArgumentParser):
    def error(self, message):
        return_exit()

# Define the parser and font argument
parser = MyArgumentParser(description='Display text in a random or specified font')
parser.add_argument('-f', '--font', help = 'Font to be used (must be in the available fonts)')

# Create arguments namespace
args = parser.parse_args()

# Set the font if argument is present
if args.font:
    # Make sure the font exists
    if args.font in font_list:
        figlet.setFont(font=args.font)
    # Otherwise exit the program
    else:
        return_exit()
# Set the font to a random one if not specified
else:
    figlet.setFont(font = choice(font_list))

# Get input text and print it in the font
text = input('Input: ')
print(figlet.renderText(text))


