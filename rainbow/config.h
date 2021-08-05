#ifndef __RAINBOW_CONFIG_H__
#define __RAINBOW_CONFIG_H__

#include <memory>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "log.h"
#include "thread.h"

namespace rainbow {

/**
 * @brief 配置变量的基类
 */
class ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;

    /**
     * @brief 构造函数
     * @param[in] name 配置参数名称 [0-9a-z_.]
     * @param[in] description 配置参数描述
     */
    ConfigVarBase(const std::string& name, const std::string& description = "") 
        : m_name(name)
        , m_description(description) {
        std::transform(m_name.begin(), m_name.end(), m_name.begin(), ::tolower);
    }

    /**
     * @brief 析构函数
     */
    virtual ~ConfigVarBase() {}

    /**
     * @brief 返回配置参数名称
     */
    const std::string& getName() const { return m_name; }

    /**
     * @brief 返回配置参数的描述
     */
    const std::string& getDescription() const { return m_description; }

    /**
     * @brief 转成字符串
     */
    virtual std::string toString() = 0;

    /**
     * @brief 从字符串初始化值
     */
    virtual bool fromString(const std::string& val) = 0;

    /**
     * @brief 返回配置参数值的类型名称
     */
    virtual std::string getTypeName() const = 0;
protected:
    // 配置参数的名称
    std::string m_name;
    // 配置参数的描述
    std::string m_description;
};

/**
 * 类型转换模板类（F 源类型，T 目标类型）
 */
template<class F, class T>
class LexicalCast {
public:
    /**
     * @brief 类型转换
     * @param[in] v 源类型值
     * @return 返回 v 转换之后的目标类型
     * @execption 当类型不可转换时抛出异常
     */
    T operator()(const F& v) {
        return boost::lexical_cast<T>(v);
    }

};

/**
 * @brief 类型转换模板类片特化（YAML string 转换成 std::vector<T>）
 */
template<class T>
class LexicalCast<std::string, std::vector<T> > {
public:
    std::vector<T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::vector<T> vec;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i) {
            ss.str("");
            ss << node[i];
            vec.push_back(LexicalCast<std::string, T>()(ss.str()));
        }
        return vec;
    }
};

/**
 * @brief 类型转换模板类片特化（std::vector<T> 转换成 YAML string）
 */
template<class T>
class LexicalCast<std::vector<T>, std::string> {
public:
    std::string operator()(const std::vector<T>& v) {
        YAML::Node node(YAML::NodeType::Sequence);
        
        for (auto& i : v) {
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};


/**
 * @brief 类型转换模板类片特化（YAML string 转换成 std::list<T>）
 */
template<class T>
class LexicalCast<std::string, std::list<T> > {
public:
    std::list<T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::list<T> vec;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i) {
            ss.str("");
            ss << node[i];
            vec.push_back(LexicalCast<std::string, T>()(ss.str()));
        }
        return vec;
    }

};


/**
 * @brief 类型转换模板类片特化（std::list<T> 转换成 YAML string）
 */
template<class T>
class LexicalCast<std::list<T>, std::string> {
public:
    std::string operator()(const std::list<T>& v) {
        YAML::Node node(YAML::NodeType::Sequence);
        
        for (auto& i : v) {
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};


/**
 * @brief 类型转换模板类片特化（YAML string 转换成 std::set<T>）
 */
template<class T>
class LexicalCast<std::string, std::set<T> > {
public:
    std::set<T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::set<T> m_set;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i) {
            ss.str("");
            ss << node[i];
            m_set.insert(LexicalCast<std::string, T>()(ss.str()));
        }
        return m_set;
    }

};

/**
 * @brief 类型转换模板类片特化（std::set<T> 转换成 YAML string）
 */
