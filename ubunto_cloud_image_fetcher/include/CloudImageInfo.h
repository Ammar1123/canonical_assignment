#pragma once

#include <string>
#include <vector>
#include <memory>

class CloudImageInfo {
public:
    virtual ~CloudImageInfo() = default;

    // Return a list of all currently supported Ubuntu releases
    virtual std::vector<std::string> getSupportedReleases() const = 0;

    // Return the current Ubuntu LTS version
    virtual std::string getCurrentLTSVersion() const = 0;

    // Return the sha256 of the disk1.img item of a given Ubuntu release
    virtual std::string getDisk1ImgSha256(const std::string& release) const = 0;
};

// Factory function to create and return a unique_ptr to CloudImageInfo
std::unique_ptr<CloudImageInfo> createCloudImageInfo();