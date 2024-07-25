#include "initer.hpp"

int main(int argc, char* argv[]) {
    auto time_recorder = TimeRecorder();
    Initer initer;
    initer.init();
    //multi_process_manager = MultiProcessingManager();
    auto param_reciver = ParamReciver();
    auto param = param_reciver.__call__(argc, argv);
    {
        param.is_success = true;
        param.fea_name = "eta";
        param.t0 = 0;
        param.t1 = 23;
        param.y0 = 60;
        param.y1 = 750;
        param.x0 = 300;
        param.x1 = 1500;
        param.nop = 5;
        param.yx_aspect = 1.76;
        param.image_type;
        param.data_folder = "../data/ISWFM-NSCS-6day";
        param.image_folder = "./output/image_sequence_eta";
    }
    SingleThreadPool = new ThreadPool(param.nop);

    auto visualer_factory = VisualerFactory();
    auto visualer = visualer_factory.__call__(param);
    if (visualer == nullptr) {
        LOG_E("Visualer create failed!, Please check param.");
        return 0;
    }
    auto runer = VisualRuner(visualer);
    runer.run();

    delete SingleThreadPool;
    time_recorder.finish();
    return 0;
}

//isw_visual.exe --data_folder=../../../isw_visual_lcl/data/ISWFM-NSCS-6day --fea_name=temp --nop=5 --image_folder=./output/image_sequence_temp 
//--t0=0 --t1=23 --x0=300 --y0=60 --x1=1500 --y1=750 --zx_aspect=20

//.\bin\vis --data_folder=data\ISWFM-NSCS-6day --fea_name=eta --nop=5 --image_folder=output\image_sequence_eta 
//--t0=0 --t1=23 --x0=300 --y0=60 --x1=1500 --y1=750 --yx_aspect=1.76