#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;
using namespace std::chrono;

// ����������� ��� ������
int Day() {
    auto t1 = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(t1);
    tm* local_tm = localtime(&currentTime);
    return local_tm->tm_wday;
}

// ��������� �������� ��� ������
string getDayName(int day) {
    switch (day) {
        case 0: return "�����������";
        case 1: return "�����������";
        case 2: return "�������";
        case 3: return "�����";
        case 4: return "�������";
        case 5: return "�������";
        case 6: return "�������";
        default: return "����������� ����";
    }
}

// ��������� ����� � ����������� �� ��� ������
string generateGamma(int dayW) {
    switch(dayW) {
        case 1:
        case 3:
        case 5:
            return "ABCD EFGH IJKL MNOP";
        case 2:
        case 4:
            return "GHEF OPMN ABCD IJKL";
        case 6:
        case 0: // 0 ������������� �����������
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
}

// ������� ����������� �����
unsigned char calculateChecksum(const string& data) {
    unsigned char checksum = 0;
    for (char ch : data) {
        checksum = (checksum + static_cast<unsigned char>(ch)) % 256;
    }
    return checksum;
}

// ����������/������������� ������ � �������������� �����
string encode(const string& data, const string& gamma) {
    string result;
    size_t sizeGamma = gamma.size();

    for (size_t i = 0; i < data.size(); i++) {
        char currentGamma = gamma[i % sizeGamma];
        result.push_back(data[i] ^ currentGamma);
    }

    return result;
}

// ������ ������ �� �����
string readFile(const string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "������ �������� ����� " << fileName << endl;
        return "";
    }

    string line, text;
    while (getline(inputFile, line)) {
        text += line + '\n';
    }
    inputFile.close();

    return text;
}

// ������ ������ � ����
void writeFile(const string& fileName, const string& data) {
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        cerr << "������ �������� ����� ��� ������ " << fileName << endl;
        return;
    }

    outputFile << data;
    outputFile.close();
}

// �����
void testGetDayName() {
    assert(getDayName(0) == "�����������");
    assert(getDayName(1) == "�����������");
    assert(getDayName(2) == "�������");
    assert(getDayName(3) == "�����");
    assert(getDayName(4) == "�������");
    assert(getDayName(5) == "�������");
    assert(getDayName(6) == "�������");
    assert(getDayName(7) == "����������� ����");
    cout << "testGetDayName �������" << endl;
}

void testGenerateGamma() {
    assert(generateGamma(1) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(2) == "GHEF OPMN ABCD IJKL");
    assert(generateGamma(3) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(4) == "GHEF OPMN ABCD IJKL");
    assert(generateGamma(5) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(6) == "GHEF CDAB OPMN KLIJ");
    assert(generateGamma(0) == "GHEF CDAB OPMN KLIJ");
    assert(generateGamma(7) == "");
    cout << "testGenerateGamma �������" << endl;
}

void testCalculateChecksum() {
    assert(calculateChecksum("") == 0);
    assert(calculateChecksum("a") == 'a');
    assert(calculateChecksum("abc") == ('a' + 'b' + 'c') % 256);
    cout << "testCalculateChecksum �������" << endl;
}

void testEncode() {
    string gamma = "ABCD";
    string data = "abcd";
    string encoded = encode(data, gamma);
    string decoded = encode(encoded, gamma);
    assert(decoded == data);
    cout << "testEncode �������" << endl;
}

void testReadWriteFile() {
    string fileName = "test_file.txt";
    string data = "Test data";
    writeFile(fileName, data);
    string readData = readFile(fileName);
    assert(readData == data + '\n');
    cout << "testReadWriteFile �������" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    testGetDayName();
    testGenerateGamma();
    testCalculateChecksum();
    testEncode();
    testReadWriteFile();

    cout << "��� ����� ��������!" << endl;
    return 0;
}
