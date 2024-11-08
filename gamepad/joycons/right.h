#include "base.h"

#include <vector>

class RightJoycon : public Joycon {
public:
    std::vector<int> axis = { 0, 0 };

    RightJoycon();
    void setPosition(int x = 0, int y = 0);
    void calibrate();

private:
    int sensitivity = 150;
    std::vector<int> origin = { 0, 0 };
};