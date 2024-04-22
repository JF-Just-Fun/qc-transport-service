#include <trantor/utils/Date.h>
#include <drogon/HttpFilter.h>
#include "../controllers/User.h"
#include "../helper/StatusCode.h"

using namespace drogon;

struct UserSessionData : public UserData
{
  trantor::Date expire;
};

class UserFilter : public HttpFilter<UserFilter>
{
public:
  UserFilter()
  {
    std::cout << "UserFilter Constructor" << std::endl;
  }

  void doFilter(const HttpRequestPtr &req,
                FilterCallback &&cb,
                FilterChainCallback &&ccb) override
  {
    auto user = req->session()->find(USER_DATA_SESSION);
    if (!user)
    {
      Json::Value json;
      json["code"] = StatusCode::NOT_LOGGED_IN;
      json["message"] = "用户未登录，请先登录！";
      auto res = HttpResponse::newHttpJsonResponse(json);
      cb(res);
      return;
    }

    // todo: 查询数据库的权限字段
    ccb();
  }
};
