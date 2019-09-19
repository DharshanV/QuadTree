#ifndef LINE_H
#define LINE_H
#include <iostream>
#include <Utitlites/VertexArray.h>
#include <Utitlites/VertexBuffer.h>
#include <Utitlites/VertexBufferLayout.h>
using namespace std;
using namespace glm;
class Line {
public:
	Line(const vec3& origin, const vec3& dir) :
		origin(origin), dir(dir) {
		init();
	}


	Line(const Line& other) {
		origin = other.origin;
		dir = other.dir;
		layout = VertexBufferLayout();
		init();
	}

	Line& operator = (const Line& other) {
		if (this == &other) return *this;
		delete VAO;
		delete VBO;
		origin = other.origin;
		dir = other.dir;
		init();
		return *this;
	}

	bool contains(const vec3& point) const {
		return false;
	}

	void draw() {
		VAO->bind();
		glDrawArrays(GL_LINES, 0, vertices.size());
	}

	~Line() {
		delete VAO;
		delete VBO;
	}
private:
	void init() {
		createVertices();
		VAO = new VertexArray();
		VBO = new VertexBuffer(&vertices[0].x, vertices.size() * 3 * 4);
		layout.push<float>(3);
		VAO->addBuffer(*VBO, layout);
	}

	void createVertices() {
		vertices.reserve(2);
		vertices.push_back(origin);
		vertices.push_back(origin + dir * 50.0f);
	}
private:
	vector<vec3> vertices;
	vec3 origin;
	vec3 dir;
	VertexArray* VAO;
	VertexBuffer* VBO;
	VertexBufferLayout layout;
};

vec3 operator * (const vec3& v, float t) {
	return vec3(v.x*t, v.y*t, v.z*t);
}

#endif // !LINE_H