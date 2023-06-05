#ifndef __ASPECT_CONFIG_H__
#define __ASPECT_CONFIG_H__

#include <memory>
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <yaml-cpp/yaml.h>
#include "aspect/log.h"

namespace aspect{
    
class ConfigVarBase {
public:
    typedef std::shared_ptr<ConfigVarBase> ptr;
    ConfigVarBase(const std::string& name,const std::string& description = "")
    :m_name(name) 
    ,m_description(description){
        // transform将操作作用于范围内每个元素，并将结果存入另一个范围内，tolower变成小写
        std::transform(m_name.begin(),m_name.end(),m_name.begin(),::tolower);
    }
        
    virtual ~ConfigVarBase(){}

    const std::string getName() const {return m_name;}
    const std::string& getDescription() const {return m_description;}

    virtual std::string toString() = 0;
    virtual bool fromString(const std::string& val) = 0;
protected:
    std::string m_name;
    std::string m_description;
};

template<class F,class T> //适应复杂类型
class LexicalCast {
public:
    T operator() (const F& v)
    {
        return boost::lexical_cast<T>(v);
    }
};

template<class T,class FromStr = LexicalCast<std::string,T>,
                class ToStr = LexicalCast<T,std::string> >
class ConfigVar : public ConfigVarBase{
public:
    typedef std::shared_ptr<ConfigVar> ptr;

    ConfigVar(const std::string& name,
    const T& default_value,
    const std::string& description = "")
    :ConfigVarBase(name,description),m_val(default_value){}

    std::string toString() override {
        try {
            //return boost::lexical_cast<std::string>(m_val); //类似于atoi,进行字符串与整浮点型的字面转换
            return ToStr()(m_val);
        }catch(std::exception& e){
            ASPECT_LOG_ERROR(ASPECT_LOG_ROOT()) << "ConfigVar::toString exception"
            << e.what() << " convert: " << typeid(m_val).name() << " to string";
        }
        return "";
    }

    bool fromString(const std::string& val) override {
        try {
            //m_val = boost::lexical_cast<T>(val);
            setValue(FromStr()(val));
        }catch (std::exception& e) {
            ASPECT_LOG_ERROR(ASPECT_LOG_ROOT()) << "ConfigVar::toString exception"
            << e.what() << " convert: string to " << typeid(m_val).name(); 
        }
        return false;
    }
    const T getValue() const {return m_val;}
    void setValue(const T& v) {m_val = v;}
private:
    T m_val;
};

class Config {
public:
    typedef std::map<std::string,ConfigVarBase::ptr> ConfigVarMap;

    //typename用于确定声明的是一个类型，而不是变量
    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name,
    const T& default_value,const std::string& description = ""){
        auto tmp = Lookup<T>(name);
        if (tmp) {
            ASPECT_LOG_INFO(ASPECT_LOG_ROOT()) << "Lookup name=" << name << " exists";
            return tmp;
        }
        // TODO:存疑
        if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz._0123456789")
        //if(name.find_first_not_of("abcdefghikjlmnopqrstuvwxyz._012345678")
            != std::string::npos) {
            ASPECT_LOG_ERROR(ASPECT_LOG_ROOT()) << "Lookup name invalid "<< name;
            throw std::invalid_argument(name);
        }
        typename ConfigVar<T>::ptr v(new ConfigVar<T>(name,default_value,description));
        s_datas[name] = v;
        return v;
    }

    template<class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name)
    {
        auto it = s_datas.find(name);
        if (it == s_datas.end()) {
            return nullptr;
        }
        return std::dynamic_pointer_cast<ConfigVar<T>>(it->second);
    }

    static void LoadFromYaml(const YAML::Node& root);

    static ConfigVarBase::ptr LookupBase(const std::string& name); //纯虚类作为返回值会报错，这里返回指针
private:
    static ConfigVarMap s_datas;
};

}
#endif