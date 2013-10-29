/*
    Õâ¸ö³ÌÐòÎ  ÔÚwintc »·¾³ÏÂ±àÒë ²¢ÇÒ²âÊÔ² ³É¹¦
    Ö÷ÒªË¼Ïë
    Ï  ÏÈ¶Ô ÒªÊäÈëµÄÎ  ÎÄ¼þ  ½øÐÐÔ¤´¦Àí
      1  ÏÈÉ  É¾³ý  Ô¤´¦Àí ²¿·Ö
      2 ÔÚÉ¾³ý ×¢ÊÍ²¿·Ö ºÍ¶àÓà   »Ø³µ ¿Õ¸ñ
      µÚ¶þ´ó²¿
        1 ÏÈÊä³ö ½ç·û
        2 ÔÚ¶ÔÎÄ¼þµÄ ¹Ø¼ü×Ö »¹ÓÐ ³£Á¿ ½øÐÐ´¦Àí



 */

#include "stdio.h"
#include "conio.h"

        int del_ba(char str[])
        {
int i=0;          /*


Õâ¸öÊÇ×Ö·û´®É¾³ý¶àÓà  ¿Õ¸ñº¯Êý



*/
int del;
while(str[i]==' ')
{
 i++;

             /* Õâ¸öÊÇ ¼ÆËã Ê××Ö·ûÊÇ·ñÎª ¿Õ×Ö·û ÊýÁ¿  */
}

if(i==0)
{
  return 1;


}
for(del=0;del<=strlen(str)-i;del++)
{
 *(str+del)=*(str+del+i);


}

return 1;
}

void main()

