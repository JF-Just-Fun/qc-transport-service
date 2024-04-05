#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <drogon/HttpFilter.h>
#define VDate "visitDate"

using namespace drogon;

class SessionFilter : public HttpFilter<SessionFilter>
{
public:
  SessionFilter()
  {
    std::cout << "SessionFilter" << std::endl;
  }

  void doFilter(const HttpRequestPtr &req,
                FilterCallback &&cb,
                FilterChainCallback &&ccb) override
  {
    trantor::Date now = trantor::Date::date();
    LOG_TRACE << "";
    if (req->session()->find(VDate))
    {
      auto lastDate = req->session()->get<trantor::Date>(VDate);
      LOG_TRACE << "last:" << lastDate.toFormattedString(false);
      req->session()->modify<trantor::Date>(VDate,
                                            [now](trantor::Date &vdate)
                                            {
                                              vdate = now;
                                            });
      LOG_TRACE << "update visitDate";
      if (now > lastDate.after(10))
      {
        // 10 sec later can visit again;
        ccb();
        return;
      }
      else
      {
        Json::Value json;
        json["result"] = "error";
        json["message"] = "Access interval should be at least 10 seconds";
        auto res = HttpResponse::newHttpJsonResponse(json);
        cb(res);
        return;
      }
    }
    LOG_TRACE << "first access,insert visitDate";
    req->session()->insert(VDate, now);
    ccb();
  }
};
