#include "include/MyApplication.h"

int main(int argc, char *argv[]) {

    basicQt::MyApplication application(argc, argv);
    application.setup();

    return application.exec();
}
