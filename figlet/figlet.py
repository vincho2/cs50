from pyfiglet import Figlet
import sys

def main():

    bool is_usage_ok = False

    if len(sys.argv) == 1:
        is_usage_ok = True
        
        text = get_input()





figlet = Figlet()
font_list = figlet.getFonts()
bool random_font = len(sys.argv) == 1
bool selected_font = (len(sys.argv) == 3 and sys.argv[2] in ('-f', '--font') and sys.argv[3] in font_list)

if  and :

    print('Invalid usage')
    sys.exit()




def get_input():
    return input('Input: ')


def

