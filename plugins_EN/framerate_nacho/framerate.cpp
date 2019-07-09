#include "framerate.h"
#include "glwidget.h"

// funcion declarada como slot en el .h
void Framerate::updateFPS() {
  fps=fcnt;                 // establecer FPS
  fcnt=0;                   // reset contador
  glwidget()->update();   // refrescar pantalla
}

void Framerate::onPluginLoad() {
  // update frame count every second
  fps=fcnt=0;
  QTimer *frameTimer=new QTimer(this);
  connect(frameTimer, SIGNAL(timeout()), this, SLOT(updateFPS()));
  frameTimer->start(1000);
  // keep repainting
  QTimer *paintTimer=new QTimer(this);
  connect(paintTimer, SIGNAL(timeout()), glwidget(), SLOT(update()));
  paintTimer->start();
}

void Framerate::postFrame() { 
  painter.begin(glwidget());
  painter.drawText(10, 20, QString("%0 fps").arg(fps));
  painter.end();
  ++fcnt;
}


#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(framerate, Framerate)   // plugin name, plugin class
#endif

