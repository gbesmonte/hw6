#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

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
        // Add your code here
        std::string temp = k;
        unsigned long long w[5] = {0};
        int c = 0;
        while (!temp.empty()){
            HASH_INDEX_T a[6] = {0};
            std::string curr = "------";
            if (temp.size() >= 6){
                curr = temp.substr(temp.size()-6, temp.size());
                temp = temp.substr(0, temp.size()-6);
            }
            else if (temp.size() >= 1){
                curr.replace(6-temp.size(), temp.size(), temp);
                temp = "";
            }
            else if (temp.empty()){
                temp = "";
            }
            for (int i =0; i < 6; i++){
                a[5-i] = letterDigitToNumber(curr[i]);
                //std::cout << "a:" << a[5-i] << std::endl;
            }
            w[c] = ((((((a[5]) * 36 + a[4]) * 36 + a[3]) * 36 + a[2]) * 36 + a[1]) * 36 + a[0]);
            std::cout << w[c] << std::endl;
            c++;
        }


        return rValues[0] * w[4] + rValues[1] * w[3] + rValues[2] * w[2] + rValues[3] * w[1] + rValues[4] * w[0];
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = tolower(letter);
        if (letter == '-'){
            return 0;
        }
        if (int(letter) >= 97 && int(letter) <= 122){
            return int(letter) - 97;
        }
        if (int(letter) >= 48 && int(letter) <= 57){
            return int(letter) - 22;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
