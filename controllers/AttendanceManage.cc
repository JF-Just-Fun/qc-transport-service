#include <drogon/HttpController.h>
#include <drogon/HttpRequest.h>

using namespace drogon;

struct UpdateAttendanceData
{
  bool attendance;
  std::string cookie;
};
struct getAttendanceData
{
  std::string start;
  std::string end;
  std::string cookie;
};

namespace drogon
{
  template <>
  inline UpdateAttendanceData fromRequest(const HttpRequest &req)
  {
    auto json = req.getJsonObject();
    auto cookie = req.getCookie("user");
    UpdateAttendanceData data;
    if (json)
    {
      data.attendance = (*json)["attendance"].asBool();
      data.cookie = cookie;
    }
    return data;
  }

  template <>
  inline getAttendanceData fromRequest(const HttpRequest &req)
  {
    auto json = req.getJsonObject();
    auto cookie = req.getCookie("user");
    getAttendanceData data;
    if (json)
    {
      data.start = (*json)["start"].asString();
      data.end = (*json)["end"].asString();
      data.cookie = cookie;
    }
    return data;
  }
}

class AttendanceManage : public drogon::HttpController<AttendanceManage>
{

public:
  METHOD_LIST_BEGIN
  // METHOD_ADD宏会在路径映射中自动把名字空间和类名作为路径的前缀
  ADD_METHOD_TO(AttendanceManage::updateAttendance, "/attendance/{1:userId}", Put, "UserValidator");
  ADD_METHOD_TO(AttendanceManage::getAttendanceInfo, "/attendance/{1:userId}", Get, "UserValidator");
  METHOD_LIST_END

  // 更新指定用户的考勤信息
  void updateAttendance(const UpdateAttendanceData &&data,
                        std::function<void(const HttpResponsePtr &)> &&callback,
                        const std::string userId) const
  {
    // 认证算法，读数据库，验证身份等...
    Json::Value ret;
    ret["result"] = "ok";
    ret["userId"] = userId;
    ret["cookie"] = data.cookie;
    ret["attendance"] = data.attendance;
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
  }

  // 获取指定用户的考勤信息
  void getAttendanceInfo(const getAttendanceData &&data,
                         std::function<void(const HttpResponsePtr &)> &&callback,
                         const std::string userId) const
  {
    // 验证token有效性等
    // 读数据库或缓存获取用户信息
    Json::Value ret;
    ret["userId"] = userId;
    ret["start"] = data.start;
    ret["end"] = data.end;
    ret["cookie"] = data.cookie;
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
  }
};
