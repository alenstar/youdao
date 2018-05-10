#! /usr/bin/python3
# coding = utf-8

# youdao.py
# To-do: get meaning of a word from youdao.com
# Author: alen
# Date: 2017/08/05

import urllib.parse
import urllib.request
from bs4 import BeautifulSoup
#import langid
import signal
import sys

GREEN = "\033[1;32m";
DEFAULT = "\033[0;49m";
BOLD = "\033[1m";
UNDERLINE = "\033[4m";
NORMAL = "\033[m";
RED = "\033[1;31m"

Black                    = "\x1b[30m";
DarkGray                 = "\x1b[30;1m";
Red                      = "\x1b[31m";
LightRed                 = "\x1b[31;1m";
Green                    = "\x1b[32m";
LightGreen               = "\x1b[32;1m";
Yellow                   = "\x1b[33m";
LightYellow              = "\x1b[33;1m";
Blue                     = "\x1b[34m";
LightBlue                = "\x1b[34;1m";
Magenta                  = "\x1b[35m";
LightMagenta             = "\x1b[35;1m";
Cyan                     = "\x1b[36m";
LightCyan                = "\x1b[36;1m";
Gray                     = "\x1b[37m";
White                    = "\x1b[37;1m";
	
def quit(signum, frame):
    print(' ')
    sys.exit()
    
def getHtml(word = 'bless'):
    #word = raw_input("Please input your word:")
    url = 'http://dict.youdao.com/search'
    data = urllib.parse.urlencode({'le': 'eng', 'q': word, 'keyfrom': 'dict'})
    #data = urllib.parse.urlencode({'q': word, 'keyfrom': 'dict'})
    #print("data: ", data)
    req = urllib.request.Request(url, data.encode('utf-8'))
    req.add_header('User-Agent', 'Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0)')
    html = urllib.request.urlopen(req).read()
    return html.decode('utf-8')
    
def showMeaning(word = 'bless'):
    #word = input('Please input your word:')
    #print("RES:", getHtml(word))
    wordSoup = BeautifulSoup(getHtml(word), 'lxml')
    # show the word
    # print ("Word:\t", wordSoup.find('span', {'class', 'keyword'}).string)
    print( '\t' + White + wordSoup.find('span', {'class', 'keyword'}).string + DEFAULT)
    # show the pronounce
    print (BOLD + "Prounaounciation:" + Gray + '\n' , end='\t')
    for prons in wordSoup.find_all('span', {'class', 'phonetic'}):
        print (prons.string, end=' ')
    print(NORMAL)
    # show meaning
    print (BOLD + 'Meaning:'+ NORMAL + LightYellow)
    for meaning in wordSoup.find_all('span', {'class', 'def'}):
        if meaning.string != "" :
            print ('\t' + meaning.string)
    print(NORMAL, end=' ')
    
def sample(word = 'bless'):
    print ("Input world to continue, input Q/q to quit.")
    signal.signal(signal.SIGINT, quit)
    signal.signal(signal.SIGTERM, quit)	
    while True:
        selection = input(">>>")
        if selection == "" :
            continue
        elif selection in ['Q', 'q']:
            exit()
        else :
             showMeaning(selection)
    
    
if __name__ == '__main__':
    sample()
