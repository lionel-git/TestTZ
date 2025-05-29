#include <chrono>
#include <iostream>

double showOffset(int xlDate)
{
    const int hours = 12;
    const int minutes = 15;
    // epoch is  1-Jan-1970 UTC
    // excel for 1-Jan-1970 is 25569
    std::chrono::seconds seconds_since_epoch((xlDate - 25569) * 24 * 3600 + hours * 3600 + minutes * 60);
    std::chrono::system_clock::time_point tp(seconds_since_epoch);
    auto now = std::chrono::system_clock::now();
    std::chrono::zoned_time zt("America/New_York", tp);
    double offset = zt.get_info().offset.count() / 3600.0;
    return offset;
}

void test_range()
{
    const int start = 45806; // 29-May-2025

    double prevOffset = 0;
    for (int i = start; i > start-365; --i)
    {
        double newOffset = showOffset(i);
        if (std::abs(newOffset - prevOffset) > 0.01)
        {
            std::cout << "Date: " << i << ", Offset: " << newOffset << " hours" << std::endl;
        }
        prevOffset = newOffset;
    }
}


int main() {

    try
    {
        test_range();
        return 0;


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

        std::chrono::zoned_time zt("America/New_York", std::chrono::local_seconds(seconds));

        std::cout << zt.get_info().offset << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred." << std::endl;
        return 1;
    }



    return 0;
}
