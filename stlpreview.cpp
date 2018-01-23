#include "stlpreview.h"
#include "mainwindow.h"
#include "triangle.h"
#include <QMouseEvent>
#include <QtMath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>
#include <GL\glu.h>

GLdouble _ab_glp[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
GLdouble _ab_glm[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
int _ab_glv[4] = {0,0,400,400};
glm::vec3 _ab_eye = glm::vec3(0,0,1);
glm::vec3 _ab_eyedir = glm::vec3(0,0,1);
glm::vec3 _ab_up = glm::vec3(0,1,0);
glm::vec3 _ab_out = glm::vec3(1,0,0);
bool STLPreview::_transparent = false;

STLPreview::STLPreview(QWidget *parent)
    : QOpenGLWidget(parent),
      _currX(0), _currY(0),
      _lastX(0), _lastY(0),
      _arcball(false), _rot(1.0)
{
    _ab_start = glm::vec3(0,0,1);
    _ab_curr = glm::vec3(0,0,1);

}


STLPreview::~STLPreview()
{
    cleanup();
}

QSize STLPreview::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize STLPreview::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void STLPreview::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _xRot) {
        _xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void STLPreview::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _yRot) {
        _yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void STLPreview::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != _zRot) {
        _zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void STLPreview::cleanup()
{/*
    if (m_program == nullptr)
        return;
    makeCurrent();
    m_logoVbo.destroy();
    delete m_program;
    m_program = 0;
    doneCurrent();*/
}

void STLPreview::initializeGL()
{
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
//    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

   // initializeOpenGLFunctions();
    //QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    glClearColor(0, 0, 0, _transparent ? 0 : 1);

//    m_program = new QOpenGLShaderProgram;
//    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
//    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
//    m_program->bindAttributeLocation("vertex", 0);
//    m_program->bindAttributeLocation("normal", 1);
//    m_program->link();

//    m_program->bind();
//    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
//    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
//    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
//    m_lightPosLoc = m_program->uniformLocation("lightPos");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
//    m_vao.create();
//    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.
//    m_logoVbo.create();
//    m_logoVbo.bind();
//    m_logoVbo.allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.
//    setupVertexAttribs();

    // Our camera never changes in this example.
//    m_camera.setToIdentity();
//    m_camera.translate(0, 0, -1);

    // Light position is fixed.
//    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

//    m_program->release();
}


void STLPreview::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // Triangles are painted based on vertices order

//    _world.setToIdentity();
    glLoadIdentity();

    glPushMatrix();
    // Translate
    glTranslatef(0.0, 0.0, 0.0);
    // Multiply by arcball matrix
    glMultMatrixf(_ab_quat);
//    _world.rotate(180.0f - (_xRot / 16.0f), 1, 0, 0);
//    _world.rotate(_yRot / 16.0f, 0, 1, 0);
//    _world.rotate(_zRot / 16.0f, 0, 0, 1);
    //glRotatef(_xRot / 16.0, 1.0, 0.0, 0.0);
    //glRotatef(_yRot / 16.0, 0.0, 1.0, 0.0);
    //glRotatef(_zRot / 16.0, 0.0, 0.0, 1.0);

//    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
//    _program->bind();
//    _program->setUniformValue(m_projMatrixLoc, m_proj);
//    _program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
//    QMatrix3x3 normalMatrix = m_world.normalMatrix();
//    _program->setUniformValue(m_normalMatrixLoc, normalMatrix);

//    glDrawArrays(GL_TRIANGLES, 0, m_logo.vertexCount());

//    m_program->release();
    //glPushMatrix();
//    if (_currX != _lastX || _currY != _lastY) {
//        std::cout << "!=\n";
//        glm::vec3 va = get_arcball_vector(_lastX, _lastY);
//        glm::vec3 vb = get_arcball_vector(_currX,  _currY);
//        float angle = acos(std::min(1.0f, glm::dot(va, vb)));
//        glm::vec3 axis_in_camera_coord = glm::cross(va, vb);
//        _quat = QQuaternion(angle, axis_in_camera_coord.x, axis_in_camera_coord.y, axis_in_camera_coord.z);

//        glm::mat3 camera2object = glm::inverse(glm::mat3(_rot));
//        glm::vec3 axis_in_object_coord = camera2object * axis_in_camera_coord;
////        std::cout << angle << std::endl;
//        _rot = glm::rotate(_rot, glm::degrees(angle), axis_in_object_coord);
//        glRotatef(qRadiansToDegrees(angle), axis_in_object_coord.x, axis_in_object_coord.y, axis_in_object_coord.z);
////        glMultMatrixf(glm::value_ptr(_rot));//glm::rotate(glm::mat4(1.0), glm::degrees(angle), axis_in_camera_coord)));
//        _lastX = _currX;
//        _lastY = _currY;
//      }
        glPushMatrix();
        drawAxis();
        float scale =  1.0/(((MainWindow*)(this->parentWidget()->parent()))->_maxLength*2.0);
//        float scaleX =  1.0/(((MainWindow*)(this->parentWidget()->parent()))->_maxXLength*2.0);
//        float scaleY =  1.0/(((MainWindow*)(this->parentWidget()->parent()))->_maxYLength*2.0);
//        float scaleZ =  1.0/(((MainWindow*)(this->parentWidget()->parent()))->_maxZLength*2.0);
        glScalef(scale, scale, scale);
        draw();
        glPopMatrix();
}

void STLPreview::resizeGL(int w, int h)
{
    _proj.setToIdentity();
    _proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void STLPreview::mousePressEvent(QMouseEvent *event) {
//    if(event->button() == Qt::LeftButton) {
//        std::cout << "mousePressEvent\n";
//        _currX = _lastX = event->x();
//        _currY = _lastY = event->y();
//        _arcball = true;
//    } else {
//        _arcball = false;
//    }
    int invert_y = (400 - event->y()) - 1; // OpenGL viewport coordinates are Cartesian
    arcball_start(event->x() ,invert_y);
}

// copy a rotation matrix
static void quatcopy(GLfloat* dst, GLfloat* src)
{ dst[0]=src[0]; dst[1]=src[1]; dst[2]=src[2];
  dst[4]=src[4]; dst[5]=src[5]; dst[6]=src[6];
  dst[8]=src[8]; dst[9]=src[9]; dst[10]=src[10]; }

// get intersection with plane for "trackball" style rotation
static glm::vec3 planar_coords(GLdouble mx, GLdouble my)
{
  GLdouble ax,ay,az;

  gluUnProject(mx,my,0,_ab_glm,_ab_glp,_ab_glv,&ax,&ay,&az);
  glm::vec3 m = glm::vec3((float)ax,(float)ay,(float)az) - _ab_eye;
  // intersect the point with the trackball plane
//  GLfloat t = (ab_planedist - ab_zoom) / (ab_eyedir * m);
  GLfloat t = (0.5 - 1.0) / glm::dot(_ab_eyedir, m);
  glm::vec3 d = _ab_eye + m*t;

  return glm::vec3(glm::dot(d,_ab_up),glm::dot(d,_ab_out),0.0);
}

void STLPreview::arcball_start(int mx, int my)
{
  // saves a copy of the current rotation for comparison
  quatcopy(_ab_last,_ab_quat);
  /*if(ab_planar) */_ab_start = planar_coords((GLdouble)mx,(GLdouble)my);
//  else ab_start = sphere_coords((GLdouble)mx,(GLdouble)my);
}



void STLPreview::mouseMoveEvent(QMouseEvent *event) {
//    if(_arcball) {
//        std::cout << "mouseMoveEvent & _arcBall\n";
//        _currX = event->x();
//        _currY = event->y();
//        update();
//    }
    int invert_y = (400 - event->y()) - 1;
    arcball_move(event->x(),invert_y);
    update();
}



// convert the quaternion into a rotation matrix
static void quaternion(GLfloat* q, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
  GLfloat x2 = x*x;
  GLfloat y2 = y*y;
  GLfloat z2 = z*z;
  GLfloat xy = x*y;
  GLfloat xz = x*z;
  GLfloat yz = y*z;
  GLfloat wx = w*x;
  GLfloat wy = w*y;
  GLfloat wz = w*z;

  q[0] = 1 - 2*y2 - 2*z2;
  q[1] = 2*xy + 2*wz;
  q[2] = 2*xz - 2*wy;

  q[4] = 2*xy - 2*wz;
  q[5] = 1 - 2*x2 - 2*z2;
  q[6] = 2*yz + 2*wx;

  q[8] = 2*xz + 2*wy;
  q[9] = 2*yz - 2*wx;
  q[10]= 1 - 2*x2 - 2*y2;
}

// multiply two rotation matrices
static void quatnext(GLfloat* dest, GLfloat* left, GLfloat* right)
{
  dest[0] = left[0]*right[0] + left[1]*right[4] + left[2] *right[8];
  dest[1] = left[0]*right[1] + left[1]*right[5] + left[2] *right[9];
  dest[2] = left[0]*right[2] + left[1]*right[6] + left[2] *right[10];
  dest[4] = left[4]*right[0] + left[5]*right[4] + left[6] *right[8];
  dest[5] = left[4]*right[1] + left[5]*right[5] + left[6] *right[9];
  dest[6] = left[4]*right[2] + left[5]*right[6] + left[6] *right[10];
  dest[8] = left[8]*right[0] + left[9]*right[4] + left[10]*right[8];
  dest[9] = left[8]*right[1] + left[9]*right[5] + left[10]*right[9];
  dest[10]= left[8]*right[2] + left[9]*right[6] + left[10]*right[10];
}

// update current arcball rotation
void STLPreview::arcball_move(int mx, int my)
{
//  if(ab_planar)
//  {
    _ab_curr = planar_coords((GLdouble)mx,(GLdouble)my);
//    if(_ab_curr.equals(ab_start)) return;
    if(_ab_curr == _ab_start) return;

    // d is motion since the last position
    glm::vec3 d = _ab_curr - _ab_start;

    GLfloat angle = d.length() * 0.01;
    GLfloat cosa = cos( angle );
    GLfloat sina = sin( angle );
    // p is perpendicular to d
    //vec p = ((ab_out*d.x)-(ab_up*d.y)).unit() * sina;
    glm::vec3 p = glm::normalize((_ab_out*d.x)-(_ab_up*d.y)) * sina;

    quaternion(_ab_next,p.x,p.y,p.z,cosa);
    quatnext(_ab_quat,_ab_last,_ab_next);
    // planar style only ever relates to the last point
    quatcopy(_ab_last,_ab_quat);
    _ab_start = _ab_curr;

//  } else {

//    ab_curr = sphere_coords((GLdouble)mx,(GLdouble)my);
//    if(ab_curr.equals(ab_start))
//    { // avoid potential rare divide by tiny
//      quatcopy(ab_quat,ab_last);
//      return;
//    }

//    // use a dot product to get the angle between them
//    // use a cross product to get the vector to rotate around
//    GLfloat cos2a = ab_start*ab_curr;
//    GLfloat sina = sqrt((1.0 - cos2a)*0.5);
//    GLfloat cosa = sqrt((1.0 + cos2a)*0.5);
//    vec cross = (ab_start^ab_curr).unit() * sina;
//    quaternion(ab_next,cross.x,cross.y,cross.z,cosa);

//    // update the rotation matrix
//    quatnext(ab_quat,ab_last,ab_next);
//  }
}


glm::vec3 STLPreview::get_arcball_vector(int x, int y) {
    std::cout << this->size().width() << std::endl;
  glm::vec3 P = glm::vec3(((float)x)/((float)this->size().width()) - 1.0,
                    ((float)y)/((float)this->size().height()) - 1.0,
                    0.0);
  P.y = -P.y;
  float OP_squared = P.x * P.x + P.y * P.y;
  if (OP_squared <= 1*1)
    P.z = sqrt(1*1 - OP_squared);  // Pythagore
  else
    P = glm::normalize(P);  // nearest point
  return P;
}

void STLPreview::draw() {
    bool wireframe = ((MainWindow*)(this->parentWidget()->parent()))->_wireframe;
    bool baseCube = ((MainWindow*)(this->parentWidget()->parent()))->_basePart;
    std::vector<Triangle> t = ((MainWindow*)(this->parentWidget()->parent()))->_triangs;

    int i = 0;
    for (std::vector<Triangle>::iterator it = t.begin() ; it != t.end(); ++it) {
        Triangle aux = *it;
        glm::vec3 v1 = aux.getV1();
        glm::vec3 v2 = aux.getV2();
        glm::vec3 v3 = aux.getV3();
        if(i < 12) {
            if(baseCube) {
                glBegin(GL_LINES);
                glColor3f(1.0,i<12?1.0:0.0,0.0);
                glVertex3fv(glm::value_ptr(v1));
                glVertex3fv(glm::value_ptr(v2));
                glEnd();
                glBegin(GL_LINES);
                glColor3f(1.0,i<12?1.0:0.0,0.0);
                glVertex3fv(glm::value_ptr(v2));
                glVertex3fv(glm::value_ptr(v3));
                glEnd();
                glBegin(GL_LINES);
                glColor3f(1.0,i<12?1.0:0.0,0.0);
                glVertex3fv(glm::value_ptr(v3));
                glVertex3fv(glm::value_ptr(v1));
                glEnd();
            }
        } else {
            if(wireframe) {
                glBegin(GL_LINES);
                glColor3f(1.0,i<12?1.0:0.0,0.0);
                glVertex3fv(glm::value_ptr(v1));
                glVertex3fv(glm::value_ptr(v2));
                glEnd();
                glBegin(GL_LINES);
                glColor3f(1.0,i<12?1.0:0.0,0.0);
                glVertex3fv(glm::value_ptr(v2));
                glVertex3fv(glm::value_ptr(v3));
                glEnd();
                glBegin(GL_LINES);
                glColor3f(1.0,i<12?1.0:0.0,0.0);
                glVertex3fv(glm::value_ptr(v3));
                glVertex3fv(glm::value_ptr(v1));
                glEnd();
            } else {
                glBegin(GL_TRIANGLES);
                glColor3f(1.0,i<12?1.0:0.0,0.0);
                glVertex3fv(glm::value_ptr(v1));
                glVertex3fv(glm::value_ptr(v2));
                glVertex3fv(glm::value_ptr(v3));
                glEnd();
            }
        }
        i++;
    }
}

void STLPreview::drawAxis()
{
    // save previous matrix
    //glPushMatrix();
    // clear matrix
    //glLoadIdentity();
    // move the axes to the screen corner
    //glTranslatef(-3.0, -2.0, 0.0);
    // draw our axes
    glBegin(GL_LINES);
    // draw line for x axis
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    // draw line for y axis
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    // draw line for Z axis
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    // load the previous matrix
    //glPopMatrix();
}
