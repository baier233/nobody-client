#pragma once
#include <string>
#include <vector>
struct ResourceData
{
	unsigned char* data;
	int size;
};
class ResourceManager
{
public:
	static ResourceManager& getInstance();
	ResourceData getResource(std::string name);
	void LoadAllResource();
private:
	void AddResource(std::string name, unsigned char* data, int size);
	struct ResourceBase
	{
		std::string name;
		unsigned char* data;
		int size;
	};
	std::vector<ResourceBase> Resources;
};

