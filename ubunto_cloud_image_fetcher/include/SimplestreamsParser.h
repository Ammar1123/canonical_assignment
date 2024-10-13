#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class SimplestreamsParser {
public:
    SimplestreamsParser();

    bool parseJson(const std::string& jsonData);
    std::vector<std::string> getSupportedReleases() const;
    std::string getCurrentLTSVersion() const;
    std::string getDisk1ImgSha256(const std::string& release) const;

private:
    nlohmann::json jsonData_;
};