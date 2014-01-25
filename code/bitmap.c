#include<stdio.h>
#include<stdlib.h>

const int BUFFER_SIZE = 1000 ;
const unsigned int  u_size = 0x7FFFFFFF / 8;
const int MAX_VALUE = u_size * 8;
const int BYTE_WIDTH = 8;

typedef struct BIT_MAP
{
    char *buffer;
    int size;
    long MAX_VALUE;
}BITMAP , *PBMAP;
const char BYTE_ARRY[] = {1<<0,1<<2,1<<3,1<<4,1<<5,1<<6,1<<7};

void * get_char_buffer(int size);
int * getbyte(char * buffer , const int buffer_size, const int size);
void setbyte(char * buffer , const unsigned int num);
PBMAP createBitMap(const int size);
bool setBitMap(PBMAP bitMap , const unsigned int num);
bool setbuffer(void * buffer ,const  int buffersize, const char num);
int *getByteMap(PBMAP bitMap , const unsigned int size);
PBMAP addBitMap(PBMAP bitMap1, PBMAP bitMap2);
int existNum(PBMAP bitMap ,unsigned int num);
int add(PBMAP bitMap ,  char *str);
bool existString(PBMAP bitMap ,  char * str);
unsigned int SDBMHash( char *str);
unsigned int RSHash( char *str);
unsigned int JSHash( char *str);
unsigned int PJWHash( char *str);
unsigned int ELFHash( char *str);
unsigned int BKDRHash( char *str);
unsigned int DJBHash( char *str);
unsigned int APHash( char *str);








int main(void)
{
    PBMAP bitmap = createBitMap(u_size);
    printf("%d\n" ,add(bitmap , "ssssss"));
    printf("%d\n" ,add(bitmap , "aaa"));
    printf("%d\n" ,add(bitmap , "sdfsd"));
    printf("%d\n" ,add(bitmap , "sdfs"));
    if(existString(bitmap , "sdfsd"))
    {
        printf("find\n");
    }
    return 0;
}

PBMAP createBitMap(const int size)
{
    PBMAP bitMap = (PBMAP)get_char_buffer(sizeof(BITMAP));
    if(bitMap != NULL)
    {
        bitMap->buffer = (char *)get_char_buffer(size);
        if(bitMap->buffer == NULL)
        {
            return NULL;
        }
        setbuffer((void *)bitMap->buffer , size , 0);
        bitMap->size = size;
        bitMap->MAX_VALUE =size * BYTE_WIDTH;
    }
    return bitMap;
}


bool setBitMap(PBMAP bitMap ,const unsigned int num)
{
    if(bitMap != NULL && (*bitMap).MAX_VALUE >= num)
    {
        bitMap->buffer[num / 8] |= BYTE_ARRY[num % 8];
        return true;
    }
    return false;
}


