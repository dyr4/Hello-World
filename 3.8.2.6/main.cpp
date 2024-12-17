#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

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

// ������� ��� ����������� ���� �����
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cyrillicCount = 0;

    for (char c : text) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            latinCount++;
        } else if ((c >= '\u0410' && c <= '\u042F') || (c >= '\u0430' && c <= '\u044F')) {
            cyrillicCount++;
        }
    }
    return latinCount > cyrillicCount ? "latin" : "cyrillic";
}

// ������� ��� ���������� ��� ������
int Day() {
    auto t1 = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(t1);
    tm* local_tm = localtime(&currentTime);
    return local_tm->tm_wday;
}

// ������� ��� ������ ����� � ����������� �� ��� ������
string generateGamma(int dayW) {
    switch (dayW) {
        case 1:
        case 3:
        case 5:
            return "ABCD EFGH IJKL MNOP";
        case 2:
        case 4:
            return "GHEF OPMN ABCD IJKL";
        case 6:
        case 0:
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
}

// ������� ��� ���������� ����������� �����, ��������� �� �������
string generateChecksum() {
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time), "%Y%m%d%H%M%S");
    string timestamp = ss.str();

    string checksum;
    for (char c : timestamp) {
        checksum += (c % 256);
    }
    return checksum;
}

// ������� ��� ������ �����
string readFile() {
    string inputFileName;
    cout << "������� ��� �������� �����: " << endl;
    cin >> inputFileName;
    string line;
    string text;

    ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            text += line + '\n';
        }
        inputFile.close();
    } else {
        cout << "������ �������� �����" << endl;
        return "";
    }
    return text;
}

// ������� ��� ������ ������������� ������ � ����
void writeFile(const string& encodedText) {
    string outputFileName;
    cout << "������� ��� ����� ��� ������ ������������� ������: " << endl;
    cin >> outputFileName;

    ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        outputFile << encodedText;
        outputFile.close();
    } else {
        cout << "������ �������� ����� ��� ������" << endl;
        return;
    }
}

int main() {
    setlocale(0, "Russian");

    // ������ ��������� ������
    string text = readFile();

    // ����� ����� ��� ����������
    string gammaType = chooseGammaType(text);
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    } else {
        gamma = "����������������������������������������������������������������";
    }

    // ��������� �����
    string generatedKey = generateKey(gamma, text.size());
    cout << "��������� �����: " << generatedKey << endl;

    // ����������
    string ciphertext = xorCipher(text, generatedKey);

    // ���������� ����������� �����
    string checksum = generateChecksum();
    ciphertext = checksum + to_string(text.size()) + ciphertext;

    // ��������� ����� � ������ ��� ������
    string marcant = generateGamma(Day());

    // �������� ����� � ���������
    generatedKey = generateKey(marcant, ciphertext.size());
    cout << "��������� ����� � ���������: " << generatedKey << endl;

    // ���������� � ���������
    string ciphertextWithMarcant = xorCipher(ciphertext, generatedKey);
    cout << "������������� �����: " << ciphertextWithMarcant << endl;

    // ������ �������������� ������ � ����
    writeFile(ciphertextWithMarcant);

    // ������������ ������ � �������������� ���� �� �����
    string decryptedTextWithMarcant = xorCipher(ciphertextWithMarcant, generatedKey);

    // ���������� ����������� ����� � ����� ������
    string extractedChecksum = decryptedTextWithMarcant.substr(0, checksum.size());
    size_t length = stoi(decryptedTextWithMarcant.substr(checksum.size(), to_string(text.size()).size()));
    string extractedCiphertext = decryptedTextWithMarcant.substr(checksum.size() + to_string(text.size()).size());

    // �������� ����������� �����
    if (extractedChecksum != checksum) {
        cout << "������: ����������� ����� �� ���������." << endl;
        return 1;
    }

    // ������������ ����������� ������
    generatedKey = generateKey(gamma, length);
    string decryptedText = xorCipher(extractedCiphertext, generatedKey);
    cout << "�������������� �����: " << decryptedText << endl;

    return 0;
}
