#pragma once

#include <netcdf.h>
#include <netcdfcpp.h>
#include "spdlog/spdlog.h"
#include <string>
#include <filesystem>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <map>
#include "NumCpp.hpp"
#include <boost/filesystem.hpp>
#include <regex>
#include <chrono>   

namespace fs = std::filesystem;
using namespace netCDF;
using namespace netCDF::exceptions;
using namespace std::chrono;

bool CreateFolder(const std::string& dir_path);
std::string replace(std::string str, const std::string& from, const std::string& to);

class AdLog {
public:
	AdLog() = delete;
	AdLog(const AdLog&) = delete;
	AdLog& operator=(const AdLog&) = delete;

	static void Init();

	static spdlog::logger* GetLoggerInstance() {
		assert(sLoggerInstance && "Logger instance is null, maybe you have not execute AdLog::Init()");
		return sLoggerInstance.get();
	}
private:
	static std::shared_ptr<spdlog::logger> sLoggerInstance;
};

#define LOG_T(...) SPDLOG_LOGGER_TRACE(AdLog::GetLoggerInstance(), __VA_ARGS__);
#define LOG_D(...) SPDLOG_LOGGER_DEBUG(AdLog::GetLoggerInstance(), __VA_ARGS__);
#define LOG_I(...) SPDLOG_LOGGER_INFO(AdLog::GetLoggerInstance(), __VA_ARGS__);
#define LOG_W(...) SPDLOG_LOGGER_WARN(AdLog::GetLoggerInstance(), __VA_ARGS__);
#define LOG_E(...) SPDLOG_LOGGER_ERROR(AdLog::GetLoggerInstance(), __VA_ARGS__);


typedef std::vector<std::vector<std::vector<float>>> tri_matrix;
typedef std::vector<std::vector<std::vector<double>>> tri_matrix_d;
typedef std::vector<std::vector<std::vector<int>>> tri_matrix_int;
typedef std::map<std::string, std::vector<std::vector<std::vector<float>>>> tri_matrix_map;

class TimeRecorder {
public:
	TimeRecorder() {
		_start = system_clock::now();
	}

	void finish() {
		_end = system_clock::now();
		auto duration = duration_cast<microseconds>(_end - _start);
		double cost_time = double(duration.count()) * microseconds::period::num / microseconds::period::den;
		LOG_I("process cost {0} s", cost_time);
	}

private:
	system_clock::time_point _start;
	system_clock::time_point _end;
};

class TriMatrix {
public:
	TriMatrix() = default;
	TriMatrix(int a, int b, int c) {
		_sizes.push_back(a);
		_sizes.push_back(b);
		_sizes.push_back(c);
		_data = new float[a * b * c];
	}

	void __init__(int a, int b, int c) {
		_sizes.push_back(a);
		_sizes.push_back(b);
		_sizes.push_back(c);
		_data = new float[a * b * c];
	}

	float getVar(int i, int j, int k) {
		return _data[i * _sizes[1] * _sizes[2] + j * _sizes[2] + k];
	}

	float* data() {
		return _data;
	}

	void clear() {
		delete[] _data;
		_data = nullptr;
	}

	tri_matrix to_tri_matrix() {
		tri_matrix res;
		res.resize(_sizes[0]);
		for (int i = 0; i < _sizes[0]; i++) {
			res[i].resize(_sizes[1]);
			for (int j = 0; j < _sizes[1]; j++) {
				res[i][j].resize(_sizes[2]);
				for (int k = 0; k < _sizes[2]; k++) {
					res[i][j][k] = getVar(i, j, k);
				}
			}
		}
		return res;
	}

	~TriMatrix() {
		if (_data != nullptr) {
			delete[] _data;
		}
	}

private:
	float* _data;
	std::vector<int> _sizes;
};

class NcFileReader{

public:
	NcFileReader() = default;

