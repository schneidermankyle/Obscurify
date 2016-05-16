#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog>
#include <QMessageBox>
#include <fstream>
#include <string>

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

// When we click go, we want to loop through the file and edit it as neccessary.
void MainWindow::on_continue_2_clicked()
{    
    if (!ui->lineEdit->text().isEmpty()) {
        // Create a string to hold our new content
        QString content = "";
        std::string path = ui->lineEdit->text().toStdString().substr(0, ui->lineEdit->text().toStdString().find_last_of('/')+1);
        std::string fileName = ui->lineEdit->text().toStdString().substr(ui->lineEdit->text().toStdString().find_last_of('/')+1, ui->lineEdit->text().toStdString().find_last_of('.') - ui->lineEdit->text().toStdString().find_last_of('/')-1);
        std::string extension = ui->lineEdit->text().toStdString().substr(ui->lineEdit->text().toStdString().find_last_of('.'));
        bool keepSpaces = false, ignoreAll = false;
        char buffer;
        int commentType = 0, count = 0;

        // Create a new file stream
        std::fstream fs;
        fs.open(ui->lineEdit->text().toStdString(), std::fstream::in | std::fstream::out);
        if (fs.is_open()) {
            while (!fs.eof()) {
                char holder = fs.get();

                 //If this is a comment, set ignoreAll to true
                if (!ignoreAll) {
                    if (holder == '/' && buffer == holder) {
                        commentType = 1;
                        ignoreAll = true;
                    } else if (holder == '*' && buffer == '/') {
                        commentType = 2;
                        ignoreAll = true;
                    }
                } else {
                    if (commentType == 1 && buffer == '\n') {
                        ignoreAll = false;
                    } else if (commentType == 2 && holder == '/' && buffer == '*') {
                        ignoreAll = false;
                    }
                }

                // Is this a quote? if so we should preserve string integrity
                if (keepSpaces == false && (buffer == '"' || buffer == '\'') ) {
                    keepSpaces = true;
                } else if (keepSpaces == true && (buffer == '"' || buffer == '\'')) {
                    keepSpaces = false;
                }

                //Now we determine if we want to do anything with this actual character
                if (!ignoreAll && count > 0) {
                    if (!keepSpaces){
                        if (buffer != ' ' && buffer != '\n' && buffer != '\t')
                            content += buffer;
                    } else {
                        if (buffer != '\n')
                            content += buffer;
                    }
                }

                buffer = holder;
                count++;
            }
            fs.close();

            // Now time to create the new file
            std::ofstream test(path + fileName + "-min" + extension, std::ios::out);
            if (test << content.toStdString())
                QMessageBox::information(this, tr("Successful"), "Success, your minified file was written into the same directory of your original file.");

        } else {
            QMessageBox::critical(this, tr("Error"), "This file could not be opened, please select a different file or make sure the proper privlidges are assigned to this user.");
        }
    } else {
        QMessageBox::critical(this, tr("Error"), "Please select or enter a valid file path.");
    }

}
