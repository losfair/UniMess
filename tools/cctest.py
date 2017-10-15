import core
import argparse

def test(data):
    cc = core.lib.unimess_config_chain_load(data, len(data))
    if cc == core.ffi.NULL:
        raise Exception("Config chain load failed")
    core.lib.unimess_config_chain_destroy(cc)
    print("OK")

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
