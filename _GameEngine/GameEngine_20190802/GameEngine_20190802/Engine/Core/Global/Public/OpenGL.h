#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

enum class EBasicPrimitive : GLenum
{
	Points = GL_POINTS,
	Lines = GL_LINES,
	LineStrip = GL_LINE_STRIP,
	LineLoop = GL_LINE_LOOP,
	Triangles = GL_TRIANGLES,
	TriangleStrip = GL_TRIANGLE_STRIP,
	TriangleFan = GL_TRIANGLE_FAN
};

// face - GL_FRONT_AND_BACK
enum class EPolygonMode : GLenum
{
	Point = GL_POINT, //�㼯
	Line = GL_LINE, //������
	Fill = GL_FILL //��� Default
};

//glFrontFace
enum class EFrontFace : GLenum
{
	CCW = GL_CCW, //���㰴��ʱ���������Ϊ����
	CW = GL_CW //˳ʱ�룬����ķ��򱻳�Ϊ��������ƣ�winding��
};

//glEnable(GL_CULL_FACE); glDisable(GL_CULL_FACE);
enum class ECullFace : GLenum
{
	Front = GL_FRONT,
	Back = GL_BACK,
	FrontAndBack = GL_FRONT_AND_BACK
};