int *getByteMap(PBMAP bitMap , const unsigned int size)
{

    int * arry = (int *)get_char_buffer(size * 4);
    int index = bitMap->size - 1;
    int arryIndex = 0;
    int byteIndex = 0;
    for( ;index >=0 ; index-- )
    {
        byteIndex = 7;
        for(;byteIndex >= 0 ; byteIndex--)
        {
            if(bitMap->buffer[index] & BYTE_ARRY[byteIndex])
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

int * getbyte(char * buffer , int buffer_size, const int size)
{

    int * arry = (int *)get_char_buffer(size * 4);
    int index = buffer_size - 1;
    int byteIndex;
    int arryIndex = 0;
    setbuffer((void *)arry  , size * 4 , 0);
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


void setbyte(char * buffer , const unsigned int num)
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


bool setbuffer(void * buffer ,const int buffersize, const char num)
{
    int index = 0;
    char *pChar = (char *)buffer;
    if(pChar != NULL)
    {
        for( ; index < buffersize ; index++)
        {
            pChar[index] = num;
        }
        return true;
    }
    return false;
}


int existNum(PBMAP bitMap , unsigned int num)
{
    if(bitMap!= NULL && bitMap->MAX_VALUE >= num)
    {
        return (bitMap->buffer[num / BYTE_WIDTH] & BYTE_ARRY[num % BYTE_WIDTH])> 0 ? 1 : 0 ;
    }
    return -1;
}

unsigned int SDBMHash( char *str)
{
    unsigned int hash = 0;
    char *tmp = str ;
    while (*tmp)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*tmp++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

// RS Hash Function
unsigned int RSHash( char *str)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    char *tmp = str ;
    while (*tmp)
    {
        hash = hash * a + (*tmp++);
        a *= b;
    }

    return (hash & 0x7FFFFFFF);
}

// JS Hash Function
unsigned int JSHash( char *str)
{
    unsigned int hash = 1315423911;
    char *tmp = str;
    while (*tmp)
    {
        hash ^= ((hash << 5) + (*tmp++) + (hash >> 2));
    }

    return (hash & 0x7FFFFFFF);
}

// P. J. Weinberger Hash Function
unsigned int PJWHash( char *str)
{
    char *tmp = str;
    unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters    = (unsigned int)((BitsInUnignedInt  * 3) / 4);
    unsigned int OneEighth        = (unsigned int)(BitsInUnignedInt / 8);
    unsigned int HighBits         = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
    unsigned int hash             = 0;
    unsigned int test             = 0;

    while (*tmp)
    {
        hash = (hash << OneEighth) + (*tmp++);
        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return (hash & 0x7FFFFFFF);
}

// ELF Hash Function
unsigned int ELFHash( char *str)
{
    unsigned int hash = 0;
    unsigned int x    = 0;
    char *tmp = str;
    while (*tmp)
    {
        hash = (hash << 4) + (*tmp++);
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }

    return (hash & 0x7FFFFFFF);
}

// BKDR Hash Function
unsigned int BKDRHash( char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    char *tmp = str ;
    while (*tmp)
    {
        hash = hash * seed + (*tmp++);
    }

    return (hash & 0x7FFFFFFF);
}

// DJB Hash Function
unsigned int DJBHash( char *str)
{
    unsigned int hash = 5381;
    char *tmp = str;
    while (*tmp)
    {
        hash += (hash << 5) + (*tmp++);
    }

    return (hash & 0x7FFFFFFF);
}

// AP Hash Function
unsigned int APHash( char *str)
{
    unsigned int hash = 0;
    int i;
    char *tmp = str;
    for (i=0; *tmp; i++)
    {
        if ((i & 1) == 0)
        {
            hash ^= ((hash << 7) ^ (*tmp++) ^ (hash >> 3));
        }
        else
        {
            hash ^= (~((hash << 11) ^ (*tmp++) ^ (hash >> 5)));
        }
    }
    return (hash & 0x7FFFFFFF);
}



int  add(PBMAP bitMap , char *str)
{
    if(str == NULL || *str == '\0' )
    {
        return -1;
    }
    if(setBitMap(bitMap ,SDBMHash(str))&&
    setBitMap(bitMap , RSHash(str))&&
    setBitMap(bitMap , JSHash(str))&&
    setBitMap(bitMap , PJWHash(str))&&
    setBitMap(bitMap , ELFHash(str))&&
    setBitMap(bitMap , BKDRHash(str))&&
    setBitMap(bitMap , DJBHash(str))&&
    setBitMap(bitMap , APHash(str)))
    {
        return 0;
    }
    return -2;
}





bool existString(PBMAP bitMap ,  char * str)
{
    if(str == NULL || *str == '\0')
    {
        return false;
    }
    return existNum(bitMap ,SDBMHash(str)) == 1&&
    existNum(bitMap ,SDBMHash(str)) == 1&&
    existNum(bitMap , RSHash(str)) == 1&&
    existNum(bitMap , JSHash(str)) == 1&&
    existNum(bitMap , PJWHash(str)) == 1&&
    existNum(bitMap , ELFHash(str)) == 1&&
    existNum(bitMap , BKDRHash(str)) == 1&&
    existNum(bitMap , DJBHash(str)) == 1&&
    existNum(bitMap , APHash(str)) == 1;
}