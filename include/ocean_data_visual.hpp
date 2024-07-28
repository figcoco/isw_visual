#pragma once

#include <vector>
#include <iostream>
#include <filesystem>
#include <string>
#include <NumCpp.hpp>
#include <ncfile_manager.hpp>
#include <cmath> 
#include <matplot/matplot.h> 
#include <chartdir_plot.hpp>

namespace fs = std::filesystem;
using namespace matplot;

static std::map<std::string, image_interpolation> interpolation_map = { {"raw", image_interpolation::raw},
                                                                        {"additional_space", image_interpolation::additional_space},
                                                                        {"nearest", image_interpolation::nearest},
                                                                        {"moving_average", image_interpolation::moving_average},
                                                                        {"bilinear", image_interpolation::bilinear},
                                                                        {"grid", image_interpolation::grid},
                                                                        {"bicubic", image_interpolation::bicubic},
                                                                        {"lanczos", image_interpolation::lanczos},
                                                                        {"", image_interpolation::bicubic} };


class ColorbarMode {
public:
    ColorbarMode() = default;
    virtual void _add() {
    }
	virtual void __call__() {
	}
};

class NoneColorBar : public ColorbarMode {
public:
    NoneColorBar() = default;
    virtual void _add() {
    }
};

struct Color {
    float r;
    float g;
    float b;
    int int_color;
};

struct LinearColorMap {
    std::string title;
    std::vector<Color> colors;
    std::vector<std::vector<double>> cmap;
    std::vector<int> int_color_map;

    //LinearColorMap() {
    //    title = "";
    //    colors = {};
    //    cmap = {};
    //    int_color_map = {};
    //}

    //LinearColorMap operator=(LinearColorMap& a) {
    //    title = a.title;
    //    colors = a.colors;
    //    cmap = a.cmap;
    //    int_color_map = a.int_color_map;
    //}

    //LinearColorMap(std::string title, std::vector<Color> colors, std::vector<std::vector<double>> cmap, std::vector<int> int_color_map) {
    //    this->title = title;
    //    this->colors = colors;
    //    this->cmap = cmap;
    //    this->int_color_map = int_color_map;
    //}
};


class DrawFun {
public:
    virtual XYChart* __call__(tri_matrix frame, float vmin = 0.0f, float vmax = 0.0f) {
        return nullptr;
    }
};

class ImageGenerator {
public:
    ImageGenerator(std::vector<int> figsize, 
                    std::shared_ptr<DrawFun> draw_fun, 
                    int fontsize, 
                    std::shared_ptr<ColorbarMode> colorbar_mode, 
                    std::string image_format = "svg") {
        _figsize = figsize;
        _draw_fun = draw_fun;
        _fontsize = fontsize;
        _image_format = image_format;
        _colorbar_mode = colorbar_mode;
    }

    virtual void _draw(tri_matrix& data, std::string image_folder, std::string image_name, std::string title, float vmin, float vmax) {

    }

    virtual void set_draw_fun(std::shared_ptr<DrawFun> draw_fun) {
        _draw_fun = draw_fun;
    }

    virtual void __call__(tri_matrix& data, std::string image_folder, std::string image_name, std::string title = "", float vmin = 0.0f, float vmax = 0.0f) {

        CreateFolder(image_folder);
        //todo
        //  plt.rcParams.update({"font.size": self._fontsize})
        _draw(data, image_folder, image_name, title, vmin, vmax);
        //  plt.cla()                   clear()
        cla();
        //  plt.close()
    }

protected:
    std::vector<int> _figsize;
    std::shared_ptr<DrawFun> _draw_fun;
    int _fontsize;
    std::shared_ptr<ColorbarMode> _colorbar_mode;
    std::string _image_format;

};

class AxesClearer {
public:
    void __call__(axes_handle ax) {
        ax->clear();
        ax->visible(false);
    }
};

class PurseImageGenerator : public ImageGenerator {
public:
    PurseImageGenerator() = default;
    PurseImageGenerator(std::vector<int> figsize, std::shared_ptr<DrawFun> draw_fun, std::string image_format = "svg") 
        : ImageGenerator(figsize, draw_fun, 0, std::make_shared<NoneColorBar>(), image_format) {
        //auto f = figure<backend::opengl>(true);
        auto f = figure(true);
        figure(f);
    }
    std::string replace(std::string str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
        return str;
    }

