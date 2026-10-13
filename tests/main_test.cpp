#include "TestRunner.h"

void run_matrix_tests();

int main() {
    std::cout << Test::BOLD << "\n================ Running Matrx Tests ================\n\n" << Test::RESET;

    run_matrix_tests(); 

    std::cout << "\n---------------------------------------------------------\n";
    int total = Test::passed_count + Test::failed_count;
    std::cout << "Results: "
              << Test::GREEN << Test::passed_count << " passed" << Test::RESET << ", "
              << (Test::failed_count > 0 ? Test::RED : "") << Test::failed_count << " failed" << Test::RESET
              << " (" << total << " total)\n\n";

    return (Test::failed_count == 0) ? 0 : 1;
}