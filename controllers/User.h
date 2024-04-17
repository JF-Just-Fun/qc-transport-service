#pragma once

#include <drogon/HttpController.h>
#include <drogon/HttpRequest.h>
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Criteria.h>
#include <drogon/orm/Mapper.h>
#include "../models/User.h"
#include "../utils/DatabaseTools.h"
#include "../helper/StatusCode.h"

#define USER_DATA_SESSION "user_data_session"

using namespace drogon;

struct UserRegistryData
{
  std::string name;
  std::string password;
  std::string email;
  int gender;
  std::string phone;
};

struct UserLoginData
{
  std::string name;
  std::string password;
  std::string phone;
};

struct UserData
{
  std::string name;
  std::string uid;
  std::string email;
  int gender;
  std::string phone;
  std::string create_time;
};

inline Json::Value toUserDataJson(drogon_model::QC_SERVER_DB::User &u)
{
  Json::Value userJson = u.toJson();
  userJson.removeMember("password");
  userJson.removeMember("validate");
  userJson.removeMember("id");
  return userJson;
}

inline UserData toUserDataStruct(Json::Value &userInfo)
{
  UserData user;
  user.name = userInfo["name"].asString();
  user.uid = userInfo["uid"].asString();
  user.email = userInfo["email"].asString();
  user.gender = userInfo["gender"].asInt();
  user.phone = userInfo["phone"].asString();
  user.create_time = userInfo["create_time"].asString();
  return user;
}

namespace drogon
{
  template <>
  inline UserRegistryData fromRequest(const HttpRequest &req)
  {
    auto json = req.getJsonObject();
    UserRegistryData user;
    if (json)
    {
      user.name = (*json)["name"].asString();
      user.password = (*json)["password"].asString();
      user.gender = (*json)["gender"].asInt();
      user.phone = (*json)["telephone"].asString();
      user.email = (*json)["email"].asString();
    }
    return user;
  }

  template <>
  inline UserLoginData fromRequest(const HttpRequest &req)
  {
    auto json = req.getJsonObject();
    UserLoginData info;

    if (json)
    {
      info.name = (*json)["name"].asString();
      info.password = (*json)["password"].asString();
      info.phone = (*json)["phone"].asString();
    }
    return info;
  }
}

class User : public drogon::HttpController<User>
{

public:
  METHOD_LIST_BEGIN
  // METHOD_ADD宏会在路径映射中自动把名字空间和类名作为路径的前缀
  ADD_METHOD_TO(User::login, "/user/login", Post, "SessionFilter");  // path is /usr/login
  ADD_METHOD_TO(User::getInfo, "/user/info/{1}", Get); // path is /usr/info/{userId}
  ADD_METHOD_TO(User::registry, "/user/registry", Post);
  METHOD_LIST_END

  // your declaration of processing function maybe like this:
  void login(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback,
             UserLoginData &&info) const;

  void getInfo(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback,
               const std::string &uid) const;

  void registry(const UserRegistryData &&NewUser,
                std::function<void(const HttpResponsePtr &)> &&callback) const;
};
