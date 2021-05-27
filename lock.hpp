#pragma once

#include <mutex>

std::mutex  g_mutex;
void  testLock() {
    std::lock_guard<std::mutex> lk(g_mutex);


}