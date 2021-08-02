#include "../rainbow/config.h"

namespace rainbow {

static rainbow::Logger::ptr g_logger = RAINBOW_LOG_NAME("system");

ConfigVarBase::ptr Config::LookUpBase(const std::string& name) {
    auto it = GetDatas().find(name);
    return it == GetDatas().end() ? nullptr : it->second;
}

/**
 * "A.B", 10
 * A:
 *   B: 10
 *   C: str
 */
static void ListAllMember(const std::string& prefix, 
                          const YAML::Node& node,
                          std::list<std::pair<std::string, const YAML::Node> >& output) {

    if (prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789") 
                != std::string::npos) {
        RAINBOW_LOG_ERROR(g_logger) << "Config invalid name: " << prefix << " : " << node;
        return;
    } 
    output.push_back(std::make_pair(prefix, node));
    if (node.IsMap()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            ListAllMember(prefix.empty() ? it->first.Scalar() : 
                    prefix + "." + it->first.Scalar(), it->second, output);
        }
    }
}


void Config::LoadFromYaml(const YAML::Node& root) {
    std::list<std::pair<std::string, const YAML::Node>> all_nodes;
    ListAllMember("", root, all_nodes);
 
    for (auto& i : all_nodes) {
        std::string key = i.first;
        if (key.empty()) continue;
        
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        ConfigVarBase::ptr var = LookUpBase(key);

        if (var) {
            if (i.second.IsScalar()) {
                var->fromString(i.second.Scalar());
            } else {
                std::stringstream ss;
                ss << i.second;
                var->fromString(ss.str());
            }
        }
    }   
}

}

