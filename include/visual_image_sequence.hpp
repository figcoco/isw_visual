#pragma once

#include <chrono>   
#include <iostream>
#include "ncfile_manager.hpp"
#include "ocean_data.hpp"
#include <boost/program_options.hpp>
#include "ThreadPool.hpp"
#include "ocean_data_visual.hpp"

using namespace std::chrono;
namespace bpo = boost::program_options;

struct Param {
    bool is_success;
    std::string fea_name;
    int t0;
    int t1;
    int z0;
    int z1;
    int y0;
    int y1;
    int x0;
    int x1;
    int nop;
    float yx_aspect;
    float zx_aspect;
    std::string image_type;
    std::string data_folder;
    std::string image_folder;
};

class ParamReciver {
public:
    Param _recieve(int argc, char* argv[]) {
        //步骤一: 构造选项描述器和选项存储器
        //选项描述器,其参数为该描述器的名字
        bpo::options_description opts("all options");
        //选项存储器,继承自map容器
        bpo::variables_map vm;

        Param param;
        param.is_success = false;
        std::map<std::string, int> fea_choices = { {"temp", 1}, {"eta", 1}, {"u", 1}, {"v", 1}, {"ut", 1} };
        std::map<std::string, int> image_type_choices = { {"svg", 1}, {"jpg", 1}, {"png", 1} };

        //步骤二: 为选项描述器增加选项
        //其参数依次为: key, value的类型，该选项的描述
        opts.add_options()
            ("fea_name", bpo::value<std::string>(&param.fea_name)->default_value("temp"), "which feature to visualize, include \"temp\" and \"eta\"")
            ("t0", bpo::value<int>(&param.t0)->default_value(0))
            ("t1", bpo::value<int>(&param.t1)->default_value(0))
            ("z0", bpo::value<int>(&param.z0)->default_value(0))
            ("z1", bpo::value<int>(&param.z1)->default_value(0))
            ("y0", bpo::value<int>(&param.y0)->default_value(0))
            ("y1", bpo::value<int>(&param.y1)->default_value(0))
            ("x0", bpo::value<int>(&param.x0)->default_value(0))
            ("x1", bpo::value<int>(&param.x1)->default_value(0))
            ("nop", bpo::value<int>(&param.nop)->default_value(1), "the number of processes")
            ("yx_aspect", bpo::value<float>(&param.yx_aspect)->default_value(1.76), "aspect of width and height when feature is eta")
            ("zx_aspect", bpo::value<float>(&param.zx_aspect)->default_value(20), "aspect of width and height when feature is temp, uv")
            ("image_type", bpo::value<std::string>(&param.image_type)->default_value("svg"))
            ("data_folder", bpo::value<std::string>(&param.data_folder), "the folder path of dataset file")
            ("image_folder", bpo::value<std::string>(&param.image_folder), "the folder path of saving image and image name is \"image_xx\"");
            

        //步骤三、四: 先对命令行输入的参数做解析,而后将其存入选项存储器
        //如果输入了未定义的选项，程序会抛出异常，所以对解析代码要用try-catch块包围
        try {
            //parse_command_line()对输入的选项做解析
            //store()将解析后的结果存入选项存储器
            bpo::store(bpo::parse_command_line(argc, argv, opts), vm);
        }
        catch (...) {
            LOG_E("undefine options!");
            bpo::notify(vm);
            return param;
        }
        bpo::notify(vm);

        if (fea_choices[param.fea_name] != 1) {
            LOG_E("undefine fea_name!");
            return param;
        }

        if (image_type_choices[param.image_type] != 1) {
            LOG_E("undefine image_type!");
            return param;
        }        
        
        if (vm.empty()) {
            LOG_E("no options found");
            return param;
        }

        param.is_success = true;
        return param;
    }

    void _adapt(Param& param) {
        std::vector<int> datas_shape = { 24, 90, 960, 1696 };
        param.t0 = param.t0 != 0 ? param.t0 : 0;
        param.z0 = param.z0 != 0 ? param.z0 : 0;
        param.y0 = param.y0 != 0 ? param.y0 : 0;
        param.x0 = param.x0 != 0 ? param.x0 : 0;
        param.t1 = param.t1 != 0 ? param.t1 : datas_shape[0];
        param.z1 = param.z1 != 0 ? param.z1 : datas_shape[1];
        param.y1 = param.y1 != 0 ? param.y1 : datas_shape[2];
        param.x1 = param.x1 != 0 ? param.x1 : datas_shape[3];
    }

