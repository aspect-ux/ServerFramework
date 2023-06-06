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
    std::string path = "/home/linno/Desktop/Project/AspectServer/bin/conf/log.yml";
    YAML::Node root = YAML::LoadFile(path);

    print_yaml(root,0);

    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << root;
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

    YAML::Node root = YAML::LoadFile("/home/linno/Desktop/Project/AspectServer/bin/conf/log.yml");
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

int main(int argc,char** argv)
{   
    //test_yaml();
    test_config();

    std::cout<<"hello aspect config!!!";
    return 0;
}