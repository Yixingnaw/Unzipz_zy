#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QFileDialog>
#include"unzipzy.h"
#include<thread>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initial_grade(){
    if(ui->A_Z->checkState()==Qt::CheckState::Checked){
        Grade x=Grade::A_Z;
            options.push_back(x);
     }
    if(ui->a_z->checkState()==Qt::CheckState::Checked){
        Grade x=Grade::a_z;
            options.push_back(x);
     }
    if(ui->all_numbers->checkState()==Qt::CheckState::Checked){
        Grade x=Grade::all_numbers;
            options.push_back(x);
     }
    if(ui->all_special_charactors->checkState()==Qt::CheckState::Checked){
        Grade x=Grade::all_special_charactors;
            options.push_back(x);
     }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString path=QFileDialog::getOpenFileName(nullptr,"选择暴力破解文件",".",tr("压缩文件(*.zip,*.RAR)"));
    ui->dir_show_line->setText(path);

}

void MainWindow::on_pushButton_4_clicked()
{
    ui->pushButton_4->setEnabled(false);
    initial_grade();//options初始化
    UnZipZy worker;

}
