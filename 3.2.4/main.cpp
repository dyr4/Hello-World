#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;


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



string encode(const string& data, const string& gamma)
{
    string encode_Data;
    size_t sizeGamma = gamma.size();

    for (size_t i = 0; i < data.size(); i++)
    {
        char current_Gamma = gamma[i % sizeGamma]; // ������ �����
        encode_Data.push_back(data[i] ^ current_Gamma); // ���������� � ������� XOR
    }

    return encode_Data;
}

string readFile()
{
    string inputFileName;
    cout << "������� ��� �������� �����: " << endl;
    cin >> inputFileName;
    string line;
    string text;

    ifstream inputFile(inputFileName);
    if (inputFile.is_open())
    {
        while (getline(inputFile, line)) {
            text += line + '\n';
        }
        inputFile.close();
    } else {
        cout << "������ �������� �����" << endl;
        return "";
    }
//    cout << text << endl;

    return text;
}



void writeFile(string encode_Text)
{

    string outputFileName = "file_out.txt";

    ofstream outputFile(outputFileName);
    if (outputFile.is_open())
    {
        outputFile << encode_Text;
        outputFile.close();
    } else {
        cout << "������ �������� ����� ��� ������" << endl;
        return;
    }

}


int main()
{
    setlocale(LC_ALL, "Russian");

    string text1 = readFile();
    string gammaType = chooseGammaType(text1);
// ����� �����
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // ��������� �����
    } else {
        gamma = "�����Ũ����������������������������������������������������������"; // ������������� �����
    }

    string encode_Text1 = encode(text1, gamma);

/*
    cout << gammaType << endl;
    cout << gamma << endl;
    cout << encode_Text1 << endl;
*/

    int key1 = 1;
    while (true)
    {

// ���������� ������
        string gamma_20 = generateGamma(key1);
        string encode_Text2 = encode(encode_Text1, gamma_20);
        cout << "������������� ������: " << endl;
        cout << encode_Text2 << endl;

        string not_encryptedData = encode(encode_Text2, gamma_20);
        cout << "�������������� ������: " << endl;
        cout << encode(not_encryptedData, gamma)  << endl;


        writeFile(encode_Text2);

        cout << "���� ���������� � �������, �����: " << key1 << endl;
        key1 = (key1 % 3) + 1;

        // �������� ���������� �����
        this_thread::sleep_for(chrono::seconds(20)); // ��������� �� ��������� �����



    }
}

