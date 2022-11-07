#pragma once

#define MY_DEBUG 1

#if MY_DEBUG == 1
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif