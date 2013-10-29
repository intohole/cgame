#include "stdio.h"
char  base[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
char  *base64_encode(char str[]);
char  *base64_discode(char str[]);
char  *xundiscode(char *xunlei);
char  *xuanfeng(char *xuan);
char  *kuaiche(char *kc);
char *flashencode(char *addr);
void main()
{  /*
char str[4]="abc";
char ans[5];
ans[0]=str[0]>>2;
  ans[1]=(str[0]&3)<<4|(str[1]>>4);
ans[2]=(str[1]&15)<<2|(str[2]>>6);
ans[3]=(str[2]&63);
     */
printf("%s",flashencode("baidu.com"));



getch();



}
char *base64_encode(char str[])
{
  char *ans;
  int lp=0,rp=0;
  int n=strlen(str);
  int len;
  if(n%3!=0)
  {
    len=n/3+1;

  }
  else
  {
    len=n/3;


  }

  ans=(char *)malloc(sizeof(char)*(len*4+1));

  for(;rp<(n/3*3);rp+=3,lp+=4)
  {
   *(ans+lp)=base[str[rp]>>2];

   *(ans+lp+1)=base[(str[rp]&3)<<4|(str[rp+1]>>4)];

   *(ans+lp+2)=base[(str[rp+1]&15)<<2|(str[rp+2]>>6)];

   *(ans+lp+3)=base[(str[rp+2]&63)];

 }
 switch(n%3)
 {
  case 0:break;
  case 1:
  *(ans+lp)=base[str[rp]>>2];

  *(ans+lp+1)=base[(str[rp]&3)<<4];

  *(ans+lp+2)=base[64];

  *(ans+lp+3)=base[64];

  break;
  case 2:
  *(ans+lp)=base[str[rp]>>2];

  *(ans+lp+1)=base[(str[rp]&3)<<4|(str[rp+1]>>4)];

  *(ans+lp+2)=base[(str[rp+1]&15)<<2];

  *(ans+lp+3)=base[64];
  break;

}

*(ans+len*4)='\0';
return ans;




}
char  *base64_discode(char str[])
{

  char *discode;
  char *svcode;
  int n=strlen(str);
  int lp,rp;
  int len=n/4*3;
  svcode=(char *)malloc(sizeof(char)*(n+1));
  discode=(char *)malloc(sizeof(char)*(len+1));


  for(lp=0;lp<n;lp++)
   for(rp=0;rp<65;rp++)
   {
     if(*(str+lp)==base[rp])
      { *(svcode+lp)=rp;

      }
    }

    for(lp=0,rp=0;lp<len;lp=lp+3,rp=rp+4)
    {

      *(discode+lp)=*(svcode+rp)<<2|(*(svcode+rp+1)&48)>>4;

      *(discode+lp+1)=(*(svcode+rp+1)&15)<<4|(*(svcode+rp+2)&60)>>2;

      *(discode+lp+2)=(*(svcode+rp+2)&3)<<6|*(svcode+rp+3);


    }

    *(discode+len)='\0';

    return discode;




  }
  char *xundiscode(char *xunlei)
  {
    char *restr;
    int len;
    restr=xunlei+10;
    restr = base64_discode(restr);
    restr=restr+2;
    len=strlen(restr);
    *(restr+len-2)='\0';
    return restr;

  }
  char *xuanfeng(char *xuan)
  {
    char *restr;
    int len;
    restr=xuan+7;
    restr=base64_discode(restr);
    return restr;




  }
  char  *kuaiche(char *kc)
  {
    char *restr;
    int len;
    restr=kc+11;
    restr=base64_discode(restr);
    len=strlen(restr);
    *(restr+len-10)='\0';
    restr=restr+10;

    return restr;





  }
  char *flashencode(char *addr)
  {
    char *sv;
    char *ans;
    char sign[]="Flashget://";
    char add[]="[FLASHGET]";
    char *tmp;
    int rp=0;
    int lp=0;


    tmp=(char *)malloc(sizeof(char)*(strlen(addr)+21));

    for(;rp<10;rp++)
    {
      *(tmp+rp)=add[rp];
      
    }
    rp=0;

    while (*(addr+rp)!='\0') {
      *(tmp+rp+10)=*(addr+rp);
      rp++;
    }
    
    


    for(lp=0;lp<11;lp++)
    {
      
      *(tmp+lp+rp+10)=add[lp];
      
    }

    *(tmp+lp+rp+10)='\0';
    printf("%s\n",tmp);
    sv=(char *)malloc(sizeof(char)*(strlen(tmp)+12));

    ans=base64_encode(tmp);
    
    free(tmp);
    
    
    
    for(rp=0;rp<11;rp++)
    {
      *(sv+rp)=sign[rp];
      
      
    }
    rp=0;
    while (*(ans+rp)!='\0') {
      *(sv+rp+11)=*(ans+rp);
      
      rp++;
    }
    *(sv+rp+11)='\0';
    free(ans);
    return sv;
    
    
    
    
    
  }
