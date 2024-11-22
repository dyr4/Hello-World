#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

// ������� ��� ��������� ����� � ����������� �� �����
string generateGamma(int key1) {
    switch (key1) {
        case 1:
            return "ABCD EFGH IJKL MNOP";
        case 2:
            return "GHAB OPIJ MNCD KLEF";
        case 3:
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
}

// ����������
string encode(const string& data, const string& gamma) {
    string encode_Data;
    size_t sizeGamma = gamma.size();

    for (size_t i = 0; i < data.size(); i++)
    {
        char current_Gamma = gamma[i % sizeGamma]; // ������ �����
        encode_Data.push_back(data[i] ^ current_Gamma); // ���������� � ������� XOR
    }

    return encode_Data;
}

// ������� ����������� �����
char kontrolnayaSumma(const string& text, int key2)
{
    int checksum = 0;
    for (int i = 0; i < text.length(); i++) {
        checksum += (int)text[i];
    }
    checksum += key2;
    return static_cast<char>(checksum);
}


int main() {
    setlocale(LC_ALL, "Russian");

    string inputFileName;
    string outputFileName;

    wcout << L"������� ��� �������� �����: " << endl;
    cin >> inputFileName;

    wcout << L"������� ��� ��������� �����: " << endl;
    cin >> outputFileName;

    // ������ �� �����
    string line;
    string text;

    ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            text += line + '\n';
        }
        inputFile.close();
    } else {
        wcout << L"������ �������� �����" << endl;
        return 1;
    }
    cout << text << endl;


    int key1 = 1;
    int key2;


    while (true)
    {

    switch(key1){
        case 1:
            key2 = 20;
        case 2:
            key2 = 40;
        case 3:
            key2 = 60;
        default:
            key2 = 0;
    }

    //���������� ����������� �����
    char kontSum = kontrolnayaSumma(text, key2);
    text += kontSum;

// ���������� ������
        string gamma = generateGamma(key1);
        string encode_Text = encode(text, gamma);
/*
        wcout << L"������������� ������: " << endl;
        cout << encode_Text << endl;

        string not_encryptedData = encode(encode_Text, gamma);
        wcout << L"�������������� ������: " << endl;
        cout << not_encryptedData << endl;
*/

        ofstream outputFile(outputFileName);
        if (outputFile.is_open()) {
            outputFile << encode_Text;
            outputFile.close();
        } else {
            wcout << L"������ �������� ����� ��� ������" << endl;
            return 1;
        }

        wcout << L"���� ���������� � �������, �����: " << key1 << endl;
        key1 = (key1 % 3) + 1;

        string decryptedtext = encode(encode_Text, gamma);

         // ���������� ����������� �����
        char kontAfterSum = decryptedtext.back();
        decryptedtext.pop_back();

        // �������� ����������� �����
        kontSum = kontrolnayaSumma(decryptedtext, key2);
        if (kontSum == kontAfterSum) {
            wcout << L"����������� ����� ���������. ������������ �������!" << endl;
        } else {
            wcout << L"����������� ����� �� ���������." << endl;
        }

        // �������� ���������� �����
        this_thread::sleep_for(chrono::seconds(20)); // ��������� �� ��������� �����


    }


}
