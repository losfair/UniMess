#include "init.h"

namespace unimess_protocols {

void init() {
    // The names must be same as [config]::get_name()
    unimess::BaseProtocolConfig::add_manager("none", NoneProtocolConfig::get_manager());
    unimess::BaseProtocolConfig::add_manager("not", NotProtocolConfig::get_manager());
    unimess::BaseProtocolConfig::add_manager("xor", XorProtocolConfig::get_manager());
    unimess::BaseProtocolConfig::add_manager("xorchain", XorChainProtocolConfig::get_manager());
    unimess::BaseProtocolConfig::add_manager("swap", SwapProtocolConfig::get_manager());
    unimess::BaseProtocolConfig::add_manager("deriv", DerivProtocolConfig::get_manager());
}

} // namespace unimess_protocols
