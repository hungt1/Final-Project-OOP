#include "GUI/LoginGUI.h"
#include <QApplication>

QVBoxLayout* UserGUI::historyPanel = nullptr;
QVBoxLayout* AdminGUI::problemSetPanel = nullptr;
QVBoxLayout* AdminGUI::contestsPanel = nullptr;
QWidget* AdminGUI::current_panel = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("Ứng dụng thi bằng lái");
    QCoreApplication::setOrganizationName("Ứng dụng thi bằng lái");
    LoginGUI w;
    w.setWindowTitle("Ứng dụng thi bằng lái"); w.show();
    return a.exec();
}
