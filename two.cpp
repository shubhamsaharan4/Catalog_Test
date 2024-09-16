#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

// Function to convert a string representation of a number in a given base to an integer
int decodeValue(const std::string& value, int base) {
    int result = 0;
    for (char c : value) {
        result *= base;
        if (std::isdigit(c)) {
            result += c - '0';
        } else if (std::islower(c)) {
            result += c - 'a' + 10;
        } else if (std::isupper(c)) {
            result += c - 'A' + 10;
        }
    }
    return result;
}

// Function to perform Lagrange interpolation to find the polynomial value at x = 0
double lagrangeInterpolation(const std::vector<int>& x, const std::vector<int>& y) {
    int n = x.size();
    double result = 0.0;

    for (int i = 0; i < n; ++i) {
        double term = y[i];
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                term *= (0 - x[j]) / static_cast<double>(x[i] - x[j]);
            }
        }
        result += term;
    }

    return result;
}

// Function to extract a value from a JSON string
std::string extractValue(const std::string& json, const std::string& key) {
    std::size_t start = json.find("\"" + key + "\": {");
    if (start == std::string::npos) return "";

    start = json.find("\"value\": \"", start) + 10;
    if (start == std::string::npos) return "";

    std::size_t end = json.find("\"", start);
    if (end == std::string::npos) return "";

    return json.substr(start, end - start);
}

// Function to extract a base from a JSON string
int extractBase(const std::string& json, const std::string& key) {
    std::size_t start = json.find("\"" + key + "\": {");
    if (start == std::string::npos) return -1;

    start = json.find("\"base\": \"", start) + 9;
    if (start == std::string::npos) return -1;

    std::size_t end = json.find("\"", start);
    if (end == std::string::npos) return -1;

    return std::stoi(json.substr(start, end - start));
}

int main() {
    // Open and read the JSON file
    std::ifstream file("testcase2.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.json" << std::endl;
        return 1;
    }

    std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    std::vector<int> x_values;
    std::vector<int> y_values;

    for (int i = 1; i <= 9; ++i) {
        std::string key = std::to_string(i);
        int base = extractBase(json, key);
        std::string value = extractValue(json, key);

        if (base != -1 && !value.empty()) {
            x_values.push_back(i);
            y_values.push_back(decodeValue(value, base));
        }
    }

    // Find the constant term c
    double constant_term = lagrangeInterpolation(x_values, y_values);

    // Output the result
    std::cout << std::fixed << std::setprecision(2) << "Constant term (c): " << constant_term << std::endl;

    return 0;
}
