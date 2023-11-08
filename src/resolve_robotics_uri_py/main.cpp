#include <iostream>
#include "resolve_robotics_uri_cpp.h"

int main() {
    std::string uri = "package://my_package/my_file.txt";
    fs::path result = ResolveRoboticsUri::resolve_robotics_uri_cpp(uri);
    std::cout << result.string() << std::endl;
    return 0;
}
