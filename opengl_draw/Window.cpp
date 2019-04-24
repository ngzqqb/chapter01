﻿#include "Window.hpp"
#include <sstd/glm/glm.hpp>
#include <sstd/glm/geometric.hpp>
#include <sstd/glm/gtc/matrix_transform.hpp>

namespace sstd {

    class WindowOpenGLData {
    public:
        GLuint thisProgram{ 0 };
        GLuint thisBuffer0{ 0 };
        GLuint thisVAO{ 0 };
        inline void construct() {
            assert(thisProgram == 0);
            thisProgram = sstd::opengl_utility::createVFProgram(
                u8R"(
#version 450

layout(location=0) in vec4 iposition;
layout(location=1) in vec4 icolor;
layout(location=2) uniform mat4 imvp;

out vec4 inoutcolor;

void main(void){
    gl_Position =  imvp * iposition ;
    inoutcolor = icolor;
}

)"sv,
u8R"(
#version 450

in vec4 inoutcolor;
out vec4 color;

void main(void){
    color = inoutcolor ;
}
)"sv);
            glCreateVertexArrays(1, &thisVAO);
            glBindVertexArray(thisVAO);
            glEnableVertexArrayAttrib(thisVAO, 0)/*position*/;
            glEnableVertexArrayAttrib(thisVAO, 1)/*color*/;

            using Row = std::array<GLfloat, 8>;
            {
                glCreateBuffers(1, &thisBuffer0);
                constexpr std::array varDrawData{
                    /*blue*/
                    Row{-0.4f,+0.4f,+0.4f,+1.0f,/**/+0.0f,+0.0f,+0.8f,+1.0f},
                    Row{+0.4f,-0.4f,+0.4f,+1.0f,/**/+0.0f,+0.0f,+0.6f,+1.0f},
                    Row{+0.4f,+0.4f,+0.4f,+1.0f,/**/+0.0f,+0.0f,+0.4f,+1.0f},
                    /*red*/
                    Row{-0.8f,+0.0f,+0.0f,+1.0f,/**/+0.8f,+0.0f,+0.0f,+1.0f},
                    Row{-0.0f,-0.8f,+0.0f,+1.0f,/**/+0.6f,+0.0f,+0.0f,+1.0f},
                    Row{+0.0f,+0.0f,+0.0f,+1.0f,/**/+0.4f,+0.0f,+0.0f,+1.0f},
                    /*green*/
                    Row{-0.6f,+0.2f,-0.2f,+1.0f,/**/+0.0f,+0.8f,+0.0f,+1.0f},
                    Row{+0.2f,-0.6f,-0.2f,+1.0f,/**/+0.0f,+0.6f,+0.0f,+1.0f},
                    Row{+0.2f,+0.2f,-0.2f,+1.0f,/**/+0.0f,+0.4f,+0.0f,+1.0f},
                };
                glNamedBufferData(thisBuffer0, sizeof(varDrawData), varDrawData.data(), GL_STATIC_DRAW);

                glVertexArrayVertexBuffer(thisVAO, 0, thisBuffer0, 0, sizeof(Row));
                glVertexArrayVertexBuffer(thisVAO, 1, thisBuffer0, 0, sizeof(Row));

                glVertexArrayAttribFormat(thisVAO, 0, 4, GL_FLOAT, false, 0);
                glVertexArrayAttribFormat(thisVAO, 1, 4, GL_FLOAT, false, sizeof(Row) / 2);

                glVertexArrayAttribBinding(thisVAO, 0, 0);
                glVertexArrayAttribBinding(thisVAO, 1, 1);

            }
        }
        inline void destruct() {
            USING_SSTD_GLEW;
            glDeleteProgram(thisProgram);
            glDeleteVertexArrays(1, &thisVAO);
            glDeleteBuffers(1, &thisBuffer0);
        }
    };

    void Window::initializeGL() {
        if (thisOpenGLData.use_count() > 0) {
            return;
        }
        Super::initializeGL();
        auto varContex = this->context();
#if defined(_DEBUG)
        auto varDebugLogger = sstd_virtual_new<QOpenGLDebugLogger>(varContex);
        varDebugLogger->initialize();
        connect(varDebugLogger, &QOpenGLDebugLogger::messageLogged,
            varDebugLogger, [](const QOpenGLDebugMessage &debugMessage) {
            qDebug() << debugMessage;
        });
        varDebugLogger->startLogging();
#endif
        auto varOpenGLData = sstd_make_shared<WindowOpenGLData>();
        varOpenGLData->construct();
        thisOpenGLData = varOpenGLData;
        connect(varContex, &QOpenGLContext::aboutToBeDestroyed,
            varContex, [varOpenGLData]() {varOpenGLData->destruct(); },
            Qt::DirectConnection);
    }

    void Window::paintGL() try {
        if (thisOpenGLData.expired()) {
            return;
        }
        auto varOpenGLData = thisOpenGLData.lock();
        USING_SSTD_GLEW;
        auto varFBO = this->defaultFramebufferObject();
        glBindFramebuffer(GL_FRAMEBUFFER, varFBO);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_CLAMP);
        {
            constexpr const GLfloat varColor[]{ 0.5f,0.5f,0.5f,1.0f };
            glClearNamedFramebufferfv(varFBO, GL_COLOR, 0, varColor);
        }
        {
            constexpr const GLfloat varDepth[]{ 1.0f };
            glClearNamedFramebufferfv(varFBO, GL_DEPTH, 0, varDepth);
        }
        const static auto varMatrix = glm::mat4x4{ 1 };
        glUseProgram(varOpenGLData->thisProgram);
        glBindVertexArray(varOpenGLData->thisVAO);
        glUniformMatrix4fv(2, 1, false, &(varMatrix[0][0]));
        glDrawArrays(GL_TRIANGLES, 0, 9);
    } catch (...) {
    }

    void Window::resizeGL(int w, int h) {
        USING_SSTD_GLEW;
        this->makeCurrent();
        auto varRatio = static_cast<GLfloat>(this->devicePixelRatio());
        auto varFBO = this->defaultFramebufferObject();
        glBindFramebuffer(GL_FRAMEBUFFER, varFBO);
        glViewportIndexedf(0, 0, 0, varRatio*w, varRatio*h);
    }

}/*namespace sstd*/

/* https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glClearBuffer.xhtml */
/* https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glViewportIndexed.xhtml */
/* https://stackoverflow.com/questions/4124041/is-opengl-coordinate-system-left-handed-or-right-handed */
//By default the Normalized Device Coordinate is left-handed.
//The glDepthRange is by default [0, 1] (near, far) 
//making the +z axis point into the screen and with +x 
//to the right and +y up it is a left-handed system.
//Quoting a previous answer from Nicol: 
//(the strike-through is my work, explained below)

