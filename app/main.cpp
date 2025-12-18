#include <libs/ui/includes/mainwindow.h>
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set application-wide font
    QFont font("Segoe UI", 10);
    app.setFont(font);

    MainWindow window;
    window.show();

    return app.exec();
}
