#include <functional>

#include "handler.h"

using onMouseMove  = std::function<void(int type, int value)>;
using onMouseClick = std::function<void(int type, int value)>;

class MouseHandler : public Handler {
public:
    MouseHandler(onMouseMove onMove, onMouseClick onClick);
    ~MouseHandler();

    void passthrough() override;
    void listen() override;
    void die() override;

private:
    onMouseMove  onMove;
    onMouseClick onClick;
};