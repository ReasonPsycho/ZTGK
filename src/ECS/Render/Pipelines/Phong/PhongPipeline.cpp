//
// Created by redkc on 15/04/2024.
//

#include "PhongPipeline.h"



void PhongPipeline::Init(Camera* camera,Primitives* primitives)  {

    _primitives = primitives;
    
    phongShader.init();
    phongInstanceShader.init();
    textureSampler.init();

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    SetUpTextureBuffers(camera->saved_display_w, camera->saved_display_h);
    
    isInnit = true;
}

void PhongPipeline::PrebindPipeline(Camera *camera) {
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();
    glm::vec3 cameraPos = camera->Position;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_BLEND);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);

    GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Depends on your needs
    
    
    phongInstanceShader.use();
    phongInstanceShader.setBool("shadows", true);
    phongInstanceShader.setMatrix4("projection", false, glm::value_ptr(projection));
    phongInstanceShader.setMatrix4("view", false, glm::value_ptr(view));
    phongInstanceShader.setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);
    phongInstanceShader.setFloat("far_plane", 25.0f);
    
    phongShader.use();

    phongShader.setBool("shadows", true);
    phongShader.setMatrix4("projection", false, glm::value_ptr(projection));
    phongShader.setMatrix4("view", false, glm::value_ptr(view));
    phongShader.setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);
    phongShader.setFloat("far_plane", 25.0f);
    
    
}

void PhongPipeline::SetUpTextureBuffers(int width, int height) {
    if(isInnit){
        glDeleteTextures(2, colorAttachments);
    }
    
    GLubyte whitePixel[4] = {255, 255, 255,255};
    GLubyte *whiteImage = new GLubyte[width * height * 4];
    for (int i = 0; i < width * height * 4; i += 4) {
        whiteImage[i] = whitePixel[0];
        whiteImage[i + 1] = whitePixel[1];
        whiteImage[i + 2] = whitePixel[2];
        whiteImage[i + 3] = whitePixel[3];
    }

    glGenTextures(2, colorAttachments);

    for (int i = 0; i <2; ++i) {
        glBindTexture(GL_TEXTURE_2D, colorAttachments[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, whiteImage);
        // Set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorAttachments[i], 0);
    }

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}

void PhongPipeline::WriteToBackBuffer(Camera *camera) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Depends on your needs
    textureSampler.use();
    glActiveTexture(GL_TEXTURE0); // Work with Texture Unit 0
    glBindTexture(GL_TEXTURE_2D, colorAttachments[0]); // Bind it to GL_TEXTURE_2D   
     glActiveTexture(GL_TEXTURE1); // Work with Texture Unit 0
    glBindTexture(GL_TEXTURE_2D, colorAttachments[1]); // Bind it to GL_TEXTURE_2D 
    textureSampler.setMatrix4("clip_to_view", false, glm::value_ptr(glm::inverse(camera->GetProjectionMatrix())));  // Here 0 is the texture unit
    
    textureSampler.setInt("colorTexture", 0);  // Here 0 is the texture unit
    textureSampler.setInt("normals_depth_texture", 1);  // Here 0 is the texture unit
    
    textureSampler.setFloat("depth_threshold", 1);  // Here 0 is the texture unit
    textureSampler.setFloat("depth_normal_threshold", 1);  // Here 0 is the texture unit
    textureSampler.setFloat("depth_normal_threshold_scale",  0.2);  // Here 0 is the texture unit
    textureSampler.setFloat("normal_threshold",  0.5);  // Here 0 is the texture unit
    
    textureSampler.setFloat("outline_width", 3);  // Here 0 is the texture unit
    textureSampler.setVec3("outline_color", glm::vec3(0));  // Here 0 is the texture unit
    
    _primitives->renderQuad();
}
