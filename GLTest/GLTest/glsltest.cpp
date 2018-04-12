#include "stdafx.h"
#include "GlslTest.h"


GlslTest::GlslTest()
{
}


GlslTest::~GlslTest()
{
}

void GlslTest::prepare()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f,0.0f,0.0f,
		0.5f, -0.5f, 0.0f,  0.0f,1.0f,0.0f,
		0.0f, 0.5f, 0.0f,   0.0f,0.0f,1.0f
	};

	glGenVertexArrays(1, &VAO);//创建顶点数组
	glBindVertexArray(VAO);//绑定VAO

	glGenBuffers(1, &VBO); //创建缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //把缓冲绑定到GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //顶点数据复制到缓冲区

																			   //链接顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);//启用顶点属性，//registered VBO as the vertex attribute's bound vertex buffer object

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//glVertexAttribPointer之后调用

	//顶点着色器
	const char* vertexShaderSouce = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec4 vertexColor;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"	vertexColor = vec4(aColor,1.0);\n"
		"}\0";

	unsigned int vertexShader;//着色器id
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建着色器对象
	glShaderSource(vertexShader, 1, &vertexShaderSouce, NULL);//着色器源码给着色器
	glCompileShader(vertexShader);//编译着色器

	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//检查编译着色器是否成功
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);//获取失败信息
		std::cout << "编译着色器失败: " << infoLog << std::endl;
	}

	//片段着色器
	const char *fragmentShaderSource = "#version 330 core\n"
		"in vec4 vertexColor;\n"
		"out vec4 fragColor;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"	fragColor = vertexColor;\n"
		//"	fragColor = ourColor;\n"
		"}\0";

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);//检查编译着色器是否成功
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);//获取失败信息
		std::cout << "编译着色器失败: " << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram();//创建程序对象
	glAttachShader(shaderProgram, vertexShader);//将顶点着色器附加到程序中
	glAttachShader(shaderProgram, fragmentShader);//将片段着色器附加到程序中
	glLinkProgram(shaderProgram);//链接着色器

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "链接着色器失败: " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);//链接完着色器后可以删掉创建的着色器了
	glDeleteShader(fragmentShader);//链接完着色器后可以删掉创建的着色器

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GlslTest::flush()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);//激活程序对象

	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 0.0f);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void GlslTest::release()
{
	delete this;
}