#include "protocol_config.h"
#include <random>

namespace unimess {

static std::map<std::string, ProtocolConfigManager> pc_managers;

std::unique_ptr<BaseProtocolConfig> BaseProtocolConfig::parse(
    BinaryData& config_data
) {
    auto name = config_data.read_string();
    if(pc_managers.find(name) == pc_managers.end()) {
        throw std::runtime_error("Manager not found");
    }

    ProtocolConfigManager& manager = pc_managers[name];
    return manager.loader(config_data);
}

std::unique_ptr<BaseProtocolConfig> BaseProtocolConfig::generate_one() {
    std::vector<std::string> names;
    for(const auto& p : pc_managers) {
        names.push_back(p.first);
    }

    if(names.empty()) {
        throw std::runtime_error("No available protocol config managers");
    }

    std::random_device random_device;
	std::mt19937 engine{random_device()};
	std::uniform_int_distribution<int> dist(0, names.size() - 1);

    auto& target_name = names[dist(engine)];

    auto& target = pc_managers[target_name];
    return target.generator();
}

const std::map<std::string, ProtocolConfigManager>& BaseProtocolConfig::get_managers() {
    return pc_managers;
}

void BaseProtocolConfig::add_manager(const std::string& name, const ProtocolConfigManager& manager) {
    pc_managers[name] = manager;
}

std::vector<unsigned char> BaseProtocolConfig::dump() {
    BinaryData ret;
    ret.write_string(get_name());

    std::vector<unsigned char> full_data = ret.get_data();
    auto body = do_dump();
    auto body_data = body.get_data();

    full_data.insert(full_data.end(), body_data.begin(), body_data.end());
    return full_data;
}

} // namespace unimess
