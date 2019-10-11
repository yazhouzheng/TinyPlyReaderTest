#include "PCLDisplay.h"
#include <gl/GLU.h>

PCLDisplay::PCLDisplay(QWidget* parent) 
    :QOpenGLWidget(parent)
    , m_pPositions(nullptr)
    , m_pColors(nullptr)
    , m_pointSize(0)
{
}

PCLDisplay::~PCLDisplay()
{
}
void PCLDisplay::SendPointCloud(float* pPositions, unsigned char* pColors, size_t pointSize)
{
    if (pPositions == nullptr || pColors == nullptr || pointSize < 0)
    {
        return;
    }
    m_pPositions = pPositions;
    m_pColors    = pColors;
    m_pointSize  = pointSize;
    update();
}

void PCLDisplay::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void PCLDisplay::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, this->width(), this->height());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)this->width() / (float)this->height(), 0.1f, 2000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 500, 0, 0, 0, -1, 0, 0);

    glPointSize(1.0f);
    glBegin(GL_POINTS);
    m_mutex.lock();
    for (int i = 0; i < m_pointSize * 3; i = i + 3)
    {
        glVertex3f(m_pPositions[i], m_pPositions[i + 1], m_pPositions[i + 2]);
        glColor3f(m_pColors[i] / 256.0f, m_pColors[i + 1] / 256.0f, m_pColors[i + 2] / 256.0f);
    }
    m_mutex.unlock();
    glEnd();
}