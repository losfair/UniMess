#pragma once

#include "../protocol_config.h"
#include "../protocol.h"

namespace unimess_protocols {

class XorProtocolConfig : public unimess::BaseProtocolConfig {
private:
    unsigned char xv;

protected:
    virtual unimess::BinaryData do_dump();

public:
    XorProtocolConfig(unsigned char new_xv);
    virtual std::string get_name();
    virtual std::unique_ptr<unimess::Protocol> get_protocol();
    static unimess::ProtocolConfigManager get_manager();
};

} // namespace unimess_protocols
