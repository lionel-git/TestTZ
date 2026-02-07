#include <chrono>
#include <iostream>

#include <stdexcept>
#include <system_error>


void debugConversion()
{
    std::cout << "\n === Debug conversion" << std::endl;
    const int xlDate = 45806; // Example date in Julian format for today (29-May-2025)
    const int hours = 12;
    const int minutes = 15;
    // epoch is  1-Jan-1970 UTC
    // excel for 1-Jan-1970 is 25569
    std::chrono::seconds seconds_since_epoch = std::chrono::days(xlDate - 25569) + std::chrono::hours(hours) + std::chrono::minutes(minutes);
    std::chrono::system_clock::time_point tp(seconds_since_epoch); // Should get a timepoint as excel date, 12:15 UTC
    auto now = std::chrono::system_clock::now();                   // For comparison

    std::cout << "now: " << now << std::endl; // Current time in UTC
    std::cout << "tp : " << tp << std::endl; // Timepoint for the Excel date
    std::cout << " === Debug conversion" << std::endl;
}



double showOffset(int xlDate)
{
    const int hours = 12;
    const int minutes = 15;
    // epoch is  1-Jan-1970 UTC
    // excel for 1-Jan-1970 is 25569
    std::chrono::seconds seconds_since_epoch = std::chrono::days(xlDate - 25569) + std::chrono::hours(hours) + std::chrono::minutes(minutes);
    std::chrono::system_clock::time_point tp(seconds_since_epoch); // Should get a timepoint as excel date, 12:15 UTC
    auto now = std::chrono::system_clock::now();                   // For comparison
    std::chrono::zoned_time zt("America/New_York", tp);
    double offset = zt.get_info().offset.count() / 3600.0;
    return offset;
}

void test_range()
{
    std::cout << "\n === Test Range (with Time Zone)" << std::endl;
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
    std::cout << " === Test Range" << std::endl;
}

void test_exception()
{
    try
    {
        try
        {
            std::cout << "\n ========== Testing exception handling, system error code 126.." << std::endl;
            auto ec = std::error_code(126, std::system_category());
            throw std::system_error(ec);
        }
        catch (const std::system_error& e)
        {
            std::cerr << "Catch as system exception: " << e.what() << " | type: " << typeid(e).name() << " " << e.code() << std::endl;
            throw;
        }
    }    
    catch (const std::exception& e)
    {
        std::cerr << "Catch as exception: " << e.what() << " | type: " << typeid(e).name() << std::endl;
    }
    std::cout << " ========== End Testing exception handling..." << std::endl;
}


int main() {

    try
    {
        //throw std::file("Test"); // Uncomment to test exception handling
       // throw std::runtime_error("Test"); // Uncomment to test exception handling
        test_exception();

        debugConversion();
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
    catch (const std::system_error& e)
    {
        std::cerr << "Exception: " << e.what() << " | type: " << typeid(e).name() << " " << e.code() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what()  << " | type: " << typeid(e).name() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown exception occurred." << std::endl;
    }



    return 0;
}
