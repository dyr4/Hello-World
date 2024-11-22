#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

//  ��������� �����
string generateGamma(int key1) {
    switch (key1) {
        case 1:
            return "ABCDEFGHIJKLMNOP";
        case 2:
            return "GHABOPIJMNCDKLEF";
        case 3:
            return "GHEFCDABOPMNKLIJ";
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
        encode_Data.push_back(data[i]  ^ current_Gamma); //  XOR
    }

    return encode_Data;
}



bool Test_generateGamma()
{
    return ((generateGamma(1) == "ABCDEFGHIJKLMNOP") &&
            (generateGamma(2) == "GHABOPIJMNCDKLEF") && (generateGamma(3) == "GHEFCDABOPMNKLIJ"));
}


bool Test_encode1()
{


    return ((encode("world", generateGamma(1)) == "6-1(!") && (encode("world", generateGamma(2)) == "0'3.+" ) &&
            (encode("world", generateGamma(3)) == "0'7*'") &&
            (encode("la-123-ga", generateGamma(1)) == "-#nuwuj/(")
            && (encode("la-123-ga", generateGamma(2)) == "+)ls}cd-,")
            && (encode("la-123-ga", generateGamma(3)) == "+)hwqwl%.") ) ;

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
        wcout << L"����������� ����� ���������. ������������ �������!" << endl;
    } else {
        wcout << L"����������� ����� �� ���������." << endl;
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    if (Test_generateGamma() == true)
    {
        wcout << L"���� �� generateGamma(): ����� ����� ����� �������" << endl;
    }
    else
    {
        wcout << L"���� �� generateGamma(): ����� ����� ����� �� �������" << endl;

    }
    if (Test_encode1() == true)
    {
        wcout << L"���� �� encode(): ���������� ������ �������" << endl;
    }
    else
    {
        wcout << L"���� �� encode(): ���������� �� �������" << endl;

    }
    summaTest();

}
