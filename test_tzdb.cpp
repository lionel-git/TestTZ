#include <chrono>
#include <iostream>

void test_tzdb() 
{
    std::cout << "\n ===== Testing tzdb" << std::endl;

    using namespace std::chrono;
    const auto &tzdb = get_tzdb();
    std::cout << "tzdb version: " << tzdb.version << std::endl;

    for (const auto& tz : tzdb.zones) {
        std::cout << tz.name() << '\n';
    }
    std::cout << " ===== End Testing tzdb" << std::endl;
}
