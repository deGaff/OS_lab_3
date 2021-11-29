//
// Created by d3Gaff on 28.11.2021.
//

#include "multithread_pi.h"
#include "safe_input.h"
#include <omp.h>
#include <iomanip>
#include <vector>

static const unsigned TEST_THREAD_COUNT = 64,
                    NUMBER_OF_TESTS = 10,
                    STUDENT_NUMBER = 930729;
static const std::vector<unsigned> TEST_THREADS = {1, 2, 4, 8, 12, 16};
static const uint64_t N = 100'000'000l;
static uint64_t ITERATION = 0;
static const long double INVERSED_N = 1.0/N;
static const size_t BLOCK_SIZE = STUDENT_NUMBER*10;
LPCRITICAL_SECTION CRIT_SECT = nullptr;
static long double RESULT = 0;

millisec calc_pi_winapi(unsigned thread_count) {
    RESULT = 0;

    HANDLE *hThreads = new HANDLE[thread_count];

    CRIT_SECT = new CRITICAL_SECTION;
    InitializeCriticalSection(CRIT_SECT);
    for (int i = 0; i < thread_count; ++i) {
        hThreads[i] = CreateThread(NULL, 0, calc_func_winapi, (LPVOID) i, CREATE_SUSPENDED, NULL);
    }
    ITERATION = thread_count * BLOCK_SIZE;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < thread_count; ++i) {
        ResumeThread(hThreads[i]);
    }
    WaitForMultipleObjects(thread_count, hThreads, TRUE, INFINITE);
    auto stop = std::chrono::high_resolution_clock::now();
    DeleteCriticalSection(CRIT_SECT);
    for (int i = 0; i < thread_count; ++i) {
        CloseHandle(hThreads[i]);
    }
    RESULT *= INVERSED_N;
    delete[] hThreads;
    delete CRIT_SECT;
    return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}

DWORD WINAPI calc_func_winapi(LPVOID lpParam) {
    long double xi,
                pi;
    uint64_t iter = ((uint64_t) lpParam) * BLOCK_SIZE;
    while (iter < N) {
        pi = 0;
        for (uint64_t i = iter; (i < iter + BLOCK_SIZE) && i < N; i++) {
            xi = (i + 0.5) * INVERSED_N;
            pi += (4.0 / (1.0 + xi * xi));
        }
        EnterCriticalSection(CRIT_SECT);
        iter = ITERATION;
        ITERATION += BLOCK_SIZE;
        RESULT += pi;
        LeaveCriticalSection(CRIT_SECT);
    }
    return 1;
}

void calc_pi(millisec (*calc_pi)(unsigned)) {
    unsigned thread_count;
    std::cout << "Enter amount of threads ";
    if(!(safestream >> thread_count)) {
        std::cout << "Invalid input: " << safestream.get_state() << '\n';
        return;
    }
    std::cout << "Calculation time: " << calc_pi(thread_count).count()
            << " ms\nResult: " << std::setprecision(15) << RESULT << '\n';
}

void test_time(millisec (*calc_pi)(unsigned)) {
//    unsigned i = 1;
    double time;
    std::cout << "Average time on " << NUMBER_OF_TESTS << " tests using\t\tis\n";
    for(const auto& i : TEST_THREADS) {
//    for(;i <= TEST_THREAD_COUNT; i<<=1) {
        time = 0.0;
        for(unsigned j = 0; j < NUMBER_OF_TESTS; ++j) {
            time += calc_pi(i).count();
        }
        std::cout << "\t\t" << i << ((i == 1)?(" thread "):(" threads"))
        << "\t\t" << time / NUMBER_OF_TESTS << '\n';
    }
}

millisec calc_pi_omp(unsigned thread_count) {
    long double xi = 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    omp_set_num_threads(int(thread_count));
#pragma omp parallel for private(xi) schedule(dynamic, BLOCK_SIZE) reduction(+:RESULT)
    for(int i = 0; i < N; ++i) {
        xi = (i+0.5) / N;
        RESULT += 4 / (1 + xi * xi);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    RESULT *= INVERSED_N;
    return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
}
