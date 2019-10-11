#ifndef _PCL_DISPLAY_H_
#define _PCL_DISPLAY_H_

#include <QOpenGLWidget>
#include <QKeyEvent>
#include <mutex>

class PCLDisplay : public QOpenGLWidget
{
public:
    PCLDisplay(QWidget* parent = nullptr);
    ~PCLDisplay();

    void SendPointCloud(float* pPositions, unsigned char* pColors, size_t pointSize);
    //int SendPointCloud(float* Xi_pPositions, unsigned char *Xi_pColors, size_t Xi_pointSize);

protected:

    void initializeGL();
    void paintGL();

private:
    float* m_pPositions;
    unsigned char* m_pColors;
    size_t m_pointSize;
    std::mutex m_mutex;
};
#endif /*_PCL_DISPLAY_H_*/