#pragma once

#include <vector>
#include <deque>


template<typename TType, int size>
class CircularBuffer
{
private:
    int caret = 0;
    std::vector<TType> buffer;
    
    std::deque<TType*> ptrs;


public:
    CircularBuffer()
    {
        buffer.resize(size);
    }


    bool addData(const TType& data)
    {
        if (ptrs.size() >= size)
            return false;
        buffer[caret] = data;
        ptrs.push_back(&buffer[caret]);
        caret = (caret + 1) % size;

        return true;
    }

    void addDataForce(const TType& data)
    {
        buffer[caret] = data;
        ptrs.push_back(&buffer[caret]);
        caret = (caret + 1) % size;
    }

    const TType& readData()
    {
        assert(!ptrs.empty());
        auto& out = *ptrs[0];
        ptrs.pop_front();
        return out;
    }

    const TType* readDataPtr()
    {
        if (ptrs.empty())
            return nullptr;

        auto out = ptrs[0];
        ptrs.pop_front();
        return out;
    }
};