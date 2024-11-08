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

    string outputFileName = "file_out.txt";

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
    string text = "text1111111111111111111111111111111111111111";
    // Добавление байта с длиной открытого текста
    char lengthByte = static_cast<char>(text.size());
//    cout << lengthByte << endl;
//    text = text + lengthByte;
    if (text.size() == 44 && static_cast<char>(text.size()) == ',')
    {
        wcout << L"Тест на поле длины открытого текста пройден" << endl;

    }
    else
    {
        wcout << L"Тест на поле длины открытого текста НЕ прошёл" << endl;

    }

    if (unit_generateGamma())
    {
        wcout << L"Правильный выбор гаммы" << endl;
    }
    else
    {
        wcout << L" НЕ правильный выбор гаммы" << endl;

    }

    if (chooseGammaType_Test())
    {
        wcout << L"Правильный выбор гаммы на основе языка" << endl;
    }
    else
    {
        wcout << L" НЕ правильный выбор гаммы на основе языка" << endl;

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