template<class T>
class LexicalCast<std::set<T>, std::string> {
public:
    std::string operator()(const std::set<T>& v) {
        YAML::Node node(YAML::NodeType::Sequence);
        
        for (auto& i : v) {
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }

};


/**
 * @brief 类型转换模板类片特化（YAML string 转换成 std::unordered_set<T>）
 */
template<class T>
class LexicalCast<std::string, std::unordered_set<T> > {
public:
    std::unordered_set<T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::unordered_set<T> m_uset;
        std::stringstream ss;
        for (size_t i = 0; i < node.size(); ++i) {
            ss.str("");
            ss << node[i];
            m_uset.insert(LexicalCast<std::string, T>()(ss.str()));
        }
        return m_uset;
    }

};

/**
 * @brief 类型转换模板类片特化（std::unordered_set<T> 转换成 YAML string）
 */
template<class T>
class LexicalCast<std::unordered_set<T>, std::string> {
public:
    std::string operator()(const std::unordered_set<T>& v) {
        YAML::Node node(YAML::NodeType::Sequence);
        
        for (auto& i : v) {
            node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }

};


/**
 * @brief 类型转换模板类片特化（YAML string 转换成 std::map<string, T>）
 */
template<class T>
class LexicalCast<std::string, std::map<std::string, T> > {
public:
    std::map<std::string, T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::map<std::string, T> m_map;
        std::stringstream ss;
        for (auto it = node.begin(); it != node.end(); ++it) {
            ss.str("");
            ss << it->second;
            m_map.insert(std::make_pair(it->first.Scalar(), 
                        LexicalCast<std::string, T>()(ss.str())));
        }
        return m_map;
    }

};

/**
 * @brief 类型转换模板类片特化（std::map<std::string, T> 转换成 YAML string）
 */
template<class T>
class LexicalCast<std::map<std::string, T>, std::string> {
public:
    std::string operator()(const std::map<std::string, T>& v) {
        YAML::Node node(YAML::NodeType::Map);
        
        for (auto& i : v) {
            node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }

};

/**
 * @brief 类型转换模板类片特化（YAML string 转换成 std::map<std::string, T>）
 */
template<class T>
class LexicalCast<std::string, std::unordered_map<std::string, T> > {
public:
    std::unordered_map<std::string, T> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        typename std::unordered_map<std::string, T> m_umap;
        std::stringstream ss;
        for (auto it = node.begin(); it != node.end(); ++it) {
            ss.str("");
            ss << it->second;
            m_umap.insert(std::make_pair(it->first.Scalar(), 
                        LexicalCast<std::string, T>()(ss.str())));
        }
        return m_umap;
    }

};

/**
 * @brief 类型转换模板类片特化（std::unordered_map<std::string, T> 转换成 YAML string）
 */
template<class T>
class LexicalCast<std::unordered_map<std::string, T>, std::string> {
public:
    std::string operator()(const std::unordered_map<std::string, T>& v) {
        YAML::Node node(YAML::NodeType::Map);
        
        for (auto& i : v) {
            node[i.first] = YAML::Load(LexicalCast<T, std::string>()(i.second));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }

};


// FromStr T operator()(const std::string)
// ToStr std::string operator()(const T&)
template<class T, class FromStr = LexicalCast<std::string, T> 
                , class ToStr = LexicalCast<T, std::string> >
class ConfigVar : public ConfigVarBase {
public:
    typedef RWMutex RWMutexType;
    typedef std::shared_ptr<ConfigVar> ptr;
    typedef std::function<void (const T& old_value, const T& new_value)> on_change_cb;

    /**
     * @brief 通过参数名，参数值，描述来构造ConfigVar
     * @param[in] name 参数名称有效字符为[0-9a-z_.]
     * @param[in] default_value 参数的默认值
     * @param[in] description 参数的描述
     */
    ConfigVar(const std::string& name
            , const T& default_value
            , const std::string& description = "")
        : ConfigVarBase(name, description)
        , m_val(default_value) {
    }

    /**
     * @brief 将参数值转换成 YAML string
     * @exception 当转换失败抛出异常
     */
    std::string toString() override {
        try {
            //return boost::lexical_cast<std::string>(m_val);
            RWMutexType::ReadLock lock(m_mutex);
            return ToStr() (m_val);
        } catch (std::exception& e) {
            RAINBOW_LOG_ERROR(RAINBOW_LOG_ROOT()) << "ConfigVar::ToString exception" << e.what() << " convert: " << typeid(m_val).name() << " to string";
        }

        return "";
    }

