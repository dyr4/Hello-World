#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ������� ��� ��������� �����
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()]; //���������� ���� ������ �����
    }
    return generatedKey;
}

// ������� ��� ���������� � ������������
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i]; // ���������� XoR ��� ���������� � ������������
    }
    return result;
}

// ������� ��� ����������� �����
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cirillicCount = 0;

    for (char c : text) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) { // ������� ��������� ��������
            latinCount++;
        } else if ((c >= '�' && c <= '�') || (c >= '�' && c <= '�')) { // ������� ���������
            cirillicCount++;
        }
    }
    if(latinCount > cirillicCount)
    {
        return "latin";
    }
    else
    {
        return "cirillic";
    }
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
    }
    else
    {
        cout << "������: �� ������� ������� ���� " << file_in << endl;
    }

    string gammaType = chooseGammaType(text);

    // ����� �����
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // ��������� �����
    } else {
        gamma = "�����Ũ����������������������������������������������������������"; // ������������� �����
    }

    // ��������� ����� ������ �����
    string generatedKey = generateKey(gamma, text.size()); // ���������� ��������� ����
    cout << "��������� �����: " << generatedKey << endl;

    // ����������
    string ciphertext = xorCipher(text, generatedKey);
    cout << "������������� �����: " << ciphertext << endl;

    // ������ �������������� ������ � ����
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "������ ��� �������� ����� " << file_out << endl;
        return 1;
    }

    outputFile << ciphertext;
    outputFile.close();

    // ������������ ������
    string decryptedtext = xorCipher(ciphertext, generatedKey);
    cout << "�������������� �����: " << decryptedtext << endl;

    return 0;
}
