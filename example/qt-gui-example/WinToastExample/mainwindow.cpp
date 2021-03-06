#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <qfiledialog.h>
#include <qmessagebox.h>

#include "../../../src/wintoastlib.h"
using namespace WinToastLib;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    WinToast::instance()->setAppName(L"WinToastExample");
    WinToast::instance()->setAppUserModelId(
                WinToast::configureAUMI(L"mohabouje", L"wintoast", L"wintoastexample", L"20161006"));
    if (!WinToast::instance()->initialize()) {
        qDebug() << "Error, your system in not compatible!";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_imagePathSelector_clicked()
{
    const QString fileName = QFileDialog::getOpenFileName(this, "Select an image", QDir::currentPath(), "*.png");
    if (fileName.isEmpty())
        return;
    ui->imagePath->setText(QDir::toNativeSeparators(fileName));

}

void MainWindow::on_showToast_clicked()
{
    WinToastHandler* handler = new WinToastHandler;
    WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageWithFourLines);
    templ.setImagePath(ui->imagePath->text().toStdWString());
    templ.setTextField(ui->firstLine->text().toStdWString(), 0);
    templ.setTextField(ui->secondLine->text().toStdWString(), 1);
    templ.setTextField(ui->secondLine->text().toStdWString(), 2);

    if (!WinToast::instance()->showToast(templ, handler)) {
        QMessageBox::warning(this, "Error", "Could not launch your toast notification!");
    }
}