    virtual void _draw(tri_matrix& data, std::string image_folder, std::string image_name, std::string title = "", float vmin = 0.0f, float vmax = 0.0f) {
        XYChart* image = _draw_fun->__call__(data, vmin, vmax);

        image_name = image_name + "." + _image_format;
        auto ab_path = (fs::absolute(image_folder) / fs::path(image_name)).string();
        auto path = replace(ab_path, "\\", "/");

        image->makeChart(path.c_str());
        delete image;
    }
private:
    AxesClearer _axes_clearer;
};

class HccExtentGenerator {
public:
    virtual std::vector<int> __call__(tri_matrix frame) {
        return {};
    }
};

class NoneExtentGenerator : public HccExtentGenerator {
public:
    virtual std::vector<int> __call__(tri_matrix frame) {
        return { 0, 0, 0, 0 };
    }
};

class HeatExtentGenerator : public HccExtentGenerator {
public:
    virtual std::vector<int> __call__(tri_matrix frame) {
        //        extent = [0, frame.shape[1], 0, frame.shape[0]]
        return { 0, static_cast<int>(frame[0][0].size()), 0, static_cast<int>(frame[0].size()) };
    }
};

class ContourExtentGenerator : public HccExtentGenerator {
public:
    virtual std::vector<int> __call__(tri_matrix frame) {
        //        extent = [0, frame.shape[1], frame.shape[0], 0]
        return { 0, static_cast<int>(frame[0][0].size()), static_cast<int>(frame[0].size()), 0 };
    }
};


class ContourLevelsGenerator {
public:
    ContourLevelsGenerator() = default;
    ContourLevelsGenerator(int level_num) {
        _level_num = level_num;
    }

    std::vector<double> __call__(float vmin, float vmax) {
        if (vmin < 0 || vmax < 0) {
            return {};
        }
        if (vmin == vmax) {
            return {};
        }
        return linspace(vmin, vmax);
    }
private:
    int _level_num;
};

class FrameAdder {
public:
    FrameAdder() = default;
    FrameAdder(float image_alpha, std::shared_ptr<HccExtentGenerator> extent_generator) {
        _image_alpha = image_alpha;
        _extent_generator = extent_generator;
    }

    virtual XYChart* __call__(tri_matrix frame, float vmin, float vmax) {
        return nullptr;
    }
protected:
    float _image_alpha;
    std::shared_ptr<HccExtentGenerator> _extent_generator;
};

class HeatFrameAdder : public FrameAdder {
public:
    HeatFrameAdder() = default;
    HeatFrameAdder(float image_alpha, float aspect, std::shared_ptr<LinearColorMap> cmap = nullptr, std::string interpolation = "")
        : FrameAdder(image_alpha, std::make_shared<HeatExtentGenerator>()) {
            _aspect = aspect;
            _interpolation = interpolation;
            _cmap = cmap;
    }
    virtual XYChart* __call__(tri_matrix frame, float vmin, float vmax) override {
        auto extent = _extent_generator->__call__(frame);

        std::vector<double> x = linspace(0, frame[0].size(), frame[0].size());
        std::vector<double> y = linspace(0, frame[0][0].size(), frame[0][0].size());

        tri_matrix_d frame_d;
        for (int i = 0; i < min(int(frame.size()), 3); i++) {
            std::vector<std::vector<double>> vec_2d;
            for (auto& j : frame[i]) {
                std::vector<double> vec_1d;
                for (auto& k : j) {
                    vec_1d.push_back(static_cast<double>(k));
                }
                vec_2d.push_back(vec_1d);
            }
            frame_d.push_back(vec_2d);
        }


        //todo
        //, _image_alpha, _aspect, extent, vmin, vmax);


        float value_field = vmax - vmin;
        std::vector<double> colormap;
        if (_cmap != nullptr) {
            for (int i = 0; i < _cmap->colors.size() - 1; i++) {
                double value = vmin + (i * value_field) / (_cmap->colors.size() - 1);
                double color_d = static_cast<double>(_cmap->colors[i].int_color);
                colormap.push_back(value);
                colormap.push_back(color_d);
            }
            colormap.push_back(vmax);
            colormap.push_back(static_cast<double>((_cmap->colors.end() - 1)->int_color));
        }

        XYChart* image = Rendering::paint_heat_map(x, y, frame_d, colormap);
        //image(ax, frame_d[0], true);
        if (_image_alpha != 0) {
            return image;
        }
        else return nullptr;
    }
    
    image_interpolation get_interpolation(std::string key) {
        auto iter = interpolation_map.find(key);
        if (iter != interpolation_map.end()) {
            return iter->second;
        }
        return interpolation_map[""];
    }
protected:
    float _aspect;
    std::shared_ptr<LinearColorMap> _cmap;
    std::string _interpolation;
};

