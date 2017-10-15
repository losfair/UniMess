import core
import argparse

def generate(size = 16):
    cc = core.lib.unimess_config_chain_generate(size)
    out_len = core.ffi.new("unsigned int *")
    out_data_raw = core.lib.unimess_config_chain_dump(cc, out_len)
    out_len = out_len[0]
    out_data = [out_data_raw[i] for i in range(out_len)]
    core.lib.unimess_binary_buffer_destroy(out_data_raw)
    core.lib.unimess_config_chain_destroy(cc)
    return bytes(out_data)

parser = argparse.ArgumentParser(
    description = "Config chain generator for UniMess"
)
parser.add_argument(
    "--chain-size",
    dest = "chain_size",
    type = int,
    default = 16,
    help = "Chain size to generate"
)
parser.add_argument(
    "out_file",
    type = str
)
args = parser.parse_args()

data = generate(args.chain_size)
with open(args.out_file, "wb") as f:
    f.write(data)
