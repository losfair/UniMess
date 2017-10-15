#pragma once

#include <vector>
#include "protocol_config.h"
#include "protocol.h"
#include "packet.h"

namespace unimess {

class ProtocolChain;

class ConfigChain {
public:
    std::vector<std::unique_ptr<BaseProtocolConfig>> elements;

    static ConfigChain generate(unsigned int size);
    std::vector<unsigned char> dump();
    static ConfigChain load(const std::vector<unsigned char>& data);
    ProtocolChain get_protocol_chain();
};

class ProtocolChain {
public:
    std::vector<std::unique_ptr<Protocol>> elements;
    void encode_packet(Packet& pkt);
    void decode_packet(Packet& pkt);
};

} // namespace unimess
