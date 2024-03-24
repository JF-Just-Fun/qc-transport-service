#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class Hello : public drogon::HttpSimpleController<Hello>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;

  PATH_LIST_BEGIN
  // list path definitions here;
  PATH_ADD("/", Get, Post);
  PATH_ADD("/hello", Get, Post);
  PATH_LIST_END
};
