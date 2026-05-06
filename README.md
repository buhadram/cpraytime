# CprayTime
## PrayTime calculator

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

### Running the CLI Tool
The executable praytime_cli requires three arguments: latitude, longitude, and method.

Local Example: Tigard, Oregon
To generate a table for the current month in Tigard, Oregon (approximate coordinates: 45.43, -122.77) using the ISNA method:

```
./praytime_cli 45.43 -122.77 ISNA
```

