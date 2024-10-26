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
    wcout << "������� ��� �������� �����: " << endl;
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




bool unit_generateGamma()
{
    return ((generateGamma(1)== "ABCD EFGH IJKL MNOP") && (generateGamma(2)== "GHAB OPIJ MNCD KLEF") && (generateGamma(3)== "GHEF CDAB OPMN KLIJ"));


}


bool chooseGammaType_Test()
{
    return((chooseGammaType("test_gamma1") == "latin")
           && (chooseGammaType("test ������") == "cirillic")
           && (chooseGammaType("�����") == "cirillic"));
}

bool Test_encode1()
{


    return ((encode("world", generateGamma(1)) == "6-1(D") && (encode("world", generateGamma(3)) == "0'7*D"))  ;

}



int main()
{

    setlocale(LC_ALL, "Russian");
    if (unit_generateGamma())
    {
        cout << "���������� ����� �����" << endl;
    }
    else
    {
        cout << " �� ���������� ����� �����" << endl;

    }

    if (chooseGammaType_Test())
    {
        cout << "���������� ����� ����� �� ������ �����" << endl;
    }
    else
    {
        cout << " �� ���������� ����� ����� �� ������ �����" << endl;

    }


    if (Test_encode1() == true)
    {
        cout << "���� �� encode(): ���������� ������ �������" << endl;
    }
    else
    {
        cout << "���� �� encode(): ���������� �� �������" << endl;

    }

    string str1 = readFile();
    if (!str1.empty())
    {
        cout << "������ �� ����� ����������:" << endl;
        cout << str1 << endl;
    }



    writeFile("Write File Test");
    string str_2 = readFile();
    if (str_2 == "Write File Test\n" )
    {
        cout << "������  ���������� � ����" << endl;
    }
    else
    {
        cout << "������ �� ���������� � ����" << endl;

    }



}
