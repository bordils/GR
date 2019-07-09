#include "model_info_1.h"
#include "glwidget.h"

void Model_info_1::onPluginLoad() {
	printModelInfo();
}

void Model_info_1::onObjectAdd() {
	printModelInfo();
}

void Model_info_1::printModelInfo() {
	// scene object	
	Scene* s = scene();

	int nObjects;
	int nPolygons  = 0;
	int nTriangles = 0;
	int nVerteces  = 0;

	float trigPercentage;

	nObjects = s->objects().size();

	// for every object in the scene
	for(int i=0; i<nObjects; i++) {
		// one at the time get a reference to the object
		const Object &obj = s->objects()[i];

		// for every face of that object
		for(int j=0; j<(int)obj.faces().size(); j++) {
			// count a polygon
			nPolygons++;			

			// get a reference to the face
			const Face &face = obj.faces()[j];
			
			int faceVertices = face.numVertices();
			
			// update the total number of vertices
			nVerteces += faceVertices;

			// if the face is a triangle, update the triangle count
			if(faceVertices == 3)
				nTriangles++;
		}
	}
	
	// print obtained results
	printf("Number of objects    : %d\n",   nObjects);
	printf("Number of polygons   : %d\n",   nPolygons);
	printf("Number of triangles  : %d\n",   nTriangles);
	printf("Number of verteces   : %d\n",   nVerteces);

	trigPercentage = 100*((float)nTriangles)/nPolygons;
	printf("Percentage of trigs  : %.2f\n\n", trigPercentage);
}
