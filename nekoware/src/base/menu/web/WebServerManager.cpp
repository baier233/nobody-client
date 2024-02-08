#include "WebServerManager.h"
std::string urlEncode(const std::string& str)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring wstr = conv.from_bytes(str);

    std::string encodedStr;
    for (const auto& ch : wstr) {
        if (isalnum(ch) || ch == '-' || ch == '_' || ch == '.' || ch == '~') {
            encodedStr += static_cast<char>(ch);
        }
        else if (ch == ' ') {
            encodedStr += '+';
        }
        else {
            encodedStr += '%';
            encodedStr += static_cast<char>((ch >> 4) + '0');
            encodedStr += static_cast<char>((ch & 0x0F) + '0');
        }
    }

    return encodedStr;
}

std::string urlDecode(const std::string& str)
{
    std::string decodedStr;

    for (std::size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '%') {
            if (i + 2 < str.length()) {
                char hex[3] = { str[i + 1], str[i + 2], '\0' };
                char decodedCh = static_cast<char>(std::stoi(hex, nullptr, 16));
                decodedStr += decodedCh;
                i += 2;
            }
        }
        else if (str[i] == '+') {
            decodedStr += ' ';
        }
        else {
            decodedStr += str[i];
        }
    }

    return decodedStr;

}


WebServerManager& WebServerManager::getInstance()
{
    static WebServerManager instance;
    return instance;
}
static std::map<std::string, Category> categoryMap = {
            {"1", Category::CLICKER},
            {"Clicker", Category::CLICKER},
            {"2", Category::COMBAT},
            {"Combat", Category::COMBAT},
            {"3", Category::PLAYER},
            {"Player", Category::PLAYER},
            {"4", Category::VISUAL},
            {"Visual", Category::VISUAL}
};



