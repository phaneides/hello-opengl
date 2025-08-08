
#include "Camera.hpp"

Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
    : yaw(-90.0f), pitch(0.0f), distance(5.0f),
      fov(fov), aspect(aspectRatio), near(nearPlane), far(farPlane),
      target(0.0f), up(0.0f, 1.0f, 0.0f)
{
    updateCameraVectors();
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    yaw += xoffset * 0.1f;
    pitch += yoffset * 0.1f;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
}

void Camera::processScroll(float yoffset) {
    distance -= yoffset;
    if (distance < 1.0f) distance = 1.0f;
    if (distance > 50.0f) distance = 50.0f;

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    float radYaw = glm::radians(yaw);
    float radPitch = glm::radians(pitch);
    glm::vec3 dir;
    dir.x = cos(radPitch) * cos(radYaw);
    dir.y = sin(radPitch);
    dir.z = cos(radPitch) * sin(radYaw);

    position = target - glm::normalize(dir) * distance;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspect, near, far);
}

void Camera::setTarget(const glm::vec3& tgt) {
    target = tgt;
    updateCameraVectors();
}
