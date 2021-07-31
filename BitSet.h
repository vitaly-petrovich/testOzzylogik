#pragma once

#include "Types.h"

#define BITS_IN_BYTE 8

template <typename T>
class BitSet
{
    public:
        BitSet(T* ptrData, const uint16_t elementsCount)
            : m_bitsCount(elementsCount)
            , m_ptrData(ptrData)
        { }

        void set(const uint16_t pos)
        {
            if(pos >= m_bitsCount)
                return;

            const uint8_t bitPos = bitPosition(pos);

            T* ptr = posPtr(pos);
            *ptr |= 1 << bitPos;

        }

        bool isSet(const uint16_t pos)
        {
            if(pos >= m_bitsCount)
                return false;

            const uint8_t bitPos = bitPosition(pos);

            T* ptr = posPtr(pos);

            return *ptr & 1 << bitPos;
        }

        uint16_t count() const
        {
            return m_bitsCount;
        }

    private:
        const uint16_t m_bitsCount;
        T* m_ptrData;

        T* posPtr(const uint16_t pos)
        {
            return m_ptrData + pos/(sizeof(T)*BITS_IN_BYTE);
        }

        uint8_t bitPosition(const uint16_t pos)
        {
            return pos%(sizeof(T)*BITS_IN_BYTE);
        }
};