{
/*

¹Ø¼ü×ÖÊý×é ÀûÓÃstrcmp£¨£©Õâ¸öº¯Êý× Öð¸öÉó²é×Ö·û´®
»¹ÓÐ ÕâÑùµÄ
µÚÒ»·ûºÏ  Ç°ÃæÃ»ÓÐ ¡°Õ


*/
char *key_word[]={"char","main","int" ,"main","long","float","break",
"else","switch","case","enum","typedof","return","union","const",
"short","continue","for","signed","void","default","goto","sizeof",
"do","if","while","struct","staic"
};

char *ope_word[]={"=","<=","<",">=",">","+","-","*","%","/",">>","<<","==","!=",
"&","^","|","&&","||","++","--","~"
};
char oper[5];
int s_line=0;
char ch;
 /*
 ¶ÁÈ¡ÎÄ¼þ×Ö·û±äÁ¿
   int gd,gm;
 gd=DETECT;
 */


 int bc=0;/* É¾³ý¶àÓàµÄ¿Õ¸ñ */
 FILE *fp;/* ±£´æ¼´½«ÒªÒª´¦ÀíµÄÎÄ¼þÖ¸Õë */
 FILE *out;  /*  ±£´æµÚÒ»±é´¦ÀíÎÄ¼þ Ö÷Òª´¦ÀíÎª É¾³ý ¶àÓàµÄ ×Ö·û »Ø³µ ×¢ÊÍ ¶àÓà¿Õ¸ñ  */
 FILE   *var;
 FILE *ope;
 char o_file[100]; /*  Êý×éÔÚ ¶Ô ÎÄ¼þ É¾³ýÔ¤´¦Àí²¿·Ö Ê±ÓÃµ½
  */
/*

±£´æ±äÁ¿ÎÄ¼þÖ¸Õë

*/
FILE *sign;
 /*

 ½ç·û¹Ø¼ü×Ö   ÎÄ¼þÖ¸Õë
 */
 FILE *tmp;
 FILE *save;/*±£´æÎÄ¼þÖ¸Õë*/
 FILE *key; /*

 ¹Ø¼ü×Ö ÎÄ¼þÖ¸Õë
 */
 int s_row=0;
 int iskey=1;
 /*
 shezhi

 */

 /*
 ÊäÈëÞ ÎÄ¼þÃû³Æ ²¢   ¡®/¡¯ ½áÎ²


 */
 char str[15]="";
 char filename[40];
 printf("Please input filename  and end of '/'  \n");
 while((ch=getch())!='/')
 {
   filename[s_row]=ch;
   printf("%c",filename[s_row]);
   s_row++;



 }
 filename[s_row]='\0';

 s_row=0;

 if((fp=fopen(filename,"r"))==NULL)
 {
   printf("\n\n\n\n \t\t\t The fime name is wrong!");

   getch();
   exit(0);


 }

 tmp=fopen("tmp.dat","w");

 while(!feof(fp))
 {
  fgets(o_file,100,fp);
  del_ba(o_file);
  if(o_file[0]=='#')
{                           /*
del¡ª¡ªbaÕâ¸öÊÇÈ¥³ýÊý×éµÄÇ  Ç°Ãæ¿Õ¸ñµÄ
Ö®ºó¿´Êý×éµÚÒ»¸ö×Ö·ûÊÇ·ñÎª #
Èç¹ûÊÇ ÔòÖ¤Ã÷ÕâÊÇ¸ö Ô¤´¦ÀíµÄÃüÁî
ËùÒÔ ¹ýÈ¥

È¥³ýÔ¤´¦Àí²¿·Ö


*/
continue;
}
else
{
  fputs(o_file,tmp);

}


}
fclose(fp);
fclose(tmp);
out=fopen("saveda.dat","w");
tmp=fopen("tmp.dat","r");
while((ch=fgetc(tmp))!=EOF)
{
 if(ch=='/')
 {
   save=tmp;
   if(fgetc(save)=='*')
   {
     while(fgetc(tmp)!='*'||fgetc(tmp)!='/')
     {

   /*


 È¥³ý×¢ÊÍ ¹¦ÄÜ Ô­Àí
 ÈçÏÂ£º
 Èç¹û·¢ÏÖ ×Ö·û Îª  /
 ¼  ¼ì²âÏÂ¸ö×Ö·ûÊÇ·ñÎª *
 Èç¹û·¢ÏÖ Ôò ÈÏÎª ÕâÊÇ¸ö×¢ÊÍ
 ÔòÑ½øÈ½øÈëÑ­»· Ö±µ½·¢ÏÖ *  /
 Õâ¸ö×éºÏ ÔòÈÏÎª ×¢ÊÍ½áÊø

*/

}

ch=fgetc(tmp);


}


}

else if(ch=='\n')
{

 fputc(' ',out);

  /*
         if(!bc&&ch==' ')
         {
         fputc(ch,out);

         bc=1;  Ô­ÀíÈçÏÂ

           ·¢ÏÖ Ò Ê×¸ö¿Õ¸ñÖ®ºó  ÈÃÊ×¸ö¿Õ¸ñ ½øÈëÎÄ¼þ £¬ÒÔºóµÄ¿Õ¸ñË ÊäÈë£¬
           ²»ÁË£¬ÖªµÀÓöµ½±ðµÄ×Ö·û ²ÅÄÜÊäÈë



         }
           */

       }
       else  if(ch==' ')
       {
         fputc(ch,out);
         while((ch=fgetc(tmp))==' ')
         {



         }
         fputc(ch,out);


       }

       else
       {
     /* bc=0;

     */
        fputc(ch,out);

      }


    }
    remove("tmp.dat");
 /*  É¾³ýÎÄ¼þ
 */
    fclose(tmp);
    fclose(out);
    out=fopen("saveda.dat","r");
    sign=fopen("sign.dat","w");

 /*

 ´¦Àí ½ç·ûµÄ Ö÷Òª ²»ÊÇ×Ö·û´®µÄ ÈçÏÂ


 */
 var=fopen("var.dat","w");
 while((ch=fgetc(out))!=EOF)
 {
   if(ch==34)
    {      /*

    34 ¼´ ¡±µÄassicµÄÖµ





    */
    fprintf(sign,"< %c,->\t",ch);

    while((ch=fgetc(out))!=34&&ch!=EOF)
    {


    }
    ;
      /*

      Õ Èç¹û·¢ÏÖ " ÔòÖ¤Ã÷ÕâÊÇ¸öÊ ×Ö·û´® ¹æ¶¨
      ÔòÖ±µ½Ñ°ÕÒµ½×Ö·û´®   ½áÊø×Ö·û "
      Ìø³öÑ­»·

      */

      fprintf(sign,"<%c ,->\t",ch);

    }

    if(ch=='\'')
      { fprintf(sign,"<%c ,->         ",ch);
    while((ch=fgetc(out))!='\''&&ch!=EOF)
    {

    }
    fprintf(sign,"<%c ,->   ",ch);

  }
  if(ch=='('||ch==')'||ch=='['||ch==']'||ch=='{'||ch=='}'||ch==';'||ch==',')
  {
                 /*
                  fputc('<',sign);
                  fputc(ch,sign);
                  fputc('£­',sign);
                  fputc('>',sign);
                   */

                  fprintf(sign,"< %c,->   ",ch);
                }




              }
              fclose(sign);
              rewind(out);
 key=fopen("key.dat","w"); /*

 ´ò¿ª key¡£datÕâ¸öÎÄ¼þ Ö®ºóÎª¶ÁÐ´
 ×ö×¨±¸



 */
 ope=fopen("oper.dat","w");


 /*

 Ö÷Òª´¦Àí²¿·Ö

 */
 while((ch=fgetc(out))!=EOF)
 {
   if(ch=='\"')
   {

     while((ch=fgetc(out))!=EOF&&ch!='\"')
     {
       str[s_row]=ch;

       s_row++;
     }

     str[s_row]='\0';
     fprintf(var,"<\"%s\",string>    ",str);
     s_row=0;

   }
   if(ch=='\'')
    {      s_row=0;

      while((ch=fgetc(out))!='\''&&ch!=EOF)
      {
        str[s_row]=ch;


        s_row++;
      }
      str[s_row]='\0';
      getch();


      fprintf(var,"<%s ,str_char>",str);
      fprintf(sign,"<%c ,->   ",ch);
      s_row=0;



    }
    if(ch=='='||ch=='>'||ch=='<'||ch=='+'||ch=='-'||ch=='*'||ch=='%'||ch=='/'||ch=='&'||ch=='|'||ch=='!'||ch=='~')
     {oper[s_line]=ch;

   /*while(((ch=fgetc(out))!=EOF)|(ch=='='||ch=='>'||ch=='<'||ch=='+'||ch=='-'||ch=='*'||ch=='%'||ch=='/'||ch=='&'||ch=='|'||ch=='!'||ch=='~'))
         {       printf("%c",ch);
              s_line++;
              oper[s_line]=ch;


         }
     */

         save=out;
     ch=fgetc(out);  /*

     Õâ¸öÊÇÔ¤ÏÈ´¦Àí·¢ÏÖ·ûºÅºóÔò ¿´ÏÂ¸ö·ûºÅÊÇÊ²Ã´
     Èç¹û·¢ÏÖÊÇ ÌØÊâ·ûºÅÔò
     ²»·Å»ØÖ¸Õë
     ²»ÊÇ Ôò
     ·µ»Ø Ö¸Õë  ÒòÎªÔËËã·ûÖ»ÓÐÁ½¸ö×Ö·û


     */
     if(ch=='='||ch=='>'||ch=='<'||ch=='+'||ch=='-'||ch=='*'||ch=='%'||ch=='/'||ch=='&'||ch=='|'||ch=='!'||ch=='~')
     {
      oper[++s_line]=ch;

    }
    else
    {

     fseek(out,-1,SEEK_CUR);

   }
   oper[++s_line]='\0';

   for(s_line=0;s_line<28;s_line++)
   {

     if(strcmp(oper,ope_word[s_line])==0)
     {

       fprintf(ope,"<%s,ope>   ",oper);

     }

   }
   s_line=0;

   if(strcmp(oper,"=")==0)
   {

     while((ch=fgetc(out))!=EOF&&(ch!=';'&&ch!='('))
     {
       o_file[s_line]=ch;
       s_line++;
     }
     o_file[s_line]='\0';

     fseek(out,-1,SEEK_CUR);
     s_line=0;
     if(ch=='(')
     {
      fprintf(var,"<%s,var>    ",o_file);


    }
    else
    {

     fprintf(var,"<%s,string>    ",o_file);
   }
 }

}

if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))
{

str[s_row]=ch;          /*

Õâ¸öÊÇÊ±ä ´¦Àí²¿·Ö

*/
while((ch=fgetc(out))!=EOF&&((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||ch=='_'||(ch>='0'&&ch<='9')))
{
  s_row++;
  str[s_row]=ch;

}
fseek(out,-1,SEEK_CUR);
str[s_row+1]='\0';
for(s_row=0;s_row<27;s_row++)
{

  if(strcmp(str,key_word[s_row])==0)
   {fprintf(key,"<%s,->    ",str);
       iskey=0;            /*

       iskey ÊÇ¸ö±êÖ¾Î» Èç¹ûÊÇ ¹Ø¼ü×Ö
       Ôò ÖÃ0
       ±íÊ¾ÕâÊÇ¸ö¹Ø¼ü×ÖÒÑ´¦Àí
       */
       break;
     }


   }
   if(iskey)
    fprintf(var,"<%s,var>    ",str);
  iskey=1;
  s_row=0;


}

}
fclose(key);
fclose(ope);
fclose(fp);
fclose(out);
fclose(var);
textcolor(BLUE);
textbackground(WHITE);
  /*

  Õâ¸ö text textcolor
  Ö®ºó²»ÄÜÔÚÊ¹ÓÃ highvideo£¨£©
  ÕâÑù»áÔì³É³åÍ»


  */
  while(1)
   { printf("\n\n\t\tpress any key!!go on!\n");
 getch();
 clrscr();

 printf("\nWrok is over ,please choese a choice for youself\n");
 printf("1   the key  word\n");
 printf("2   the sign word\n");
 printf("3   the var  word\n");
 printf("4   the ope  word\n");
 printf("q   exit widow!   \n");

 ch=getch();
 printf("\n \t \tYour choice   :%c \n\n\t\t\tplease press Enter",ch);
 getch();



 switch(ch)
   {                         /*



   Õâ²¿·ÖÎª Êä³ö²¿·Ö


   */
   case 'q':exit(0);break;
   case '1':clrscr();
   printf("the key word  :\n");
   out=fopen("key.dat","r");
   while(!feof(out))
               {  fgets(o_file,100,out);  /*


               ÖðÐÐ¶Á³ö Êä³ö

               */
               printf("%s",o_file);

             }
             fclose(out);break;
             case '2':clrscr();
             printf("the sign word  :\n");
             out=fopen("sign.dat","r");
             while(!feof(out))
               {  fgets(o_file,100,out);
                 printf("%s",o_file);

               }
               fclose(out); break;
               case '3':clrscr();printf("the var word  :\n");out=fopen("var.dat","r");
               while(!feof(out))
                 {  fgets(o_file,100,out);
                   printf("%s",o_file);

                 }
                 fclose(out);break;
                 case '4':clrscr();printf("the operator word  :\n");out=fopen("oper.dat","r");
                 while(!feof(out))
                   {  fgets(o_file,100,out);
                     printf("%s",o_file);

                   }
                   fclose(out);break;
                   default :break;
                 }




               }
               getch();


             }
