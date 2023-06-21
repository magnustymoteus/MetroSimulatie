#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int currentImage = 0;
    bool autoPlay = false;

private slots:
    void on_rightArrow_clicked();

    void on_leftArrow_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* myTimer;
};
#endif // MAINWINDOW_H
