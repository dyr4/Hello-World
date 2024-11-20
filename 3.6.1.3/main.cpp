#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

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

int main() {
    setlocale(LC_ALL, "Russian");

    string inputFileName = "file_in.txt";
    string outputFileName = "file_out.txt";

    // ����������� �������� ��� ������
    int currentDay = Day();
    string dayName = getDayName(currentDay);

    // ��������� �����
    string gamma = generateGamma(currentDay);

    cout << "�������: " << dayName << endl;
    cout << "������������ �����: " << gamma << endl;

    // ������ ������ �� �������� �����
    string data = readFile(inputFileName);

    // ����� ����������� �����
    unsigned char checksum = calculateChecksum(data);
    cout << "����������� ����� ������: " << static_cast<int>(checksum) << endl;

    // ���������� ������
    string encodedData = encode(data, gamma);

    // ������ �������������� ������ � ����
    writeFile(outputFileName, encodedData);

    // ������������� ������ ��� ��������
    string decodedData = encode(encodedData, gamma); // ������������� ��������� ����������

    // ����� �����������
    cout << "\n�������� �����:\n" << data << endl;
    cout << "\n������������� �����:\n" << encodedData << endl;
    cout << "\n�������������� ����� (��������):\n" << decodedData << endl;

    cout << "\n���������� ���������. ��������� ������� � " << outputFileName << endl;

    return 0;
}
