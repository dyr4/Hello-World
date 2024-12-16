#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <numeric>  // ��� accumulate

using namespace std;

// ������� ��� ��������� �����
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()];
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

// ������� ��� ���������� ����������� �����
uint8_t calculateChecksum(const string& text) {
    return accumulate(text.begin(), text.end(), 0) % 256;  // ������� ����������� �����
}

// ������� ��� ���������� ����� ������
int Day()
{
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));

    cout << "������� ����: " << buf << endl;

    return stoi(buf);
}

int main() {
    setlocale(0, "Russian");

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";
    string text;

    // �������� ����� � �������� �������
    ifstream fileIn(file_in);

    if (fileIn.is_open()) {
        getline(fileIn, text);
        fileIn.close();
    } else {
        cout << "������: �� ������� ������� ���� " << file_in << endl;
        return 1;
    }

    // ������� ����� ��������� ������ � ����������� �����
    size_t textLength = text.size();
    uint8_t checksum = calculateChecksum(text);

    // ����� ����� ��� ����������
    string gammaType = chooseGammaType(text);
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // ��������� �����
    } else {
        gamma = "�����Ũ����������������������������������������������������������"; // ������������� �����
    }

    // ��������� �����
    string generatedKey = generateKey(gamma, text.size());
    cout << "��������� �����: " << generatedKey << endl;

    // ����������
    string ciphertext = xorCipher(text, generatedKey);

    // ����� ����� ��������
    int Date;
    string chooseDay;
    cout << "����� ���� �� �������?(Yes or No)" << endl;
    cin >> chooseDay;

    if (chooseDay == "Yes" || chooseDay == "yes") {
        Date = Day();
    } else if (chooseDay == "No" || chooseDay == "no") {
        cout << "������� �����: ";
        cin >> Date;
    } else {
        cout << "������������ ����" << endl;
        return 0;
    }

    string marcant;
    if (Date % 2 == 0) {
        marcant = "ABCDEFGHIJKLMNOP"; // ����� ��� ������ ����� ������
    } else {
        marcant = "GHEFABCDOPMNIJKL"; // ����� ��� �������� ����� ������
    }

    // �������� ����� ��������
    generatedKey = generateKey(marcant, text.size()); // ���������� ��������� ����
    cout << "��������� ����� � ���������: " << generatedKey << endl;

    // ���������� � ���������
    string ciphertextwithmarcan = xorCipher(ciphertext, generatedKey);
    cout << "������������� �����: " << ciphertextwithmarcan << endl;

    // ������ �������������� ������ � ����
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "������ ��� �������� ����� " << file_out << endl;
        return 1;
    }

    outputFile << ciphertextwithmarcan;
    outputFile.close();

    // ������������ ������ � �������������� ���� �� �����
    string decryptedtextwithmarcan = xorCipher(ciphertextwithmarcan, generatedKey);
    generatedKey = generateKey(gamma, text.size());
    string decryptedtext = xorCipher(decryptedtextwithmarcan, generatedKey);
    cout << "�������������� �����: " << decryptedtext << endl;

    // ����� ����� ������ � ����������� ����� � �������� ������
    cout << "����� ��������� ������: " << textLength << endl;
    cout << "����������� ����� ������: " << static_cast<int>(checksum) << endl;

    return 0;
}
