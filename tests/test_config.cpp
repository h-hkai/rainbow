#include "../rainbow/config.h"
#include "../rainbow/log.h"

#include <yaml-cpp/yaml.h>

#if 0 
rainbow::ConfigVar<int>::ptr g_int_value_config = 
    rainbow::Config::Lookup("system.port", (int)8080, "system port");

rainbow::ConfigVar<float>::ptr g_int_valuex_config = 
    rainbow::Config::Lookup("system.port", (float)8080, "system port");

rainbow::ConfigVar<float>::ptr g_float_value_config = 
    rainbow::Config::Lookup("system.value", (float)80.80, "system value");

rainbow::ConfigVar<std::vector<int> >::ptr g_int_vector_value_config = 
    rainbow::Config::Lookup("system.int_vec", std::vector<int>{1, 2, 4}, "system int vector");

rainbow::ConfigVar<std::list<int> >::ptr g_int_list_value_config = 
    rainbow::Config::Lookup("system.int_list", std::list<int>{1, 2, 4}, "system int list");

rainbow::ConfigVar<std::set<int> >::ptr g_int_set_value_config = 
    rainbow::Config::Lookup("system.int_set", std::set<int>{1, 2, 4}, "system int set");

rainbow::ConfigVar<std::unordered_set<int> >::ptr g_int_uset_value_config = 
    rainbow::Config::Lookup("system.int_uset", std::unordered_set<int>{1, 2, 4}, "system int uset");

rainbow::ConfigVar<std::map<std::string, int> >::ptr g_str_int_map_value_config = 
    rainbow::Config::Lookup("system.str_int_map", std::map<std::string, int>{{"No1", 1}, {"No2", 4}}, "system int map");

rainbow::ConfigVar<std::unordered_map<std::string, int> >::ptr g_str_int_umap_value_config = 
    rainbow::Config::Lookup("system.str_int_umap", std::unordered_map<std::string, int>{{"No1", 1}, {"No2", 4}}, "system int umap");

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

void test_config() {
    RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "before: "  << g_int_value_config->toString();
    RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "before: "  << g_float_value_config->toString();

#define XX(g_var, name, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for (auto& i : v) { \
            RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << #prefix " " #name ": " << i; \
        } \
        RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
    }

#define XX_M(g_var, name, prefix) \
    { \
        auto& v = g_var->getValue(); \
        for (auto& i : v) { \
            RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << #prefix " " #name ": {" << i.first << " - " << i.second << "}"; \
        } \
        RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << #prefix " " #name " yaml: " << g_var->toString(); \
    }

    XX(g_int_vector_value_config, int_vec, before);
    XX(g_int_list_value_config, int_list, before);
    XX(g_int_set_value_config, int_set, before);
    XX(g_int_uset_value_config, int_uset, before);
    XX_M(g_str_int_map_value_config, int_map, before);
    XX_M(g_str_int_umap_value_config, int_umap, before);

    YAML::Node root = YAML::LoadFile("/home/zhangyu/rainbow/bin/conf/log.yml");
    rainbow::Config::LoadFromYaml(root);

    RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "after: "  << g_int_value_config->toString();
    RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "after: "  << g_float_value_config->toString();

    XX(g_int_vector_value_config, int_vec, after);
    XX(g_int_list_value_config, int_list, after);
    XX(g_int_set_value_config, int_set, after);
    XX(g_int_uset_value_config, int_uset, after);
    XX_M(g_str_int_map_value_config, int_map, after);
    XX_M(g_str_int_umap_value_config, int_umap, after);
}
#endif

class Person {
public:
    Person() {}
    std::string m_name;
    int m_age = 0;
    bool m_sex = 0;

    std::string toString() const {
        std::stringstream ss;
        ss << "[Preson name = " << m_name
           << " age = " << m_age
           << " sex = " << m_sex
           <<"]";
        return ss.str();
    } 
};

namespace rainbow {

template<>
class LexicalCast<std::string, Person> {
public:
    Person operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        Person p;
        p.m_name = node["name"].as<std::string>();
        p.m_age = node["age"].as<int>();
        p.m_sex = node["sex"].as<bool>();
        return p;
    }

};

template<>
class LexicalCast<Person, std::string> {
public:
    std::string operator()(const Person& p) {
        YAML::Node node(YAML::NodeType::Sequence);
        node["name"] = p.m_name;
        node["age"] = p.m_age;
        node["sex"] = p.m_sex;
        std::stringstream ss;
        ss << node;
        return ss.str();
    }

};

}

rainbow::ConfigVar<Person>::ptr g_person = 
    rainbow::Config::Lookup("class.person", Person(), "system person");

rainbow::ConfigVar<std::map<std::string, Person>>::ptr g_person_map = 
    rainbow::Config::Lookup("class.map", std::map<std::string, Person>(), "system person");

rainbow::ConfigVar<std::map<std::string, std::vector<Person>>>::ptr g_person_map_vec = 
    rainbow::Config::Lookup("class.map_vec", std::map<std::string, std::vector<Person>>(), "system vector person");


void test_class() {
    //RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "before " << g_person->getValue().toString() << " - " << g_person->toString();

#define XX_PM(g_var, prefix) \
    { \
        auto m = g_var->getValue(); \
        for (auto& i : m) { \
            RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << prefix <<  ": " << i.first  << " - " << i.second.toString(); \
        } \
        RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << prefix << ": size = " << m.size(); \
    } 

    //XX_PM(g_person_map, "class.map before");
    
    RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "before: " << g_person_map_vec->toString();

    YAML::Node root = YAML::LoadFile("/home/zhangyu/rainbow/bin/conf/log.yml");
    rainbow::Config::LoadFromYaml(root);
    
    //RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "after " <<  g_person->getValue().toString() << " - " << g_person->toString();

    RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "after: " << g_person_map_vec->toString();
    //XX_PM(g_person_map, "class.map after");
}

int main(int argc, char** argv) {
    //test_yaml();
    //test_config();
    test_class();        
    return 0;
}
