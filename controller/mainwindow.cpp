///////////////////////////////////////////////////////////////////////
// File: mainwindow.cpp
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../model/hangman.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _image({ {Picture::ONE, "border-image:url(:/images/gallows0.png)"}, // images for hangman numbers correspond with how many wrong guesses
{Picture::TWO, "border-image:url(:/images/gallows1.png)"},
{Picture::THREE, "border-image:url(:/images/gallows2.png)"},
{Picture::FOUR, "border-image:url(:/images/gallows3.png)"},
{Picture::FIVE, "border-image:url(:/images/gallows4.png)"},
{Picture::SIX, "border-image:url(:/images/gallows5.png)"},
{Picture::SEVEN,"border-image:url(:/images/gallows6.png)"}})
{
    ui->setupUi(this);
    _game = std::unique_ptr<Hangman>(new Hangman()); // Instance of Hangman

    auto vlMain = new QVBoxLayout(ui->centralWidget); // Layouts
    auto glLetters = new QGridLayout();
    auto hlTop = new QHBoxLayout();
    auto hlPhrase = new QHBoxLayout();
    auto hlNewButton = new QHBoxLayout();

    labelPicture = new QLabel(); // Label to show picture
    labelPicture->setMaximumSize(300,300);
    labelPicture->setMinimumSize(300,300);

    // Creates letters a - z
    for (char c='a'; c <= 'z'; ++c)
    {
        auto btn = new QPushButton(); // creates new button for each letter
        btn->setMinimumSize(20,20);   // sets min size
        btn->setMaximumSize(20,20);   // sets max size
        btn->setText(QString(c));     // assigns the current letter of the loop (a thourgh z) to the button text

        glLetters->addWidget(btn, (c - 'a') / 13, (c - 'a') % 13); // c-a is a 0 based index

        connect(btn, &QPushButton::clicked, this,&MainWindow::onLetterClicked); // connects the letter buttons to the function

        letters.push_back(btn);
    }

    hlTop->addWidget(labelPicture); // adds label to the layout

    QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);
    hlTop->addSpacerItem(spacer);
    hlTop->addLayout(glLetters);

    vlMain->addLayout(hlTop);

    QSpacerItem *spacer1 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);

    labelPhrase = new QLabel;  // Label for the Phrase
    labelPhrase->setMaximumSize(350,30);
    labelPhrase->setMinimumSize(350,30);
    labelPhrase->setFrameStyle(QFrame::NoFrame);

    hlPhrase->addWidget(labelPhrase);
    hlPhrase->addSpacerItem(spacer1);

    vlMain->addLayout(hlPhrase);

    QSpacerItem *spacer2 = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed);

    auto btnNewPhrase= new QPushButton();
    btnNewPhrase->setMaximumSize(100,25);
    btnNewPhrase->setMaximumSize(100,25);
    btnNewPhrase->setText(QString("New Phrase"));


    hlNewButton->addSpacerItem(spacer2);
    hlNewButton->addWidget(btnNewPhrase);

    connect(btnNewPhrase, &QPushButton::clicked, this, &MainWindow::onNewPhraseClicked);

    vlMain->addLayout(hlNewButton);
    _game->newPhrase();
    QString word = QString::fromStdString(_game->workingPhrase());
    labelPhrase->setText(word);


    draw();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{

    QString word = QString::fromStdString(_game->workingPhrase());

    labelPhrase->setText(word);

    labelPicture->setStyleSheet(_image.at(_game->show()));

    for (auto btn : letters)
    {
        QString letter = btn->text();
        std::string lguess = letter.toLocal8Bit().constData();
        char c = lguess.at(0);

        if(_game->hasBeenGuessed(c))
        {
            btn->setEnabled(false);
        }
        else
        {
            btn->setEnabled(true);
        }
    }
    static bool endWindow = false;

    if(_game->isWon() && !endWindow)
    {
        endWindow = true;
        QMessageBox endMessage;
        endMessage.setText("You win");
        endMessage.show();
        delay();
    }
    if(!_game->isWon())
    {
        endWindow = false;
    }

    if(_game->isLost())
    {
        QString word = QString::fromStdString(_game->getPhrase());
        labelPhrase->setText(word);
        endWindow = true;
        QMessageBox endMessage;
        endMessage.setText("You lose");
        endMessage.show();
        delay();
    }
}

void MainWindow::onLetterClicked()
{
    // sender must be a QPushButton so
    // downcast is safe
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());

    //update model
    QString letter = btn->text();
    std::string lguess = letter.toLocal8Bit().constData();
    char c = lguess.at(0);
    _game->guess(c);


    draw();
}

void MainWindow::onNewPhraseClicked()
{
    _game->newPhrase();
    draw();
}

void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(3);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
