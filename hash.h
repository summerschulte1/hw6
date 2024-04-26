#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

#include <cctype> // for std::tolower
#include <string>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
    // Convert the string into numbers and compute hash value
    HASH_INDEX_T w[5] = {0, 0, 0, 0, 0};
    int n = k.size();
    int segment = 0;  // This will track which segment we are filling
    for (int i = n; i > 0; i -= 6) {
        int j = std::max(0, i - 6); // Start of the substring of up to 6 characters
        HASH_INDEX_T value = 0;
        HASH_INDEX_T power = 1;
        for (int pos = i - 1; pos >= j; --pos) {
            value += letterDigitToNumber(k[pos]) * power;
            power *= 36;
        }
        w[4 - segment] = value;  // Populate w from end to start
        segment++;
    }

    // Debug prints to verify the w values and computation
    for (int i = 0; i < 5; ++i) {
        std::cout << "w[" << i << "] = " << w[i] << std::endl;
    }

    // Compute the final hash value
    HASH_INDEX_T h_k = 0;
    for (int i = 0; i < 5; ++i) {
        h_k += rValues[i] * w[i];
    }

    //std::cout << "Computed hash: " << h_k << std::endl;

    return h_k;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (std::isdigit(letter))
            return 26 + (letter - '0'); // 0-9 -> 26-35
        letter = std::tolower(letter);
        if (std::isalpha(letter))
            return letter - 'a'; // a-z -> 0-25
        return 0; // default case (should not occur i

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i = 0; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
