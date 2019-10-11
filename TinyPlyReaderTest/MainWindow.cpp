#include "MainWindow.h"
#include <memory>
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
    m_spShowPlyButton(nullptr),
    m_spPclDisplay(nullptr),
    m_spPlyReader(nullptr)
{
    ui.setupUi(this);
    initReadPlyButton();
    initPCLDisplay();
    initPlyReader();
}

void MainWindow::initReadPlyButton()
{
    m_spShowPlyButton = std::make_shared<QPushButton>(this);
    m_spShowPlyButton->setGeometry(this->width()*0.05, this->height()*0.1, this->width()*0.05, this->height()*0.025);
    m_spShowPlyButton->setText("TestPly");
    connect(m_spShowPlyButton.get(), SIGNAL(clicked()), this, SLOT(ShowPlyButtonClick()));
}

void MainWindow::initPlyReader()
{
    m_spPlyReader = std::make_shared<PlyReader>(m_spPclDisplay);
}

void MainWindow::ShowPlyButtonClick()
{
    m_spPlyReader->ReadPlyFile("test.ply");
}

void MainWindow::initPCLDisplay()
{
    m_spPclDisplay = std::make_shared<PCLDisplay>(this);
    m_spPclDisplay->setGeometry(this->width()*0.3, this->height()*0, this->width()*0.7, this->height()*1.0);
}

MainWindow::~MainWindow()
{
}