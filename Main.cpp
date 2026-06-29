#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
// всё что содержит gl.h идёт впереди всего остального
// anything what is including gl.h comes before anything else 
#include <GLFW/glfw3.h> 



GLfloat vertices[] =
{	//				coords											//					colours						//
	-0.5f, -0.5f * float(sqrt(3)) / 3,     0.0f, 1.0f, 0.3f, 0.02f,
	0.5f,  -0.5f * float(sqrt(3)) / 3,     0.0f, 0.8f, 0.4f, 0.12f,
	0.0f,   0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 0.5f, 0.6f, 0.27f,
	-0.25f, 0.5f * float(sqrt(3)) / 6,     0.0f, 0.4f, 0.7f, 0.36f,
	0.25f,  0.5f * float(sqrt(3)) / 6,     0.0f, 0.3f, 0.9f, 0.42f,
	0.0f,  -0.5f * float(sqrt(3)) / 3,     0.0f, 0.01f, 1.0f, 0.95f,
};

GLuint indices[] =
{
	0,3,5,
	3,2,4,
	5,4,1,
};

int main()
{
	// инициализация хуйни
	glfwInit();

	// говорим компьютеру какой версии хуйня
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// окно и курсор для хуйни
	GLFWwindow* window = glfwCreateWindow(800, 800, "Qetr", NULL, NULL);
	/* GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR); */

	
	// если окно хуйни не работает, то херачим ошибка и съёбываемся
	if (window == NULL) 
	{ 
		printf( "GLFW window creation failure" );
		glfwTerminate();
		return -1;
	}
	
	// заставляем окно и курсор хуйни работать
	glfwMakeContextCurrent(window);
	/*glfwSetCursor(window, cursor);*/

	//загружаем пиздоблю для графона
	gladLoadGL((GLADloadfunc)glfwGetProcAddress);
		 

	// как пиздобля для графона рисуется
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");


	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0 );
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)( 3 * sizeof(float)) );
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();
											
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	// пока не щёлкнешь - не закроется
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.05f, 0.07f, 0.03f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();	
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// закончилась работа - съёбываем
	/* glfwDestroyCursor(cursor); */
	glfwDestroyWindow(window);
	glfwTerminate();
	
	// это база - это знать надо!
	return 0;
}