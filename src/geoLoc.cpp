#include "geoLoc.h"


Location::Location(const std::string& locationName) : name(locationName) {
    auto it = locationDatabase.find(locationName);
    
    if (it != locationDatabase.end()) {
        latitude = it->second.latitude;
        longitude = it->second.longitude;
        usesDST = it->second.usesDST;
    } else {
        throw std::invalid_argument("Location '" + locationName + "' not found in database.");
    }
}


// Initialize the mock database with some example cities
const std::unordered_map<std::string, GeoData> Location::locationDatabase = {
    {"New York", {40.7128, -74.0060, true}},
    {"London",   {51.5074, -0.1278, true}},
    {"Tokyo",    {35.6762, 139.6503, false}}, // Japan does not observe DST
    {"Tigard",   {45.455277777778, -122.750833333, true}},
    {"Portland", {45.522148, -122.676483, true}},
    {"Beaverton", {45.522148, -122.676483, true}},
    {"Clackamas", {45.432222, -122.771111, true}},
    {"Lake Oswego", {45.432222, -122.771111, true}},
    {"Sydney",   {-33.8688, 151.2093, true}},
    {"Phoenix",  {33.4484, -112.0740, false}} // Arizona does not observe DST
};

