#pragma once

#include <vector>
#include "Types.h"

struct MessageSerializer
{
    static bool serialize(std::vector<uint16_t>& in, std::vector<uint8_t>& out);

private:
    static const uint16_t msc_startMarker;
    static const uint8_t msc_endMarker;

    MessageSerializer();
    ~MessageSerializer();
};
