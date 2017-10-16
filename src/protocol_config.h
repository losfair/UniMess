#pragma once

#include <map>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>
#include <type_traits>
#include "protocol.h"
#include "binary_data.h"

namespace unimess {

class BaseProtocolConfig;

typedef std::function<std::unique_ptr<BaseProtocolConfig>(BinaryData& data)> ProtocolConfigLoader;
typedef std::function<std::unique_ptr<BaseProtocolConfig>()> ProtocolConfigGenerator;

class ProtocolConfigManager {
public:
    ProtocolConfigLoader loader;
    ProtocolConfigGenerator generator;
};

class BaseProtocolConfig {
protected:
    virtual BinaryData do_dump() = 0;

public:
    virtual ~BaseProtocolConfig() {}

    static std::unique_ptr<BaseProtocolConfig> parse(BinaryData& config_data);
    static std::unique_ptr<BaseProtocolConfig> generate_one();
    static const std::map<std::string, ProtocolConfigManager>& get_managers();
    static void add_manager(const std::string& name, const ProtocolConfigManager& manager);

    virtual std::unique_ptr<Protocol> get_protocol() = 0;
    virtual std::string get_name() = 0;
    std::vector<unsigned char> dump();
};

} // namespace unimess
