#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ������� ��� ��������� �����
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()]; // ���������� ���� ������ �����
    }
    return generatedKey;
}

// ������� ��� ���������� � ������������
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i]; // ���������� XOR ��� ���������� � ������������
    }
    return result;
}

int main() {
    setlocale(0, "Russian");

    string file_in, file_out;
    file_in = "file_in.txt";
    file_out = "file_out.txt";

    // ������ ������ �� �����
    string text;
    ifstream fileIn(file_in);

    if (fileIn.is_open()) {
        getline(fileIn, text);
        fileIn.close();
    } else {
        cout << "������: �� ������� ������� ���� " << file_in << endl;
        return 1; // ��������� ��������� ��� ������
    }

    // ����� �����
    string gamma = "2";

    // ��������� ����� ������ �����
    string generatedKey = generateKey(gamma, text.size());
    cout << "��������� �����: " << generatedKey << endl;

    // ����������
    string ciphertext = xorCipher(text, generatedKey);

    // ���������� ����� � ������ ��������� ������
    char lengthByte = static_cast<char>(text.size());
    ciphertext += lengthByte; //  ��������� ���� �����

    cout << "������������� �����: " << ciphertext << endl;

    // ������ �������������� ������ � ����
    ofstream outputFile(file_out, ios::binary); // ��������� ���� � �������� ������
    if (!outputFile.is_open()) {
        cout << "������ ��� �������� ����� " << file_out << endl;
        return 1;
    }

    outputFile.write(ciphertext.c_str(), ciphertext.size());
    outputFile.close();

    // ������������ ������
    int originalLength = static_cast<unsigned char>(ciphertext.back()); // �������� ����� �� ���������� �����
    string decryptedtext = xorCipher(ciphertext.substr(0, ciphertext.size() - 1), generatedKey); // ������� ��������� ����
    cout << "�������������� �����: " << decryptedtext.substr(0, originalLength) << endl; // ������� ������ ������������ �����

    return 0;
}

