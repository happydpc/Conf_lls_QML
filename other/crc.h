#ifndef CRC_H
#define CRC_H

#include <stdint.h>
#include <QByteArray>

class Crc
{
public:
    Crc();
    uint8_t crc8_dallas(char *data, int size);
    uint8_t crc8(uint8_t *pmsg, uint8_t msg_size);
    uint8_t crc8(QByteArray *pmsg);
    uint32_t passwordHash(uint8_t *pData, uint8_t size);
};

#endif // CRC_H
