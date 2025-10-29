// RinexReader.cpp (����������, ���� C++11, �����޸���Ŀ����)

#include "RinexReader.h"
#include <algorithm> // for std::sort if needed
#include <vector>    // for std::vector
#include <utility>   // for std::pair

// ��������1: ���ݹ۲����ȡƵ�ʱ��
int getFreqFromCode(const std::string& code) {
    if (code.length() < 2) return 0;
    // ��2���ַ�ͨ������Ƶ�� (e.g., C1C, L2W, S5X)
    char freq_char = code[1];
    if (isdigit(freq_char)) {
        return freq_char - '0';
    }
    return 0; //�޷�ʶ���Ƶ��
}

// readFile �� parseHeader �������ֲ��� (�����֮ǰû�޸Ĺ�)

bool RinexObsReader::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }

    if (!parseHeader(file)) {
        std::cerr << "Error: Failed to parse RINEX header." << std::endl;
        return false;
    }

    if (!parseBody(file)) {
        std::cerr << "Error: Failed to parse RINEX body." << std::endl;
        return false;
    }

    file.close();
    return true;
}

bool RinexObsReader::parseHeader(std::ifstream& file) {
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("SYS / # / OBS TYPES") != std::string::npos) {
            char sys_char = line[0];
            if (sys_char == ' ') { // ������ G R E C �����
                std::string sys_str;
                std::stringstream ss(line);
                ss >> sys_str;
                if (!sys_str.empty()) sys_char = sys_str[0];
                else continue;
            }

            std::stringstream ss(line);
            std::string temp;
            int num_obs_types;

            ss >> temp; // ����ϵͳ�ַ���ո�
            if (sys_char != 'G' && sys_char != 'R' && sys_char != 'E' && sys_char != 'C' && sys_char != 'J' && sys_char != 'I') { // �����һ������ϵͳ�ַ����ٶ�һ��
                ss >> temp;
            }
            ss >> num_obs_types;

            std::vector<std::string> obs_types;
            for (int i = 0; i < num_obs_types; ++i) {
                if (ss >> temp) {
                    obs_types.push_back(temp);
                }
                else { // ���һ�ж����꣬���м�����
                    if (std::getline(file, line)) {
                        std::stringstream next_ss(line);
                        for (int j = 0; j < 13 && i < num_obs_types; ++j, ++i) { // RINEX 3.x �������13��
                            if (next_ss >> temp) obs_types.push_back(temp);
                            else break;
                        }
                        i--; // ѭ��������������Ҫ��һ
                    }
                }
            }
            sys_obs_types[sys_char] = obs_types;
        }
        else if (line.find("END OF HEADER") != std::string::npos) {
            return true;
        }
    }
    return false;
}


