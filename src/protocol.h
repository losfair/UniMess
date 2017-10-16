#pragma once

#include "packet.h"

namespace unimess {

class Protocol {
public:
    virtual ~Protocol() {}

    virtual void encode(Packet&) = 0;
    virtual void decode(Packet&) = 0;
};

} // namespace unimess
