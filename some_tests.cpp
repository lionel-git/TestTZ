#include <chrono>
#include <iostream>

#include <stdexcept>
#include <system_error>

#include <icu.h>
//#include <icucommon.h>

namespace toto
{

    void debugConversion()
    {
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
        const int start = 45806; // 29-May-2025

        double prevOffset = 0;
        for (int i = start; i > start - 365; --i)
        {
            double newOffset = showOffset(i);
            if (std::abs(newOffset - prevOffset) > 0.01)
            {
                std::cout << "Date: " << i << ", Offset: " << newOffset << " hours" << std::endl;
            }
            prevOffset = newOffset;
        }
    }

    void test_exception()
    {
        try
        {
            std::cout << "Testing exception handling..." << std::endl;
            auto ec = std::error_code(126, std::system_category());
            throw std::system_error(ec);
        }
        catch (const std::system_error& e)
        {
            std::cerr << "Exception: " << e.what() << " | type: " << typeid(e).name() << " " << e.code() << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Exception: " << e.what() << " | type: " << typeid(e).name() << std::endl;
        }
    }

    void testScan(const std::string& str)
    {
        //int hours = 0, minutes = 0;
        //std::sscanf(str.c_str(), "%d:%d", &hours, &minutes); // Example scan, replace with actual logic
        //std::cout << "Parsed time: " << hours << ":" << minutes << std::endl;

        for (double x = -2.0; x < 2.0; x += 0.1) {
            std::cout << "x: " << x << " int:" << (int)(x) << std::endl;
        }
    }

    void testformat()
    {
        for (int i = 0; i < 23; ++i) {
            std::cout << "Formatted number: " << std::format("{:02}:{:02}", i, i) << std::endl; // Example format, replace with actual logic
        }

    }

    int f1() { std::cout << "evalf1" << std::endl; return 1; } // Example function, replace with actual logic
    int f2() { std::cout << "evalf2" << std::endl; return 2; } // Example function, replace with actual logic


    int testTernaire(int v)
    {
        return v % 2 == 0 ? f1() : f2(); // Example ternary operation, replace with actual logic
    }

    struct Container
    {
        Container(int v) : value_(v) {}
        void print() const { std::cout << "Container value: " << value_ << std::endl; } // Example print function, replace with actual logic
        // Example operator overload, replace with actual logic
        const int value_;
        int value2_{ -1 };
    };;

    void testTZ()
    {
        test_range();

    }


    int main() {

        try
        {
            testTZ(); return 0;

            const Container c1(1);
            //c1.value2_ = 2; // Example usage, replace with actual logic
            c1.print(); // Example print, replace with actual logic


            for (int i = 0; i < 10; ++i)
            {
                std::cout << "============ = " << std::endl;
                int r = rand();
                testTernaire(r + 341); // Example test for ternary operation, replace with actual logic
            }
            return 0;
            testformat(); return 0;
            testScan("17:45"); return 0;

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
            std::cerr << "Exception: " << e.what() << " | type: " << typeid(e).name() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Unknown exception occurred." << std::endl;
        }



        return 0;
    }
}