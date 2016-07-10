#include "mainwindow.h"
#include <QApplication>
#include "runguard.h"



int main(int argc, char *argv[])
{
    // запрешаю создавать клон приложения
    // http://stackoverflow.com/questions/5006547/qt-best-practice-for-a-single-instance-app-protection
    RunGuard guard( "some_random_key" );
        if ( !guard.tryToRun() )
            return 0;

        QApplication a(argc, argv);

        MainWindow w;
        w.show();



        return a.exec();
}

