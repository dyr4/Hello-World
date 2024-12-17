#include <gtest/gtest.h>
#include "cipher.h"  // ���������� ������������ ���� � ����� �����

// ���� ������� generateKey
TEST(CipherTests, GenerateKey) {
    std::string key = "ABC";
    size_t length = 10;
    std::string generatedKey = generateKey(key, length);
    EXPECT_EQ(generatedKey, "ABCABCABCA");
}

// ���� ������� xorCipher
TEST(CipherTests, XorCipher) {
    std::string data = "HELLO";
    std::string key = "ABCDE";
    std::string encrypted = xorCipher(data, key);
    EXPECT_EQ(xorCipher(encrypted, key), data); // ������������ ������ ������� �������� ������
}

// ���� ������� chooseGammaType
TEST(CipherTests, ChooseGammaType) {
    EXPECT_EQ(chooseGammaType("HELLO"), "latin");
    EXPECT_EQ(chooseGammaType("������"), "cyrillic");
}

// ���� ������� generateGamma
TEST(CipherTests, GenerateGamma) {
    EXPECT_EQ(generateGamma(1), "ABCD EFGH IJKL MNOP");
    EXPECT_EQ(generateGamma(0), "GHEF CDAB OPMN KLIJ");
}

// ���� ������� generateChecksum
TEST(CipherTests, GenerateChecksum) {
    std::string checksum1 = generateChecksum();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::string checksum2 = generateChecksum();
    EXPECT_NE(checksum1, checksum2); // ����������� ����� � ������ �������� ������ ����������
}

// ���� ������� ���������� � ������������
TEST(CipherTests, FullEncryptionDecryption) {
    std::string text = "HELLO WORLD";
    std::string gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string checksum = generateChecksum();

    // ��������� ������
    std::string key = generateKey(gamma, text.size());
    std::string ciphertext = xorCipher(text, key);
    ciphertext = checksum + std::to_string(text.size()) + ciphertext;

    std::string marcant = generateGamma(Day());
    std::string marcantKey = generateKey(marcant, ciphertext.size());
    std::string encryptedWithMarcant = xorCipher(ciphertext, marcantKey);

    // ������������
    std::string decryptedWithMarcant = xorCipher(encryptedWithMarcant, marcantKey);
    std::string extractedChecksum = decryptedWithMarcant.substr(0, checksum.size());
    size_t length = std::stoi(decryptedWithMarcant.substr(checksum.size(), std::to_string(text.size()).size()));
    std::string extractedCiphertext = decryptedWithMarcant.substr(checksum.size() + std::to_string(text.size()).size());

    // �������� ����������� �����
    EXPECT_EQ(extractedChecksum, checksum);

    // ������������ ������
    std::string decryptedText = xorCipher(extractedCiphertext, key);
    EXPECT_EQ(decryptedText, text);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
