#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog>
#include <QDialog>
#include <QMessageBox>
#include <string>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLineEdit *lineEdit;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
   QCoreApplication::quit();
}

void MainWindow::on_Select_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", tr("Javascript Files (*.js)"));
    ui->lineEdit = this->findChild<QLineEdit *>("lineEdit");

    ui->lineEdit->setText(fileName);
}

void MainWindow::on_continue_2_clicked()
{
    char test[50];
    std::fstream fs;
    fs.open(ui->lineEdit->text().toStdString(), std::fstream::in | std::fstream::out);
    fs.getline(test, 50);
    fs.close();

    QMessageBox::information(this, tr("test"), test);


}
