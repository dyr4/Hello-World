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
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));

    cout << "������� ����: " << buf << endl;

    return stoi(buf);
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

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";
    string text;

    //�������� ����� � �������� �������
    ifstream fileIn(file_in);

    if (fileIn.is_open()) {
        getline(fileIn, text);
        fileIn.close();
    } else {
        cout << "������: �� ������� ������� ���� " << file_in << endl;
        return 1;
    }

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
    int Date;
    string chooseDay;
    cout << "����� ���� �� �������?(Yes or No)" << endl;
    cin >> chooseDay;

    if (chooseDay == "Yes" || chooseDay == "yes") {
        Date = Day();
    } else if (chooseDay == "No" || chooseDay == "no") {
        cout << "������� �����: ";
        cin >> Date;
    } else {
        cout << "������������ ����" << endl;
        return 0;
    }

    string marcant;
    if (Date % 2 == 0) {
        marcant = "ABCDEFGHIJKLMNOP"; // ����� ��� ������ ����� ������
    } else {
        marcant = "GHEFABCDOPMNIJKL"; // ����� ��� �������� ����� ������
    }

    //�������� ����� ��������
    generatedKey = generateKey(marcant, text.size()); // ���������� ��������� ����
    cout << "��������� ����� � ���������: " << generatedKey << endl;

    // ���������� � ���������
    string ciphertextwithmarcan = xorCipher(ciphertext, generatedKey);
    cout << "������������� �����: " << ciphertextwithmarcan << endl;

    // ������ �������������� ������ � ����
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "������ ��� �������� ����� " << file_out << endl;
        return 1;
    }

    outputFile << ciphertextwithmarcan;
    outputFile.close();

    // ������������ ������ � �������������� ���� �� �����
    string decryptedtextwithmarcan = xorCipher(ciphertextwithmarcan, generatedKey);
    generatedKey = generateKey(gamma, text.size());
    string decryptedtext=xorCipher(decryptedtextwithmarcan, generatedKey);

    cout<<"��������������� ����: " << decryptedtext<<endl;

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

    cout << "�������������� �����: " << decryptedtext << endl;


    }

    return 0;
}
