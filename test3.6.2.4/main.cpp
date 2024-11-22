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

// ������� ��� ����������� ����� �� ������ ����� ������
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cirillicCount = 0;

    for (char c : text) {
        // ������� ��������� ��������
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            latinCount++;
        }
        // ������� ������������� ��������
        else if ((c >= '�' && c <= '�') || (c >= '�' && c <= '�')) {
            cirillicCount++;
        }
    }

    return (latinCount > cirillicCount) ? "latin" : "cirillic";
}



string encode(const string& data, const string& gamma) {
    string encodedData;
    size_t gammaSize = gamma.size();

    for (size_t i = 0; i < data.size(); i++) {
        char currentGammaChar = gamma[i % gammaSize]; // ������ �����
        encodedData.push_back(data[i] ^ currentGammaChar); // ���������� � ������� XOR
    }

    return encodedData;
}

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



void writeFile(const string& encodedText) {
    string outputFileName = "file_out.txt";

    ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        outputFile << encodedText;
        outputFile.close();
    } else {
        cout << "������ �������� ����� ��� ������" << endl;
        return;
    }
}


bool unit_generateGamma() {
    return (generateGamma(1) == "ABCD EFGH IJKL MNOP") && (generateGamma(2) == "GHAB OPIJ MNCD KLEF") && (generateGamma(3) == "GHEF CDAB OPMN KLIJ");
}


bool chooseGammaType_Test() {
    return (chooseGammaType("test_gamma1") == "latin") && (chooseGammaType("���� �����") == "cirillic") && (chooseGammaType("�����") == "cirillic");
}

bool Test_encode1() {
    return (encode("world", generateGamma(1)) == "6-1(D") && (encode("world", generateGamma(3)) == "0'7*D");
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

void summaTest()
{
    string text = "Hello;";
    char kontSum = kontrolnayaSumma(text);

    if (kontSum == '/') {
        cout << "����������� ����� ���������. ������������ �������!" << endl;
    } else {
        cout << "����������� ����� �� ���������." << endl;
    }
}

int main() {


    if (unit_generateGamma()) {
        cout << "���������� ����� �����" << endl;
    } else {
        cout << "������������ ����� �����" << endl;
    }

    if (chooseGammaType_Test()) {
        cout << "���������� ����� ����� �� ������ �����" << endl;
    } else {
        cout << "������������ ����� ����� �� ������ �����" << endl;
    }

    if (Test_encode1()) {
        cout << "���� �� encode(): ���������� ������ �������" << endl;
    } else {
        cout << "���� �� encode(): ���������� �� �������" << endl;
    }

    string textFromFile = readFile();
    if (!textFromFile.empty()) {
        string gammaType = chooseGammaType(textFromFile);
        string gamma = generateGamma(1); // �������� ����� (����� ��������)
        string encodedText = encode(textFromFile, gamma);
        writeFile(encodedText);
        cout << "����� ���������� � ������� � file_out.txt" << endl;
    }

    summaTest();
    return 0;
}
