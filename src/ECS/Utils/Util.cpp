// 
// Created by cheily on 21.03.2024. 
// 
 
#include "Util.h" 
 
namespace ztgk { 
 
    long long time() { 
        return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::steady_clock::now().time_since_epoch()).count(); 
    } 
 
    Console ztgk::console = Console(); 
} 
