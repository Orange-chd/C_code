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

// 1. �洢����Ƶ��Ļ����۲����� (α�ࡢ�ز��������)
struct ObsData {
    double P; // Pseudorange (α��)
    double L; // Carrier Phase (�ز���λ)
    double S; // Signal-to-Noise Ratio (�����)
    std::string p_code, l_code, s_code; // ��¼ʵ��ʹ�õĹ۲�������

    ObsData() : P(0.0), L(0.0), S(0.0) {}
};
// 2. �洢���������ڵ�����Ԫ������Ƶ��۲�����
struct SatObs {
    char system;     // ����ϵͳ ('G', 'C', 'R', 'E')
    int prn;         // ����PRN��
    // ʹ�� map �洢��ͬƵ��Ĺ۲�����, key: Ƶ��� (1, 2, 5, 7...), value: ��Ƶ��Ĺ۲�����
    std::map<int, ObsData> obs_data;
};

// 3. �洢������Ԫ���������ǹ۲�����
struct EpochObs {
    // ��Ԫʱ��
    int year, month, day, hour, minute;
    double second;
    // ����Ԫ�µ����ǹ۲��б�
    std::vector<SatObs> sat_obs_list;
};

// 4. RINEX�۲��ļ���ȡ����
class RinexObsReader {
public:
    // ��ȡ������RINEX�۲��ļ�
    bool readFile(const std::string& filename);

    // ��ȡ������Ԫ�Ĺ۲�����
    const std::vector<EpochObs>& getEpochs() const { return all_epochs_data; }

    // (��ѡ) ��ӡ��ȡ�������Թ���֤
    void printData() const;

private:
    // ����ͷ�ļ�
    bool parseHeader(std::ifstream& file);
    // ����������
    bool parseBody(std::ifstream& file);

    // �洢ͷ�ļ��ж���Ĺ۲�����
    // key: ����ϵͳ ('G', 'C'...), value: ��ϵͳ��Ӧ�Ĺ۲������б� (�� {"C1C", "L1C", "S1C", ...})
    std::map<char, std::vector<std::string>> sys_obs_types;

    // �洢������Ԫ������
    std::vector<EpochObs> all_epochs_data;
};

#endif // RINEX_READER_H