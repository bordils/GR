#ifndef _HIGHLIGHTSELECTEDMOUSE_H
#define _HIGHLIGHTSELECTEDMOUSE_H

#include "plugin.h"

#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLWidget>

class HighlightSelectedMouse: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		void postFrame();
		void mouseReleaseEvent(QMouseEvent *e);

	private:
		QGLShader *boxVS;
		QGLShader *boxFS;
		QGLShaderProgram *boxShaderProgram;

		QGLShader *colorVS;
		QGLShader *colorFS;
		QGLShaderProgram *colorShaderProgram;

		GLuint textureID;
		GLuint cubeVAO;
		GLuint verticesVBO;
		GLuint colorVBO;

		bool created;

		void drawSelectedBox();
		void drawColorScene();
		void setSelectedObject(int selected);

		void createBuffers();
		void generateVBO(GLuint &vbo_ID, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size);
};

#endif