    Param __call__(int argc, char* argv[]) {
        Param res = _recieve(argc, argv);
        _adapt(res);
        return res;
    }
};


class DistCalcor {
public:
    DistCalcor() = default;
    int __call__(int x0, int y0, int x1, int y1) {
        return int(sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
    }
};

class Cropper {
public:
    Cropper() = default;
    Cropper(int x0, int x1, int y0, int y1) {
        _x0 = x0;
        _x1 = x1;
        _y0 = y0;
        _y1 = y1;
    }

    tri_matrix __call__(tri_matrix& data) {
        tri_matrix res(data.size(), std::vector<std::vector<float>>(data[0].size(), std::vector<float>(data[0][0].size(), 0.0f)));
        //nc::flip(a, nc::Axis::ROW)
        for (int channel = 0; channel < data.size(); channel++) {
            for (int i = _y1 - 1; i >= _y1; i--) {
                for (int j = _x0; j < _x1; j++) {
                    res[channel][_y1 - i - 1][j] = data[channel][i][j];
                }
            }
        }
        return res;
    }

private:
    int _x0;
    int _x1;
    int _y0;
    int _y1;
};

class Gradientor {
public:
    tri_matrix __call__(tri_matrix& data) {
        tri_matrix final_mat;
        std::vector<std::vector<float>> vec_2d;
        for (int i = 2; i < data[0].size() - 2; i++) {
            std::vector<float> vec;
            for (int j = 2; j < data[0][i].size() - 2; j++) {
                float res = (data[0][i][j + 1] - data[0][i][j - 1]) / 2.0;
                vec.push_back(res);
            }
            vec_2d.push_back(vec);
        }
        final_mat.push_back(vec_2d);
        return final_mat;
    }
};


class SlashInterpolator {
public:
    SlashInterpolator() = default;
    SlashInterpolator(int x0, int x1, int y0, int y1, int z0, int z1) {
        _xy_dist = _dist_calcor.__call__(x0, y0, x1, y1);
        _x0 = x0;
        _x1 = x1;
        _y0 = y0;
        _y1 = y1;
        _z0 = z0;
        _z1 = z1;
    }

    tri_matrix __call__(tri_matrix& data) {
        //auto& data_shape = data.shape();
        auto x_coords = nc::linspace(_x0, _x1 - 1, _xy_dist);
        auto y_coords = nc::linspace(_y0, _y1 - 1, _xy_dist);
        //todo
        // interp_func = RegularGridInterpolator(
        //     (nc::arange(data_shape.cols), nc::arange(data_shape.rows), np.arange(data_shape[2])), 
        //    data);
        auto coordss = tri_matrix_int(_z1 - _z0, std::vector<std::vector<int>>(_xy_dist, std::vector<int>(3, 0)));
        for (int i = 0; i < _z1 - _z0; i++) {
            for (int j = 0; j < _xy_dist; j++) {
                coordss[i][j][0] = _z0 + i;
                coordss[i][j][1] = y_coords[j];
                coordss[i][j][2] = x_coords[j];
            }
        }
        //data = interp_func(coordss);
        return data;
    }

    DistCalcor _dist_calcor;
    int _x0;
    int _x1;
    int _y0;
    int _y1;
    int _z0;
    int _z1;
    int _xy_dist;
};


class ZeroValueTransformer {
public:
    ZeroValueTransformer() = default;
    ZeroValueTransformer(float transform_value) {
        _transform_value = transform_value;
    }

    void __call__(tri_matrix& data) {
        for (auto& i : data) {
            for (auto& j : i) {
                for (auto& k : j) {
                    if (k == 0) {
                        k = _transform_value;
                    }
                }
            }
        }
    }

private:
    float _transform_value;
};

struct Color {
    float r;
    float g;
    float b;
};

struct LinearColorMap {
    std::string title;
    std::vector<Color> colors;
    std::vector<std::vector<double>> cmap;
};

class Colorbar {
public:
    Colorbar() = default;
    Colorbar(std::vector<std::string> colors, float min, float max) {
        _colors = colors;
        vmin = min;
        vmax = max;
    }

