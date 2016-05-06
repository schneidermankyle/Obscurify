#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    QLineEdit *lineEdit = this->findChild<QLineEdit *>("lineEdit");

    lineEdit->setText(fileName);
}