class NoneFrameAdder : public FrameAdder {
public:
    NoneFrameAdder() 
        : FrameAdder(0.0, std::make_shared<NoneExtentGenerator>()){
    }
    virtual XYChart* __call__(tri_matrix frame, float vmin, float vmax) override {
        return nullptr;
    }
};

class NoneHeatFrameAdder : public HeatFrameAdder {
public:
    NoneHeatFrameAdder() = default;
    NoneHeatFrameAdder(float aspect) 
        : HeatFrameAdder(0.0f, 0.0f) {
        _aspect = aspect;
        _interpolation = "";
    }
};

class ContourfFrameAdder : public FrameAdder {
public:
    ContourfFrameAdder() = default;
    ContourfFrameAdder(float image_alpha, int level_num, std::shared_ptr<LinearColorMap> cmap)
        : FrameAdder(image_alpha, std::make_shared<ContourExtentGenerator>()) {
        _levels_generator = ContourLevelsGenerator(level_num);
        _cmap = cmap;
    }

    virtual XYChart* __call__(tri_matrix frame, float vmin, float vmax) override {
        if (_image_alpha != 0) {
            auto extent = _extent_generator->__call__(frame);
            auto levels = _levels_generator.__call__(vmin, vmax);
            //todo
            //extent, _image_alpha);
            std::vector<double> x = linspace(0, frame[0].size(), frame[0].size());
            std::vector<double> y = linspace(0, frame[0][0].size(), frame[0][0].size());
            tri_matrix_d frame_d;
            for (int i = 0; i < min(int(frame.size()), 3); i++) {
                std::vector<std::vector<double>> vec_2d;
                for (auto& j : frame[i]) {
                    std::vector<double> vec_1d;
                    for (auto& k : j) {
                        vec_1d.push_back(static_cast<double>(k));
                    }
                    vec_2d.push_back(vec_1d);
                }
                frame_d.push_back(vec_2d);
            }

            float value_field = vmax - vmin;
            std::vector<double> colormap;
            if (_cmap != nullptr) {
                for (int i = 0; i < _cmap->colors.size() - 1; i++) {
                    double value = vmin + (i * value_field) / (_cmap->colors.size() - 1);
                    double color_d = static_cast<double>(_cmap->colors[i].int_color);
                    colormap.push_back(value);
                    colormap.push_back(color_d);
                }
                colormap.push_back(vmax);
                colormap.push_back(static_cast<double>((_cmap->colors.end() - 1)->int_color));
            }

            XYChart* image = Rendering::paint_contour(x, y, frame_d, colormap);
            return image;
        }
        else {
            return nullptr;
        }
    }

private:
    ContourLevelsGenerator _levels_generator;
    std::shared_ptr<LinearColorMap> _cmap;
};


class ContourFrameAdder : public FrameAdder {
public:
    ContourFrameAdder() = default;
    ContourFrameAdder(float image_alpha, std::string color, int level_num) 
        : FrameAdder(image_alpha, std::make_shared<ContourExtentGenerator>()) {
        _levels_generator = ContourLevelsGenerator(level_num);
        _color = color;
        _level_num = level_num;
    }
    virtual XYChart* __call__(tri_matrix frame, float vmin, float vmax) override {
        auto extent = _extent_generator->__call__(frame);
        auto levels = _levels_generator.__call__(vmin, vmax);
        //todo
        //gcf()->size(frame[0].size(), frame[0][0].size());
        vector_1d x = linspace(0, frame[0][0].size(), frame[0][0].size());
        vector_1d y = linspace(0, frame[0].size(), frame[0].size());
        tri_matrix_d frame_d;
        for (int i = 0; i < min(int(frame.size()), 3); i++) {
            std::vector<std::vector<double>> vec_2d;
            for (auto& j : frame[i]) {
                std::vector<double> vec_1d;
                for (auto& k : j) {
                    vec_1d.push_back(static_cast<double>(k));
                }
                vec_2d.push_back(vec_1d);
            }
            frame_d.push_back(vec_2d);
        }
        //auto [X, Y] = meshgrid(x, y);
        //contour(ax, X, Y, frame[0], levels)->color("black");
        // extent, _image_alpha);
        if (_image_alpha != 0) {
            return nullptr;
        }
        return nullptr;
    }
private:
    ContourLevelsGenerator _levels_generator;
    std::string _color;
    int _level_num;
};

