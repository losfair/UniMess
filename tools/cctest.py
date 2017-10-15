import core
import argparse

def print_buf(buf, len):
    data = [buf[i] for i in range(len)]
    print(bytes(data))

def test(data):
    cc = core.lib.unimess_config_chain_load(data, len(data))
    if cc == core.ffi.NULL:
        raise Exception("Config chain load failed")
    pc = core.lib.unimess_config_chain_get_protocol_chain(cc)
    core.lib.unimess_config_chain_destroy(cc)
    print("Load OK")

    test_input = "Hello world".encode()
    #print(test_input)

    enc_out_len = core.ffi.new("unsigned int *")
    enc_out = core.lib.unimess_protocol_chain_encode_packet(pc, enc_out_len, test_input, len(test_input))
    if enc_out == core.ffi.NULL:
        raise Exception("Encode failed")
    #print_buf(enc_out, enc_out_len[0])

    dec_out_len = core.ffi.new("unsigned int *")
    dec_out = core.lib.unimess_protocol_chain_decode_packet(pc, dec_out_len, enc_out, enc_out_len[0])
    if enc_out == core.ffi.NULL:
        raise Exception("Encode failed")

    #print_buf(dec_out, dec_out_len[0])

    if dec_out_len[0] != len(test_input):
        raise Exception("Length mismatch")
    for i in range(dec_out_len[0]):
        if dec_out[i] != test_input[i]:
            raise Exception("Data mismatch")

    print("Data OK")

parser = argparse.ArgumentParser(
    description = "Config chain generator for UniMess"
)
parser.add_argument(
    "in_file",
    type = str
)
args = parser.parse_args()

with open(args.in_file, "rb") as f:
    test(f.read())
