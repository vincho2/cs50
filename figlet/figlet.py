from pyfiglet import Figlet
import sys

figlet = Figlet()
font_list = figlet.getFonts()

if len(sys.argv) != 1 and (len(sys.argv) != 3 or sys.argv[2] not in ('-f', '--font') or sys.argv[3] not in font_list):

    print('Invalid usage')
    sys.exit()

input('Input: ')
