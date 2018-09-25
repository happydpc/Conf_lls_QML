#include "crc.h"

Crc::Crc()
{

}

uint8_t Crc::crc8(uint8_t *pmsg, uint8_t msg_size) {
    uint8_t crc=0x00;
    uint8_t i=0x00;
    uint8_t a=0x00;
    for (i=0;i<(msg_size-1);i++)
    {
        a=*(pmsg+i)^crc;
        crc=0;
        if (a&0x01) crc ^= 0x5E;
        if (a&0x02) crc ^= 0xBC;
        if (a&0x04) crc ^= 0x61;
        if (a&0x08) crc ^= 0xC2;
        if (a&0x10) crc ^= 0x9D;
        if (a&0x20) crc ^= 0x23;
        if (a&0x40) crc ^= 0x46;
        if (a&0x80) crc ^= 0x8C;
    }
    return (crc);
}

unsigned char crc_bits(unsigned char data)
{
    unsigned char crc = 0;
    if(data & 1)     crc ^= 0x5e;
    if(data & 2)     crc ^= 0xbc;
    if(data & 4)     crc ^= 0x61;
    if(data & 8)     crc ^= 0xc2;
    if(data & 0x10)  crc ^= 0x9d;
    if(data & 0x20)  crc ^= 0x23;
    if(data & 0x40)  crc ^= 0x46;
    if(data & 0x80)  crc ^= 0x8c;
    return crc;
}

uint8_t Crc::crc8_dallas(char *data, int size)
{
    unsigned char crc = 0;
    for ( unsigned int i = 0; i < size; ++i )
    {
         crc = crc_bits(data[i] ^ crc);
    }
    return crc;
}

uint8_t Crc::crc8(QByteArray *pmsg) {
    uint8_t crc=0x00;
    uint8_t i=0x00;
    uint8_t a=0x00;
    uint8_t msg_size = pmsg->size();
    for (i=0;i<(msg_size-1);i++)
    {
        a = pmsg->at(i+1)^crc;
        crc=0;
        if (a&0x01) crc ^= 0x5E;
        if (a&0x02) crc ^= 0xBC;
        if (a&0x04) crc ^= 0x61;
        if (a&0x08) crc ^= 0xC2;
        if (a&0x10) crc ^= 0x9D;
        if (a&0x20) crc ^= 0x23;
        if (a&0x40) crc ^= 0x46;
        if (a&0x80) crc ^= 0x8C;
    }
    return (crc);
}

//Hash funcion for string
uint32_t Crc::passwordHash(uint8_t *pData, uint8_t size)
{
      unsigned int ret_val = 0;
      int i=0;
            int val=0;
      while (i<size)
      {
            val = (int) *(pData+i);
            ret_val ^= val;
            ret_val <<= 1;
            i++;
      }
      return ret_val;
}
