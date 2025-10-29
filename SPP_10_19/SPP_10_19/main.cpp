// main.cpp

#include "RinexReader.h"

int main() {
    RinexObsReader reader;

    // 替换为你的观测文件名
    std::string filename = "E:\\data\\不同O文件\\HSC011520.obs";

    if (reader.readFile(filename)) {
        std::cout << "Successfully read and parsed file: " << filename << std::endl;
        std::cout << std::endl;

        // 打印读取的数据进行验证
        reader.printData();
    }
    else {
        std::cerr << "Failed to process file: " << filename << std::endl;
    }

    // 后续可以从 reader 对象中获取数据进行SPP计算
    // const auto& all_epochs = reader.getEpochs();
    // for(const auto& epoch : all_epochs) {
    //     // 在这里开始对每个历元进行SPP解算...
    // }

    return 0;
}