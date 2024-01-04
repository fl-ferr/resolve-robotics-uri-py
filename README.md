# resolve-robotics-uri-cpp

A C++ library to resolve a package:// (ROS-style) or model:// (Gazebo-style) URI to an absolute filename.

## Installation

Install using CMake to build and install the library:

```bash
mkdir build
cd build
cmake ..
make install
```

## Usage in C++

Include the library in your C++ file, then take inspiration from the following examples:

```cpp
#include <iostream>
#include "ResolveRoboticsURI.h"

int main() {
    try {
        std::string uri = "package://iCub/robots/iCubGazeboV2_7/model.urdf";
        fs::path absolute_path = ResolveRoboticsURI::resolve_robotics_uri(uri);
        std::cout << "Absolute Path: " << absolute_path << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
    return 0;
}
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[BSD-3-Clause](https://spdx.org/licenses/BSD-3-Clause.html)
