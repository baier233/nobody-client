#include <Windows.h>
#include <thread>
#include "../util/xorstr.h"
#include "logger.h"
#include <fstream>

FILE* out;
FILE* err;

std::string username;
std::string password;

static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
bool check_license(const char* user, const char* users_license)
{
	std::string license;
	size_t ll = strlen(users_license);
	size_t l = strlen(user), lic_ctr = 0;
	int add = 0;

	for (size_t i = 0; i < ll; i++)
		if (users_license[i] != '-')
			license += users_license[i];

	while (lic_ctr < license.length()) {
		size_t i = lic_ctr;
		i %= l;
		int current = 0;
		while (i < l) current += user[i++];
		current += add;
		add++;
		if (license[lic_ctr] != letters[current % sizeof letters])
			return false;
		lic_ctr++;
	}
	return true;
}

void Logger::Init()
{

	AllocConsole();
	
	freopen_s(&out, "CONOUT$", "w", stdout);
	freopen_s(&err, "CONOUT$", "w", stderr);
	
	Logger::Initialized = true;
}

void Logger::Kill()
{
	if (Logger::Initialized)
	{
		fclose(out);
		fclose(err);
		FreeConsole();
	}
}

void Logger::Log(std::string message)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ LOG ] :: " + message << "\n";
}

void Logger::Log(double message)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << message << "\n";
}


void Logger::LogPosition(Vector3 position)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ LOG POS ] :: X -> " << position.x << " Y -> " << position.y << " Z ->" << position.z << std::endl;
}

void Logger::Err(std::string message)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ ERR ] :: " + message << std::endl;
}

void Logger::LogWait(std::string message, int seconds)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ LOG ] :: " + message << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void Logger::ErrWait(std::string message, int seconds)
{
	if (!Logger::Initialized) Logger::Init();
	std::cout << "[ ERR ] :: " + message << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
