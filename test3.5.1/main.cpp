#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

//  генерация гаммы
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

// шифрование
string encode(const string& data, const string& gamma) {
    string encode_Data;
    size_t sizeGamma = gamma.size();

    for (size_t i = 0; i < data.size(); i++)
    {
        char current_Gamma = gamma[i % sizeGamma]; // повтор гаммы
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



    if (Test_generateGamma() == true)
    {
        wcout << L"Тест на generateGamma(): выбор гаммы пршёл успешно" << endl;
    }
    else
    {
        wcout << L"Тест на generateGamma(): выбор гаммы пршёл НЕ успешно" << endl;

    }
    if (Test_encode1() == true)
    {
        wcout << L"Тест на encode(): шифрование прошёл успешно" << endl;
    }
    else
    {
        wcout << L"Тест на encode(): шифрование НЕ успешно" << endl;

    }


}
