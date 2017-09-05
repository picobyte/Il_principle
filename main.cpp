/*
 * (c) Picobyte 2017, GPL2
 */

#include "mainwindow.h"
#include <QApplication>
#include <PythonQt/PythonQt.h>
#include <Python.h>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);
    MainWindow w;
    // init PythonQt and Python itself
    PythonQt::init();
    //PythonQt_QtAll::init();

    // get a smart pointer to the __main__ module of the Python interpreter
    PythonQtObjectPtr context = PythonQt::self()->getMainModule();

    // add the QApplication to the namespace of the __main__ module
    context.addObject("qapp", &qapp);

    // add an interface to the C++ application to the namespace of the __main__ module
    context.addObject("model", &w);

    // hand control flow over and initialize the Python part of the application
    // this will also execute the Qt main loop
    QDir dir;
    dir.setPath(QCoreApplication::applicationDirPath()+"/../Il_principle/initialize.py");
    context.evalFile(dir.path());

    w.show();

    return qapp.exec();
}
