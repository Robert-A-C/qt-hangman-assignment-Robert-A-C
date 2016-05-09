#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto vlMain = new QVBoxLayout(ui->centralWidget);
    auto glLetters = new QGridLayout();

    //Letters
    for (char c='a'; c <= 'z'; ++c)
    {
        auto btn = new QPushButton();
        btn->setMinimumSize(20,20);
        btn->setMaximumSize(20,20);
        btn->setText(QString(c));
        glLetters->addWidget(btn, (c - 'a') / 13, (c - 'a') % 13); // c-a is a 0 based index

        connect(btn, &QPushButton::clicked, this,&MainWindow::onLetterClicked);

    }

    vlMain->addLayout(glLetters);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLetterClicked()
{
    // sender must be a QPushButton so
    // downcast is safe
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());

    //update model


    //draw()
    btn->setEnabled(false);
    qWarning() << btn->text();

}
