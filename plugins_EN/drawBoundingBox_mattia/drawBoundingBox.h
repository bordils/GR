#ifndef _DRAWBOUNDINGBOX_H
#define _DRAWBOUNDINGBOX_H

#include "plugin.h"

#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLWidget>

class DrawBoundingBox: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		void postFrame();

	private:
		QGLShader *vs;
		QGLShader *fs;
		QGLShaderProgram *shaderProgram;

		GLuint textureID;

		bool created;
		
		GLuint cubeVAO;
		GLuint verticesVBO;
		GLuint colorVBO;

		void drawBoxes();
		void createBuffers();
		void generateVBO(GLuint &vbo_ID, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size);
};

#endif
