#include<stdio.h>
#include<stdlib.h>

const int BUFFER_SIZE = 1000 ;

const int MAX_VALUE = BUFFER_SIZE * 8;
void * get_char_buffer(int size);
int * getbyte(char * buffer , int buffer_size, const int size);
void setbyte(char * buffer , int num);
const int BYTE_ARRY[] = {1<<0,1<<2,1<<3,1<<4,1<<5,1<<6,1<<7};



int main(void)
{
    char *buffer = (char *)get_char_buffer(BUFFER_SIZE);
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
    int * arry  = getbyte(buffer , BUFFER_SIZE, 9 );
    for(int i = 0 ; i < 9 ; i++)
    {
        printf("%d \n" , *(arry+i));
    }
    printf("%s" , buffer);
    return 0;
}


int * getbyte(char * buffer , int buffer_size, const int size)
{

    int * arry = (int *)get_char_buffer(size * 4);
    int index = buffer_size - 1;
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
                if(arryIndex == size)
                {
                    return arry ;
                }
            }
        }
    }
    return arry;
}


void setbyte(char * buffer , int num)
{
    if(num > MAX_VALUE)
    {
        printf("num must be < %d" , MAX_VALUE);
        return;
    }
    int high = num / 8 ;
    int low = num % 8;
    *(buffer + high) = *(buffer + high) +  BYTE_ARRY[low] ;
}


void * get_char_buffer(int size)
{
    return malloc(size);
}
