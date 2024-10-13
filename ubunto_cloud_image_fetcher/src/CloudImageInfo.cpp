#include "CloudImageInfo.h"
#include "SimplestreamsParser.h"
#include <curl/curl.h>
#include <stdexcept>

class UbuntuCloudImageInfo : public CloudImageInfo {
public:
    UbuntuCloudImageInfo() {
        const std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
        std::string jsonData = downloadJson(url);
        parser_.parseJson(jsonData);
    }

    std::vector<std::string> getSupportedReleases() const override {
        return parser_.getSupportedReleases();
    }

    std::string getCurrentLTSVersion() const override {
        return parser_.getCurrentLTSVersion();
    }

    std::string getDisk1ImgSha256(const std::string& release) const override {
        return parser_.getDisk1ImgSha256(release);
    }

private:
    SimplestreamsParser parser_;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string downloadJson(const std::string& url) {
        CURL* curl = curl_easy_init();
        std::string readBuffer;

        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            CURLcode res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) {
                throw std::runtime_error("Failed to download JSON data");
            }
        }

        return readBuffer;
    }
};

// Factory function to create and return a unique_ptr to CloudImageInfo
std::unique_ptr<CloudImageInfo> createCloudImageInfo() {
    return std::make_unique<UbuntuCloudImageInfo>();
}