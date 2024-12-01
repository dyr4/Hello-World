#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

// calculateChecksum
char calculateChecksum(const string& data) {
    char checksum = 0;
    for (char c : data) {
        checksum ^= c;
    }
    return checksum;
}

// chooseGammaType
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

string encode(const string& data, const string& gamma) {
    string encodedData;
    size_t sizeGamma = gamma.size();

    for (size_t i = 0; i < data.size(); i++) {
        char currentGamma = gamma[i % sizeGamma];
        encodedData.push_back(data[i] ^ currentGamma);
    }

    return encodedData;
}

bool Test_calculateChecksum() {
    return (calculateChecksum("ABC") == ('A' ^ 'B' ^ 'C')) &&
           (calculateChecksum("") == 0) && // ������ ������
           (calculateChecksum("123456789") == ('1' ^ '2' ^ '3' ^ '4' ^ '5' ^ '6' ^ '7' ^ '8' ^ '9')) &&
           (calculateChecksum("TestChecksum") == ('T' ^ 'e' ^ 's' ^ 't' ^ 'C' ^ 'h' ^ 'e' ^ 'c' ^ 'k' ^ 's' ^ 'u' ^ 'm'));
}

bool Test_chooseGammaType() {
    return (chooseGammaType("Hello123") == "latin") &&
           (chooseGammaType("������123") == "cirillic") &&
           (chooseGammaType("123456") == "latin") &&
           (chooseGammaType("") == "cirillic");
}


bool Test_encode1()
{
    return ((encode("world", "ABCDEFGHIJKLMNOP") == "6-1(!") &&
            (encode("worl", "GHEFABCDOPMNIJKL") == "0'7*") &&
            (encode("la-123-ga", "ABCDEFGHIJKLMNOP") == "-#nuwuj/(")
            && (encode("la-12----dd", "GHEFABCDOPMNIJKL") == "+)hwsonib4)")
              ) ;

}

int Day()
{
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));

    cout << "������� ����: " << buf << endl;

    return stoi(buf);
}

bool Test_Day()
{
    int today;
    cin >> today;
    return (Test_Day() == today ); // �������� ��������� ����
}

int main() {
    setlocale(LC_ALL, "Russian");


    if (Test_calculateChecksum()) {
        cout << "���� �� calculateChecksum() ������� �������." << endl;
    } else {
        cout << "���� �� calculateChecksum() �� �������." << endl;
    }


    if (Test_chooseGammaType()) {
        cout << "���� �� chooseGammaType() ������� �������." << endl;
    } else {
        cout << "���� �� chooseGammaType() �� �������." << endl;
    }

    if (Test_encode1()) {
        cout << "���� �� encode() ������� �������." << endl;
    } else {
        cout << "���� �� encode() �� �������." << endl;
    }

    if (Test_Day())
    {
       cout << "���� �� Day() ������� �������." << endl;
    } else
    {
        cout << "���� �� Day() �� �������." << endl;
    }


}

