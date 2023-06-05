#include "thread.h"

namespace aspect {

static thread_local std::string t_thread_name = "UNKNOW";
    //Thread::Thread(const std::string& name):m_name(name){}

    const std::string& Thread::GetName() {
        return t_thread_name;
    }
}