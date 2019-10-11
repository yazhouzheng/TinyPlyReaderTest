#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QWidget>
#include <QPushButton>
#include "ui_MainWindow.h"
#include <memory>
#include "PCLDisplay.h"
#include "PlyReader.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

    void initReadPlyButton();
    void initPlyReader();
    void initPCLDisplay();

private:
    Ui::MainWindow ui;
    std::shared_ptr<QPushButton> m_spShowPlyButton;
    std::shared_ptr<PCLDisplay> m_spPclDisplay;
    std::shared_ptr<PlyReader> m_spPlyReader;

public slots:
    void ShowPlyButtonClick();
};
#endif /*_MAIN_WINDOW_H_*/