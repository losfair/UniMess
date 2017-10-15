#include "xor.h"
#include <stdlib.h>

namespace unimess_protocols {

class XorProtocol : public unimess::Protocol {
private:
    unsigned char xv;
public:
    XorProtocol(unsigned char new_xv) {
        xv = new_xv;
    }

    virtual void encode(unimess::Packet& pkt) {
        for(auto& c : pkt.data) {
            c ^= xv;
        }
    }
    virtual void decode(unimess::Packet& pkt) {
        for(auto& c : pkt.data) {
            c ^= xv;
        }
    }
};

XorProtocolConfig::XorProtocolConfig(unsigned char new_xv) {
    xv = new_xv;
}

unimess::BinaryData XorProtocolConfig::do_dump() {
    unimess::BinaryData ret;
    ret.write_primitive<unsigned char>(xv);
    return ret;
}

std::string XorProtocolConfig::get_name() {
    return std::string("xor");
}

std::unique_ptr<unimess::Protocol> XorProtocolConfig::get_protocol() {
    return std::unique_ptr<unimess::Protocol>(new XorProtocol(xv));
}

unimess::ProtocolConfigManager XorProtocolConfig::get_manager() {
    unimess::ProtocolConfigManager ret;
    ret.loader = [](unimess::BinaryData& data) {
        unsigned char xv = data.read_primitive<unsigned char>();
        return std::unique_ptr<unimess::BaseProtocolConfig>(new XorProtocolConfig(xv));
    };
    ret.generator = []() {
        return std::unique_ptr<unimess::BaseProtocolConfig>(new XorProtocolConfig(rand() % 256));
    };
    return ret;
}

} // namespace unimess_protocols
