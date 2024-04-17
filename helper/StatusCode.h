#pragma once

#include <map>

enum StatusCode
{
  OK = 0,
  FAIL = 1,
  TOO_FREQUENTLY = 2,
  NO_PERMISSION = 3,
  BAD_PARAMETER = 4,
  NOT_LOGGED_IN = 5,
};
