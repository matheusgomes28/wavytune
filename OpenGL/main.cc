#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shaders/shaderProgram.h"
#include "Graphics/drawBuffer.h"
#include "Graphics/drawData2.h"
#include "Graphics/drawData3.h"
#include "Graphics/barBuffer.h"
#include "Graphics/entity.h"

// The look at stuff
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <iostream>


struct BufferVBO {
	GLuint vertices = 0;
	GLuint normals = 0;
	GLuint texels = 0;
};

BufferVBO createBuffers()
{
	BufferVBO vbo;

	glGenBuffers(1, &vbo.vertices);
	glGenBuffers(1, &vbo.normals);
	glGenBuffers(1, &vbo.texels);

	return vbo;
}

void sendBufferData(const DrawBuffer& buffer, const GLuint& shader, const GLuint& VAO, const BufferVBO& VBO)
{
	glBindVertexArray(VAO);

	// TODO : guards to see if the data here is completely valid
	const std::vector<glm::vec3>& vertices = buffer.getVertices().getData();
	glBindBuffer(GL_ARRAY_BUFFER, VBO.vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	GLint posPtr = glGetAttribLocation(shader, "aPos");
	glVertexAttribPointer(posPtr, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posPtr);

	// Normals
	const std::vector<glm::vec3>& normals = buffer.getNormals().getData();
	glBindBuffer(GL_ARRAY_BUFFER, VBO.normals);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	GLint norPtr = glGetAttribLocation(shader, "aNor");
	glVertexAttribPointer(norPtr, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(norPtr);

	// Texels
	const std::vector<glm::vec2>& texels = buffer.getTexels().getData();
	glBindBuffer(GL_ARRAY_BUFFER, VBO.texels);
	glBufferData(GL_ARRAY_BUFFER, texels.size() * sizeof(glm::vec2), &texels[0], GL_STATIC_DRAW);
	GLint texPtr = glGetAttribLocation(shader, "aTex");
	glVertexAttribPointer(texPtr, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(texPtr);
}

void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


// TODO : encapsulate all of this global look at stuff
glm::vec3 eye;
glm::vec3 pos;
glm::vec3 up;
glm::mat4 lookAt;

void changeLookAt(glm::mat4& lookAt, const glm::vec3& eye, const glm::vec3& pos, const glm::vec3& up)
{
	lookAt = glm::lookAt(
		eye,
		pos,
		up
	);
}

enum class AXIS {
	X,
	Y,
	Z
};
glm::vec3 rotateVector(const glm::vec3& vector, const glm::vec3& from, const AXIS& axis, const float& angle)
{
	const glm::vec3 INV_VECTOR{
		-from.x,
		-from.y,
		-from.z
	};

	switch (axis) {
	case AXIS::X:
	{
		const glm::vec3 ROT_AXIS{ 1, 0, 0 };
		const glm::mat4& ROT_MATRIX = glm::rotate(angle, ROT_AXIS);
		glm::vec3 retVal = ROT_MATRIX * glm::vec4{ vector.x + INV_VECTOR.x,
			vector.y + INV_VECTOR.y,
			vector.z + INV_VECTOR.z,
			1 };

		return retVal - INV_VECTOR;
	}
	case AXIS::Y:
	{
		const glm::vec3 ROT_AXIS{ 0, 1, 0 };
		const glm::mat4& ROT_MATRIX = glm::rotate(angle, ROT_AXIS);
		glm::vec3 retVal = ROT_MATRIX * glm::vec4{ vector.x + INV_VECTOR.x,
			vector.y + INV_VECTOR.y,
			vector.z + INV_VECTOR.z,
			1 };
		return retVal - INV_VECTOR;
	}
	case AXIS::Z:
	{
		const glm::vec3 ROT_AXIS{ 0, 0, 1 };
		const glm::mat4& ROT_MATRIX = glm::rotate(angle, ROT_AXIS);
		glm::vec3 retVal = ROT_MATRIX * glm::vec4{ vector.x + INV_VECTOR.x,
			vector.y + INV_VECTOR.y,
			vector.z + INV_VECTOR.z,
			1 };
		return retVal - INV_VECTOR;
	}
	}
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		pos += glm::vec3{ 0, 0.5, 0 };
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		pos += glm::vec3{ 0, -0.5, 0 };
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		pos = rotateVector(pos, eye, AXIS::Y, glm::radians(10.0f));
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		pos = rotateVector(pos, eye, AXIS::Y, glm::radians(-10.0f));
	}
}

int main(int argc, char* argv)
{
	glewExperimental = GL_TRUE;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "TestingOut Window", NULL, NULL);
	if (!window) {
		std::cout << "Could not create window. Exiting..." << std::endl;
		glfwTerminate();
		return -1;
	}
	
	// Create the viewport
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwMakeContextCurrent(window);

	// Create the shader program
	glewInit(); // Initialise all the openGL macros
	const std::string VS_PATH = "C:\\Users\\Matheus\\audioVisualiser\\vs.glsl";
	const std::string FS_PATH = "C:\\Users\\Matheus\\audioVisualiser\\fs.glsl";
	ShaderProgram shader(VS_PATH, FS_PATH); // The shader program
	shader.compileandLink();
	shader.use();

	// For the triangles
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	BufferVBO vbo = createBuffers();

	// TODO : Create a class that inherits from this
	BarBuffer buffer;
	sendBufferData(buffer, shader.getAddress(), VAO, vbo);

	eye = { 0, 0, 10 };
	pos = { 0, 0, 0 };
	up = { 0, 1, 0 };

	glm::mat4 proj = glm::perspective<float>(
		glm::radians(45.0f),
		800/600,
		0.01,
		100
	);

	// Callback from commands
	glfwSetKeyCallback(window, keyCallBack);

	// Game loop
	while (!glfwWindowShouldClose(window)) {
		lookAt = glm::lookAt(
			eye,
			pos,
			up
		);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Green uniform 
		float green = abs(0.5+sin(glfwGetTime()*2)/2.0);
		shader.setUniform("green", green);
		shader.setUniform("proj", proj);
		shader.setUniform("view", lookAt);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
