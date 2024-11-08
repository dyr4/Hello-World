#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;
using namespace std::chrono;

int Day()
{

    auto t1 = chrono::system_clock::now();

    // time_point в time_t
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
        char current_Gamma = gamma[i % sizeGamma]; // повтор гаммы
        encode_Data.push_back(data[i] ^ current_Gamma); // Шифрование с помощью XOR
    }

    return encode_Data;
}

string readFile()
{
    string inputFileName;
    wcout << L"Введите имя входного файла: " << endl;
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
                wcout << L"В файле ничего нет" << endl;
                return "";

            }
        }
        inputFile.close();
    }

    else
    {
        wcout << L"Ошибка открытия файла" << endl;
        return "";
    }
//    cout << text << endl;
    char lengthByte = static_cast<char>(text.size());
    text += lengthByte;
    return text;
}

string decode(const string& encoded_data, const string& gamma) {
    string decoded_data = encode(encoded_data, gamma);
    int originalLength = static_cast<unsigned char>(decoded_data.back());
    return decoded_data.substr(0, originalLength);
}


void writeFile(string encode_Text)
{

    string outputFileName;
    wcout << L"Введите имя файла, в который запишутся зашифрованные данные" << endl;
    cin >> outputFileName;

    ofstream outputFile(outputFileName);
    if (outputFile.is_open())
    {
        outputFile << encode_Text;
        outputFile.close();
    } else {
        wcout << L"Ошибка открытия файла для записи" << endl;
        return;
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool unit_Day ()
{
    unsigned int day1;
    wcout << L"Ведите текущий день недели" << endl;
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



int main()
{
    setlocale(LC_ALL, "Russian");
    if (unit_Day())
    {
        wcout << L"Правильный текущий день недели" << endl;
    }
    else
    {
        wcout << L" НЕ правильный текущий день недели" << endl;

    }
    if (unit_generateGamma())
    {
        wcout << L"Правильный выбор гаммы" << endl;
    }
    else
    {
        wcout << L" НЕ правильный выбор гаммы" << endl;

    }

    if (Test_encode1() == true)
    {
        wcout << L"Тест на encode(): шифрование прошёл успешно" << endl;
    }
    else
    {
        wcout << L"Тест на encode(): шифрование НЕ успешно" << endl;

    }

    string str1 = readFile();
    if (!str1.empty())
    {
        wcout << L"Данные из файла записались:" << endl;
        cout << str1 << endl;
    }



    writeFile("Write File Test");
    string str_2 = readFile();
    if (str_2 == "Write File Test\n" )
    {
        wcout << L"Данные  записались в файл" << endl;
    }
    else
    {
        wcout << L"Данные НЕ записались в файл" << endl;

    }



}

