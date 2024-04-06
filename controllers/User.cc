#include <drogon/HttpController.h>
#include <drogon/HttpRequest.h>
#include <drogon/orm/DbClient.h>
#include "../models/User.h"
#include <drogon/orm/Mapper.h>
#include "../utils/DatabaseTools.h"
#include <drogon/orm/Criteria.h>

using namespace drogon;

struct UserRegistryData
{
  std::string name;
  std::string password;
  int gender;
  std::string telephone;
};

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
      user.telephone = (*json)["telephone"].asString();
    }
    return user;
  }
}

class User : public drogon::HttpController<User>
{

public:
  METHOD_LIST_BEGIN
  // METHOD_ADD宏会在路径映射中自动把名字空间和类名作为路径的前缀
  ADD_METHOD_TO(User::login, "/user/login", Post, "SessionFilter"); // path is /usr/login
  ADD_METHOD_TO(User::getInfo, "/user/info/{1}", Get);              // path is /usr/info/{userId}
  ADD_METHOD_TO(User::registry, "/user/registry", Post);
  METHOD_LIST_END

  // your declaration of processing function maybe like this:
  void login(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback)
  {
    // 从 body 中获取参数
    auto parameters = req->getParameters();
    std::string name, password;

    if (parameters.find("name") != parameters.end())
    {
      name = parameters["name"];
    }

    if (parameters.find("password") != parameters.end())
    {
      password = parameters["password"];
    }

    // 认证算法，读数据库，验证身份等...
    Json::Value ret;
    ret["result"] = "ok";
    ret["token"] = drogon::utils::getUuid();
    ret["name"] = name;
    ret["password"] = password;
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
  }

  void getInfo(const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback,
               const std::string &token) const
  {
    // 验证token有效性等
    // 读数据库或缓存获取用户信息
    Json::Value ret;

    try
    {

      auto clientPtr = drogon::app().getDbClient();
      drogon::orm::Mapper<drogon_model::QC_SERVER_DB::User> mp(clientPtr);

      auto u = mp.findOne(drogon::orm::Criteria(drogon_model::QC_SERVER_DB::User::Cols::_uid, drogon::orm::CompareOperator::EQ, token));

      if (*u.getValidate())
      {
        ret["result"] = "ok";
        ret["name"] = *u.getName();
        ret["id"] = *u.getUid();
        ret["gender"] = *u.getGender();
        ret["phone"] = *u.getPhone();
        // ret["email"] = *u.getEmail();
        std::cout << "u validate: " << *u.getName() << std::endl;
      }
      else
      {
        ret["result"] = "error";
        ret["message"] = "user was invalidated";
        std::cout << "error, no data" << std::endl;
      }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
      ret["result"] = "error";
      ret["message"] = "no user!";
      std::cout << "error:" << e.base().what() << std::endl;
    }

    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
  }

  void registry(const UserRegistryData &&NewUser,
                std::function<void(const HttpResponsePtr &)> &&callback) const
  {
    Json::Value ret;
    drogon_model::QC_SERVER_DB::User user;

    const std::string uid = DatabaseTools::generateUid();
    user.setName(NewUser.name);
    user.setPassword(NewUser.password);
    user.setPhone(NewUser.telephone);
    user.setGender(NewUser.gender);
    user.setUid(uid);

    try
    {
      auto clientPtr = drogon::app().getDbClient();
      drogon::orm::Mapper<drogon_model::QC_SERVER_DB::User> mp(clientPtr);
      // std::vector<Admin> uu = mp.orderBy(Admin::Cols::_id).limit(25).offset(0).findAll();

      auto s = mp.count();
      std::cout << " there are rows " << s << "!" << std::endl;

      mp.insert(user);

      auto u = mp.findOne(drogon::orm::Criteria(drogon_model::QC_SERVER_DB::User::Cols::_uid, drogon::orm::CompareOperator::EQ, uid));

      if (*u.getValidate())
      {
        std::cout << "u validate: " << *u.getValidate() << std::endl;
      }
      else
      {
        std::cout << "error, no data" << std::endl;
      }

      // if (u.getValidate())
      // {
      //   ret["id"] = *(u.getUid());
      //   ret["name"] = *(u.getName());
      //   ret["email"] = *(u.getEmail());
      //   ret["gender"] = *(u.getGender());
      //   ret["phone"] = *(u.getPhone());
      //   ret["validate"] = *(u.getValidate());
      // } else {
      //   std::cout << "error, no data" << std::endl;
      // }
    }
    catch (const drogon::orm::DrogonDbException &e)
    {
      std::cout << "error:" << e.base().what() << std::endl;
    }

    auto resp = HttpResponse::newHttpJsonResponse(ret);

    callback(resp);
  }
};
