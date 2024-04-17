#include "DatabaseTools.h"

namespace DatabaseTools
{

  std::string _encryptAndDecrypt(const std::string plaintext, const std::string key = "THIS IS KEY")
  {
    std::string ciphertext = plaintext;
    for (size_t i = 0; i < ciphertext.length(); ++i)
    {
      ciphertext[i] ^= key[i % key.length()];
    }
    // plaintext = std::make_shared<std::string>(ciphertext);
    std::cout << "_encryptAndDecrypt..." << ciphertext << std::endl;
    return ciphertext;
  }

  void decrypt(std::shared_ptr<std::string> &t)
  {
    std::cout << "Decrypting..." << *t << std::endl;
    t = std::make_shared<std::string>(_encryptAndDecrypt(*t));
    std::cout << "Decrypting after..." << *t << std::endl;
  }

  void encrypt(std::shared_ptr<std::string> &t)
  {
    std::cout << "Encrypting..." << *t << std::endl;
    t = std::make_shared<std::string>(_encryptAndDecrypt(*t));
    std::cout << "Encrypting after..." << *t << std::endl;
  }

  std::string generateUid(const int len)
  {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    std::string uid;
    uid.reserve(len);
    for (int i = 0; i < len; ++i)
    {
      uid += alphanum[dis(gen)];
    }

    return uid;
  }

  void updateTime(std::shared_ptr<::trantor::Date> &t)
  {
    std::cout << "update time :" << t << std::endl;
  }
}
