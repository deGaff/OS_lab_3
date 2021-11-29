#include <iostream>
#include <windows.h>
#include "menu.h"
#include "multithread_pi.h"


int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    view_menu main_menu("MAIN MENU", menu({
        std::make_shared<view_menu>("Count pi using WINAPI functions", menu({
            std::make_shared<action_menu>("Choose amount of threads", [] {calc_pi(calc_pi_winapi);}),
            std::make_shared<action_menu>("Test on 1-64 threads 100 times each", [] {test_time(calc_pi_winapi);})
        })),
        std::make_shared<view_menu>("Count pi using OpenMP functions", menu({
            std::make_shared<action_menu>("Choose amount of threads", [] {calc_pi(calc_pi_omp);}),
            std::make_shared<action_menu>("Test on 1-64 threads 100 times each", [] {test_time(calc_pi_omp);})
        }))
    }));
    main_menu.execute();
    return 0;
}
