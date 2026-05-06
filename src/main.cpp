#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <ctime>
#include "praytime.h"

void printHeader(const std::string& method, double lat, double lng) {
    std::cout << "\nPrayer Times for " << lat << ", " << lng << " (Method: " << method << ")\n";
    std::cout << std::string(75, '-') << "\n";
    std::cout << std::left << std::setw(12) << "Date" 
              << std::setw(10) << "Fajr" 
              << std::setw(10) << "Sunrise" 
              << std::setw(10) << "Dhuhr" 
              << std::setw(10) << "Sunset" 
              << std::setw(10) << "Maghrib" 
              << std::setw(10) << "Isha" << "\n";
    std::cout << std::string(75, '-') << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <lat> <lng> <method>\n";
        std::cerr << "Methods: MWL, ISNA, Egypt, Makkah, Karachi, Tehran, Jafari\n";
        return 1;
    }

    double lat = std::stod(argv[1]);
    double lng = std::stod(argv[2]);
    std::string method = argv[3];

    PrayTime pt(method);
    pt.setLocation(lat, lng);
    // You may want to set timezone based on your local system time
    pt.setTimezone(-7.0); // Defaulting to PDT (UTC-7) for Tigard/Portland area

    // Get current date
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    struct tm *ltm = std::localtime(&now_time);
    
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;

    // Determine number of days in current month
    int daysInMonth[] = {31, (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int numDays = daysInMonth[ltm->tm_mon];

    printHeader(method, lat, lng);

    for (int day = 1; day <= numDays; ++day) {
        auto times = pt.getTimes(year, month, day);
        
        // For numeric fields we want zero-padding on the left (e.g. 05, 01).
        // `std::left` would pad on the right when combined with `std::setfill('0')`.
        std::cout << std::right << std::setw(4) << year << "-" 
                  << std::setfill('0') << std::setw(2) << month << "-" 
                  << std::setw(2) << day << std::setfill(' ') << "  "
                  << std::setw(10) << times["Fajr"]
                  << std::setw(10) << times["Sunrise"]
                  << std::setw(10) << times["Dhuhr"]
                  << std::setw(10) << times["Sunset"]
                  << std::setw(10) << times["Maghrib"]
                  << std::setw(10) << times["Isha"] << "\n";
    }
    std::cout << std::string(75, '-') << "\n";

    return 0;
}