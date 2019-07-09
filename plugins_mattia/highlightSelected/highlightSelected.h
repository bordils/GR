#ifndef _HIGHLIGHTSELECTED_H
#define _HIGHLIGHTSELECTED_H

#include "plugin.h"

#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLWidget>

class HighlightSelected: public QObject, public Plugin {
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

		GLuint cubeVAO;
		GLuint verticesVBO;
		GLuint colorVBO;
		
		bool created;

		void drawBoxes();
		void createBuffers();
		void generateVBO(GLuint &vbo_ID, GLsizeiptr size, const GLfloat *data, GLuint attribute_ID, GLint attributeSize);
		
};

#endif
