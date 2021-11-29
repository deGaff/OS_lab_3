//
// Created by d3Gaff on 28.11.2021.
//

#ifndef L3_MULTITHREAD_PI_H
#define L3_MULTITHREAD_PI_H
#include <windows.h>
#include <chrono>

using millisec = std::chrono::milliseconds;

millisec calc_pi_winapi(unsigned thread_count);

DWORD WINAPI calc_func_winapi(LPVOID lpParam);

void calc_pi(millisec (*calc_pi)(unsigned)) ;

void test_time(millisec (*calc_pi)(unsigned)) ;

millisec calc_pi_omp(unsigned thread_count);


#endif //L3_MULTITHREAD_PI_H