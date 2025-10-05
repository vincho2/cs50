from pyfiglet import Figlet
import sys
import argparse
from random import choice

figlet = Figlet()
font_list = figlet.getFonts()

parser = argparse.ArgumentParser(description='Display text in a random or specified font')
parser.add_argument('-f', '--font', help = 'Font to be used (must be in the available fonts)')

args = parser.parse_args

if args.font:
    if args.font in font_list:
        figlet.setFont(font=args.font)
    else:
        return_exit()
else:




if len(sys.argv) == 1:
    figlet.setFont(font = choice(font_list))

elif len(sys.argv) == 3 and sys.argv[1] in ('-f', '--font') and sys.argv[2] in font_list:
    figlet.setFont(font=sys.argv[2])

else:
    print('Invalid usage')
    sys.exit(1)

text = input('Input: ')
print(figlet.renderText(text))


def return_exit():
    print('Invalid usage')
    sys.exit(1)
