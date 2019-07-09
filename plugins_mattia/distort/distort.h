#ifndef _DISTORT_H
#define _DISTORT_H

#include "plugin.h"

#include <QGLShader>
#include <QGLShaderProgram>
#include <QElapsedTimer>
#include <QGLWidget>

class Distort: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		bool paintGL();

	private:
		QGLShader *vs;
		QGLShader *fs;
		QGLShaderProgram *shaderProgram;
		
		GLuint textureID;
		QElapsedTimer elapsedTimer;

		void drawRect();
};

#endif