//#define LOCALHTML
void WebServerManager::Start(int port)
{
    this->port = port;
    this->server.Get("/", [](const httplib::Request&, httplib::Response& res) {
#ifndef LOCALHTML
        ResourceData resource = ResourceManager::getInstance().getResource("http-index");
        std::string str(reinterpret_cast<char const*>(resource.data), resource.size);
        res.set_content(str, "text/html;charset=utf-8");
#else // LOCALHTML
        std::string localFilePath = "E:\\Dev\\SkidwareWorkSpace\\main\\Skidware-Inject\\Skidware\\src\\base\\resource\\other\\index.html";

        // 打开文件流
        std::ifstream file(localFilePath, std::ios::binary);

        if (file) {
            file.seekg(0, std::ios::end);
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> buffer(size);
            if (file.read(buffer.data(), size)) {
                std::string content(buffer.data(), size);
                res.set_content(content, "text/html;charset=utf-8");
            }
            else {
                res.status = 500; 
                res.set_content("Error reading file", "text/plain");
            }
            file.close();
        }
        else {
            res.status = 404;
            res.set_content("File not found", "text/plain");
        }


#endif
        

       
        });
    /*
    * categoriesList
    */
    this->server.Get("/api/categoriesList", [](const httplib::Request&, httplib::Response& res) {
        nlohmann::json jsonObject;
        nlohmann::json result;
        result["Clicker"] = "Mouse";
        result["Combat"] = "Swords";
        result["Player"] = "Person";
        result["Visual"] = "Visibility";
        jsonObject["result"] = result;
        jsonObject["success"] = true;
    res.set_content(jsonObject.dump(), "application/json;charset=utf-8");
        });
    /*
    * setStatus
    */
    this->server.Get("/api/setStatus", [](const httplib::Request& req, httplib::Response& res) {
        nlohmann::json jsonObject;
    nlohmann::json result;
    std::string module = req.get_param_value("module");
    std::string state = req.get_param_value("state");

    bool states = ModuleManager::getInstance().getModule(module)->getToggle();
    std::cout << module << state << std::endl;
    if (state.find("true") != -1)states = true;
    else if (state.find("false") != -1)states = false;
    ModuleManager::getInstance().getModule(module)->setToggle(states);
    jsonObject["result"] = states;
    jsonObject["success"] = true;
    res.set_content(jsonObject.dump(), "application/json;charset=utf-8");
        });
    /*
    * setBind
    */
    this->server.Get("/api/setBind", [](const httplib::Request& req, httplib::Response& res) {
        nlohmann::json jsonObject;
    nlohmann::json result;
    bool states;
    std::string module = req.get_param_value("module");
    std::string keycode = req.get_param_value("keycode");
    std::cout << keycode << std::endl;
    int key = std::stoi(keycode);
    ModuleManager::getInstance().getModule(module)->setKeyCode(key);
    jsonObject["result"] = key;
    jsonObject["success"] = true;
    res.set_content(jsonObject.dump(), "application/json;charset=utf-8");
        });
    /*
   * updateModulesInfo
   */
    this->server.Get("/api/updateModulesInfo", [](const httplib::Request& req, httplib::Response& res) {
        std::string category = req.get_param_value("category");
        nlohmann::json jsonObject;
        nlohmann::json result;
        std::vector<HMOD> currentmods;


        if (categoryMap.find(category) != categoryMap.end()) {
            Category enumCategory = categoryMap[category];
            ModuleManager::getInstance().getModule(enumCategory, &currentmods);

            auto processModule = [&result](HMOD modules) {
                result[urlEncode(ToBaseModule(modules)->getName())] = ToBaseModule(modules)->getToggle();
            };

            std::for_each(currentmods.begin(), currentmods.end(), processModule);
        }

        jsonObject["result"] = result;
        jsonObject["success"] = true;
        res.set_content(jsonObject.dump(), "application/json;charset=utf-8");
        });

    /*
    * modulesList
    */
    this->server.Get("/api/modulesList", [](const httplib::Request& req, httplib::Response& res) {
        std::string category = req.get_param_value("category");
        std::cout << category << std::endl;

        nlohmann::json jsonObject;
        nlohmann::json result;
        std::vector<HMOD> currentmods;
        //你之前写的是什么几把。。
        if (categoryMap.find(category) != categoryMap.end()) {
            Category enumCategory = categoryMap[category];
            ModuleManager::getInstance().getModule(enumCategory, &currentmods);

            for (auto& modules : currentmods) {
                nlohmann::json moduleJsonObj;
                moduleJsonObj["state"] = ToBaseModule(modules)->getToggle();
                moduleJsonObj["desc"] = ToBaseModule(modules)->getDesc();
                moduleJsonObj["binding"] = ToBaseModule(modules)->getKey();
                moduleJsonObj["settings"] = !ToBaseModule(modules)->getValues().empty();
                moduleJsonObj["canToggle"] = true;
                result[ToBaseModule(modules)->getName()] = moduleJsonObj;
            }
        }

        jsonObject["result"] = result;
        jsonObject["success"] = true;
        res.set_content(jsonObject.dump(), "application/json;charset=utf-8");
        });

    /*
    * getModuleSetting
    */
    this->server.Get("/api/getModuleSetting", [](const httplib::Request& req, httplib::Response& res) {
        std::string moduleName = req.get_param_value("module");
        nlohmann::json jsonObject;
        bool isFound = false;
        std::vector<HMOD> mods = ModuleManager::getInstance().getMods();

        for (auto& modules : mods) {
            if (ToBaseModule(modules)->getName().find(moduleName) != -1) {
                nlohmann::json moduleJsonArray;
                isFound = true;
                auto values = ToBaseModule(modules)->getValues();

                for (const auto& value : values) {
                    nlohmann::json moduleSet;

                    moduleSet["name"] = value.second->getName();

                    switch (value.first) {
                    case BoolType: {
                        BoolValue* pValue = static_cast<BoolValue*>(value.second);
                        moduleSet["type"] = "checkbox";
                        moduleSet["value"] = pValue->getValue();
                        break;
                    }
                    case FloatType: {
                        FloatValue* pValue = static_cast<FloatValue*>(value.second);
                        moduleSet["type"] = "slider";
                        moduleSet["min"] = pValue->getMin();
                        moduleSet["max"] = pValue->getMax();
                        moduleSet["step"] = 0.1;
                        moduleSet["value"] = pValue->getValue();
                        break;
                    }
                    case ListType: {
                        ModeValue* pValue = static_cast<ModeValue*>(value.second);
                        moduleSet["type"] = "selection";
                        nlohmann::json values;
                        for (size_t i = 0; i < pValue->getModes().size(); i++)
                        {
                            values.push_back(pValue->getDescs()[i]);
                        }
                        moduleSet["values"] = values;
                        moduleSet["value"] = urlEncode(pValue->getDescs()[pValue->getValue()]);
                        break;
                    }
                    default:
                        break;
                    }

                    if (!moduleSet.empty() && !moduleSet.is_null()) {
                        moduleJsonArray.push_back(moduleSet);
                    }
                }

                std::cout << moduleJsonArray.dump() << std::endl;
                jsonObject["result"] = moduleJsonArray;
            }
        }

        jsonObject["success"] = isFound;
        if (!isFound) jsonObject["reason"] = "Can't find module";
        res.set_content(jsonObject.dump(), "application/json;charset=utf-8");
        });
    /*
    * setModuleSettingValue
    */
    this->server.Get("/api/setModuleSettingValue", [](const httplib::Request& req, httplib::Response& res) {
        std::string moduleName = req.get_param_value("module");
        std::string name = req.get_param_value("name");
        std::string value = req.get_param_value("value");
        HMOD mods = ModuleManager::getInstance().getModule(moduleName);
        nlohmann::json jsonObject;
        auto values = ToBaseModule(mods)->getValues();
        for (size_t i = 0; i < values.size(); i++) {
            //额。。
            if (values[i].second->getName()._Equal(name)) {
                switch (values[i].first) {
                case ListType: {
                    ModeValue* pValue = (ModeValue*)values[i].second;
                    nlohmann::json  values;
                    for (size_t i = 0; i < pValue->getModes().size(); i++)
                    {
                        if (std::string(pValue->getDescs()[i]).find(value) != -1) {
                            *pValue->getValuePtr() = i;
                        }
                    }
                    jsonObject["result"] = value;
                    break;
                }
                case BoolType: {
                    BoolValue* pValue = (BoolValue*)values[i].second;
                    if (value.find("true") != -1)
                    {
                        *pValue->getValuePtr() = true;
                        jsonObject["result"] = true;
                    }
                    if (value.find("false") != -1)
                    {
                        *pValue->getValuePtr() = false;
                        jsonObject["result"] = false;;
                    }
                
                    break;
                }
                case FloatType: {
                    FloatValue* pValue = (FloatValue*)values[i].second;
                    *pValue->getValuePtr() = std::stof(value);
                    jsonObject["result"] = std::stof(value);
                    break;
          

                }
            }
        }
    }

    jsonObject["success"] = true;
    res.set_content(jsonObject.dump(), "application/json;charset=utf-8");
        });


    std::thread ths(&WebServerManager::ListenThread, this);
    ths.detach();
}

void WebServerManager::detach()
{
    this->server.stop();
}

void WebServerManager::ListenThread()
{
    std::cout  << "Start Successful localhost:" << std::dec << this->port << std::endl;
    this->server.listen("0.0.0.0", this->port);
}
