#ifndef _SHOWDEGREE_H
#define _SHOWDEGREE_H

#include "plugin.h"

#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLWidget>

class ShowDegree: public QObject, public Plugin {
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

		double averageDeg;

		void calculateAvgDeg();
		void drawRectangle();
};

#endif
