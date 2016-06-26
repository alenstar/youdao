#! /usr/bin/python3
# coding = utf-8

# youdao.py
# To-do: get meaning of a word from youdao.com
# Author: Steven
# Date: 2013/04/21

import urllib.parse
import urllib.request
from bs4 import BeautifulSoup
#import langid
import sys

#inputDecode = sys.stdin.encoding
#outputDecode = sys.stdout.encoding


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
    print ("Word:\t", wordSoup.find('span', {'class', 'keyword'}).string)
    # show the pronounce
    print ("Prounaounciation:")
    for prons in wordSoup.find_all('span', {'class', 'phonetic'}):
        print ((prons.string))
    # show meaning
    print ('Meaning:')
    for meaning in wordSoup.find_all('span', {'class', 'def'}):
        if meaning.string != "" :
            print (meaning.string)
    
    
def sample(word = 'bless'):
    print ("Input world to continue, input Q/q to quit.")	
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
