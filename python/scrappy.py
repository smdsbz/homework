#coding=utf-8
import requests
import re

user = 'Anyone You\'d want to scrap'
user = str(input("Who do you want to scrap?\n>>> "))

url = 'https://github.com/%s' % user
html = requests.get(url).text

# scrap user repositories
target = re.findall('<a href="/%s/(.*?)" class="text-bold">' % user, html)

# scrap organization repositories
target.extend(re.findall('<a href="/%s/(.*?)" itemprop="name codeRepository">' % user, html))

for each in target:
	print(each)
