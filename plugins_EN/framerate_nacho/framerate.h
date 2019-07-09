#ifndef _FRAMERATE_H  
#define _FRAMERATE_H

#include "plugin.h"
#include "qpainter.h"

class Framerate: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)


  int fcnt;
  int fps;

  GLuint textureID;
  QOpenGLShaderProgram* program;
  QOpenGLShader* vs;
  QOpenGLShader* fs;

public:
  void onPluginLoad();
  void postFrame();

public slots:
  void updateFPS();
private:
	QPainter painter;
};

#endif