    Color string2Color(std::string color) {
        Color res;
        std::string r(color.begin() + 1, color.begin() + 3);
        std::string g(color.begin() + 3, color.begin() + 5);
        std::string b(color.begin() + 5, color.end());
        r = "0x" + r;
        g = "0x" + g;
        b = "0x" + b;
        res.r = atoi(r.c_str());
        res.g = atoi(g.c_str());
        res.b = atoi(b.c_str());
        return res;
    }

    LinearColorMap linearSegmentedColormap(std::string title, std::vector<std::string>& colors, int sum) {
        LinearColorMap res;
        res.title = title;
        int segment = colors.size() - 1;                        //10        3
        int seg_size = sum / segment - 1;                           //90        96
        for (int i = 0; i < colors.size() - 1; i++) {           //
            //"#fddbc7"
            std::string before = colors[i];
            Color before_c = string2Color(before);
            std::string after = colors[i + 1];
            Color after_c = string2Color(after);
            for (int j = 0; j <= seg_size; j++) {
                Color mid_c;
                std::vector<double> mid_v;
                mid_c.r = (after_c.r - before_c.r) / seg_size + before_c.r;
                mid_c.g = (after_c.g - before_c.g) / seg_size + before_c.g;
                mid_c.b = (after_c.b - before_c.b) / seg_size + before_c.b;
                mid_v.push_back(mid_c.r);
                mid_v.push_back(mid_c.g);
                mid_v.push_back(mid_c.b);
                res.colors.push_back(mid_c);
                res.cmap.push_back(mid_v);
            }
        }
        LOG_I("{0} create colormap size : {1}", __FUNCTION__, res.colors.size());
        return res;
    }

    LinearColorMap get_camp() {
        return linearSegmentedColormap("cmap", _colors, 100);
    }

    void save(std::string folder) {
        CreateFolder(folder);
        std::fstream fs;
        fs.open("checkjson.json", std::ios::app | std::ios::in | std::ios::out);
        Json::Value root;
        Json::FastWriter writer;
        Json::Value colors;
        for (auto& i : _colors) {
            colors.append(i);
        }
        root["colors"] = colors;
        root["vmin"] = vmin;
        root["vmax"] = vmax;
        std::string json_file = writer.write(root);
        fs << json_file << std::endl;
        fs.close();
    }

    std::vector<std::string> _colors;
    float vmin;
    float vmax;
};


class ImageRecorder {
public:
    ImageRecorder() = default;
    ImageRecorder(std::shared_ptr<ImageGenerator> image_generator, Colorbar colorbar, std::string image_folder) {
        _image_generator = image_generator;
        _colorbar = colorbar;
        _image_folder = image_folder;
    }

    void __call__(tri_matrix_map& data, std::string image_name) {
        tri_matrix Data = data.begin()->second;
        _image_generator->__call__(Data, _image_folder, image_name, "", _colorbar.vmin, _colorbar.vmax);
    }

    void __call__(tri_matrix_map& data0, tri_matrix_map& data1, std::string image_name) {
        tri_matrix Data0 = data0.begin()->second;
        tri_matrix Data1 = data1.begin()->second;
        _image_generator->__call__(Data0, _image_folder, image_name, "", _colorbar.vmin, _colorbar.vmax);
        _image_generator->__call__(Data1, _image_folder, image_name, "", _colorbar.vmin, _colorbar.vmax);
    }

private:
    std::shared_ptr<ImageGenerator> _image_generator;
    Colorbar _colorbar;
    std::string _image_folder;
};


class Visualer {
public:
    Visualer() = default;
    Visualer(NcfileManager ncfile_manager, ImageRecorder image_recorder) {
        _ncfile_manager = ncfile_manager;
        _image_recorder = image_recorder;
    }

    std::vector<int> get_time_indexs() {
        return _ncfile_manager.get_time_indexs();
    }

    virtual void run(std::vector<int>& time_indexs){}

protected:
    NcfileManager _ncfile_manager;
    ImageRecorder _image_recorder;
};

class TempVisualer : public Visualer {
public:
    TempVisualer() = default;
    TempVisualer(NcfileManager ncfile_manager, ImageRecorder image_recorder, ZeroValueTransformer zero_value_transformer, SlashInterpolator slash_interpolator)
        :Visualer(ncfile_manager, image_recorder) {
        _slash_interpolator = slash_interpolator;
        _zero_value_transformer = zero_value_transformer;
    }

