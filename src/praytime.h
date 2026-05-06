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

class PrayTime {
public:
    PrayTime(std::string method = "MWL");

    void setMethod(std::string method);
    void setLocation(double lat, double lng);
    void setTimezone(double offset); 
    void setHighLats(std::string mode);
    
    // Main calculation trigger
    std::map<std::string, std::string> getTimes(int year, int month, int day);

private:
    MethodParams activeMethod;
    double lat, lng, timeZone;
    std::string highLats = "NightMiddle";
    long long utcTime;

    struct SunPos { double declination, equation; };
    SunPos sunPosition(double time);
    double midDay(double time);
    double angleTime(double angle, double time, int direction = 1);
    double fixAngle(double a) { return a - 360.0 * std::floor(a / 360.0); }
    std::string formatTime(double time);

    std::map<std::string, MethodParams> methods;
};
