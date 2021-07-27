#include "../rainbow/config.h"
#include "../rainbow/log.h"

#include <yaml-cpp/yaml.h>

rainbow::ConfigVar<int>::ptr g_int_value_config = 
    rainbow::Config::Lookup("system.port", (int)8080, "system port");

rainbow::ConfigVar<float>::ptr g_float_value_config = 
    rainbow::Config::Lookup("system.value", (float)80.80, "system value");

void print_yaml(const YAML::Node& node, int level) {
    if (node.IsScalar()) {
        RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << std::string(level * 4, ' ') 
            << node.Scalar() << " - " << node.Type() << "-" << level;
    } else if (node.IsNull()) {
        RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << std::string(level * 4, ' ')
            << "NULL - " << node.Type() << " - " << level; 
    } else if (node.IsMap()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << std::string(level * 4, ' ')
                << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level+1);
        }
    } else if (node.IsSequence()) {
        for (auto it = node.begin(); it != node.end(); ++it) {
            for (size_t i = 0; i < node.size(); ++i) {
                RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << std::string(level * 4, ' ') 
                    << i << " - " << node[i].Type() << " - " << level;
                print_yaml(node[i], level+1);
            }
        } 
    }
    
}

void test_yaml() {
    YAML::Node root = YAML::LoadFile("/home/zhangyu/rainbow/bin/conf/log.yml");
    print_yaml(root, 0);
    //RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << root;

}


int main(int argc, char** argv) {

    RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << g_int_value_config->toString();
    RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << g_float_value_config->toString();

    test_yaml();

    return 0;
}