	tri_matrix_map __call__(std::string file_path, std::string fea_name) {
		NcFile dataFile(file_path, NcFile::read);
		NcVar data = dataFile.getVar(fea_name);
		transform(fea_name.begin(), fea_name.end(), fea_name.begin(), ::tolower);
		if (data.isNull()) {
			return {};
		}
		tri_matrix_map res;
		TriMatrix Matrix;
		if (fea_name == "eta") {
			//data_size = 1696 * 960;
			NcDim Nx = dataFile.getDim("Nx");
			NcDim Ny = dataFile.getDim("Ny");
			//Matrix = tri_matrix(1, std::vector<std::vector<float>>(Ny.getSize(), std::vector<float>(Nx.getSize(), 0.00f)));
			Matrix.__init__(1, Ny.getSize(), Nx.getSize());
			data.getVar(Matrix.data());
		}
		else {
			NcDim Nx = dataFile.getDim("Nx");
			NcDim Ny = dataFile.getDim("Ny");
			NcDim Nr = dataFile.getDim("Nr");
			Matrix.__init__(Nr.getSize(), Ny.getSize(), Nx.getSize());
			data.getVar(Matrix.data());
		}
		dataFile.close();
		res[fea_name] = Matrix.to_tri_matrix();
		return res;
	}
};

void getAllFiles(std::string path, std::vector<std::string>& files);

class NcfileSearcher {

public:
	NcfileSearcher() = default;

	std::vector<std::string> __call__(std::string file_folder, std::string file_name_patern) {
		std::vector<std::string> file_paths;
		std::vector<std::string> res;

		fs::path all_path = fs::absolute(fs::path(file_folder)) ;
		std::regex reg_exp(".*" + file_name_patern);
		try {
			getAllFiles(all_path.string(), file_paths);

			for (int i = 0; i < file_paths.size(); i++) {
				bool ret = regex_match(file_paths[i].c_str(), reg_exp);
				if (ret == true) {
					res.push_back(file_paths[i].c_str());
				}
			}
		}
		catch (...) {
			LOG_E("The path is not exist! The path is {0}", file_folder);
		}
		return res;
	}
};


struct NcVar_t {
	tri_matrix_map grid_data;
	int time;
};

class NcfileManager {

public:

	NcfileManager() = default;

	NcfileManager(std::string file_folder, std::string file_name_patern, std::string fea_name, int t0, int t1) {
		std::vector<std::string> file_paths = _file_searcher.__call__(file_folder, file_name_patern);
		sort(file_paths.begin(), file_paths.end());
		for (auto& i : file_paths) {
			i = replace(i, "\\", "/");
		}
		if (file_paths.size() == 0) {
			LOG_E("No file found! The path is {0}", file_folder);
			return;
		}
		std::vector<std::string> file_paths_t;
		for (int i = t0; i < std::min(t1, (int)file_paths.size()); i++) {
			file_paths_t.push_back(file_paths[i]);
		}

		std::vector<std::string> splitRes;
		for (auto file_path : file_paths_t) {
			splitRes.clear();
			Stringsplit(file_path, '.', splitRes);
			int index;
			if (std::string(file_path.end() - 7, file_path.end() - 3) == "glob") {
				index = -3;
			}
			else {
				index = -2;
			}
			_times.push_back(atoi((*(splitRes.end() + index)).c_str()));
		}

		_fea_name = fea_name;
		_file_paths = file_paths_t;
	}

	std::vector<int> get_time_indexs() {
		std::vector<int> res;
		for (int i = 0; i < __len__(); i++) {
			res.push_back(i);
		}
		return res;
	}

	int __len__() {
		return _times.size();
	}

	NcVar_t __getitem__(int index) {
		tri_matrix_map grid_data = _file_reader.__call__(_file_paths[index], _fea_name);
		int time = _times[index];
		return { grid_data, time };
	}

	std::vector<std::string> get_file_paths() {
		return _file_paths;
	}

	std::string get_fea_name() {
		return _fea_name;
	}

	void Stringsplit(std::string str, const char split, std::vector<std::string>& res);

private:

	NcFileReader _file_reader;
	NcfileSearcher _file_searcher;
	std::vector<int> _times;
	std::string _fea_name;
	std::vector<std::string> _file_paths;
};
