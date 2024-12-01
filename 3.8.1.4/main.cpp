#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <numeric>

using namespace std;

// ������� ��� ��������� �����
string generateGamma(const string& initialGamma, size_t length) {
    string gamma = initialGamma;
    while (gamma.size() < length) {
        gamma += initialGamma;
    }
    return gamma.substr(0, length);
}

// ������� ����������
string encrypt(const string& plainText, const string& gamma) {
    if (plainText.size() != gamma.size()) {
        throw invalid_argument("������ ������ � ����� ������ ���������");
    }
    string cipherText;
    for (size_t i = 0; i < plainText.size(); ++i) {
        cipherText += plainText[i] ^ gamma[i];
    }
    return cipherText;
}

// ������� ���������� ����������� �����
uint8_t calculateChecksum(const string& text) {
    return accumulate(text.begin(), text.end(), 0) % 256;
}

// ������� ���������� �����
void encryptFile(const string& inputFileName, const string& outputFileName, const string& initialGamma) {
    ifstream inputFile(inputFileName, ios::binary);
    if (!inputFile) {
        throw runtime_error("�� ������� ������� ������� ����");
    }

    string plainText((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    // ����� ����� ��������� ������
    cout << "����� ��������� ������: " << plainText.size() << endl;

    // ��������� ����� � ����������
    string gamma = generateGamma(initialGamma, plainText.size());
    string cipherText = encrypt(plainText, gamma);

    // ���������� ����������� �����
    uint8_t checksum = calculateChecksum(plainText);

    // ������ � �������� ����
    ofstream outputFile(outputFileName, ios::binary);
    if (!outputFile) {
        throw runtime_error("�� ������� ������� �������� ����");
    }
    outputFile.write(cipherText.c_str(), cipherText.size());
    outputFile.put(static_cast<char>(checksum)); // ���������� ����������� ����� � ����� �����
    outputFile.close();

    cout << "���������� ���������. ����������� ����� ��������� ������: " << static_cast<int>(checksum) << endl;
}

// ������� ����������� � ��������
void decryptAndValidate(const string& inputFileName, const string& initialGamma) {
    ifstream inputFile(inputFileName, ios::binary);
    if (!inputFile) {
        throw runtime_error("�� ������� ������� ������������� ����");
    }

    // ������ �������������� ������ � ����������� �����
    string cipherText((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    if (cipherText.empty()) {
        throw runtime_error("���� ����");
    }
    uint8_t checksum = static_cast<uint8_t>(cipherText.back());
    cipherText.pop_back(); // ������� ����������� ����� �� ������
    inputFile.close();

    // ��������� ����� � �����������
    string gamma = generateGamma(initialGamma, cipherText.size());
    string decryptedText = encrypt(cipherText, gamma); // XOR-�������

    // ���������� ����������� ����� ��������������� ������
    uint8_t calculatedChecksum = calculateChecksum(decryptedText);

    // ��������
    if (calculatedChecksum != checksum) {
        throw runtime_error("����������� ����� �� ���������. ���� ��������!");
    }

    cout << "����������� �������. ����������� �����: " << static_cast<int>(calculatedChecksum) << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        // ���������� ������� � �������� �����, � ����� �����
        const string inputFileName = "file_in.txt";
        const string outputFileName = "file_out.txt";
        const string initialGamma = "ABCDEFGH"; // ������ �����

        // ���������� �����
        encryptFile(inputFileName, outputFileName, initialGamma);

        // �������� � ����������� �����
        decryptAndValidate(outputFileName, initialGamma);

        return 0;
    } catch (const exception& e) {
        cerr << "������: " << e.what() << endl;
        return 1;
    }
}
