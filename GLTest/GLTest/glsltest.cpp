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

	glGenVertexArrays(1, &VAO);//������������
	glBindVertexArray(VAO);//��VAO

	glGenBuffers(1, &VBO); //�����������
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //�ѻ���󶨵�GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //�������ݸ��Ƶ�������

																			   //���Ӷ�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);//���ö������ԣ�//registered VBO as the vertex attribute's bound vertex buffer object

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//glVertexAttribPointer֮�����

	//������ɫ��
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

	unsigned int vertexShader;//��ɫ��id
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//������ɫ������
	glShaderSource(vertexShader, 1, &vertexShaderSouce, NULL);//��ɫ��Դ�����ɫ��
	glCompileShader(vertexShader);//������ɫ��

	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//��������ɫ���Ƿ�ɹ�
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);//��ȡʧ����Ϣ
		std::cout << "������ɫ��ʧ��: " << infoLog << std::endl;
	}

	//Ƭ����ɫ��
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

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);//��������ɫ���Ƿ�ɹ�
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);//��ȡʧ����Ϣ
		std::cout << "������ɫ��ʧ��: " << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram();//�����������
	glAttachShader(shaderProgram, vertexShader);//��������ɫ�����ӵ�������
	glAttachShader(shaderProgram, fragmentShader);//��Ƭ����ɫ�����ӵ�������
	glLinkProgram(shaderProgram);//������ɫ��

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "������ɫ��ʧ��: " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);//��������ɫ�������ɾ����������ɫ����
	glDeleteShader(fragmentShader);//��������ɫ�������ɾ����������ɫ��

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void GlslTest::flush()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shaderProgram);//����������

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