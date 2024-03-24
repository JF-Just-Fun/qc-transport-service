#include <drogon/drogon.h>
#include <iostream>
using namespace std;

const int PORT = 5555;

int main()
{
  // Set HTTP listener address and port
  drogon::app().addListener("0.0.0.0", PORT);
  // Load config file
  drogon::app().loadConfigFile("../config.json");
  // drogon::app().loadConfigFile("../config.yaml");
  // Run HTTP framework,the method will block in the internal event loop
  cout << "service starting at " << PORT << endl;
  drogon::app().run();
  return 0;
}
