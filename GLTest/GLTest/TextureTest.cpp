#include "stdafx.h"
#include "TextureTest.h"
#include "stb_image.h"
#include "shader.h"


TextureTest::TextureTest()
{
	VAO = 0;
	VBO = 0;
	EBO = 0;
	texture = 0;
}


TextureTest::~TextureTest()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture);
	delete pShader;
}

void TextureTest::prepare()
{						 
	float vertices[] = {
		0.5f, 0.5f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO); //�����������
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //�ѻ���󶨵�GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //�������ݸ��Ƶ�������

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);//glVertexAttribPointer֮�����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//glVertexAttribPointer֮�����

	//������ɫ��
	const char* vertexShaderSouce = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"layout (location = 2) in vec2 aTexCoord;\n"
		"out vec3 ourColor;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
		"	ourColor = aColor;\n"
		"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
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
		"out vec4 fragColor;\n"
		"in vec3 ourColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D texture1;\n"
		"void main()\n"
		"{\n"
		"	fragColor = texture(texture1, TexCoord);\n"
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
	glDeleteShader(fragmentShader);//��������ɫ�������ɾ����������ɫ����

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char * data = stbi_load("D:\\test\\test\\GLTest\\resources\\textures\\container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
}

void TextureTest::flush()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// bind Texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void TextureTest::release()
{
	delete this;
}