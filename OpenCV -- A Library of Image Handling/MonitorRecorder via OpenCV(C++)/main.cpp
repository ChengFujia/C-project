#include "monitor.hpp"

Ptr<BackgroundSubtractor> pMOG;
Ptr<BackgroundSubtractor> pMOG2;
int keyboard;

char recordName[128];

void help()
{
    cout<< "----------------------------------------------------------------------------\n"
        << "Usage:                                                                      \n"
        << " ./MonitorRecorder.exe [VIS] [MODE] [FPS] [THRESHOLD] [OUTPUTFILE]          \n"
        << "   [VIS]  : use -vis to show the monitor window, or it will run background. \n"
        << "   [MODE] : -src   shows the original frame;                                \n"
        << "            -mog1       shows the MOG frame;                                \n"
        << "            -mog2      shows the MOG2 frame.                                \n"
        << "   [FPS]  : set the fps of record file, default is 24.                      \n"
        << "   [THRESHOLD]                                                              \n"
        << "          : set the number x that the monitor will start recording after    \n"
        << "            x unnormal frames passed.                                       \n"
        << "   [OUTPUTFILE]                                                             \n"
        << "          : assign the output recording file. It must be .avi format.       \n"
        << "----------------------------------------------------------------------------\n";
}

int main(int argc,char* argv[])
{
    bool showWindow = false;
    unsigned int method =0,unnormal = 10,fps =24;
    if(argc > 6)
    {
        cerr << "Invalid Parameters,Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    if(argc >=2)
    {
        if(strcmp(argv[1],"-vis") == 0)
            showWindow = true;
        if(strcmp(argv[1],"-h") == 0 ||
            strcmp(argv[1],"--help")==0)
        {
            help();
            exit(EXIT_SUCCESS);
        }
    }
    if(argc >=3)
    {
        if(strcmp(argv[2],"-mog2") == 0)
            method = 0;
        if(strcmp(argv[2],"-mog1") == 0)
            method = 1;
        if(strcmp(argv[2],"-src") == 0)
            method = 2;
    }
    if(argc >=4)
    {
        // STRING 2 INT
        int param = stoi(argv[3],nullptr,10);
        if(param <= 10)
            fps = 24;
        else
            fps = param;
    }
    if(argc >=5)
    {
        int param = stoi(argv[4],nullptr,10);
        if(param <= 0)
            unnormal = 10;
        else
            unnormal = param;
    }

    if(argc >= 6)
        strcpy(recordName,argv[5]);
    else
    {
        // set record video file name
        time_t t = time(NULL);
        sprintf(recordName,"%d.avi",int(t));
    }

    cout << "Starts After 2s..." << endl;
    sleep(2);
    if(showWindow)
        namedWindow("Monitor");

    pMOG = new BackgroundSubtractorMOG();
    pMOG2 = new BackgroundSubtractorMOG2();

    processCamera(showWindow,method,unnormal,fps);

    destroyAllWindows();
    return EXIT_SUCCESS;
}