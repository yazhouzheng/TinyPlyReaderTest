#ifndef _PCL_DISPLAY_H_
#define _PCL_DISPLAY_H_

#include <QOpenGLWidget>
#include <mutex>
#include "Vec.h"

#define MAX_NUM                             1000000.0f

typedef struct tagSTPoint
{
    Vec3f vecPos;
    Vec3f vecColor;
    Vec3f vecNormal;
    Vec2f vecUV;

    tagSTPoint* pNeighbour;
    float fMinDist;
    float Dist2(tagSTPoint* pstPoint)
    {
        return vecPos.dist2(pstPoint->vecPos);
    }

    tagSTPoint()
    {
        pNeighbour = nullptr;
        fMinDist = MAX_NUM;
    }

    tagSTPoint(float fX1, float fX2, float fX3)
    {
        vecPos = Vec3f(fX1, fX2, fX3);
        pNeighbour = nullptr;
        fMinDist = MAX_NUM;
    }

    tagSTPoint(Vec3f vec)
    {
        vecPos = vec;
        pNeighbour = nullptr;
        fMinDist = MAX_NUM;
    }

}STPoint;

class PCLDisplay : public QOpenGLWidget
{
public:
    PCLDisplay(QWidget* parent = nullptr);
    ~PCLDisplay();

    int SendPointCloud(float* Xi_pPositions, unsigned char *Xi_pColors, size_t Xi_pointSize);

protected:
    void initializeGL();
    void paintGL();

private:
    std::vector<STPoint> m_vecPoints;
    std::mutex m_mutex;
};
#endif /*_PCL_DISPLAY_H_*/