    /**
     * @brief 从 YAML string 转换成参数的值
     * @exception 当转换失败抛出异常
     */
    bool fromString(const std::string& val) {
        try {
            //m_val = boost::lexical_cast<T>(val);
            setValue(FromStr()(val));
        } catch (std::exception& e) {
            RAINBOW_LOG_ERROR(RAINBOW_LOG_ROOT()) << "ConfigVar::ToString exception" << e.what() << " convert: string to " << typeid(m_val).name();
        }
        return false;
    }

    const T getValue() { 
        RWMutexType::ReadLock lock(m_mutex);
        return m_val; }

    /**
     * @brief 设置当前参数的值
     * @exception 如果参数的值又发生变化，则通知对应的回调函数
     */
    void setValue(const T& v) { 
        {
            RWMutexType::ReadLock lock(m_mutex);
            if (v == m_val) {
                return;
            }
            for (auto& i : m_cbs) {
                i.second(m_val, v);
            }
        }
        RWMutexType::WriteLock lock(m_mutex);
        m_val = v;
    }
    std::string getTypeName() const override { return typeid(T).name(); }

    uint64_t addListener(on_change_cb cb) {
        static uint64_t s_fun_id = 0;
        RWMutexType::WriteLock lock(m_mutex);
        ++s_fun_id;
        m_cbs[s_fun_id] = cb;
        return s_fun_id;
    }

    void delListener(uint64_t key) {
        RWMutexType::WriteLock lock(m_mutex);
        m_cbs.erase(key);
    }

    on_change_cb getListener(uint64_t key) {
        RWMutexType::ReadLock lock(m_mutex);
        auto it = m_cbs.find(key);
        return it == m_cbs.end() ? nullptr : it->second;
    }

    void clearListener() {
        RWMutexType::WriteLock lock(m_mutex);
        m_cbs.clear();
    }
private:
    RWMutexType m_mutex;
    T m_val;
    // 变更回调函数组，uint64_t key，要求唯一，一般可以用hash
    std::map<uint64_t, on_change_cb> m_cbs;
};

class Config {
public:
    typedef std::unordered_map<std::string, ConfigVarBase::ptr> ConfigVarMap;
    typedef RWMutex RWMutexType;

    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name,
            const T& default_value, const std::string& description = "") {
        RWMutexType::WriteLock lock(GetMutex());
        auto it = GetDatas().find(name);
        if (it != GetDatas().end()) {
            auto tmp = std::dynamic_pointer_cast<ConfigVar<T> >(it->second);    
            if (tmp) {
                RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "Lookup name=" << name << " exists";
                return tmp;
            } else {
                RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "Lookup name=" << 
                    name << " exists but type not " << typeid(T).name() << 
                    " real_type = " << it->second->getTypeName() << " " << 
                    it->second->toString();
                return nullptr;
            }
        }
        
        if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789") != std::string::npos) {
            RAINBOW_LOG_ERROR(RAINBOW_LOG_ROOT()) << "Lookup name invalid " << name;
            throw std::invalid_argument(name);
        }

        typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_value, description));
        GetDatas()[name] = v;
        return v;
    }

    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name) {
        RWMutexType::ReadLock lock(GetMutex());
        auto it = GetDatas().find(name); 
        if (it == GetDatas().end()) {
            return nullptr;
        }
        return std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
    }

    static void LoadFromYaml(const YAML::Node& root);

    static ConfigVarBase::ptr LookUpBase(const std::string& name);

    static void Visit(std::function<void(ConfigVarBase::ptr cb)>);
private:
    static ConfigVarMap& GetDatas() {
        static ConfigVarMap s_datas;
        return s_datas;
    }

    static RWMutexType& GetMutex() {
        static RWMutexType s_mutex;
        return s_mutex;
    }

};

}


#endif
