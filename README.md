Lagrange Interpolation Program
Overview
This C++ program performs Lagrange interpolation based on values extracted from a JSON file.

Requirements
C++11 or later
C++ compiler (e.g., g++)
JSON File Format
testcase2.json should be formatted like this:

json
Copy code
{
    "1": {"base": "10", "value": "15"},
    "2": {"base": "16", "value": "A"},
    ...
}
Compilation
Compile the program with:

bash
Copy code
g++ -o interpolation main.cpp
Running
Run the executable:

bash
Copy code
./interpolation
Ensure testcase2.json is in the same directory.
