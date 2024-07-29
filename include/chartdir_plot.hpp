#pragma once
#include "chartdir.h"
#include <string>
#include <vector>
#include "ncfile_manager.hpp"

class Rendering {
public:
    static XYChart* paint_heat_map(std::vector<double>& dataX, std::vector<double>& dataY, tri_matrix_d data, std::vector<double>& cmap, float alpha, float aspect)
    {
        int width = dataX.size();
        int height = dataY.size();
        int data_size = width * height;
        double* data_d = new double[width * height];
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                data_d[i + j * width] = data[0][i][j];
            }
        }
        DoubleArray zData(data_d, data_size);

        height = width * aspect;
        // Create an XYChart object of size width x height pixels.
        XYChart* c = new XYChart(width + 200, height + 200);

        // Set the plotarea at (0, 0) and of size width x height pixels.
        //PlotArea* p = c->setPlotArea(30, 50, height, width);
        PlotArea* p = c->setPlotArea(30, 60, width, height, -1, -1, -1, c->dashLineColor(0x80000000, Chart::DotLine), -1);
        
        // Add a contour layer using the given data
        ContourLayer* layer = c->addContourLayer(DoubleArray(&dataX[0], dataX.size()), DoubleArray(&dataY[0], dataY.size()), zData);
        
        // Position the color axis 20 pixels to the right of the plot area and of the same height as the
        // plot area. Put the labels on the right side of the color axis. Use 8pt Arial Bold font for
        // the labels.
        ColorAxis* cAxis = layer->setColorAxis(p->getRightX() + 20, p->getTopY(), Chart::TopLeft,
            p->getHeight(), Chart::Right);
        DoubleArray colorArray(&cmap[0], cmap.size());
        cAxis->setColorScale(colorArray);

        return c;

    }



    static XYChart* paint_contour(std::vector<double>& dataX, std::vector<double>& dataY, tri_matrix_d data, std::vector<double>& cmap, float alpha, std::vector<double>& levels)
    {
        int width = dataX.size();
        int height = dataY.size();
        int dataZ_size = width * height;
        double* dataZ_d = new double[width * height];
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                dataZ_d[i + j * width] = data[0][i][j];
            }
        }
        DoubleArray zData(dataZ_d, dataZ_size);

        width = std::max(width, height);
        height = std::max(width, height);
        // Create a XYChart object of size height x width pixels
        XYChart* c = new XYChart(width + 200, height + 200);

        // Set the plotarea at (0, 0) and of size height x width pixels. Use semi-transparent black
        // (80000000) dotted lines for both horizontal and vertical grid lines
        PlotArea* p = c->setPlotArea(30, 60, width, height, -1, -1, -1, c->dashLineColor(0x80000000, Chart::DotLine), -1);

        // Add a contour layer using the given data
        ContourLayer* layer = c->addContourLayer(DoubleArray(&dataX[0], dataX.size()), DoubleArray(&dataY[0],
            dataY.size()), zData);

        ColorAxis* cAxis = layer->setColorAxis(p->getRightX() + 20, p->getTopY(), Chart::TopLeft,
            p->getHeight(), Chart::Right);

        DoubleArray colorArray(&cmap[0], cmap.size());
        cAxis->setColorScale(colorArray);

        return c;

    }
};

