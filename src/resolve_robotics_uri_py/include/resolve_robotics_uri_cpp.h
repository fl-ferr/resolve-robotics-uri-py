#ifndef RESOLVE_ROBOTICS_URI_CPP
#define RESOLVE_ROBOTICS_URI_CPP

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

class RoboticsURIRResolver {
public:
    // Function to split a string by a delimiter
    static std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    // Function to resolve the URI
    static fs::path resolve_robotics_uri(const std::string& uri) {
        // List of environment variables to consider
        std::vector<std::string> env_list = {
            "GAZEBO_MODEL_PATH", "ROS_PACKAGE_PATH", "AMENT_PREFIX_PATH",
            "SDF_PATH", "IGN_GAZEBO_RESOURCE_PATH", "GZ_SIM_RESOURCE_PATH"
        };

        // Preliminary step: if there is no scheme, consider this a path and return it as is
        if (uri.find("://") == std::string::npos) {
            return fs::path(uri);
        }

        // Get scheme from URI
        size_t schemePos = uri.find("://");
        std::string scheme = uri.substr(0, schemePos);
        std::string uriPath = uri.substr(schemePos + 3);

        if (scheme != "file" && scheme != "package" && scheme != "model") {
            throw std::runtime_error("Passed URI \"" + uri + "\" uses a non-supported scheme: " + scheme);
        }

        std::vector<fs::path> model_filenames;

        if (scheme == "file") {
            model_filenames.push_back(uri.substr(7));  // Remove "file://" from the URI
        }

        if (scheme == "package" || scheme == "model") {
            for (const auto& env : env_list) {
                char* envValue = std::getenv(env.c_str());
                if (envValue) {
                    std::vector<std::string> folders = split(envValue, fs::path::preferred_separator);
                    for (const std::string& folder : folders) {
                        fs::path candidate_file_name = fs::path(folder) / uriPath;
                        if (fs::exists(candidate_file_name) && fs::is_regular_file(candidate_file_name)) {
                            model_filenames.push_back(candidate_file_name);
                        }
                    }
                }
            }
        }

        if (!model_filenames.empty()) {
            if (model_filenames.size() > 1) {
                std::cerr << "resolve-robotics-uri-cpp: Multiple files (";
                for (const auto& filename : model_filenames) {
                    std::cerr << filename.string() << ' ';
                }
                std::cerr << ") found for uri \"" << uri << "\", returning the first one." << std::endl;
            }
            return model_filenames[0];
        }

        throw std::runtime_error("resolve-robotics-uri-cpp: No file corresponding to uri \"" + uri + "\" found");
    }
};

#endif // RESOLVE_ROBOTICS_URI_CPP

