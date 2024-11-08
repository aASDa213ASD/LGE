#include <functional>

#include "handler.h"

using onKeyPress = std::function<void(int type, int value)>;

class KeyboardHandler : public Handler {
public:
    KeyboardHandler(onKeyPress onPress);
    ~KeyboardHandler();

    void passthrough() override;
    void listen() override;
    void die() override;

private:
    onKeyPress onPress;
};
