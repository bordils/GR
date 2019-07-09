// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "showColor.h"
#include "glwidget.h"


void ShowColor::preFrame()
{
	
}

void ShowColor::postFrame() 
{
	GLWidget &g = *glwidget();
	g.makeCurrent();
	mousex = g.mapFromGlobal(QCursor::pos()).x();
	mousey = g.mapFromGlobal(QCursor::pos()).y();
	height= g.size().height();
	int mousey2 = height - mousey;
	glReadPixels(mousex,mousey2,1,1,GL_RGB, GL_UNSIGNED_BYTE, &color);

	QFont font;
	font.setPixelSize(32);
	painter.begin(glwidget());
	painter.setFont(font);
	int x = 15;
	int y = 40;
	painter.drawText(x, y, QString("Color RGB: ")+QString::number(color[0])+QString(" ")+QString::number(color[1])+QString(" ")+QString::number(color[2]));

	painter.end();
	g.update();
}


