from pyfiglet import Figlet
import sys
import argparse
from random import choice

def return_exit():
    print('Invalid usage')
    sys.exit(1)

figlet = Figlet()
font_list = figlet.getFonts()

class MyArgumentParser(argparse.ArgumentParser):
    def error(self, message):
        return_exit()

parser = MyArgumentParser(description='Display text in a random or specified font')
parser.add_argument('-f', '--font', help = 'Font to be used (must be in the available fonts)')

args = parser.parse_args()

if args.font:
    if args.font in font_list:
        figlet.setFont(font=args.font)
    else:
        return_exit()
else:
    figlet.setFont(font = choice(font_list))

text = input('Input: ')
print(figlet.renderText(text))


