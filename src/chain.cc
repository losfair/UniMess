#include "chain.h"

namespace unimess {

ConfigChain ConfigChain::generate(unsigned int size) {
    ConfigChain ret;
    for(int i = 0; i < size; i++) {
        ret.elements.push_back(BaseProtocolConfig::generate_one());
    }
    return ret;
}

std::vector<unsigned char> ConfigChain::dump() {
    BinaryData header_writer;
    header_writer.write_string("UNIMESS_V1");

    std::vector<unsigned char> ret = header_writer.get_data();
    for(auto& c : elements) {
        auto d = c -> dump();
        ret.insert(ret.end(), d.begin(), d.end());
    }
    return ret;
}

ConfigChain ConfigChain::load(const std::vector<unsigned char>& data) {
    BinaryData reader(data);
    ConfigChain ret;

    auto header = reader.read_string();
    if(header != "UNIMESS_V1") {
        throw std::runtime_error("Invalid data header");
    }

    while(!reader.at_end()) {
        ret.elements.push_back(BaseProtocolConfig::parse(reader));
    }

    return ret;
}

ProtocolChain ConfigChain::get_protocol_chain() {
    ProtocolChain ret;
    for(auto& c : elements) {
        ret.elements.push_back(c -> get_protocol());
    }

    return ret;
}

void ProtocolChain::encode_packet(Packet& pkt) {
    for(auto& p : elements) {
        p -> encode(pkt);
    }
}

void ProtocolChain::decode_packet(Packet& pkt) {
    for(auto itr = elements.rbegin(); itr != elements.rend(); itr++) {
        auto& p = *itr;
        p -> decode(pkt);
    }
}

} // namespace unimess
