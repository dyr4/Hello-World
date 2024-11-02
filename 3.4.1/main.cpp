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

// ������� ����������� �����
char kontrolnayaSumma(const string& text)
{
    int checksum = 0;
    for (int i = 0; i < text.length(); i++) {
        checksum += (int)text[i];
    }
    return static_cast<char>(checksum);
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

    // ������� ����������� �����
    char kontSum = kontrolnayaSumma(text);
    text += kontSum;

    // ����������
    string ciphertext = xorCipher(text, generatedKey);
    cout << "������������� �����: " << ciphertext << endl;

    // ������ �������������� ������ � ����
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "������ ��� �������� ����� " << file_out << endl;
        return 1;
    }

    outputFile.write(ciphertext.c_str(), ciphertext.size());
    outputFile.close();

    // ������������ ������
    string decryptedtext = xorCipher(ciphertext, generatedKey);
    cout << "�������������� �����: " << decryptedtext<< endl;

     // ���������� ����������� �����
    char kontAfterSum = decryptedtext.back();
    decryptedtext.pop_back();

    // �������� ����������� �����
    kontSum = kontrolnayaSumma(decryptedtext);
    if (kontSum == kontAfterSum) {
        cout << "����������� ����� ���������. ������������ �������!" << endl;
    } else {
        cout << "����������� ����� �� ���������." << endl;
    }

    return 0;
}
