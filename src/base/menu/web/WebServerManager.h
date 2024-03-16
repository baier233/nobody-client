#pragma once
#include "../../../../ext/httplib/httplib.h"
#include <string>
#include <thread>
#include <codecvt>
#include <locale>
#include "../../Resource/ResourceManager.h"
//#include "../../../../ext/json/CJsonObject.hpp"
#include "../../../../ext/json/json.hpp"
#include "../../moduleManager/ModuleManager.h"
class WebServerManager
{
public:
	static WebServerManager& getInstance();
	void Start(int port);
	void detach();
private:
	httplib::Server server;
	int port;
	void ListenThread();

	//std::string urlEncode(const std::string& str);
	//std::string urlDecode(const std::string& str);
};
