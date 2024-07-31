#include "ncfile_manager.hpp"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> AdLog::sLoggerInstance{};

void AdLog::Init() {
	sLoggerInstance = spdlog::stdout_color_mt<spdlog::async_factory>("async_logger");
	sLoggerInstance->set_level(spdlog::level::trace);
	sLoggerInstance->set_pattern("%^%H:%M:%S:%e [%P-%t] [%1!L] [%20s:%-4#] - %v%$");
}


void NcfileManager::Stringsplit(std::string str, const char split, std::vector<std::string>& res) {
	std::istringstream iss(str);	// 输入流
	std::string tmp_string;			// 接收缓冲区
	while (getline(iss, tmp_string, split)) {
		res.push_back(tmp_string); // 输出
	}
}

bool CreateFolder(const std::string& dir_path) {
    try {
        if (!boost::filesystem::exists(dir_path)) {
            boost::filesystem::create_directories(dir_path);
        }
        else {
        }
        return true;
    }
    catch (const std::exception& e) {
        LOG_E("Dir Create failed! {0}", e.what());
        return false;
    }
}

void getAllFiles(std::string path, std::vector<std::string>& files)
{
    for (const auto& file : fs::directory_iterator(path)) {
        files.push_back(file.path().string());
    }
}

std::string replace(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}