#include <drogon/HttpController.h>
#include <drogon/HttpRequest.h>

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
  ADD_METHOD_TO(User::login, "/user/login", Post);     // path is /usr/login
  ADD_METHOD_TO(User::getInfo, "/user/info/{1}", Get); // path is /usr/info/{userId}
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
    LOG_DEBUG << "User token:" << token << " get his information";

    // 验证token有效性等
    // 读数据库或缓存获取用户信息
    Json::Value ret;
    ret["result"] = "ok";
    ret["token"] = token;
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
  }

  void registry(const UserRegistryData &&NewUser,
                std::function<void(const HttpResponsePtr &)> &&callback) const
  {
    Json::Value ret;
    ret["name"] = NewUser.name;
    ret["password"] = NewUser.password;
    ret["gender"] = NewUser.gender;
    ret["telephone"] = NewUser.telephone;
    auto resp = HttpResponse::newHttpJsonResponse(ret);

    callback(resp);
  }
};
