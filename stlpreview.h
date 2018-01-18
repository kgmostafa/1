#ifndef STLPREVIEW_H
#define STLPREVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class STLPreview : public QOpenGLWidget
{
    Q_OBJECT
public:
    STLPreview(QWidget *parent = 0);
    ~STLPreview();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    // Arcball variables
    float _currX;
    float _currY;
    float _lastX;
    float _lastY;
    bool _arcball;
    QQuaternion _quat;
    glm::mat4 _rot;
    GLfloat _ab_quat[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    GLfloat _ab_last[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
    GLfloat _ab_next[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};


    glm::vec3 _ab_start;
    glm::vec3 _ab_curr;

    void arcball_start(int mx, int my);
    void arcball_move(int mx, int my);

    glm::vec3 get_arcball_vector(int x, int y);

    int _xRot;
    int _yRot;
    int _zRot;
    QPoint _lastPos;

//    QOpenGLShaderProgram *_program;

    QMatrix4x4 _proj;
    QMatrix4x4 _camera;
    QMatrix4x4 _world;

    static bool _transparent;

    void draw();
    void drawAxis();

};

#endif // STLPREVIEW_H
