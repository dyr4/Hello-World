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
        while (getline(inputFile, line)) {
            text += line + '\n';
        }
        inputFile.close();
    } else {
        wcout << L"Ошибка открытия файла" << endl;
        return "";
    }
//    cout << text << endl;

    return text;
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

int main()
{
    setlocale(LC_ALL, "Russian");
    writeFile(encode(readFile(),generateGamma(Day())));

}
