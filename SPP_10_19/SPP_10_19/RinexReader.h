#pragma once
// RinexReader.h

#ifndef RINEX_READER_H
#define RINEX_READER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

// 1. 存储单个频点的基本观测数据 (伪距、载波、信噪比)
struct ObsData {
    double P; // Pseudorange (伪距)
    double L; // Carrier Phase (载波相位)
    double S; // Signal-to-Noise Ratio (信噪比)
    std::string p_code, l_code, s_code; // 记录实际使用的观测码类型

    ObsData() : P(0.0), L(0.0), S(0.0) {}
};
// 2. 存储单颗卫星在单个历元的所有频点观测数据
struct SatObs {
    char system;     // 卫星系统 ('G', 'C', 'R', 'E')
    int prn;         // 卫星PRN号
    // 使用 map 存储不同频点的观测数据, key: 频点号 (1, 2, 5, 7...), value: 该频点的观测数据
    std::map<int, ObsData> obs_data;
};

// 3. 存储单个历元的所有卫星观测数据
struct EpochObs {
    // 历元时间
    int year, month, day, hour, minute;
    double second;
    // 该历元下的卫星观测列表
    std::vector<SatObs> sat_obs_list;
};

// 4. RINEX观测文件读取器类
class RinexObsReader {
public:
    // 读取并解析RINEX观测文件
    bool readFile(const std::string& filename);

    // 获取所有历元的观测数据
    const std::vector<EpochObs>& getEpochs() const { return all_epochs_data; }

    // (可选) 打印读取的数据以供验证
    void printData() const;

private:
    // 解析头文件
    bool parseHeader(std::ifstream& file);
    // 解析数据体
    bool parseBody(std::ifstream& file);

    // 存储头文件中定义的观测类型
    // key: 卫星系统 ('G', 'C'...), value: 该系统对应的观测类型列表 (如 {"C1C", "L1C", "S1C", ...})
    std::map<char, std::vector<std::string>> sys_obs_types;

    // 存储所有历元的数据
    std::vector<EpochObs> all_epochs_data;
};

#endif // RINEX_READER_H