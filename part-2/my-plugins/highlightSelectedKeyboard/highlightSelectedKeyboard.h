#ifndef _HIGHLIGHTSELECTEDKEYBOARD_H
#define _HIGHLIGHTSELECTEDKEYBOARD_H

#include "plugin.h"

#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLWidget>

class HighlightSelectedKeyboard: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		void postFrame();
		void keyPressEvent(QKeyEvent *e);

	private:
		QGLShader *vs;
		QGLShader *fs;
		QGLShaderProgram *shaderProgram;

		GLuint textureID;
		GLuint cubeVAO;
		GLuint verticesVBO;
		GLuint colorVBO;

		bool created;

		void drawSelectedBox();
		void setSelectedObject(int selected);
		
		void createBuffers();
		void generateVBO(GLuint &vbo_ID, GLsizeiptr size, const GLfloat *data, GLuint attribute_id, GLint attribute_size);
};

#endif
