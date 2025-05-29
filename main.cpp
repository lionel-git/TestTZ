#include <chrono>
#include <iostream>

int main() {
    // Get the current time in UTC
    auto now = std::chrono::system_clock::now();
 
    // Date = 28-May-2025, excel = 45805
    // Date = 29-May-2025, excel = 45806
    
    // Epoch is 1-Jan-1970 UTC, excel epoch is 1-Jan-1900
    std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    std::cout << now << " since epoch: " << seconds << std::endl;

    // excel for 1-Jan-1970 is 25569
    const int date_today = 45806; // Example date in Julian format for today
    const int hours = 7;
    const int minutes = 15;
    const int seconds2 = (date_today - 25569) * 24 * 3600 + hours * 3600 + minutes * 60; // Convert to seconds since epoch

    std::cout << seconds2 << " " << seconds.count() - seconds2 << std::endl;

    return 0;
}
