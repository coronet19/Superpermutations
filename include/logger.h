#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <concepts>
#include <chrono>


class Logger{
private:
    std::ofstream file;
    std::chrono::time_point<std::chrono::steady_clock> startTime;

    template <typename T>
    std::string vectorToString(const std::vector<T>& v){
        std::stringstream ss;

        for(size_t i = 0; i < v.size(); ++i){
            if constexpr(std::same_as<T, uint8_t>){
                ss << static_cast<uint32_t>(v[i]);
            } else{
                ss << v[i];
            }
        }

        return ss.str();
    }

public:
    Logger(const std::string& fileName){
        file.open(fileName, std::ios::app);

        if(file.is_open() && file.tellp() == 0){
            file << "Time,n,Superperm Size,Superperm\n";
        }

        startTime = std::chrono::steady_clock::now();
    }

    ~Logger() {
        if(file.is_open()) file.close();
    }

    template <typename T>
    bool log(const size_t& size, const std::vector<T>& v){
        if(!file.is_open()) return false;

        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - startTime;

        file << elapsed.count() << "," << static_cast<uint32_t>(size) << "," << v.size() << "," << vectorToString(v) << "\n";
        file.flush();

        return true;
    }
};
