#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;
using namespace std::chrono;

int Day()
{

    auto t1 = chrono::system_clock::now();

    // time_point � time_t
    time_t currentTime = chrono::system_clock::to_time_t(t1);
    tm* local_tm = localtime(&currentTime);
    int l = local_tm->tm_wday;
    return local_tm->tm_wday;

}




string generateGamma(int dayW)
{
    switch(dayW)
    {
        case 1:
        case 3:
        case 5:
            return "ABCD EFGH IJKL MNOP";
        case 2:
        case 4:
            return "GHEF OPMN ABCD IJKL";
        case 6:
        case 7:
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
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
    wcout << L"������� ��� �������� �����: " << endl;
    cin >> inputFileName;
    string line;
    string text;

    ifstream inputFile(inputFileName);
    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
        {
            text += line + '\n';
            if (text.empty())
            {
                wcout << L"� ����� ������ ���" << endl;
                return "";

            }
        }
        inputFile.close();
    }

    else
    {
        wcout << L"������ �������� �����" << endl;
        return "";
    }
//    cout << text << endl;

    return text;
}



void writeFile(string encode_Text)
{

    string outputFileName;
    wcout << L"������� ��� �����, � ������� ��������� ������������� ������" << endl;
    cin >> outputFileName;

    ofstream outputFile(outputFileName);
    if (outputFile.is_open())
    {
        outputFile << encode_Text;
        outputFile.close();
    } else {
        wcout << L"������ �������� ����� ��� ������" << endl;
        return;
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool unit_Day ()
{
    unsigned int day1;
    wcout << L"������ ������� ���� ������" << endl;
    cin >> day1;
    cout << Day() << endl;

    return (day1 == Day());
}

bool unit_generateGamma()
{
    return ((generateGamma(1)== "ABCD EFGH IJKL MNOP") && (generateGamma(3)== "ABCD EFGH IJKL MNOP") && (generateGamma(5)== "ABCD EFGH IJKL MNOP") &&
            (generateGamma(2)== "GHEF OPMN ABCD IJKL") && (generateGamma(4)== "GHEF OPMN ABCD IJKL") &&
            (generateGamma(6)== "GHEF CDAB OPMN KLIJ") && (generateGamma(7)== "GHEF CDAB OPMN KLIJ") &&
            (generateGamma(0)== "") && (generateGamma(8)== ""));



}

bool Test_encode1()
{


    return ((encode("world", generateGamma(1)) == "6-1(D") && (encode("world", generateGamma(4)) == "0'7*D")
            && (encode("world world world", generateGamma(6)) == "0'7*Dc3.0L+p:!R'(") )  ;

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
    if (unit_Day())
    {
        wcout << L"���������� ������� ���� ������" << endl;
    }
    else
    {
        wcout << L" �� ���������� ������� ���� ������" << endl;

    }
    if (unit_generateGamma())
    {
        wcout << L"���������� ����� �����" << endl;
    }
    else
    {
        wcout << L" �� ���������� ����� �����" << endl;

    }

    if (Test_encode1() == true)
    {
        wcout << L"���� �� encode(): ���������� ������ �������" << endl;
    }
    else
    {
        wcout << L"���� �� encode(): ���������� �� �������" << endl;

    }

    string str1 = readFile();
    if (!str1.empty())
    {
        wcout << L"������ �� ����� ����������:" << endl;
        cout << str1 << endl;
    }



    writeFile("Write File Test");
    string str_2 = readFile();
    if (str_2 == "Write File Test\n" )
    {
        wcout << L"������  ���������� � ����" << endl;
    }
    else
    {
        wcout << L"������ �� ���������� � ����" << endl;

    }

    summaTest();

}
