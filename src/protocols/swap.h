#pragma once

#include "../protocol_config.h"
#include "../protocol.h"

namespace unimess_protocols {

class SwapProtocolConfig : public unimess::BaseProtocolConfig {
private:
    unsigned char dist;

protected:
    virtual unimess::BinaryData do_dump();

public:
    SwapProtocolConfig(unsigned char new_dist);
    virtual std::string get_name();
    virtual std::unique_ptr<unimess::Protocol> get_protocol();
    static unimess::ProtocolConfigManager get_manager();
};

} // namespace unimess_protocols
