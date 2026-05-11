# CprayTime
## PrayTime calculator

[![MIT License][license-image]][license] [![NPM version][npm-version-image]][npm-url]

C++ Prayer Times Calculator
This project is a C++ port of the praytime.js library, optimized for performance and modularity. 
It includes a core library (static and shared) and a CLI tool to generate prayer time tables.

This program is based on Javascript version of the same name ('prayname') by Zarrabi Hamid (https://github.com/zarrabi/praytime)

## Prerequisites
Ensure your Linux environment (such as Ubuntu, Kubuntu, or Mint) has the following installed:

CMake (v3.10+)

GCC or Clang (supporting C++17)

Make

## How to build


### clone it
git clone https://github.com/buhadram/cpraytime
cd cpraytime

### Build Instructions
Follow these steps to generate the shared library (.so), static library (.a), and the CLI executable:

1. Create a build directory:

```
mkdir build && cd build
```

2. Configure with CMake:

```
cmake ..
```

3. Compile:
```
make
```
or
```
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Running the CLI Tool
The executable praytime_cli requires three arguments: latitude, longitude, and method.

Local Example: Tigard, Oregon

To generate a table for the current month in Tigard, Oregon (approximate coordinates: 45.43, -122.77) using the ISNA method:

```
./praytime_cli 45.455277777778 -122.750833333 ISNA
```

### Conversion of Longitude/Latitude to their decimals

To convert Degrees, Minutes, and Seconds (DMS) to Decimal Degrees, use this formula:

\(\text{Decimal\ Degrees}=\text{Degrees}+\left(\frac{\text{Minutes}}{60}\right)+\left(\frac{\text{Seconds}}{3600}\right)\)

Quick Conversion Steps
1. Divide the minutes by 60.
2. Divide the seconds by 3600. 
3. Add those two values to the degrees.
4. Assign the sign based on direction:
   - North (N) / East (E): Positive (+)
   - South (S) / West (W): Negative (-)

### Example: 
45° 27' 19" N
- 45 + \frac{27}{60} + \frac{19}{3600} = 45.455277777778
- Since it is North, the final answer is +45.455277777778

122° 45' 03" W
- 122 + \frac{45}{60} + \frac{03}{3600} = 
- Since it is West, the final answer is -122.750833333
