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

struct UserUpdateData
{
  std::string id;
  std::string name;
  std::string password;
  std::string email;
  int gender = -1;
  std::string phone;
};
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
  inline UserUpdateData fromRequest(const HttpRequest &req)
  {
    auto json = req.getJsonObject();
    UserUpdateData user;

    if (json)
    {
      if ((*json)["id"])
        user.id = (*json)["id"].asString();
      if ((*json)["name"])
        user.name = (*json)["name"].asString();
      if ((*json)["password"])
        user.password = (*json)["password"].asString();
      if ((*json)["gender"])
        user.gender = (*json)["gender"].asInt();
      if ((*json)["telephone"])
        user.phone = (*json)["telephone"].asString();
      if ((*json)["email"])
        user.email = (*json)["email"].asString();
    }

    return user;
  }

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
  ADD_METHOD_TO(User::login, "/user/login", Post);                                       // path is /usr/login
  ADD_METHOD_TO(User::getCurrentInfo, "/user/info", Get, "SessionFilter", "UserFilter"); // 获取本人信息
  ADD_METHOD_TO(User::getInfo, "/user/info/{1}", Get, "SessionFilter");                  // 获取指定用户信息
  ADD_METHOD_TO(User::registry, "/user/registry", Post);
  ADD_METHOD_TO(User::updateSelf, "/user/update", Post, "UserFilter"); // 更新本人信息
  ADD_METHOD_TO(User::update, "/user/update/{1}", Post, "UserFilter"); // 更新指定用户的信息
  METHOD_LIST_END

  // your declaration of processing function maybe like this:
  void login(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback,
             UserLoginData &&info) const;

  void getInfo(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback,
               const std::string &uid) const;

  void getCurrentInfo(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback) const;

  void registry(const UserRegistryData &&NewUser,
                std::function<void(const HttpResponsePtr &)> &&callback) const;

  void update(const UserUpdateData &&NewUser,
              std::function<void(const HttpResponsePtr &)> &&callback,
              const std::string &uid) const;

  void updateSelf(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback,
                  UserUpdateData &&NewUser) const;

private:
  Json::Value getUserFromSession(const HttpRequestPtr &req) const
  {
    Json::Value ret;

    try
    {
      ret = req->session()->get<Json::Value>(USER_DATA_SESSION);
    }
    catch (...)
    {
      ret = Json::nullValue;
    }

    return ret;
  };
};
