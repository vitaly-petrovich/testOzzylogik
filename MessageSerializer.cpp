#include <cstring>

#include "MessageSerializer.h"
#include "BitSet.h"
#include "CRC16.h"

#define START_MARKER_SIZE   2
#define MSG_HEADER_SIZE     2
#define CRC_SIZE            2
#define END_MARKER_SIZE     1

const uint16_t MessageSerializer::msc_startMarker = 0x2A0d; //42 13
const uint8_t MessageSerializer::msc_endMarker = 0x0;


bool MessageSerializer::serialize(std::vector<uint16_t>& in, std::vector<uint8_t>& out)
{
    if(!in.size() || !*in.rbegin())
        return false;

    const uint16_t msgSize = *in.rbegin()+1;
    const uint16_t msgSizeBytes = msgSize/8 + (msgSize%8 > 0 ? 1 : 0);
    const uint16_t fullMsgSize = START_MARKER_SIZE + MSG_HEADER_SIZE + msgSizeBytes + CRC_SIZE + END_MARKER_SIZE;

    out.resize(fullMsgSize);
    uint8_t* msg = &out.front();

    memcpy(msg, reinterpret_cast<const uint8_t*>(&msc_startMarker), START_MARKER_SIZE);

    memcpy(msg + START_MARKER_SIZE, reinterpret_cast<const uint8_t*>(&msgSizeBytes), MSG_HEADER_SIZE);

    BitSet<uint8_t> bitSet(msg + START_MARKER_SIZE + MSG_HEADER_SIZE, msgSize);
    for(std::vector<uint16_t>::iterator it = in.begin();
        it != in.end();
        it++)
        bitSet.set(*it);

    const uint16_t crc = CRC16::gen(msg + START_MARKER_SIZE + MSG_HEADER_SIZE, msgSize);
    memcpy(msg + START_MARKER_SIZE + MSG_HEADER_SIZE + msgSizeBytes, reinterpret_cast<const uint8_t*>(&crc), CRC_SIZE);

    memcpy(msg + START_MARKER_SIZE + MSG_HEADER_SIZE + msgSizeBytes + CRC_SIZE, reinterpret_cast<const uint8_t*>(&msc_endMarker), END_MARKER_SIZE);

    return true;
}
