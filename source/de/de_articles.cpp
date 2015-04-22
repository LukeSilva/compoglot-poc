#include "de.h"
#include "../Language.h"
#include "../settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char defarticles[4*4][7]={
//Nominative
"der ","die ","das ","die ",
//Accusative
"den ","die ","das ","die ",
//Dative
"dem ","der ","dem ","den ",
//Genitive
"des ","der ","des ","der "
};
char indefarticles[4*4][7]={
//Nominative
"ein "  ,"eine " ,"ein "  ,"",
//Accusative
"einen ","eine " ,"ein "  ,"",
//Dative
"einem ","einer ","einem ","",
//Genitive
"eines ","einer ","eines ",""
};
char possessive_pronouns[4*4*12][9]={
"mein "   ,"meine "  ,"mein "   ,"meine "  ,
"meinen " ,"meine "  ,"mein "   ,"meine "  ,
"meinem " ,"meiner " ,"meinem " ,"meinen " ,
"meines " ,"meiner " ,"meines " ,"meiner " ,
"dein "   ,"deine "  ,"dein "   ,"deine "  ,
"deinen " ,"deine "  ,"dein "   ,"deine "  ,
"deinem " ,"deiner " ,"deinem " ,"deinen " ,
"deines " ,"deiner " ,"deines " ,"deiner " ,
"sein "   ,"seine "  ,"sein "   ,"seine  " ,
"seinen " ,"seine "  ,"sein "   ,"seine  " ,
"seinem " ,"seiner " ,"seinem " ,"seinen " ,
"seines " ,"seiner " ,"seines " ,"seiner " ,
"ihr "    ,"ihre "   ,"ihr "    ,"ihre "   ,
"ihren "  ,"ihre "   ,"ihr "    ,"ihre "   ,
"ihrem "  ,"ihrer "  ,"ihrem "  ,"ihren "  ,
"ihres "  ,"ihrer "  ,"ihres "  ,"ihrer "  ,
"sein "   ,"seine "  ,"sein "   ,"seine  " ,
"seinen " ,"seine "  ,"sein "   ,"seine  " ,
"seinem " ,"seiner " ,"seinem " ,"seinen " ,
"seines " ,"seiner " ,"seines " ,"seiner " ,
"unser "  ,"unsere " ,"unser "  ,"unsere " ,
"unseren ","unsere " ,"unser "  ,"unsere " ,
"unserem ","unserer ","unserem ","unseren ",
"unseres ","unserer ","unseres ","unserer ",
"euer "   ,"eure "   ,"euer "   ,"eure "   ,
"euren "  ,"eure "   ,"euer "   ,"eure "   ,
"eurem "  ,"eure "   ,"eurem "  ,"euren "  ,
"eures "  ,"eurer "  ,"eures "  ,"eurer "  ,
"Ihr "    ,"Ihre "   ,"Ihr "    ,"Ihre "   ,
"Ihren "  ,"Ihre "   ,"Ihr "    ,"Ihre "   ,
"Ihrem "  ,"Ihrer "  ,"Ihrem "  ,"Ihren "  ,
"Ihres "  ,"Ihrer "  ,"Ihres "  ,"Ihrer "  ,
"ihr "    ,"ihre "   ,"ihr "    ,"ihre "   ,
"ihren "  ,"ihre "   ,"ihr "    ,"ihre "   ,
"ihrem "  ,"ihrer "  ,"ihrem "  ,"ihren "  ,
"ihres "  ,"ihrer "  ,"ihres "  ,"ihrer "  ,
""        ,""        ,""        ,"viele "  ,
""        ,""        ,""        ,"viele "  ,
""        ,""        ,""        ,"vielen " ,
""        ,""        ,""        ,"vieler " ,
"dieser " ,"diese "  ,"dieses " ,"diese "  ,
"diesen " ,"diese "  ,"dieses " ,"diese "  ,
"diesem " ,"dieser " ,"diesem " ,"diesen " ,
"dieses " ,"dieser " ,"dieses " ,"dieser " };
char zahlen[11][10]={"null ","ein ","zwei ","drei ","vier ","fünf ","sechs ","sieben ","acht ","neun ","zehn "};
char* de::_getArticle(int id,int form,int num,int cas,int t){
 char typ = getNounType(id);
 if (t==-1)
 {
  if (cas>3) return (char*)"";
  //Definate Article
  int a = 0;
  if (typ=='f') a=1;
  else if (typ=='n') a=2;
  if (form) a=3;
   a+=cas*4;
  return &defarticles[a][0];
 }else if (t==-2){
  //Indefinate Article
  int a = 0;
  if (typ=='f') a=1;
  else if (typ=='n') a=2;
  if (form) a=3;
   a+=cas*4;
  return &indefarticles[a][0];
 }else if (t>0){
    int a = 0;
  if (typ=='f') a=1;
  else if (typ=='n') a=2;
  if (form) a=3;
   a+=cas*4;
  a+=(t-1)*16;
  return &possessive_pronouns[a][0];
 }
 return &indefarticles[3][0];
}
char* de::getArticle(int id,int form,int num,int cas,int t){
 char* buffer = (char*)calloc(BUFFER_SIZE,sizeof(char));
 strcat(buffer,_getArticle(id,form,num,cas,t));
 if (num > 10 || num < -10)
 {
  if(num > 0)
   sprintf(buffer,"%d ",num-1);
  else if (num <0)
   sprintf(buffer,"%d ",num+1);
 }else{
  if (num<0){
   strcat(buffer,DE_NEGATIVE);
   num=num*-1;
  }
  strcat(buffer,zahlen[num-1]);
 }
 return buffer;
}
