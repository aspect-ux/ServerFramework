#include "aspect/aspect.h"
#include "aspect/log.h"
aspect::Logger::ptr g_logger = ASPECT_LOG_ROOT();

void fun1() {
    ASPECT_LOG_INFO(g_logger) << "name: " << aspect::Thread::GetName()
                              << " this.name: " << aspect::Thread::GetThis()->getName()
                              << " id: " << aspect::GetThreadId()
                              << " this.id: " << aspect::Thread::GetThis()->getId();
}

void fun2(){}

int main(int argc,char** argv)
{
    ASPECT_LOG_INFO(g_logger) << "thread test begin";
    std::vector<aspect::Thread::ptr> thrs;
    for (int i = 0; i < 5; ++i) {
        aspect::Thread::ptr thr(new aspect::Thread(&fun1, "name_" + std::to_string(i)));
        thrs.push_back(thr);
    }

    for (int i = 0; i < 5; ++i) {
        thrs[i]->join();
    }
    ASPECT_LOG_INFO(g_logger) << "thread test end";
    return 0;
}
