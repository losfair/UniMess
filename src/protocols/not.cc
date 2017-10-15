#include "not.h"

namespace unimess_protocols {

class NotProtocol : public unimess::Protocol {
public:
    virtual void encode(unimess::Packet& pkt) {
        for(auto& c : pkt.data) {
            c = ~c;
        }
    }
    virtual void decode(unimess::Packet& pkt) {
        for(auto& c : pkt.data) {
            c = ~c;
        }
    }
};

unimess::BinaryData NotProtocolConfig::do_dump() {
    return unimess::BinaryData();
}

std::string NotProtocolConfig::get_name() {
    return std::string("not");
}

std::unique_ptr<unimess::Protocol> NotProtocolConfig::get_protocol() {
    return std::unique_ptr<unimess::Protocol>(new NotProtocol());
}

unimess::ProtocolConfigManager NotProtocolConfig::get_manager() {
    unimess::ProtocolConfigManager ret;
    ret.loader = [](unimess::BinaryData& data) {
        return std::unique_ptr<unimess::BaseProtocolConfig>(new NotProtocolConfig());
    };
    ret.generator = []() {
        return std::unique_ptr<unimess::BaseProtocolConfig>(new NotProtocolConfig());
    };
    return ret;
}

} // namespace unimess_protocols
