#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>

// A helper struct to hold our location data
struct GeoData {
    double latitude;
    double longitude;
    bool usesDST; // True if the location observes Daylight Saving Time
};

class Location {
private:
    std::string name;
    double latitude;
    double longitude;
    bool usesDST;

    // Simulated internal database of locations
    static const std::unordered_map<std::string, GeoData> locationDatabase;

public:
    // Constructor: Takes a location name and populates the class members
    Location(const std::string& locationName);

    // Getters
    std::string getName() const { return name; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    bool hasDST() const { return usesDST; }
};

