#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

    void processMouseMovement(float xoffset, float yoffset);
    void processScroll(float yoffset);
    void updateCameraVectors();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

    void setTarget(const glm::vec3& target);

private:
    float yaw, pitch;
    float distance;
    float fov;
    float aspect, near, far;

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
};
