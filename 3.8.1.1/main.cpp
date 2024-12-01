#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// ������� ��� ��������� ����� ������ �����
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

// ������� ��� ���������� ����������� �����
char calculateChecksum(const string& data) {
    char checksum = 0;
    for (char c : data) {
        checksum ^= c;
    }
    return checksum;
}

// ������� ��� ������ ����� � ����������� �� �����
string selectGamma(int cycle) {
    switch (cycle) {
        case 1: return "ABCD EFGH IJKL MNOP";
        case 2: return "GHAB OPIJ MNCD KLEF";
        case 3: return "GHEF CDAB OPMN KLIJ";
        default: return "ABCD EFGH IJKL MNOP"; // ����������� ����� �� ������ ������
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";

    // ������ ��������� ������ �� �����
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

    // ���������� ����������� ����� ��������� ������
    char originalChecksum = calculateChecksum(text);
    cout << "����������� ����� ��������� ������: " << (int)originalChecksum << endl;

    // ����������� ����� ��������� ������
    size_t textLength = text.size();
    cout << "����� ��������� ������: " << textLength << endl;

    int cycle = 1; // ��������� �������� ����� �����
    while (true) {
        // ����� ����� � ����������� �� �������� �����
        string gamma = selectGamma(cycle);
        cout << "������������ �����: " << gamma << endl;

        // ��������� ����� ������ �����
        string generatedKey = generateKey(gamma, text.size());

        // ���������� ������
        string ciphertext = xorCipher(text, generatedKey);
        cout << "\n������������� �����:\n\n" << ciphertext << endl;

        // ���������� ����� ��������� ������ � ����������� ����� � �������������� ������
        ciphertext.insert(0, reinterpret_cast<const char*>(&textLength), sizeof(textLength));
        ciphertext += originalChecksum;

        // ������ �������������� ������ � ����
        ofstream outputFile(file_out, ios::binary);
        if (!outputFile.is_open()) {
            cout << "������ ��� �������� ����� " << file_out << endl;
            return 1;
        }
        outputFile.write(ciphertext.data(), ciphertext.size());
        outputFile.close();

        cout << "���� ���������� � �������. ���� �����: " << cycle << endl;

        // �������� ������ �� ����� ��� �����������
        ifstream inputFile(file_out, ios::binary);
        if (!inputFile.is_open()) {
            cout << "������ ��� �������� ����� " << file_out << endl;
            return 1;
        }
        string encryptedText((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
        inputFile.close();

        // ���������� ����� ��������� ������ �� �������������� ������
        size_t extractedTextLength;
        memcpy(&extractedTextLength, encryptedText.data(), sizeof(extractedTextLength));
        encryptedText.erase(0, sizeof(extractedTextLength));

        // ���������� ����������� ����� �� �������������� ������
        char storedChecksum = encryptedText.back();
        encryptedText.pop_back();

        // �������� ����������� �����
        if (originalChecksum != storedChecksum) {
            cout << "������: ����������� ����� �� ���������! ���� ���������." << endl;
            return 1;
        }

        // ����������� ������
        string decryptedText = xorCipher(encryptedText, generatedKey);
        cout << "\n�������������� �����:\n\n" << decryptedText << endl;

        // �������� ������������ �����������
        if (decryptedText == text) {
            cout << "����������� �������! �������� ��������� �����...\n" << endl;

        } else {
            cout << "������: �������������� ����� �� ��������� � ��������!" << endl;
        }

        // ������� � ���������� ����� �����
        cycle = (cycle % 3) + 1;

        // �������� 20 ������ ����� ��������� ������
        this_thread::sleep_for(chrono::seconds(20));
    }

    return 0;
}
