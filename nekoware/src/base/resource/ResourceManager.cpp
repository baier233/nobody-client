#include "ResourceManager.h"
#include "image/error.h"
#include "image/info.h"
#include "image/success.h"
#include "image/waring.h"
#include "other/index.h"
ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager inst;
    return inst;
}

ResourceData ResourceManager::getResource(std::string name)
{
    ResourceData data{};
    for (size_t i = 0; i < this->Resources.size(); i++)
    {
        if (this->Resources[i].name.compare(name) == 0) {
            data.data = this->Resources[i].data;
            data.size = this->Resources[i].size;
            return data;
        }
    }
    data.data = nullptr;
    data.size = 0;
    return data;
}

void ResourceManager::LoadAllResource()
{
    this->AddResource("noti-error", error, error_size);
    this->AddResource("noti-info", info, info_size);
    this->AddResource("noti-success", success, success_size);
    this->AddResource("noti-waring", waring, waring_size);
    this->AddResource("http-index", index, index_size);
}


void ResourceManager::AddResource(std::string name, unsigned char* data, int size)
{
    ResourceBase base;
    base.name = name;
    base.data = data;
    base.size = size;
    this->Resources.push_back(base);
}
