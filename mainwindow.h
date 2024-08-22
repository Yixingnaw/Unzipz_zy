#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vector>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class UnZipZy;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum class Grade
    {
        A_Z=1,
        a_z,
        all_numbers,
        all_special_charactors
    };
    void initial_grade();
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;


    std::vector<Grade> options;
    int charator_numbers;//字符数
    int thrads;//线程数

};
#endif // MAINWINDOW_H