    virtual void run(std::vector<int>& time_indexs) {
        for (auto& time_index : time_indexs) {
            NcVar_t data = _ncfile_manager.__getitem__(time_index);
            LOG_I("time_index : {0} / {1} complete.", time_index, time_indexs.size());
            data.grid_data.begin()->second = _slash_interpolator.__call__(data.grid_data.begin()->second);
            _zero_value_transformer.__call__(data.grid_data.begin()->second);
            std::string time_index_s = std::to_string(time_index);
            while (time_index_s.size() < 2) {
                time_index_s = "0" + time_index_s;
            }
            _image_recorder.__call__(data.grid_data, "image_" + time_index_s);
        }
    }

private:
    SlashInterpolator _slash_interpolator;
    ZeroValueTransformer _zero_value_transformer;
};

class UtVisualer : public Visualer {
public:
    UtVisualer() = default;
    UtVisualer(NcfileManager u_ncfile_manager, 
                NcfileManager temp_ncfile_manager, 
                ImageRecorder image_recorder, 
                ZeroValueTransformer zero_value_transformer, 
                SlashInterpolator slash_interpolator)
        :Visualer(u_ncfile_manager, image_recorder) {
        _u_ncfile_manager = u_ncfile_manager;
        _temp_ncfile_manager = temp_ncfile_manager;
        _slash_interpolator = slash_interpolator;
        _zero_value_transformer = zero_value_transformer;
    }

    virtual void run(std::vector<int>& time_indexs) {
        for (auto& time_index : time_indexs) {
            NcVar_t u_data = _u_ncfile_manager.__getitem__(time_index);
            NcVar_t temp_data = _temp_ncfile_manager.__getitem__(time_index);
            LOG_I("time_index : {0} / {1} complete.", time_index, time_indexs.size());
            temp_data.grid_data.begin()->second = _slash_interpolator.__call__(temp_data.grid_data.begin()->second);
            u_data.grid_data.begin()->second = _slash_interpolator.__call__(u_data.grid_data.begin()->second);
            _zero_value_transformer.__call__(temp_data.grid_data.begin()->second);
            std::string time_index_s = std::to_string(time_index);
            while (time_index_s.size() < 2) {
                time_index_s = "0" + time_index_s;
            }
            _image_recorder.__call__(u_data.grid_data, temp_data.grid_data, "image_" + time_index_s);
        }
    }

private:
    SlashInterpolator _slash_interpolator;
    ZeroValueTransformer _zero_value_transformer;
    NcfileManager _u_ncfile_manager;
    NcfileManager _temp_ncfile_manager;
};

class UvVisualer : public Visualer {
public:
    UvVisualer() = default;
    UvVisualer(NcfileManager ncfile_manager, ImageRecorder image_recorder, SlashInterpolator slash_interpolator)
        :Visualer(ncfile_manager, image_recorder) {
        _slash_interpolator = slash_interpolator;
    }

    virtual void run(std::vector<int>& time_indexs) {
        for (auto& time_index : time_indexs) {
            NcVar_t data = _ncfile_manager.__getitem__(time_index);
            LOG_I("time_index : {0} / {1} complete.", time_index, time_indexs.size());
            data.grid_data.begin()->second = _slash_interpolator.__call__(data.grid_data.begin()->second);
            std::string time_index_s = std::to_string(time_index);
            while (time_index_s.size() < 2) {
                time_index_s = "0" + time_index_s;
            }
            _image_recorder.__call__(data.grid_data, "image_" + time_index_s);
        }
    }

private:
    SlashInterpolator _slash_interpolator;
};

class EtaVisualer : public Visualer {
public:
    EtaVisualer() = default;
    EtaVisualer(NcfileManager ncfile_manager, ImageRecorder image_recorder, Cropper cropper, Gradientor gradientor)
        :Visualer(ncfile_manager, image_recorder) {
        _cropper = cropper;
        _gradientor = gradientor;
    }

