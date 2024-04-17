#include <trantor/utils/Date.h>
#include <drogon/HttpFilter.h>
#include "../helper/StatusCode.h"
#include "../controllers/User.h"

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
    trantor::Date now = trantor::Date::date();
    if (req->session()->find(USER_DATA_SESSION))
    {
      auto u = req->session()->get<Json::Value>(USER_DATA_SESSION);

      std::cout << "session" << u << std::endl;

      req->session()->modify<Json::Value>(USER_DATA_SESSION,
                                          [now](Json::Value &vdate)
                                          {
                                            vdate["expire"] = now.after(60 * 60 * 24).toFormattedString(false);
                                          });
      ccb();
    }
    else
    {
      Json::Value json;
      json["code"] = StatusCode::NOT_LOGGED_IN;
      json["message"] = "用户未登录，请先登录！";
      auto res = HttpResponse::newHttpJsonResponse(json);
      cb(res);
    }
  }
};
