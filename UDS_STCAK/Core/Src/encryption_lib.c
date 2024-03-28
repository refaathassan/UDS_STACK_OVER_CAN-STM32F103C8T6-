#include"STD_TYPES.h"
#include<string.h>
#include "encryption_lib.h"
static void swap(u8 *a, u8 *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
static void intiate_key_s(u8 *key,u8 *s_arr,u8 *key_arr)
{
u8 key_count=(u8)strlen(key);
u8 rem=0;
for(int i=0;i<256;i++)
{
    s_arr[i]=i;
}
for(int i=0;i<256;i++)
{
    if(i<key_count)
    {
     key_arr[i]=key[i];
    }
    else if(i>=key_count)
    {
       rem=(i%key_count);
      key_arr[i]= key[rem];

    }
}
}


static void KSA(u8* s_arr,u8 *key_arr)
{
    u32 j=0;
    for(int i=0;i<256;i++)
    {
       j=(j+s_arr[i]+key_arr[i])%256;
       swap(&s_arr[i],&s_arr[j]);
    }
}

static void PRGA(u8 *s_arr,u8 *key_generate)
{
    u32 i=0;
    u32 j=0;
    u32 t=0;
    for(i=0;i<256;i++)
    {
        j=(j+s_arr[i])%256;
        swap(&s_arr[i],&s_arr[j]);
        t=(s_arr[j]+s_arr[i])%256;
        key_generate[i]=s_arr[t];
    }
}

void encryption_rc4_key_generation(u8 *key,u8 *key_generated)
{
    u8 s_arr[256];
    u8 key_arr[256];
    intiate_key_s(key,s_arr,key_arr);
    KSA(s_arr,key_arr);
    PRGA(s_arr,key_generated);
}
void encryption_rc4_encry(u8 *plain_text,u8 plain_count ,u8 *key_generated,u8 *cipher_text)
{
    for(int i=0;i<plain_count;i++)
    {
     cipher_text[i]=plain_text[i]^key_generated[i];
    }
}
void encryption_rc4_decry(u8 *cipher_text,u8 cipher_count ,u8 *key_generated,u8 *plain_text)
{
    for(int i=0;i<cipher_count;i++)
    {
        plain_text[i]=cipher_text[i]^key_generated[i];
    }
}
