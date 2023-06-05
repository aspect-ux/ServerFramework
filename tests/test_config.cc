#include <iostream>
#include "aspect/config.h"
#include "aspect/log.h"
#include "yaml-cpp/yaml.h"

aspect::ConfigVar<int>::ptr g_int_value_config =
    aspect::Config::Lookup("system.port", (int)8080, "system port");

aspect::ConfigVar<float>::ptr g_float_value_config =
    aspect::Config::Lookup("system.value", (float)10.2f, "system value");

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

    YAML::Node root = YAML::LoadFile("/home/linno/Desktop/Project/AspectServer/bin/conf/log.yml");
    aspect::Config::LoadFromYaml(root);

    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "after:" << g_int_value_config->getValue();
    ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "after:" << g_float_value_config->toString();
}

int main(int argc,char** argv)
{   
    //test_yaml();
    test_config();

    std::cout<<"hello aspect config!!!";
    return 0;
}