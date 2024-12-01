#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

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
        result[i] = data[i] ^ key[i];
    }
    return result;
}

// ������� ��� ���������� ����������� ����� �� ������ ��������� ������
char calculateChecksum(const string& data) {
    char checksum = 0;
    for (char c : data) {
        checksum ^= c;
    }
    return checksum;
}

// ������� ��� ��������� �������� ���
int getDay() {
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));
    cout << "������� ����: " << buf << endl;
    return stoi(buf);
}

int main() {
    setlocale(LC_ALL, "Russian");

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";

    // ������ ����� ����������� �� �����
    string text;
    ifstream fileIn(file_in);
    if (fileIn.is_open()) {
        stringstream buffer;
        buffer << fileIn.rdbuf();
        text = buffer.str();
        fileIn.close();
    } else {
        cout << "������: �� ������� ������� ���� " << file_in << endl;
        return 1;
    }

    // ���������� ����������� ����� �� ������ ��������� ������
    char originalChecksum = calculateChecksum(text);
    cout << "����������� ����� ��������� ������: " << (int)originalChecksum << endl;

    // ����������� ����� ��������� ������
    size_t textLength = text.size();
    cout << "����� ��������� ������: " << textLength << endl;

    string chooseDay;
    cout << "����� ���� �� �������? (Yes or No): ";
    cin >> chooseDay;
    int gammaType;

    if (chooseDay == "Yes" || chooseDay == "yes") {
        gammaType = getDay();
    } else if (chooseDay == "No" || chooseDay == "no") {
        cout << "������� �����: ";
        cin >> gammaType;
    } else {
        cout << "������������ ����" << endl;
        return 0;
    }

    // ����� �����
    string gamma;
    if (gammaType % 2 == 0) {
        gamma = "ABCDEFGHIJKLMNOP";
    } else {
        gamma = "GHEFABCDOPMNIJKL";
    }

    // ��������� ����� ������ �����
    string generatedKey = generateKey(gamma, text.size());
    cout << "��������� �����: " << generatedKey << endl;

    // ����������
    string ciphertext = xorCipher(text, generatedKey);
    cout << "\n������������� �����:\n\n" << ciphertext << endl;

    // ���������� ����������� ����� � �������������� ������
    ciphertext += originalChecksum;

    // ������ �������������� ������ � ����
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "������ ��� �������� ����� " << file_out << endl;
        return 1;
    }
    outputFile << ciphertext;
    outputFile.close();

    // ������ �������������� ������ �� ����� ��� �����������
    ifstream inputFile(file_out);
    if (!inputFile.is_open()) {
        cout << "������ ��� �������� ����� " << file_out << endl;
        return 1;
    }
    string encryptedText((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    // ���������� ����������� ����� �� �������������� ������
    char storedChecksum = encryptedText.back();
    encryptedText.pop_back();

    // �������� ����������� �����
    if (originalChecksum != storedChecksum) {
        cout << "������: ����������� ����� �� ���������! ���� ��������." << endl;
        return 1;
    }

    // ������������ ������
    string decryptedText = xorCipher(encryptedText, generatedKey);
    cout << "\n�������������� �����:\n\n" << decryptedText << endl;

    return 0;
}
