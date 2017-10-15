#include "none.h"

namespace unimess_protocols {

class NoneProtocol : public unimess::Protocol {
public:
    virtual void encode(unimess::Packet& pkt) {

    }
    virtual void decode(unimess::Packet& pkt) {

    }
};

unimess::BinaryData NoneProtocolConfig::do_dump() {
    return unimess::BinaryData();
}

std::string NoneProtocolConfig::get_name() {
    return std::string("none");
}

std::unique_ptr<unimess::Protocol> NoneProtocolConfig::get_protocol() {
    return std::unique_ptr<unimess::Protocol>(new NoneProtocol());
}

unimess::ProtocolConfigManager NoneProtocolConfig::get_manager() {
    unimess::ProtocolConfigManager ret;
    ret.loader = [](unimess::BinaryData& data) {
        return std::unique_ptr<unimess::BaseProtocolConfig>(new NoneProtocolConfig());
    };
    ret.generator = []() {
        return std::unique_ptr<unimess::BaseProtocolConfig>(new NoneProtocolConfig());
    };
    return ret;
}

} // namespace unimess_protocols
