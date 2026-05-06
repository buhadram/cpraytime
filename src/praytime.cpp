#include "praytime.h"
#include <cstdio>

PrayTime::PrayTime(std::string method) {
    methods["MWL"] = {18.0, 17.0};
    methods["ISNA"] = {15.0, 15.0};
    methods["Egypt"] = {19.5, 17.5};
    methods["Makkah"] = {18.5, 90.0, 1.0, "min", "min"};
    methods["Karachi"] = {18.0, 18.0};
    methods["Tehran"] = {17.7, 14.0, 4.5, "angle", "angle", "Jafari"};
    methods["Jafari"] = {16.0, 14.0, 4.0, "angle", "angle", "Jafari"};
    
    setMethod(method);
    setLocation(0, 0);
    setTimezone(0);
}

void PrayTime::setMethod(std::string method) {
    if (methods.count(method)) activeMethod = methods[method];
}

void PrayTime::setLocation(double _lat, double _lng) {
    lat = _lat; lng = _lng;
}

void PrayTime::setTimezone(double offset) {
    timeZone = offset;
}

// Calculate sun position   
// Returns declination and equation of time
PrayTime::SunPos PrayTime::sunPosition(double time) {
    double D = (utcTime / 86400.0) - 10957.5 + (time / 24.0) - (lng / 360.0);
    double g = fixAngle(357.529 + 0.98560028 * D);
    double q = fixAngle(280.459 + 0.98564736 * D);
    double L = fixAngle(q + 1.915 * std::sin(g * M_PI / 180.0) + 0.020 * std::sin(2 * g * M_PI / 180.0));
    double e = 23.439 - 0.00000036 * D;
    double RA = std::atan2(std::cos(e * M_PI / 180.0) * std::sin(L * M_PI / 180.0), std::cos(L * M_PI / 180.0)) * 180.0 / M_PI / 15.0;
    
    return { std::asin(std::sin(e * M_PI / 180.0) * std::sin(L * M_PI / 180.0)) * 180.0 / M_PI, (q / 15.0) - fixAngle(RA) };
}

double PrayTime::midDay(double time) {
    return fixAngle(12.0 - sunPosition(time).equation);
}

double PrayTime::angleTime(double angle, double time, int direction) {
    double decl = sunPosition(time).declination;
    double numerator = -std::sin(angle * M_PI / 180.0) - std::sin(lat * M_PI / 180.0) * std::sin(decl * M_PI / 180.0);
    double denominator = std::cos(lat * M_PI / 180.0) * std::cos(decl * M_PI / 180.0);
    double diff = std::acos(numerator / denominator) * 180.0 / M_PI / 15.0;
    return midDay(time) + (diff * direction);
}

std::map<std::string, std::string> PrayTime::getTimes(int year, int month, int day) {
    struct tm t = {0};
    t.tm_year = year - 1900; t.tm_mon = month - 1; t.tm_mday = day;
    utcTime = mktime(&t);

    double fajr = angleTime(activeMethod.fajr, 5, -1);
    double sunrise = angleTime(0.833, 6, -1);
    double dhuhr = midDay(12);
    double sunset = angleTime(0.833, 18);
    double maghrib = (activeMethod.maghribType == "min") ? sunset + activeMethod.maghrib / 60.0 : angleTime(activeMethod.maghrib, 18);
    double isha = (activeMethod.ishaType == "min") ? maghrib + activeMethod.isha / 60.0 : angleTime(activeMethod.isha, 18);

    return {
        {"Fajr", formatTime(fajr)}, {"Sunrise", formatTime(sunrise)},
        {"Dhuhr", formatTime(dhuhr)}, {"Sunset", formatTime(sunset)},
        {"Maghrib", formatTime(maghrib)}, {"Isha", formatTime(isha)}
    };
}

std::string PrayTime::formatTime(double time) {
    time = fixAngle(time + timeZone - lng / 15.0);
    int hours = (int)std::floor(time);
    int minutes = (int)std::floor((time - hours) * 60 + 0.5);
    char buf[10];
    std::snprintf(buf, sizeof(buf), "%02d:%02d", hours, minutes);
    return std::string(buf);
}