class DrawHccFrameTemplate : public DrawFun {
public:
    DrawHccFrameTemplate() = default;
    DrawHccFrameTemplate(std::shared_ptr<HeatFrameAdder> heat_image_adder, std::shared_ptr<FrameAdder> contourf_image_adder, std::shared_ptr<FrameAdder> contour_image_adder) {
        _heat_image_adder = heat_image_adder;
        _contourf_image_adder = contourf_image_adder;
        _contour_image_adder = contour_image_adder;
    }

    virtual void set_values(std::shared_ptr<HeatFrameAdder> heat_image_adder, std::shared_ptr<FrameAdder> contourf_image_adder, std::shared_ptr<FrameAdder> contour_image_adder) {
        _heat_image_adder = heat_image_adder;
        _contourf_image_adder = contourf_image_adder;
        _contour_image_adder = contour_image_adder;
    }

    virtual XYChart* __call__(tri_matrix frame, float vmin, float vmax) override {
        auto heat_image = _heat_image_adder->__call__(frame, vmin, vmax);
        auto contourf_image = _contourf_image_adder->__call__(frame, vmin, vmax);
        auto contour_image = _contour_image_adder->__call__(frame, vmin, vmax);
        //todo
        auto image = heat_image;
        //auto image = heat_image or contourf_image;
        return image;
    }

protected:
    std::shared_ptr<HeatFrameAdder> _heat_image_adder;
    std::shared_ptr<FrameAdder> _contourf_image_adder;
    std::shared_ptr<FrameAdder> _contour_image_adder;
};
 
// HCC: heat, courtourf and courtour, composition

class DrawHcFrame : public DrawHccFrameTemplate {
public:
    DrawHcFrame(int level_num, float aspect = 1, std::shared_ptr<LinearColorMap> cmap = nullptr, std::string heat_interpolation = "", std::string contour_color = "black") {
        auto heat_image_adder = std::make_shared <HeatFrameAdder>(1.0, aspect, cmap, heat_interpolation);
        auto contourf_image_adder = std::make_shared<NoneFrameAdder>();
        auto contour_image_adder = std::make_shared <ContourFrameAdder>(1.0, contour_color, level_num);
        set_values(heat_image_adder, contourf_image_adder, contour_image_adder);
    }
};

class DrawHeatFrame : public DrawHccFrameTemplate {
public:
    DrawHeatFrame(float aspect = 1, std::shared_ptr<LinearColorMap> cmap = nullptr, std::string heat_interpolation = "") {
        auto heat_image_adder = std::make_shared <HeatFrameAdder>(1.0, aspect, cmap, heat_interpolation);
        auto contourf_image_adder = std::make_shared<NoneFrameAdder>();
        auto contour_image_adder = std::make_shared<NoneFrameAdder>();
        set_values(heat_image_adder, contourf_image_adder, contour_image_adder);
    }
};

class DrawCcFrame : public DrawHccFrameTemplate {
    //CC: contourf and contour
public:
    DrawCcFrame(int level_num, float aspect = 1, std::shared_ptr<LinearColorMap> cmap = nullptr, std::string contour_color = "black") {
        auto heat_image_adder = std::make_shared <NoneHeatFrameAdder>(aspect);
        auto contourf_image_adder = std::make_shared<ContourfFrameAdder>(1.0, level_num, cmap);
        auto contour_image_adder = std::make_shared<ContourFrameAdder>(1.0, contour_color, level_num);
        set_values(heat_image_adder, contourf_image_adder, contour_image_adder);
    }
};

class DrawDoubleHcFrame : public DrawHccFrameTemplate {
    //    # HC: heat and contour
public:
    DrawDoubleHcFrame(int level_num, float aspect = 1, std::shared_ptr<LinearColorMap> cmap = nullptr, std::string heat_interpolation = "", std::string contour_color = "black") {
        auto heat_image_adder = std::make_shared <HeatFrameAdder>(1.0, aspect, cmap, heat_interpolation);
        auto contourf_image_adder = std::make_shared<NoneFrameAdder>();
        auto contour_image_adder = std::make_shared<ContourFrameAdder>(1.0, contour_color, level_num);
        set_values(heat_image_adder, contourf_image_adder, contour_image_adder);
    }

    virtual XYChart* __call__(tri_matrix frame, float vmin, float vmax) {
        auto heat_frame = frame;
        auto contour_frame = frame;
        auto heat_image = _heat_image_adder->__call__(heat_frame, vmin, vmax);
        auto contourf_image = _contourf_image_adder->__call__(contour_frame, vmin, vmax);
        //todo
        //_contour_image_adder->__call__(contour_frame, ax, min(contour_frame), max(contour_frame));
        //todo
        //image = heat_image or contourf_image
        return heat_image;
    }
};

