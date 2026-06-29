#ifndef EBO_CLASS_H
#define EBO_CLASS_H
#include<glad/gl.h>
class EBO
{
public:
		GLuint ID;
		EBO(GLuint* indices, GLsizeiptr size);

		void Bind();
		void UnBind();
		void Delete();
};
#endif // !VBO_CLASS_H
#pragma once
