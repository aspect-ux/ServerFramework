#include <iostream>
#include "aspect/config.h"
#include "aspect/log.h"
#include "yaml-cpp/yaml.h"

aspect::ConfigVar<int>::ptr g_int_value_config =
    aspect::Config::Lookup("system.port", (int)8080, "system port");

aspect::ConfigVar<float>::ptr g_float_value_config =
    aspect::Config::Lookup("system.value", (float)10.2f, "system value");

aspect::ConfigVar<std::vector<int>>::ptr g_int_vec_value_config =
    aspect::Config::Lookup("system.int_vec", std::vector<int>{1,2}, "system int vec");

aspect::ConfigVar<std::list<int>>::ptr g_int_list_value_config =
    aspect::Config::Lookup("system.int_list", std::list<int>{1,2}, "system int list");

aspect::ConfigVar<std::set<int>>::ptr g_int_set_value_config =
    aspect::Config::Lookup("system.int_set", std::set<int>{1,2}, "system int set");

aspect::ConfigVar<std::unordered_set<int>>::ptr g_int_unordered_set_value_config =
    aspect::Config::Lookup("system.int_uset", std::unordered_set<int>{1,2}, "system int unordered_set");

aspect::ConfigVar<std::map<std::string,int>>::ptr g_str_int_map_value_config =
    aspect::Config::Lookup("system.str_int_map", std::map<std::string,int>{{"k",2}}, "system str int map");

aspect::ConfigVar<std::unordered_map<std::string,int>>::ptr g_str_int_unordered_map_value_config =
    aspect::Config::Lookup("system.str_int_umap", std::unordered_map<std::string,int>{{"k",2}}, "system str int unordered_map");
void print_yaml(const YAML::Node& node, int level) {
    if(node.IsScalar()) {
        ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << std::string(level * 4, ' ')
            << node.Scalar() << " - " << node.Type() << " - " << level;
    } else if(node.IsNull()) {
        ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << std::string(level * 4, ' ')
            << "NULL - " << node.Type() << " - " << level;
    } else if(node.IsMap()) {
        for(auto it = node.begin();
                it != node.end(); ++it) {
            ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << std::string(level * 4, ' ')
                    << it->first << " - " << it->second.Type() << " - " << level;
            print_yaml(it->second, level + 1);
        }
    } else if(node.IsSequence()) {
        for(size_t i = 0; i < node.size(); ++i) {
            ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << std::string(level * 4, ' ')
                << i << " - " << node[i].Type() << " - " << level;
            print_yaml(node[i], level + 1);
        }
    }
}
void test_yaml() {
    std::string path = "/home/linno/Desktop/Project/AspectServer/bin/conf/test.yml";
    YAML::Node root = YAML::LoadFile(path);

    print_yaml(root,0);

    //ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << root;
}

void test_config()
{
    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "before:" << g_int_value_config->getValue();
    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "before:" << g_float_value_config->toString();

#define XX(g_var, name, prefix) \
    { \
        auto&v = g_var->getValue(); \
        for (auto& i : v) { \
            ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << #prefix ":" #name ":" << i; \
        } \
        ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << #prefix ":" #name " yaml:" << g_var->toString(); \
    }
#define XX_M(g_var, name, prefix) \
    { \
        auto&v = g_var->getValue(); \
        for (auto& i : v) { \
            ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << #prefix ":" #name ": {" \
                            << i.first << " - " << i.second << "}"; \
        }; \
        ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << #prefix ":" #name " yaml:" << g_var->toString(); \
    }

    XX(g_int_vec_value_config,int_vec,before);
    XX(g_int_list_value_config,int_list,before);
    XX(g_int_set_value_config,int_set,before);
    XX(g_int_unordered_set_value_config,int_unordered_set,before);
    XX_M(g_str_int_map_value_config,str_int_map,before);
    XX_M(g_str_int_unordered_map_value_config,str_int_umap,before);

    YAML::Node root = YAML::LoadFile("/home/linno/Desktop/Project/AspectServer/bin/conf/test.yml");
    aspect::Config::LoadFromYaml(root);

    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "after:" << g_int_value_config->getValue();
    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "after:" << g_float_value_config->toString();

    XX(g_int_vec_value_config,int_vec,after);
    XX(g_int_list_value_config,int_list,after);
    XX(g_int_set_value_config,int_set,after);
    XX(g_int_unordered_set_value_config,int_unordered_set,after);
    XX_M(g_str_int_map_value_config,str_int_map,after);
    XX_M(g_str_int_unordered_map_value_config,str_int_umap,after);

}