    virtual void run(std::vector<int>& time_indexs) {
        for (auto& time_index : time_indexs) {
            NcVar_t data = _ncfile_manager.__getitem__(time_index);
            LOG_I("time_index : {0} / {1} complete.", time_index, time_indexs.size());
            data.grid_data.begin()->second = _cropper.__call__(data.grid_data.begin()->second);
            data.grid_data.begin()->second = _gradientor.__call__(data.grid_data.begin()->second);
            std::string time_index_s = std::to_string(time_index);
            while (time_index_s.size() < 2) {
                time_index_s = "0" + time_index_s;
            }
            _image_recorder.__call__(data.grid_data, "image_" + time_index_s);
        }
    }

private:
    Cropper _cropper;
    Gradientor _gradientor;
};

class TimeRecorder {
public:
    TimeRecorder() {
        _start = system_clock::now();
    }

    void finish() {
        _end = system_clock::now();
        auto duration = duration_cast<microseconds>(_end - _start);
        double cost_time = double(duration.count())* microseconds::period::num / microseconds::period::den;
        LOG_I("process cost {0} s", cost_time);
    }

private:
    system_clock::time_point _start;
    system_clock::time_point _end;
};

class VisualRuner {
public:
    VisualRuner() = default;
    VisualRuner(std::shared_ptr<Visualer> visualer) {
        _visualer = visualer;
        _time_indexs = _visualer->get_time_indexs();
    }

    void run() {
        //self._multi_process_manager.run(self._visualer.run, self._time_indexs);
        _visualer->run(_time_indexs);
    }

private:
    std::shared_ptr<Visualer> _visualer;
    std::vector<int> _time_indexs;
    //_multi_process_manager;
};


class VisualerFactory {
public:
    VisualerFactory() = default;

