#!/usr/bin/python

import json,os,subprocess

languages = ["en","eo","de"]

# Build the noun list documentation

NounJson = open(os.path.join("documentation","nounlist.json"),"r")
NounObj = json.load(NounJson)
NounHTML = open(os.path.join("documentation","nounlist.compoglot.html"),"w")
NounHTML.write("\n".join(NounObj["header"]))
NounHTML.write("\n\n\n")

for noun in NounObj["nouns"]:
	NounHTML.write("<tr>\n")
	NounHTML.write("<td>"+str(noun["id"])+"</td>\n")
	NounHTML.write("<td>${LANG( sub(n("+str(noun["id"])+",0,false,false,0,false,false,false)) punc 0 )}</td>\n")
	NounHTML.write("<td></td><td></td>\n</tr>\n\n")

NounHTML.write("\n\n\n")
NounHTML.write("\n".join(NounObj["footer"]))

NounHTML.close()

for lang in languages:
	subprocess.call(["compoglot","file",lang,os.path.join("documentation","nounlist.compoglot.html"),os.path.join("documentation","nounlist."+lang+".html")])