class Person {
public:
    std::string m_name;
    int m_age = 0;
    bool m_sex = 0;

    std::string toString() const {
        std::stringstream ss;
        ss << "[Person name=" << m_name
           << " age=" << m_age
           << " sex=" << m_sex
           << "]";
        return ss.str();
    }

    bool operator==(const Person& oth) const {
        return m_name == oth.m_name
            && m_age == oth.m_age
            && m_sex == oth.m_sex;
    }
};

aspect::ConfigVar<Person>::ptr g_person = 
    aspect::Config::Lookup("class.person", Person(), "system person");

aspect::ConfigVar<std::map<std::string,Person>>::ptr g_person_map = 
    aspect::Config::Lookup("class.map", std::map<std::string,Person>(), "system person map");

aspect::ConfigVar<std::map<std::string,std::vector<Person>>>::ptr g_person_vec_map = 
    aspect::Config::Lookup("class.vec_map", std::map<std::string,std::vector<Person>>(), "system person vec_map");

void test_class() {
    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "before: " << g_person->getValue().toString() << " - " << g_person->toString();

#define XX_PM(g_var, prefix) \
    { \
        auto m = g_person_map->getValue(); \
        for (auto& i : m) {\
            ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << prefix << ": " << i.first << " - " << " - " <<  \
                i.second.toString(); \
        } \
        ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << prefix << ": size=" << m.size(); \
    } 

    g_person->addListener(10,[](const Person& old_value, const Person& new_value) {
        ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "old_value=" << old_value.toString() <<
            " new_value=" << new_value.toString(); 
    });

    XX_PM(g_person_map,"class.map before");
    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "before: " << g_person_vec_map->toString();
    
    std::string path = "/home/linno/Desktop/Project/AspectServer/bin/conf/test.yml";
    YAML::Node root = YAML::LoadFile(path);
    aspect::Config::LoadFromYaml(root);

    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "after: " << g_person->getValue().toString() << " - " << g_person->toString();
    XX_PM(g_person_map,"class.map after");
    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "after: " << g_person_vec_map->toString();
}

namespace aspect {
/**
 * @brief 读取yaml的Person:自定义类型
*/
//for Person
template<>
class LexicalCast<std::string,Person> {
public: //c++ struct默认访问权限public,class默认为private
    Person operator() (const std::string& v) {
        YAML::Node node = YAML::Load(v);
        Person p;
        std::stringstream ss;
        p.m_age = node["age"].as<int>();
        p.m_name = node["name"].as<std::string>();
        p.m_sex = node["sex"].as<bool>();
        return p;
    }
};
/**
 * @brief 向yaml写入Person
*/
template<>
class LexicalCast<Person,std::string> {
public:
     std::string operator() (const Person& p) {
        YAML::Node node;
        node["age"] = p.m_age;
        node["name"] = p.m_name;
        node["sex"] = p.m_sex;
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};
}

void test_log() {
    static aspect::Logger::ptr system_log = ASPECT_LOG_NAME("system");
    ASPECT_LOG_INFO(system_log) << "hello system" << std::endl;
    std::cout << aspect::LoggerMgr::GetInstance()->toYamlString() << std::endl;

    std::string path = "/home/linno/Desktop/Project/AspectServer/bin/conf/log.yml";
    YAML::Node root = YAML::LoadFile(path);
    aspect::Config::LoadFromYaml(root);

    std::cout << "=============" << std::endl;
    std::cout << aspect::LoggerMgr::GetInstance()->toYamlString() << std::endl;
    std::cout << "=============" << std::endl;
    std::cout << root << std::endl;
    ASPECT_LOG_INFO(system_log) << "hello system" << std::endl;

    system_log->setFormatter("%d - %m%n");
    ASPECT_LOG_INFO(system_log) << "hello system" << std::endl;
}
int main(int argc,char** argv)
{   
    //test_yaml();
    //test_config();
    //test_class();
    test_log();

    std::cout<<"hello aspect config!!!";
    return 0;
}