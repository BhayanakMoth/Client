#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void writeToServerArea(QString qstr);
    bool isReturnPressed();
    void setMessage();
    std::string getMessage();
    void resetReturnPressed();
private slots:
    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    std::string message = "";
    bool isPressed = false;
};

#endif // MAINWINDOW_H
