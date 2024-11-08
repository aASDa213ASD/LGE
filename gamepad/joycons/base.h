#ifndef JOYCON
#define JOYCON

#include <algorithm> 

class Joycon {
public:
    int getX() const
    {
        return this->x;
    }

    int getY() const
    {
        return this->y;
    }

    void reset()
    {
        this->x = 0;
        this->y = 0;
    }

    int clamp(int value) const
    {
        return std::max(min_limit, std::min(max_limit, value));
    }

protected:
    int x = 0;
    int y = 0;
    int min_limit = -32768;
    int max_limit = 32767;
};

#endif // JOYCON
