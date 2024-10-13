#include "CloudImageInfo.h"
#include <iostream>
#include <memory>
#include <stdexcept>

int main(int argc, char *argv[])
{
    try
    {
        std::unique_ptr<CloudImageInfo> cloudInfo = createCloudImageInfo();

        if (argc < 2)
        {
            std::cout << "Usage: " << argv[0] << " [releases|lts|sha256 <release>]" << std::endl;
            return 1;
        }

        std::string option = argv[1];

        if (option == "releases")
        {
            auto releases = cloudInfo->getSupportedReleases();
            std::cout << "Supported Ubuntu releases:" << std::endl;
            for (const auto &release : releases)
            {
                std::cout << release << std::endl;
            }
        }
        else if (option == "lts")
        {
            std::cout << "Current Ubuntu LTS version: " << cloudInfo->getCurrentLTSVersion() << std::endl;
        }
        else if (option == "sha256" && argc == 3)
        {
            std::string release = argv[2];
            try
            {
                std::cout << "SHA256 of disk1.img for Ubuntu " << release << ": "
                          << cloudInfo->getDisk1ImgSha256(release) << std::endl;
            }
            catch (const std::runtime_error &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
                return 1;
            }
        }
        else
        {
            std::cout << "Invalid option. Usage: " << argv[0] << " [releases|lts|sha256 <release>]" << std::endl;
            return 1;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}