#include<stdio.h>
#include<stdlib.h>

const int BUFFER_SIZE = 1000 ;
const int MAX_VALUE = BUFFER_SIZE * 8;
void * get_char_buffer(int size);
int * getbyte(char * buffer , int size);
void setbyte(char * buffer , int num);
const int BYTE_ARRY[] = {1<<0,1<<2,1<<3,1<<4,1<<5,1<<6,1<<7};



int main(void)
{
    char *buffer = (char *)get_char_buffer(1000);
    if(buffer == NULL)
    {
        exit(0);
    }
    setbyte(buffer , 7);
    setbyte(buffer , 2 );
    setbyte(buffer , 101);
    setbyte(buffer , 1);
    setbyte(buffer , 5);
    setbyte(buffer , 1001);
    setbyte(buffer , 1234);
    setbyte(buffer, 1024);
    int * arry  = getbyte(buffer , 8);
    for(int i = 0 ; i < 6 ; i++)
    {
        printf("%d \n" , *(arry+i));
    }
    printf("%s" , buffer);
    return 0;
}


int * getbyte(char * buffer , int size)
{

    int * arry = (int *)get_char_buffer(size * 4);
    int index = 999;
    int byteIndex;
    int arryIndex = 0;
    for(;index >= 0 ; index--)
    {
        byteIndex = 7;
        for( ; byteIndex >= 0 ; byteIndex --)
        {
            if(buffer[index] & BYTE_ARRY[byteIndex])
            {
                *(arry + arryIndex) = index * 8 + byteIndex;
                arryIndex = arryIndex + 1;
            }
        }
    }
    return arry;
}


void setbyte(char * buffer , int num)
{
    int high = num / 8 ;
    int low = num % 8;
    printf("num %d =>high :%d low : %d \n" , num , high,low);
    *(buffer + high) = *(buffer + high) +  BYTE_ARRY[low] ;
}


void * get_char_buffer(int size)
{
    return malloc(size);
}
