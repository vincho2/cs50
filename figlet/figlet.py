from pyfiglet import Figlet
import sys

def main():

    figlet = Figlet()
    font_list = figlet.getFonts()

    if len(sys.argv) == 1:

        figlet.setFont(font = choice(font_list))

    elif len(sys.argv) == 3 and sys.argv[2] in ('-f', '--font'):

        if sys.argv[3] in font_list:
            figlet.setFont(font=sys.argv[3])

    else:
        print('Invalid usage')
        sys.exit()

    text = input('Input: ')
    print(figlet.renderText(text))






bool random_font = len(sys.argv) == 1
bool selected_font = (len(sys.argv) == 3 and sys.argv[2] in ('-f', '--font') and sys.argv[3] in font_list)

if  and :

    print('Invalid usage')



def get_input():
    return


def get_random_font(font_list):



