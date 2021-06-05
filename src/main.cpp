#include <QApplication>
#include <application/Application.hpp>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    application::Application app;
    app.startApplication();

    return a.exec();
}
