#include "./User.h"

void User::login(const HttpRequestPtr &req,
                 std::function<void(const HttpResponsePtr &)> &&callback,
                 UserLoginData &&info) const
{
  Json::Value ret;
  try
  {
    auto clientPtr = drogon::app().getDbClient();
    drogon::orm::Mapper<drogon_model::QC_SERVER_DB::User> mp(clientPtr);
    // std::vector<Admin> uu = mp.orderBy(Admin::Cols::_id).limit(25).offset(0).findAll();

    auto condition_name = drogon::orm::Criteria(drogon_model::QC_SERVER_DB::User::Cols::_name, drogon::orm::CompareOperator::EQ, info.name);
    auto condition_phone = drogon::orm::Criteria(drogon_model::QC_SERVER_DB::User::Cols::_phone, drogon::orm::CompareOperator::EQ, info.phone);
    auto condition_password = drogon::orm::Criteria(drogon_model::QC_SERVER_DB::User::Cols::_password, drogon::orm::CompareOperator::EQ, info.password);

    auto u = mp.findOne((condition_name || condition_phone) && condition_password);

    if (*u.getValidate())
    {
      Json::Value userJson = toUserDataJson(u);

      ret["code"] = StatusCode::OK;
      ret["message"] = "login success!";
      ret["data"] = userJson;

      req->session()->insert(USER_DATA_SESSION, userJson);
    }
    else
    {
      ret["code"] = 1;
      ret["message"] = "user has been banned!";
    }
  }
  catch (const drogon::orm::DrogonDbException &e)
  {
    ret["code"] = StatusCode::FAIL;
    ret["message"] = e.base().what();
  }
  auto resp = HttpResponse::newHttpJsonResponse(ret);
  callback(resp);
}

void User::getInfo(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   const std::string &uid) const
{
  Json::Value ret;

  try
  {
    auto clientPtr = drogon::app().getDbClient();
    drogon::orm::Mapper<drogon_model::QC_SERVER_DB::User> mp(clientPtr);

    auto u = mp.findOne(drogon::orm::Criteria(drogon_model::QC_SERVER_DB::User::Cols::_uid, drogon::orm::CompareOperator::EQ, uid));

    if (*u.getValidate())
    {
      Json::Value userJson = toUserDataJson(u);

      ret["code"] = StatusCode::OK;
      ret["message"] = "login success!";
      ret["data"] = userJson;
    }
    else
    {
      ret["code"] = StatusCode::FAIL;
      ret["message"] = "user has been banned!";
    }
  }
  catch (const drogon::orm::DrogonDbException &e)
  {
    ret["code"] = StatusCode::FAIL;
    ret["message"] = e.base().what();
  }

  auto resp = HttpResponse::newHttpJsonResponse(ret);
  callback(resp);
}

void User::registry(const UserRegistryData &&NewUser,
                    std::function<void(const HttpResponsePtr &)> &&callback) const
{
  Json::Value ret;
  drogon_model::QC_SERVER_DB::User user;

  const std::string uid = DatabaseTools::generateUid();
  user.setName(NewUser.name);
  user.setPassword(NewUser.password);
  user.setEmail(NewUser.email);
  user.setPhone(NewUser.phone);
  user.setGender(NewUser.gender);
  user.setUid(uid);

  try
  {
    auto clientPtr = drogon::app().getDbClient();
    drogon::orm::Mapper<drogon_model::QC_SERVER_DB::User> mp(clientPtr);
    // std::vector<Admin> uu = mp.orderBy(Admin::Cols::_id).limit(25).offset(0).findAll();

    auto s = mp.count();

    mp.insert(user);

    auto u = mp.findOne(drogon::orm::Criteria(drogon_model::QC_SERVER_DB::User::Cols::_uid, drogon::orm::CompareOperator::EQ, uid));

    if (*u.getValidate())
    {
      Json::Value userJson = toUserDataJson(u);

      ret["code"] = StatusCode::OK;
      ret["message"] = "registry success!";
      ret["data"] = userJson;
    }
  }
  catch (const drogon::orm::DrogonDbException &e)
  {
    ret["code"] = StatusCode::FAIL;
    ret["message"] = e.base().what();
  }

  auto resp = HttpResponse::newHttpJsonResponse(ret);

  callback(resp);
}