    std::shared_ptr<Visualer> __call__(Param& param) {
        if (!param.is_success) {
            LOG_E("param failed");
            return nullptr;
        }
        if (param.fea_name == "eta") {
            auto ncfile_manager = NcfileManager(param.data_folder, "stateEta.*.glob.nc", "Eta", param.t0, param.t1 + 1);
            auto cropper = Cropper(param.x0, param.x1, param.y0, param.y1);
            auto gradientor = Gradientor();
            std::vector<std::string> colors = { "#0000FF", "#FFFFFF" };
            colors = { "#4b0095", "#0c7ff2", "#fefefe", "#fa8b04" };
            auto colorbar = Colorbar(colors, -0.01, 0.01);
            colorbar.save(param.image_folder);
            auto draw_fun = std::make_shared<DrawHeatFrame>(param.yx_aspect, colorbar.get_camp().cmap);
            std::vector<int> figsize = { 20 * (param.x1 - param.x0 - 2) / (param.y1 - param.y0 - 2), 20 };
            auto image_generator = std::make_shared <PurseImageGenerator>(figsize, draw_fun, param.image_type);
            auto image_recorder = ImageRecorder(image_generator, colorbar, param.image_folder);
            std::shared_ptr<Visualer> res = std::make_shared <EtaVisualer>(ncfile_manager, image_recorder, cropper, gradientor);
            return res;
        }
        else if (param.fea_name == "temp") {
            auto ncfile_manager = NcfileManager(param.data_folder, "stateT.*.glob.nc", "Temp", param.t0, param.t1 + 1);
            auto zero_value_transformer = ZeroValueTransformer(15);
            auto slash_interpolator = SlashInterpolator(param.x0, param.x1, param.y0, param.y1, param.z0, param.z1);
            std::vector<std::string> colors = { "#053061", "#2166ac", "#4393c3", "#92c5de", "#d1e5f0", "#f7f7f7", "#fddbc7", "#f4a582", "#d6604d", "#b2182b", "#67001f" };
            auto colorbar = Colorbar(colors, 0.0, 30.0);
            colorbar.save(param.image_folder);
            auto draw_fun = std::make_shared<DrawCcFrame>(33, param.zx_aspect, colorbar.get_camp().cmap);
            std::vector<int> figsize = { 20 * slash_interpolator._xy_dist / (param.z1 - param.z0), 20 };
            auto image_generator = std::make_shared<PurseImageGenerator>(figsize, draw_fun, param.image_type);
            auto image_recorder = ImageRecorder(image_generator, colorbar, param.image_folder);
            std::shared_ptr<Visualer> res = std::make_shared<TempVisualer>(ncfile_manager, image_recorder, zero_value_transformer, slash_interpolator);
            return res;
        }
        else if (param.fea_name == "ut") {
            auto u_ncfile_manager = NcfileManager(param.data_folder, "stateU.*.glob.nc", "U", param.t0, param.t1 + 1);
            auto temp_ncfile_manager = NcfileManager(param.data_folder, "stateT.*.glob.nc", "Temp", param.t0, param.t1 + 1);
            auto zero_value_transformer = ZeroValueTransformer(15);
            auto slash_interpolator = SlashInterpolator(param.x0, param.x1, param.y0, param.y1, param.z0, param.z1);
            std::vector<std::string> colors = { "#67001f", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#f7f7f7", "#d1e5f0", "#92c5de", "#4393c3", "#2166ac", "#053061" };
            auto colorbar = Colorbar(colors, -1.0, 1.0);
            colorbar.save(param.image_folder);
            //todo
            auto draw_fun = std::make_shared<DrawDoubleHcFrame>(33, param.zx_aspect, colorbar.get_camp().cmap);
            std::vector<int> figsize = { 20 * slash_interpolator._xy_dist / (param.z1 - param.z0), 20 };
            auto image_generator = std::make_shared<PurseImageGenerator>(figsize, draw_fun, param.image_type);
            auto image_recorder = ImageRecorder(image_generator, colorbar, param.image_folder);
            std::shared_ptr<Visualer> res = std::make_shared<UtVisualer>(u_ncfile_manager, temp_ncfile_manager, image_recorder, zero_value_transformer, slash_interpolator);
            return res;
        }
        else if (param.fea_name == "u") {
            auto ncfile_manager = NcfileManager(param.data_folder, "stateU.*.glob.nc", "U", param.t0, param.t1 + 1);
            auto slash_interpolator = SlashInterpolator(param.x0, param.x1, param.y0, param.y1, param.z0, param.z1);
            std::vector<std::string> colors = { "#67001f", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#f7f7f7", "#d1e5f0", "#92c5de", "#4393c3", "#2166ac", "#053061" };
            auto colorbar = Colorbar(colors, -1.0, 1.0);
            colorbar.save(param.image_folder);
            auto draw_fun = std::make_shared<DrawHeatFrame>(param.zx_aspect, colorbar.get_camp().cmap);
            std::vector<int> figsize = {20 * slash_interpolator._xy_dist / (param.z1 - param.z0), 20};
            auto image_generator = std::make_shared<PurseImageGenerator>(figsize, draw_fun, param.image_type);
            auto image_recorder = ImageRecorder(image_generator, colorbar, param.image_folder);
            std::shared_ptr<Visualer> res = std::make_shared<UvVisualer>(ncfile_manager, image_recorder, slash_interpolator);
            return res;
        }
        else if (param.fea_name == "v") {
            auto ncfile_manager = NcfileManager(param.data_folder, "V.*.glob.nc", "V", param.t0, param.t1 + 1);
            auto slash_interpolator = SlashInterpolator(param.x0, param.x1, param.y0, param.y1, param.z0, param.z1);
            std::vector<std::string> colors = {"#67001f", "#b2182b", "#d6604d", "#f4a582", "#fddbc7", "#f7f7f7", "#d1e5f0", "#92c5de", "#4393c3", "#2166ac", "#053061"};
            auto colorbar = Colorbar(colors, -1.0, 1.0);
            colorbar.save(param.image_folder);
            auto draw_fun = std::make_shared<DrawHeatFrame>(param.zx_aspect, colorbar.get_camp().cmap);
            std::vector<int> figsize = { 20 * slash_interpolator._xy_dist / (param.z1 - param.z0), 20 };
            auto image_generator = std::make_shared<PurseImageGenerator>(figsize, draw_fun, param.image_type);
            auto image_recorder = ImageRecorder(image_generator, colorbar, param.image_folder);
            std::shared_ptr<Visualer> res = std::make_shared<UvVisualer>(ncfile_manager, image_recorder, slash_interpolator);
            return res;
        }
        else {
            LOG_E("no visualer named {0}", param.fea_name);
        }
    }

private:
    DistCalcor _dist_calcor;
};

