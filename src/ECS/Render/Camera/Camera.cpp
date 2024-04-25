//
// Created by redkc on 21/11/2023.
//

#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float nearClip, float farClip) : Front(
        glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), nearClip(
        nearClip), farClip(farClip) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(
        glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, double deltaTime) {
    float velocity = MovementSpeed * (float)deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    if (direction == UPWARD)
        Position += Up * velocity;
    if (direction == DOWNWARD)
        Position -= Up * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch, double deltaTime) {
    xoffset *= MouseSensitivity * deltaTime;
    yoffset *= MouseSensitivity * deltaTime;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset, float deltaTime) {
    Zoom -= (float) yoffset * deltaTime;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front,
                                      WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::UpdateShader(Shader *shader) {
    shader->use();
    // pass projection matrix to shader 
    glm::mat4 projection = GetProjectionMatrix();
    shader->setMatrix4("projection", false, glm::value_ptr(projection));

    // camera/view transformation
    glm::mat4 view = GetViewMatrix();
    shader->setMatrix4("view", false, glm::value_ptr(view));
}

void Camera::UpdateShader(Shader *shader, int display_w, int display_h) {
    saved_display_w = display_w;
    saved_display_h = display_h;
    shader->use();
    // pass projection matrix to shader 
    glm::mat4 projection = GetProjectionMatrix();
    shader->setMatrix4("projection", false, glm::value_ptr(projection));

    // camera/view transformation
    glm::mat4 view = GetViewMatrix();
    shader->setMatrix4("view", false, glm::value_ptr(view));
}

glm::mat4 Camera::GetProjectionMatrix() {
    return glm::perspective(glm::radians(Zoom), (float) saved_display_w / (float) saved_display_h, nearClip, farClip);
}

void Camera::UpdateCamera(int display_w, int display_h) {
    saved_display_w = display_w;
    saved_display_h = display_h;
}


glm::vec3 Camera::getDirFromCameraToCursor(float mouseX, float mouseY, int screenWidth, int screenHeight) {
    // Calculate normalized device coordinates (NDC)
    float x = (2.0f * mouseX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / screenHeight;
    float z = 1.0f;

    // Convert NDC to clip space
    glm::vec3 ray_nds = glm::vec3(x, y, z);
    glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0, 1.0);

    // Convert clip space to eye space
    glm::vec4 ray_eye = glm::inverse(GetProjectionMatrix()) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

    // Convert eye space to world space (use updated view matrix)
    glm::mat4 viewMatrix = GetViewMatrix();
    glm::vec3 ray_wor = glm::vec3(glm::inverse(viewMatrix) * ray_eye);
    ray_wor = glm::normalize(ray_wor);

    return ray_wor;
}

float Camera::GetAspectRatio() {
    return (float ) saved_display_w/(float )saved_display_h;
}

















