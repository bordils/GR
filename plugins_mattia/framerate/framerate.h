#ifndef _FRAMERATE_H
#define _FRAMERATE_H

#include "plugin.h"

#include <QGLShader>
#include <QGLShaderProgram>
#include <QGLWidget>

class Framerate: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		void postFrame();
	
	public slots:
		void updateFPS();

	private:
		int frameCount;
		int fps;

		GLuint textureID;
		QGLShader *vs;
		QGLShader *fs;
		QGLShaderProgram *shaderProgram;

		void drawRectangle();
};

#endif
