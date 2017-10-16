#include "swap.h"
#include <stdlib.h>

namespace unimess_protocols {

class SwapProtocol : public unimess::Protocol {
private:
    unsigned char dist;
public:
    SwapProtocol(unsigned char new_dist) {
        dist = new_dist;
    }

    virtual void encode(unimess::Packet& pkt) {
        size_t len = pkt.data.size();

        for(int i = 0;; i++) {
            int l = i;
            int r = i + dist;
            if(r >= len) break;

            unsigned char t = pkt.data[l];
            pkt.data[l] = pkt.data[r];
            pkt.data[r] = t;
        }
    }

    virtual void decode(unimess::Packet& pkt) {
        size_t len = pkt.data.size();
        
        for(int i = len - 1;; i--) {
            if(i < dist) break; // ensure l >= 0
            int r = i;
            int l = i - dist;

            unsigned char t = pkt.data[l];
            pkt.data[l] = pkt.data[r];
            pkt.data[r] = t;
        }
    }
};

SwapProtocolConfig::SwapProtocolConfig(unsigned char new_dist) {
    dist = new_dist;
}

unimess::BinaryData SwapProtocolConfig::do_dump() {
    unimess::BinaryData ret;
    ret.write_primitive<unsigned char>(dist);
    return ret;
}

std::string SwapProtocolConfig::get_name() {
    return std::string("swap");
}

std::unique_ptr<unimess::Protocol> SwapProtocolConfig::get_protocol() {
    return std::unique_ptr<unimess::Protocol>(new SwapProtocol(dist));
}

unimess::ProtocolConfigManager SwapProtocolConfig::get_manager() {
    unimess::ProtocolConfigManager ret;
    ret.loader = [](unimess::BinaryData& data) {
        unsigned char dist = data.read_primitive<unsigned char>();
        return std::unique_ptr<unimess::BaseProtocolConfig>(new SwapProtocolConfig(dist));
    };
    ret.generator = []() {
        return std::unique_ptr<unimess::BaseProtocolConfig>(new SwapProtocolConfig(rand() % 32 + 1));
    };
    return ret;
}

} // namespace unimess_protocols
