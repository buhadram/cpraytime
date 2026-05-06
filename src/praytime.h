#pragma once

#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <ctime>


struct MethodParams {
    double fajr;
    double isha;
    double maghrib = 1.0;
    std::string ishaType = "angle"; 
    std::string maghribType = "min";
    std::string midnight = "Standard";
};

/**
 * @class PrayTime
 * @brief This class provides methods for calculating prayer times based on various methods.
 */
class PrayTime {
public:
    /**
     * @brief Constructs a new instance of the PrayTime class.
     *
     * @param method The calculation method to use. Default is "MWL".
     */
    PrayTime(std::string method = "MWL");

    void setMethod(std::string method);
    void setLocation(double lat, double lng);
    void setTimezone(double offset); 
    void setHighLats(std::string mode);
    
    // Main calculation trigger
    std::map<std::string, std::string> getTimes(int year, int month, int day);

private:
    MethodParams activeMethod;
    double       lat, lng, timeZone;
    std::string  highLats = "NightMiddle";
    long long    utcTime;
    std::map<std::string, MethodParams> methods;

    struct SunPos { double declination, equation; };

    /// @brief 
    /// @param time 
    /// @return 
    SunPos sunPosition(double time);

    /// @brief calculate midday
    /// @param time 
    /// @return
    double midDay(double time);

    /// @brief calculate time for a given angle
    /// @param angle 
    /// @param time 
    /// @param direction 1 for sunrise, -1 for sunset
    /// @return
    double angleTime(double angle, double time, int direction = 1);

    /// @brief fix angle to range 0-360
    /// @param a 
    /// @return 
    double fixAngle(double a) { return a - 360.0 * std::floor(a / 360.0); }

    /// @brief format time in HH:MM format
    /// @param time 
    /// @return std::string of HH:MM
    std::string formatTime(double time);

};