// **����**: parseBody ����ʹ�� C++11 �﷨��д
bool RinexObsReader::parseBody(std::ifstream& file) {
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] != '>') {
            continue;
        }

        EpochObs current_epoch;
        std::stringstream ss(line);
        char gt;
        int num_sats_in_header;
        ss >> gt >> current_epoch.year >> current_epoch.month >> current_epoch.day
            >> current_epoch.hour >> current_epoch.minute >> current_epoch.second >> gt >> num_sats_in_header;

        for (int i = 0; i < num_sats_in_header; ++i) {
            if (!std::getline(file, line)) {
                break;
            }

            char sys = line[0];
            if (sys == ' ' || sys_obs_types.find(sys) == sys_obs_types.end()) {
                continue;
            }
            int prn = std::stoi(line.substr(1, 2));
            const auto& obs_type_order = sys_obs_types.at(sys);

            std::map<std::string, double> raw_obs_map;
            for (size_t k = 0; k < obs_type_order.size(); ++k) {
                size_t start_pos = 3 + k * 16;
                if (start_pos + 14 > line.length()) break;

                std::string obs_str = line.substr(start_pos, 14);
                if (obs_str.find_first_not_of(' ') != std::string::npos) {
                    try {
                        raw_obs_map[obs_type_order[k]] = std::stod(obs_str);
                    }
                    catch (const std::invalid_argument&) {
                        // ����ת��ʧ�ܵ��ֶ�
                    }
                }
            }

            std::map<int, std::map<char, std::pair<double, std::string>>> grouped_by_freq;
            for (std::map<std::string, double>::const_iterator it = raw_obs_map.begin(); it != raw_obs_map.end(); ++it) {
                const std::string& code = it->first;
                double value = it->second;
                char type = code[0];
                int freq = getFreqFromCode(code);
                if (freq > 0 && (type == 'C' || type == 'L' || type == 'S')) {
                    if (grouped_by_freq[freq].find(type) == grouped_by_freq[freq].end()) {
                        grouped_by_freq[freq][type] = std::make_pair(value, code);
                    }
                }
            }

            SatObs sat_obs;
            sat_obs.system = sys;
            sat_obs.prn = prn;

            // **����**: ʹ�� C++11 �� for ѭ������ map
            for (std::map<int, std::map<char, std::pair<double, std::string>>>::const_iterator it = grouped_by_freq.begin(); it != grouped_by_freq.end(); ++it) {
                int freq = it->first;
                const std::map<char, std::pair<double, std::string>>& obs_map = it->second;

                std::map<char, std::pair<double, std::string>>::const_iterator p_it = obs_map.find('C');
                std::map<char, std::pair<double, std::string>>::const_iterator l_it = obs_map.find('L');
                std::map<char, std::pair<double, std::string>>::const_iterator s_it = obs_map.find('S');

                if (p_it != obs_map.end() && l_it != obs_map.end() && s_it != obs_map.end() &&
                    p_it->second.first != 0.0 && l_it->second.first != 0.0 && s_it->second.first != 0.0) {

                    ObsData data;
                    data.P = p_it->second.first;
                    data.p_code = p_it->second.second;
                    data.L = l_it->second.first;
                    data.l_code = l_it->second.second;
                    data.S = s_it->second.first;
                    data.s_code = s_it->second.second;
                    sat_obs.obs_data[freq] = data;
                }
            }

            if (!sat_obs.obs_data.empty()) {
                current_epoch.sat_obs_list.push_back(sat_obs);
            }
        }
        all_epochs_data.push_back(current_epoch);
    }
    return true;
}

// **����**: printData ����ʹ�� C++11 �﷨
void RinexObsReader::printData() const {
    std::cout << "===== RINEX Observation Data Loaded =====" << std::endl;
    std::cout << "Total Epochs Read: " << all_epochs_data.size() << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    if (all_epochs_data.empty()) {
        std::cout << "No valid epochs found after filtering." << std::endl;
        return;
    }

    // ���޸Ŀ�ʼ��������������һ�� for ѭ��������������Ԫ
    for (std::vector<EpochObs>::const_iterator epoch_it = all_epochs_data.begin(); epoch_it != all_epochs_data.end(); ++epoch_it) {
        // ��ѭ���ڲ���epoch ����ǰ���ڴ������һ����Ԫ
        const EpochObs& epoch = *epoch_it;

        // ������ ԭ�����еĴ�ӡ�������ڶ������ѭ���ڲ� ������

        // ��ӡ��ǰ��Ԫ��ͷ��Ϣ
        printf("Epoch: %04d/%02d/%02d %02d:%02d:%05.2f | Valid Satellites: %zu\n",
            epoch.year, epoch.month, epoch.day, epoch.hour, epoch.minute, epoch.second, epoch.sat_obs_list.size());

        // ��ӡ��ǰ��Ԫ�µ�������������
        for (size_t i = 0; i < epoch.sat_obs_list.size(); ++i) {
            const SatObs& sat = epoch.sat_obs_list[i];
            printf("  - Sat: %c%02d\n", sat.system, sat.prn);

            std::map<int, ObsData> sorted_obs(sat.obs_data.begin(), sat.obs_data.end());
            for (std::map<int, ObsData>::const_iterator it = sorted_obs.begin(); it != sorted_obs.end(); ++it) {
                const int& freq = it->first;
                const ObsData& obs_data = it->second;
                printf("    - Freq %d: P(%s)=%.3f, L(%s)=%.3f, S(%s)=%.3f\n",
                    freq,
                    obs_data.p_code.c_str(), obs_data.P,
                    obs_data.l_code.c_str(), obs_data.L,
                    obs_data.s_code.c_str(), obs_data.S);
            }
        }
        std::cout << "-----------------------------------------" << std::endl;

    } // ���޸Ľ�����for ѭ�����˽���
}