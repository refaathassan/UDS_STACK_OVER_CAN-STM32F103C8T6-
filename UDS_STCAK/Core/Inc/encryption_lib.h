#ifndef _ENCRYPTION_LIN_H
#define  _ENCRYPTION_LIN_H
void encryption_rc4_key_generation(u8 *key,u8 *key_generated);
void encryption_rc4_encry(u8*plain_text,u8 plain_count ,u8 *key_generated,u8 *cipher_text);
void encryption_rc4_decry(u8 *cipher_text,u8 cipher_count ,u8 *key_generated,u8 *plain_text);
#endif
