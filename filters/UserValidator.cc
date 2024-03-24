#include <drogon/HttpFilter.h>
using namespace drogon;

class UserValidator : public HttpFilter<UserValidator>
{
public:
  UserValidator()
  {
    std::cout << "UserValidator" << std::endl;
  }

  void doFilter(const HttpRequestPtr &req,
                FilterCallback &&fcb,
                FilterChainCallback &&fccb) override
  {
    auto userCookie = req->getCookie("user");
    // Edit your logic here
    if (!userCookie.empty())
    {
      auto attributes = req->attributes();
      (*attributes)["userInfo"] = userCookie;
    }
    fccb();
    return;

    // Check failed
    // auto res = drogon::HttpResponse::newHttpResponse();
    // res->setStatusCode(k500InternalServerError);
    // fcb(res);
  }
};
