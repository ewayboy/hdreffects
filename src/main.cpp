#include <unistd.h>
#include <stdexcept>
#include <string>

#include "app.h"
#include "objparser.h"

using namespace std;

int main(int argc, char *argv[]) {
    int width = 800, height = 600, c;
    bool fullscreen = false;

    while((c = getopt(argc, argv, "w:h:f:")) != -1) {
        switch(c) {
        case 'w':
            width = atoi(optarg);
            break;
        case 'h':
            height = atoi(optarg);
            break;
        case 'f':
            fullscreen = atoi(optarg);
            break;
        case '?':
            cerr << "Usage " << argv[0] << " [-w width] [-h height] [-f fullscreen]" << endl;
            return EXIT_FAILURE;
        }
    }

    try {
        Debug::Instance() << "Debug mode" << endl;
        App app(width, height, fullscreen);

        app.Init();
        app.MainLoop();
        Debug::Release();
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
