#include "base.h"

#include <vector>

class LeftJoycon : public Joycon {
public:
    std::vector<int> axis = { 0, 0 };

    void setAxis(int x = 0, int y = 0);
    void switchHalfMode();
    
private:
    bool half_mode = false;
};