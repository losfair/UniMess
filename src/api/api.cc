#include "../protocols/init.h"
#include "../chain.h"
#include "../packet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <exception>
#include <time.h>

extern "C" void unimess_init() {
    srand(time(0));

    unimess_protocols::init();
}

extern "C" unimess::ConfigChain * unimess_config_chain_generate(unsigned int size) {
    unimess::ConfigChain *cc = new unimess::ConfigChain(unimess::ConfigChain::generate(size));
    return cc;
}

extern "C" unsigned char * unimess_config_chain_dump(unimess::ConfigChain *cc, unsigned int *len_out) {
    auto data = cc -> dump();
    unsigned char *raw_data = (unsigned char *) malloc(data.size());
    memcpy(raw_data, &data[0], data.size());
    *len_out = data.size();

    return raw_data;
}

extern "C" unimess::ConfigChain * unimess_config_chain_load(unsigned char *raw_data, unsigned int len) {
    std::vector<unsigned char> data;
    for(int i = 0; i < len; i++) {
        data.push_back(raw_data[i]);
    }

    try {
        auto cc_local = unimess::ConfigChain::load(data);
        unimess::ConfigChain *cc = new unimess::ConfigChain(std::move(cc_local));
        return cc;
    } catch(std::exception& e) {
        fprintf(stderr, "unimess_config_chain_load: %s\n", e.what());
        return NULL;
    }
}

extern "C" void unimess_config_chain_destroy(unimess::ConfigChain *cc) {
    delete cc;
}

extern "C" unimess::ProtocolChain * unimess_config_chain_get_protocol_chain(unimess::ConfigChain *cc) {
    unimess::ProtocolChain *pc = new unimess::ProtocolChain(cc -> get_protocol_chain());
    return pc;
}

extern "C" unsigned char * unimess_protocol_chain_encode_packet(unimess::ProtocolChain *pc, unsigned int *len_out, unsigned char *pkt, unsigned int len) {
    std::vector<unsigned char> _data(pkt, pkt + len);
    unimess::Packet data(std::move(_data));

    try {
        pc -> encode_packet(data);
    } catch(std::exception& e) {
        fprintf(stderr, "unimess_protocol_chain_encode_packet: %s\n", e.what());
        *len_out = 0;
        return NULL;
    }

    unsigned char *raw_data = (unsigned char *) malloc(data.data.size());
    memcpy(raw_data, &data.data[0], data.data.size());
    *len_out = data.data.size();

    return raw_data;
}

extern "C" unsigned char * unimess_protocol_chain_decode_packet(unimess::ProtocolChain *pc, unsigned int *len_out, unsigned char *pkt, unsigned int len) {
    std::vector<unsigned char> _data(pkt, pkt + len);
    unimess::Packet data(std::move(_data));

    try {
        pc -> decode_packet(data);
    } catch(std::exception& e) {
        fprintf(stderr, "unimess_protocol_chain_decode_packet: %s\n", e.what());
        *len_out = 0;
        return NULL;
    }

    unsigned char *raw_data = (unsigned char *) malloc(data.data.size());
    memcpy(raw_data, &data.data[0], data.data.size());
    *len_out = data.data.size();

    return raw_data;
}

extern "C" void unimess_protocol_chain_destroy(unimess::ProtocolChain *pc) {
    delete pc;
}

extern "C" void unimess_binary_buffer_destroy(unsigned char *buf) {
    free(buf);
}
