#include <drogon/drogon.h>
#include <iostream>
using namespace std;

const int PORT = 5555;

int main()
{
  // Set HTTP listener address and port
  // drogon::app().addListener("0.0.0.0", PORT);
  // Load config file
  const char *env = std::getenv("BRANCH_NAME");
  const char *envSuffix = "config.json";
  if (env != nullptr)
  {
    if (std::strcmp(env, "test") == 0)
    {
      envSuffix = "config.test.json";
    }
    else if (std::strcmp(env, "main") == 0)
    {
      envSuffix = "config.main.json";
    }
  }

  drogon::app().loadConfigFile(envSuffix);
  // Run HTTP framework,the method will block in the internal event loop
  cout << "service starting at " << PORT << endl;
  drogon::app().enableSession(60 * 60 * 24).run();
  return 0;
}
