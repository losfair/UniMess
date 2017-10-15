#include "xorchain.h"

namespace unimess_protocols {

class XorChainProtocol : public unimess::Protocol {
public:
    virtual void encode(unimess::Packet& pkt) {
        unsigned char v = 0;
        for(auto& c : pkt.data) {
            unsigned char nv = c;
            c ^= v;
            v = nv;
        }
    }
    virtual void decode(unimess::Packet& pkt) {
        unsigned char v = 0;
        for(auto& c : pkt.data) {
            c ^= v;
            v = c;
        }
    }
};

unimess::BinaryData XorChainProtocolConfig::do_dump() {
    return unimess::BinaryData();
}

std::string XorChainProtocolConfig::get_name() {
    return std::string("xorchain");
}

std::unique_ptr<unimess::Protocol> XorChainProtocolConfig::get_protocol() {
    return std::unique_ptr<unimess::Protocol>(new XorChainProtocol());
}

unimess::ProtocolConfigManager XorChainProtocolConfig::get_manager() {
    unimess::ProtocolConfigManager ret;
    ret.loader = [](unimess::BinaryData& data) {
        return std::unique_ptr<unimess::BaseProtocolConfig>(new XorChainProtocolConfig());
    };
    ret.generator = []() {
        return std::unique_ptr<unimess::BaseProtocolConfig>(new XorChainProtocolConfig());
    };
    return ret;
}

} // namespace unimess_protocols
