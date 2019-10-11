#include "PCLDisplay.h"
#include <gl/GLU.h>

PCLDisplay::PCLDisplay(QWidget* parent) 
    :QOpenGLWidget(parent)
{
    m_vecPoints.clear();
}

PCLDisplay::~PCLDisplay()
{
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

    for (int i = 0; i < m_vecPoints.size(); i++)
    {
        STPoint stPoint = m_vecPoints.at(i);
        glColor3f(stPoint.vecColor.b, stPoint.vecColor.g, stPoint.vecColor.r);
        glVertex3f(stPoint.vecPos.x, stPoint.vecPos.y, -stPoint.vecPos.z);
    }
    m_mutex.unlock();

    glEnd();
}

int PCLDisplay::SendPointCloud(float* Xi_pPositions, unsigned char *Xi_pColors, size_t Xi_pointSize)
{
    if (Xi_pPositions == nullptr ||
        Xi_pColors == nullptr ||
        Xi_pointSize < 0)
    {
        return -1;
    }

    STPoint stPoint;

    m_mutex.lock();

    m_vecPoints.clear();

    for (int i = 0; i < Xi_pointSize * 3; i = i + 3)
    {
        stPoint.vecPos = Vec3f(Xi_pPositions[i], Xi_pPositions[i + 1], Xi_pPositions[i + 2]);

        if (Xi_pColors != nullptr)
        {
            stPoint.vecColor = Vec3f(Xi_pColors[i] / 256.0f, Xi_pColors[i + 1] / 256.0f, Xi_pColors[i + 2] / 256.0f);
        }

        m_vecPoints.push_back(stPoint);
    }

    m_mutex.unlock();

    update();
    return 0;
}