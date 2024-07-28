#pragma once
#include "chartdir.h"
#include <string>
#include <vector>
#include "ncfile_manager.hpp"

class Rendering {
public:
    static XYChart* paint_heat_map(std::vector<double> dataX, std::vector<double> dataY, tri_matrix_d data, std::vector<double>& cmap)
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

        // Create an XYChart object of size width x height pixels.
        XYChart* c = new XYChart(width + 200, height + 200);

        // Set the plotarea at (0, 0) and of size width x height pixels.
        //PlotArea* p = c->setPlotArea(30, 50, height, width);
        PlotArea* p = c->setPlotArea(30, 50, width, height, -1, -1, -1, c->dashLineColor(0x80000000, Chart::DotLine), -1);
        
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



    static XYChart* paint_contour(std::vector<double> dataX, std::vector<double> dataY, tri_matrix_d data, std::vector<double>& cmap)
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

        // Create a XYChart object of size 600 x 500 pixels
        XYChart* c = new XYChart(width, height);

        // Set the plotarea at (0, 0) and of size width x height pixels. Use semi-transparent black
        // (80000000) dotted lines for both horizontal and vertical grid lines
        c->setPlotArea(0, 0, width, height, -1, -1, -1, c->dashLineColor(0x80000000, Chart::DotLine), -1);

        // Add a contour layer using the given data
        ContourLayer* layer = c->addContourLayer(DoubleArray(&dataX[0], dataX.size()), DoubleArray(&dataY[0],
            dataY.size()), zData);

        // Add a color axis (the legend) in which the top left corner is anchored at (505, 40). Set the
        // length to 400 pixels and the labels on the right side.
        ColorAxis* cAxis = layer->setColorAxis(505, 40, Chart::TopLeft, 400, Chart::Right);

        DoubleArray colorArray(&cmap[0], cmap.size());
        cAxis->setColorScale(colorArray);

        return c;

    }
};

