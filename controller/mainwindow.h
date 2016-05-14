///////////////////////////////////////////////////////////////////////
// File: mainwindow.h
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include <memory>
#include <QString>
#include <map>

namespace Ui {
class MainWindow;

}

class Hangman;
enum class Picture;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void draw(); // draws the view
    void delay(); // delays the end game message so it is viewable
    ~MainWindow();

public slots:
    void onLetterClicked(); // Event when a letter button is clicked
    void onNewPhraseClicked(); // Event when the new phrase button is clicked

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Hangman> _game; // game instance
    const std::map<Picture,QString> _image; // image for the hangman
    std::vector<QPushButton*> letters; // Vector for the button used to established which buttons to disable
    QLabel* labelPicture;
    QLabel* labelPhrase;
};

#endif // MAINWINDOW_H
