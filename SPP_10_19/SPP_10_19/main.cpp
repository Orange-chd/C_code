// main.cpp

#include "RinexReader.h"

int main() {
    RinexObsReader reader;

    // �滻Ϊ��Ĺ۲��ļ���
    std::string filename = "E:\\data\\��ͬO�ļ�\\HSC011520.obs";

    if (reader.readFile(filename)) {
        std::cout << "Successfully read and parsed file: " << filename << std::endl;
        std::cout << std::endl;

        // ��ӡ��ȡ�����ݽ�����֤
        reader.printData();
    }
    else {
        std::cerr << "Failed to process file: " << filename << std::endl;
    }

    // �������Դ� reader �����л�ȡ���ݽ���SPP����
    // const auto& all_epochs = reader.getEpochs();
    // for(const auto& epoch : all_epochs) {
    //     // �����￪ʼ��ÿ����Ԫ����SPP����...
    // }

    return 0;
}