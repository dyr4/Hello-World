#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// ������� ��� ��������� �����
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()];
    }
    return generatedKey;
}

// ������� ��� ���������� � ������������
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i]; // ���������� XOR ��� ���������� � ������������
    }
    return result;
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

// ������� ��� ���������� ����� ������
int Day()
{

    auto t1 = chrono::system_clock::now();

    // time_point � time_t
    time_t currentTime = chrono::system_clock::to_time_t(t1);
    tm* local_tm = localtime(&currentTime);
    int l = local_tm->tm_wday;
    return local_tm->tm_wday;
}

//������� ��� ������ ����� � ����������� �� ��� ������
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

// ������� ��� ������ �����
string readFile()
{
    string inputFileName;
    cout << "������� ��� �������� �����: " << endl;
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

    string outputFileName;
    cout << "������� ��� �����, � ������� ��������� ������������� ������" << endl;
    cin >> outputFileName;

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

// ������� ����������� �����
char kontrolnayaSumma(const string& text, int key2)
{
    int checksum = 0;
    for (int i = 0; i < text.length(); i++) {
        checksum += (int)text[i];
    }
    checksum += key2;
    return static_cast<char>(checksum);
}


int main() {

    //������ ��������� ������
    string text = readFile();

    int key1 = 1;
    int key2;

    while(true)
    {

    switch(key1){
        case 1:
            key2 = 20;
        case 2:
            key2 = 40;
        case 3:
            key2 = 60;
        default:
            key2 = 0;
    }

    key1 = (key1 % 3) + 1;

    //����� ����� ��� ����������
    string gammaType = chooseGammaType(text);
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // ��������� �����
    } else {
        gamma = "�����Ũ����������������������������������������������������������"; // ������������� �����
    }

    //���������� ����������� �����
    char kontSum = kontrolnayaSumma(text, key2);
    text += kontSum;

    //��������� �����
    string generatedKey = generateKey(gamma, text.size());
    cout << "��������� �����: " << generatedKey << endl;

    // ����������
    string ciphertext = xorCipher(text, generatedKey);

    //����� ����� ��������
    string marcant = generateGamma(Day());

    //�������� ����� ��������
    generatedKey = generateKey(marcant, text.size()); // ���������� ��������� ����
    cout << "��������� ����� � ���������: " << generatedKey << endl;

    // ���������� � ���������
    string ciphertextwithmarcan = xorCipher(ciphertext, generatedKey);
    cout << "������������� �����: " << ciphertextwithmarcan << endl;

    //������ �������������� ������ � ����
    writeFile(text);

    // ������������ ������ � �������������� ���� �� �����
    string decryptedtextwithmarcan = xorCipher(ciphertextwithmarcan, generatedKey);
    generatedKey = generateKey(gamma, text.size());
    string decryptedtext=xorCipher(decryptedtextwithmarcan, generatedKey);
    cout << "�������������� �����: " << decryptedtext << endl;

    // ���������� ����������� �����
        char kontAfterSum = decryptedtext.back();
        decryptedtext.pop_back();

        // �������� ����������� �����
        kontSum = kontrolnayaSumma(decryptedtext, key2);
        if (kontSum == kontAfterSum) {
            cout << "����������� ����� ���������. ������������ �������!" << endl;
        } else {
            cout << "����������� ����� �� ���������." << endl;
        }

        // �������� ���������� �����
        this_thread::sleep_for(chrono::seconds(20)); // ��������� �� ��������� �����

    }
    return 0;
}
