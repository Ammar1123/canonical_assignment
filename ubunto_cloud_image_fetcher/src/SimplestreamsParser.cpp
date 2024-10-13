#include "SimplestreamsParser.h"
#include <algorithm>
#include <stdexcept>

SimplestreamsParser::SimplestreamsParser() {}

bool SimplestreamsParser::parseJson(const std::string& jsonData) {
    try {
        jsonData_ = nlohmann::json::parse(jsonData);
        return true;
    } catch (const nlohmann::json::parse_error& e) {
        return false;
    }
}

std::vector<std::string> SimplestreamsParser::getSupportedReleases() const {
    std::vector<std::string> releases;
    const auto& products = jsonData_["products"];

    for (const auto& [key, value] : products.items()) {
        if (value.contains("release") && value["release"].is_string()) {
            releases.push_back(value["release"].get<std::string>());
        }
    }

    std::sort(releases.begin(), releases.end());
    releases.erase(std::unique(releases.begin(), releases.end()), releases.end());
    return releases;
}

std::string SimplestreamsParser::getCurrentLTSVersion() const {
    const auto& products = jsonData_["products"];
    std::string latestLTS;

    for (const auto& [key, value] : products.items()) {
        if (value.contains("release") && value["release"].is_string() &&
            value.contains("version") && value["version"].is_string() &&
            value.contains("support_eol") && value["support_eol"].is_string()) {
            
            const auto& release = value["release"].get<std::string>();
            const auto& version = value["version"].get<std::string>();
            const auto& supportEol = value["support_eol"].get<std::string>();

            if (version.find("LTS") != std::string::npos && (latestLTS.empty() || release > latestLTS)) {
                latestLTS = release;
            }
        }
    }

    return latestLTS;
}

std::string SimplestreamsParser::getDisk1ImgSha256(const std::string& release) const {
    const auto& products = jsonData_["products"];

    for (const auto& [key, value] : products.items()) {
        if (value.contains("release") && value["release"] == release &&
            value.contains("versions")) {
            
            const auto& versions = value["versions"];
            for (const auto& [versionKey, versionValue] : versions.items()) {
                if (versionValue.contains("items") && versionValue["items"].contains("disk1.img")) {
                    const auto& disk1Img = versionValue["items"]["disk1.img"];
                    if (disk1Img.contains("sha256") && disk1Img["sha256"].is_string()) {
                        return disk1Img["sha256"].get<std::string>();
                    }
                }
            }
        }
    }

    throw std::runtime_error("SHA256 for disk1.img not found for the specified release");
}