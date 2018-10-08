#ifndef SHADER_H
#define SHADER_H

#include <glad\glad.h>
#include <glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Shader
{
public:

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	Shader() {};
	void use(); // use/activate the shader
	unsigned int getID() { return ID; };
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec3(const std::string &name, glm::vec3 &value) const;
	void setMat3(const std::string &name, glm::mat4 value) const;
	void setMat4(const std::string &name, glm::mat4 value) const;
	~Shader();

private:
	unsigned int ID;

	void CompileShader(unsigned int &vertexShader, unsigned int &fragmentShader, std::string vertexCode, std::string fragmentCode);
	void createShaderProgram(unsigned int& ID, int vertexShader, int fragmentShader);
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif

