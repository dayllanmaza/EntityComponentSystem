///-------------------------------------------------------------------------------------------------
/// File:	Camera.cpp.
///
/// Summary:	Implements the camera class.
///-------------------------------------------------------------------------------------------------

#include "Camera.h"

Camera::Camera() :
	m_Mode(PerspectiveViewmode),
	m_fov(60.0f),
	m_aspect(1.0f),
	m_Near(0.01f),
	m_Far(100.0f),
	m_zoom(1.0f),
	m_Position(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_LookAt(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_Up(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_Viewport(0.0f, 0.0f, 1.0f, 1.0f)
{}

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) :
	m_Mode(PerspectiveViewmode),
	m_fov(60.0f),
	m_aspect(1.0f),
	m_Near(0.01f),
	m_Far(100.0f),
	m_zoom(1.0f),
	m_Position(eye),
	m_LookAt(target),
	m_Up(up),
	m_Viewport(0.0f, 0.0f, 1.0f, 1.0f)
{}

Camera::~Camera()
{}

Transform Camera::GetViewTransform()
{
	if (this->m_Mode == PerspectiveViewmode)
	{
		return glm::lookAt(this->m_Position, this->m_LookAt, this->m_Up);
	}
	else
	{
		glm::mat4 P = glm::translate(glm::mat4(1.0), this->m_Position);
		return P;
	}
}

Transform Camera::GetProjectionTransform()
{
	if (this->m_Mode == PerspectiveViewmode)
	{
		return glm::perspective(this->m_fov, this->m_aspect, this->m_Near, this->m_Far);
	}
	else
	{
		const float scaledHalfWidth  = this->m_Viewport.z * 0.5f * this->m_zoom;
		const float scaledHalfHeight = this->m_Viewport.w * 0.5f * this->m_zoom;

		return glm::ortho(-scaledHalfWidth, scaledHalfWidth, scaledHalfHeight, -scaledHalfHeight, this->m_Near, this->m_Far);
	}
}