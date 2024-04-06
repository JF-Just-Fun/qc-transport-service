#pragma once

#include <drogon/utils/Utilities.h>
#include <string>
#include <iostream>
#include <random>

namespace DatabaseTools
{
  void decrypt(std::shared_ptr<std::string> &);
  void encrypt(std::shared_ptr<std::string> &);
  std::string generateUid(const int = 12);
  void updateTime(std::shared_ptr<::trantor::Date> &);
}
