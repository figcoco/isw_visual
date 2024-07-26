#include "initer.hpp"
#include <string>

void Initer::init() {

    AdLog::Init();
    LOG_I("process start!");
    //////-------------------Ocean_Data---------------------------///////
    // Json::FastWriter writer;
    // auto sapce_data_array = new SpaceDataArray();

    // auto time_data_array = new TimeDataArray(2, 40);
    // auto point_data = new AmpPointData(20, 4);
    // time_data_array->add(point_data);
    // point_data = new AmpPointData(18, 5);
    // time_data_array->add(point_data);
    // sapce_data_array->add(time_data_array);
    
    // time_data_array = new TimeDataArray(3, 40);
    // point_data = new AmpPointData(20, 7);
    // time_data_array->add(point_data);
    // point_data = new AmpPointData(22, 9);
    // time_data_array->add(point_data);
    // sapce_data_array->add(time_data_array);

    // point_data = new AmpPointData(22, 7);
    // sapce_data_array->add_point_data(3, 41, point_data);

    // sapce_data_array->sort();
    // std::string json_file = writer.write(sapce_data_array->json());
    // std::cout << json_file << std::endl;


    //////-----------------------Coord_Generator---------------------/////
    // XyCoordGenerator coordg;
    // auto res = coordg.__call__(1, 5, 10, 9);
    // for (auto i : res) {
    //     for (auto j : i) {
    //         std::cout << j << " ";
    //     }
    //     std::cout << std::endl;
    // }

    //////-----------------------NcFile_Manager---------------------/////
    //NcFileReader reader;
    //reader.__call__();
    //NcFile dataFile("../isw_visual_lcl/data/ISWFM-NSCS-1day/stateEta.0000121320.glob.nc", NcFile::read);
    //for (auto& i : dataFile.getVars()) {
    //    std::string dims;
    //    for (auto& j : i.second.getDims()) {
    //        dims += " " + j.getName();
    //    }
    //    std::cout << i.second.getName() << "  " << dims << std::endl;
    //}
    //Eta   Ny Nx
    //Nx  1696
    //Ny  960
    //NcFile dataFile("../isw_visual_lcl/data/ISWFM-NSCS-6day/stateT.0000076680.glob.nc", NcFile::read);
    //for (auto& i : dataFile.getVars()) {
    //    std::string dims;
    //    for (auto& j : i.second.getDims()) {
    //        dims += " " + j.getName() + " " + std::to_string(j.getSize());
    //    }
    //    std::cout << i.second.getName() << "  " << dims << std::endl;
    //}
    //Temp   Nr Ny Nx
    //Nr  90
    //Nx  1696
    //Ny  960
    //NcFile dataFile("../isw_visual_lcl/data/ISWFM-NSCS-1day/stateU.0000122400.glob.nc", NcFile::read);
    //for (auto& i : dataFile.getDims()) {
    //    std::cout << i.second.getName() << "  " << i.second.getSize() << std::endl;
    //}
    //Nr  90
    //Nx  1696
    //Ny  960
    //iter  1
    //NcFile dataFile("../isw_visual_lcl/data/ISWFM-NSCS-1day/V.0000127800.glob.nc", NcFile::read);
    //for (auto& i : dataFile.getDims()) {
    //    std::cout << i.second.getName() << "  " << i.second.getSize() << std::endl;
    //}
    //for (auto& i : dataFile.getVars()) {
    //    std::cout << i.second.getName() << "  " << i.second.getDimCount() << std::endl;
    //}
    //Nr  90
    //Nx  1696
    //Ny  960
    //iter  1
    //dataFile.close();

    //////-----------------------Visual_Image_Sequence---------------------/////


    //visualer_factory = VisualerFactory();
    //visualer = visualer_factory(param);
    //runer = VisualRuner(visualer);
    //runer.run();

    //////-----------------------Visual_Image_Sequence---------------------/////
    //auto [X, Y] = meshgrid(matplot::iota(-8, .5, +8));
    //auto Z = matplot::transform(X, Y, [](double x, double y)
    //    { double eps = std::nextafter(0.0, 1.0);
    //double R = sqrt(pow(x, 2) + pow(y, 2)) + eps;
    //return sin(R) / R; });
    //matplot::mesh(X, Y, Z);
    //show();// 需要调用show才能显示 return 0; 
    //为了实现在命令窗口（CMD）下画图，我们需要配置一下系统环境变量：自定义安装目录\gnuplot\bin
    
    //////-----------------------easyx   test-------------------------------/////
    //
    //initgraph(640, 480);	// 创建绘图窗口，大小为 640x480 像素
    //circle(200, 200, 100);	// 画圆，圆心(200, 200)，半径 100
    //_getch();				// 按任意键继续
    //closegraph();			// 关闭绘图窗口


    //////-----------------------png2svg------------------------------------/////
    //Aspose::Cells::Startup();
    //Aspose::Cells::Workbook wkb(u"input.png");
    //wkb.Save(u"Output.svg");
    //Aspose::Cells::Cleanup();


    //////-----------------------chartdir------------------------------------/////
    // The x-axis and y-axis labels
    //const char* xLabels[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
    //const int xLabels_size = (int)(sizeof(xLabels) / sizeof(*xLabels));
    //const char* yLabels[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    //const int yLabels_size = (int)(sizeof(yLabels) / sizeof(*yLabels));

    //// Random data for the 10 x 10 cells
    //RanSeries* r = new RanSeries(2);
    //int x_size = xLabels_size * 200;
    //int y_size = yLabels_size * 90;
    //DoubleArray zData = r->get2DSeries(x_size, y_size, -0.01, 0.01);

    //vector_1d datax = linspace(0, x_size, x_size);
    //vector_1d datay = linspace(0, y_size, y_size);

    //// Create an XYChart object of size 520 x 470 pixels.
    //XYChart* c = new XYChart(1040, 940);

    //// Set the plotarea at (50, 30) and of size 400 x 400 pixels.
    //PlotArea* p = c->setPlotArea(75, 40, 800, 800, -1, -1, -1, c->dashLineColor(0x80000000, Chart::DotLine), -1);
    ////PlotArea* p = c->setPlotArea(50, 30, 800, 800);

    //// Create a discrete heat map with 10 x 10 cells
    ////DiscreteHeatMapLayer* layer = c->addDiscreteHeatMapLayer(zData, x_size);
    //// Add a contour layer using the given data
    //ContourLayer* layer = c->addContourLayer(DoubleArray(&datax[0], x_size), DoubleArray(&datay[0],
    //    y_size), zData);
    //

    //// Position the color axis 20 pixels to the right of the plot area and of the same height as the
    //// plot area. Put the labels on the right side of the color axis. Use 8pt Arial Bold font for
    //// the labels.
    //ColorAxis* cAxis = layer->setColorAxis(p->getRightX() + 20, p->getTopY(), Chart::TopLeft,
    //    p->getHeight(), Chart::Right);

    //// Output the chart
    //c->makeChart("discreteheatmap.svg");

    ////free up resources
    //delete r;
    //delete c;

    ////free up resources
    //delete c;

}