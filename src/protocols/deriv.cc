#include "deriv.h"
#include <vector>

namespace unimess_protocols {

class DerivProtocol : public unimess::Protocol {
public:
    virtual void encode(unimess::Packet& pkt) {
        if(pkt.data.size() == 0) {
            return;
        }

        std::vector<unsigned char> new_pkt;
        new_pkt.push_back(pkt.data[0]);
        new_pkt.push_back(0);
        int ob_ptr = 1;
        int ob_pos = 0;
        unsigned char prev_byte = pkt.data[0];

        for(int i = 1; i < pkt.data.size(); i++) {
            if(ob_pos == 8) {
                new_pkt.push_back(0);
                ob_ptr = new_pkt.size() - 1;
                ob_pos = 0;
            }

            unsigned char c = pkt.data[i];
            unsigned char dt;
            unsigned char is_inc;

            if(c > prev_byte) {
                dt = c - prev_byte;
                is_inc = 1;
            } else {
                dt = prev_byte - c;
                is_inc = 0;
            }

            new_pkt.push_back(dt);

            new_pkt[ob_ptr] |= (is_inc << ob_pos);
            ob_pos++;

            prev_byte = c;
        }

        pkt.data = std::move(new_pkt);
    }

    virtual void decode(unimess::Packet& pkt) {
        if(pkt.data.size() == 0) {
            return;
        }

        std::vector<unsigned char> new_pkt;
        new_pkt.push_back(pkt.data[0]); // initial byte
        int pd_pos = 1;

        while(pd_pos < pkt.data.size()) {
            unsigned char ob = pkt.data[pd_pos];
            pd_pos++;

            int local_pos = 0;
            while(local_pos < 8 && pd_pos < pkt.data.size()) {
                unsigned char c = pkt.data[pd_pos];
                if(ob & (1 << local_pos)) { // inc
                    new_pkt.push_back(*new_pkt.rbegin() + c);
                } else {
                    new_pkt.push_back(*new_pkt.rbegin() - c);
                }
                local_pos++;
                pd_pos++;
            }
        }

        pkt.data = std::move(new_pkt);
    }
};

unimess::BinaryData DerivProtocolConfig::do_dump() {
    return unimess::BinaryData();
}

std::string DerivProtocolConfig::get_name() {
    return std::string("deriv");
}

std::unique_ptr<unimess::Protocol> DerivProtocolConfig::get_protocol() {
    return std::unique_ptr<unimess::Protocol>(new DerivProtocol());
}

unimess::ProtocolConfigManager DerivProtocolConfig::get_manager() {
    unimess::ProtocolConfigManager ret;
    ret.loader = [](unimess::BinaryData& data) {
        return std::unique_ptr<unimess::BaseProtocolConfig>(new DerivProtocolConfig());
    };
    ret.generator = []() {
        return std::unique_ptr<unimess::BaseProtocolConfig>(new DerivProtocolConfig());
    };
    return ret;
}

} // namespace unimess_protocols
