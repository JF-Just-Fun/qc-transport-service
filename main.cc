#include <drogon/drogon.h>
#include <iostream>
using namespace std;

const int PORT = 5555;

int main()
{
  // Set HTTP listener address and port
  // drogon::app().addListener("0.0.0.0", PORT);
  // Load config file
  drogon::app().loadConfigFile("../config.json");
  // Run HTTP framework,the method will block in the internal event loop
  cout << "service starting at " << PORT << endl;
  drogon::app().enableSession(60 * 60 * 24).run();
  return 0;
}
