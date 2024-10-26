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

// Функция для определения гаммы
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cirillicCount = 0;

    for (char c : text) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) { // Подсчёт латинских символов
            latinCount++;
        } else if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я')) { // Подсчёт кириллицы
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
        char current_Gamma = gamma[i % sizeGamma]; // повтор гаммы
        encode_Data.push_back(data[i] ^ current_Gamma); // Шифрование с помощью XOR
    }

    return encode_Data;
}

string readFile()
{
    string inputFileName;
    wcout << "Введите имя входного файла: " << endl;
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
        cout << "Ошибка открытия файла" << endl;
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
        cout << "Ошибка открытия файла для записи" << endl;
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
           && (chooseGammaType("test гамммы") == "cirillic")
           && (chooseGammaType("гамма") == "cirillic"));
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
        cout << "Правильный выбор гаммы" << endl;
    }
    else
    {
        cout << " НЕ правильный выбор гаммы" << endl;

    }

    if (chooseGammaType_Test())
    {
        cout << "Правильный выбор гаммы на основе языка" << endl;
    }
    else
    {
        cout << " НЕ правильный выбор гаммы на основе языка" << endl;

    }


    if (Test_encode1() == true)
    {
        cout << "Тест на encode(): шифрование прошёл успешно" << endl;
    }
    else
    {
        cout << "Тест на encode(): шифрование НЕ успешно" << endl;

    }

    string str1 = readFile();
    if (!str1.empty())
    {
        cout << "Данные из файла записались:" << endl;
        cout << str1 << endl;
    }



    writeFile("Write File Test");
    string str_2 = readFile();
    if (str_2 == "Write File Test\n" )
    {
        cout << "Данные  записались в файл" << endl;
    }
    else
    {
        cout << "Данные НЕ записались в файл" << endl;

    }



}
