#ifndef _ANIMATEVERTICES_H
#define _ANIMATEVERTICES_H

#include "plugin.h"
#include <QGLShader>
#include <QGLShaderProgram>
#include <QElapsedTimer>
#include <QGLWidget>

class AnimateVertices: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
		void preFrame();
		void postFrame();

	private:
		QGLShader *vs;
		QGLShader *fs;
		QGLShaderProgram *shaderProgram;
		QElapsedTimer elapsedTimer;
};

#endif
