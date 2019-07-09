#include "drawSmooth.h"
#include "glwidget.h"
#include <cassert>
#include <cmath>

DrawVBOng::~DrawVBOng() {
	cleanUp();
}

void DrawVBOng::onSceneClear() {
	cleanUp();
}

void DrawVBOng::cleanUp() {
	GLWidget &g = *glwidget();
	g.glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
	g.glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
	g.glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
	g.glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);
	g.glDeleteVertexArrays(VAOs.size(), &VAOs[0]);
	coordBuffers.clear();
	normalBuffers.clear();
	stBuffers.clear();
	colorBuffers.clear();
	VAOs.clear();
	numIndices.clear();
}

bool DrawVBOng::drawObject(int i) {
	GLWidget &g = *glwidget();
	g.makeCurrent();
	g.glBindVertexArray(VAOs[i]);
	g.glDrawArrays(GL_TRIANGLES, 0, numIndices[i]);
	g.glBindVertexArray(0);
	return true;
}

bool DrawVBOng::drawScene() {
	GLWidget &g = *glwidget();
	g.makeCurrent();
	for(unsigned int i=0; i<VAOs.size(); i++) // for each buffer (that is, for each object)
		drawObject(i);
	return true;
}

void DrawVBOng::onPluginLoad() {
	for(unsigned int i=0; i<scene()->objects().size(); i++)
		addVBO(i);
}

void DrawVBOng::onObjectAdd() {
	addVBO(scene()->objects().size() - 1);
}

void DrawVBOng::addVBO(unsigned int currentObject) {
	// Step 1: create and fill the four arrays (vertex coords, vertex normals, vertex colors and face indeces)
	//		   - each coord/normal will appear n times (one for each corner with unique normal)
	//		   - non-triangular faces will be triangulated on the fly: (v0, v1, v2, v3) -> (v0, v1, v2) and (v0, v2, v3)

	vector<float> vertices;		// (x, y, z)	final size: 3 * number of corners
	vector<float> normals;		// (nx, ny, nz)	final size: 3 * number of corners
	vector<float> texCoords;	// (s, t)		final size: 2 * number of corners
	vector<float> colors;		// (r, g, b)	final size: 3 * number of corners
	vector<int>   indeces;		// 				final size: 3 * number of triangles

	// V' = V
	// this implies that every vertex (x, y, z) appears only once (without repetitions) and with only one normal in the VBO
	// Therefore, every face that uses that vertex will receive the same normal
	// The same applies with the remaining attributes (color and texture coordinates)

	const Object 		 &obj   = scene() -> objects()[currentObject];
	const vector<Vertex> &verts = obj.vertices();
	const vector<Face>   &faces = obj.faces();

	// let the normal of a vertex be the average of the normals of the faces that insist on it
	vector<Vector> vertexNormals(obj.vertices().size(), Vector(0.0, 0.0, 0.0));						// it will contain, for every vertex, its averaged normal
	vector<int>    vertexCounter(obj.vertices().size(), 0);											// it will contain, for every vertex, the count of the normals insisting on it
	
	// for every face
	for(int i=0; i<(int)faces.size(); i++) {
		// get a reference to it
		const Face   &face       = faces[i];
		// and to its normal
		const Vector &faceNormal = face.normal().normalized();

		// for every vertex of that face
		for(int j=0; j<(int)face.numVertices(); j++) {
			// add the face normal to the vertexNormals array in order to calculate the average
			vertexNormals[face.vertexIndex(j)] += faceNormal;
			vertexCounter[face.vertexIndex(j)]++;
		}
	}

	// calculate the average
	for(int i=0; i<(int)vertices.size(); i++) {
		Vector averagedNormal = vertexNormals[i]/vertexCounter[i];
		
		const Point &point = verts[i].coord();
		vertices.push_back(P.x());
		vertices.push_back(P.y());
		vertices.push_back(P.z());

		// TODO CONTINUE FROM HERE
	}

	
}
