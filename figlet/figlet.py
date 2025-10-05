from pyfiglet import Figlet
import sys
from random import choice

figlet = Figlet()
font_list = figlet.getFonts()

if len(sys.argv) == 1:
    figlet.setFont(font = choice(font_list))

elif len(sys.argv) == 3 and sys.argv[2] in ('-f', '--font') and sys.argv[3] in font_list:
    figlet.setFont(font=sys.argv[3])

else:
    print('Invalid usage')
    sys.exit()

text = input('Input: ')
print(figlet.renderText(text))
