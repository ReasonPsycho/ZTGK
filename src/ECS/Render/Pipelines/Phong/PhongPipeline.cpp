//
// Created by redkc on 15/04/2024.
//

#include "PhongPipeline.h"



void PhongPipeline::Init(Camera* camera,Primitives* primitives)  {

    _primitives = primitives;
    
    phongShader.init();
    phongInstanceShader.init();
    phongInstanceLightShader.init();
    textureSampler.init();

    downscale.init();
    upscale.init();
    
    m_mip_levels =4 ; //It dosn't work above it
    //CalculateMipmapLevels(camera->saved_display_w,camera->saved_display_h);
    
    glCreateFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    SetUpTextureBuffers(camera->saved_display_w, camera->saved_display_h);
    
    bloomDirtTexture = new Texture("res/textures/bloom_dirt_mask.png","");
    
    
    isInnit = true;
}

void PhongPipeline::PrebindPipeline(Camera *camera) {
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();
    glm::vec3 cameraPos = camera->Position;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << error << std::endl;
    }
    GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);
    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << error << std::endl;
    }
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);


    GLenum fb_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch (fb_status) {
        case GL_FRAMEBUFFER_COMPLETE:
            std::cout << "SUCCESS::FRAMEBUFFER:: Framebuffer is complete." << std::endl;
            break;
        case GL_FRAMEBUFFER_UNDEFINED:
            std::cout << "ERROR::FRAMEBUFFER::GL_FRAMEBUFFER_UNDEFINED:: Default framebuffer does not exist." << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            std::cout << "ERROR::FRAMEBUFFER::GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:: Any of the framebuffer attachment points are framebuffer incomplete." << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            std::cout << "ERROR::FRAMEBUFFER::GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:: The framebuffer does not have at least one image attached to it." << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            std::cout << "ERROR::FRAMEBUFFER::GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:: The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi." << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            std::cout << "ERROR::FRAMEBUFFER::GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:: GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER." << std::endl;
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            std::cout << "ERROR::FRAMEBUFFER::GL_FRAMEBUFFER_UNSUPPORTED:: The combination of internal formats of the attached images violates an implementation-dependent set of restrictions." << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            std::cout << "ERROR::FRAMEBUFFER::GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:: The value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or , if the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES." << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            std::cout << "ERROR::FRAMEBUFFER::GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:: Any framebuffer attachment is layered and any populated attachment is not layered, or all populated color attachments are not from textures of the same target." << std::endl;
            break;
        default:
            std::cout << "ERROR::FRAMEBUFFER:: Unknown error." << std::endl;
            break;
    }
    
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


    phongInstanceLightShader.use();
    phongInstanceLightShader.setMatrix4("projection", false, glm::value_ptr(projection));
    phongInstanceLightShader.setMatrix4("view", false, glm::value_ptr(view));
    phongInstanceLightShader.setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);

    glDisable(GL_BLEND);
}

void PhongPipeline::SetUpTextureBuffers(int width, int height) {
    if(isInnit){
        glDeleteTextures(3, colorAttachments);
    }
    
    GLubyte whitePixel[4] = {255, 255, 255,255};
    GLubyte *whiteImage = new GLubyte[width * height * 4];
    for (int i = 0; i < width * height * 4; i += 4) {
        whiteImage[i] = whitePixel[0];
        whiteImage[i + 1] = whitePixel[1];
        whiteImage[i + 2] = whitePixel[2];
        whiteImage[i + 3] = whitePixel[3];
    }


    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << error << std::endl;
    }
    glCreateTextures(GL_TEXTURE_2D, 3, colorAttachments);
    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << error << std::endl;
    }
    for (int i = 0; i <3; ++i) {
        glTextureStorage2D(colorAttachments[i], m_mip_levels, GL_RGBA32F, width, height); // internalformat = GL_RGB32F

        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL Error: " << error << std::endl;
        }
        glTextureParameteri(colorAttachments[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(colorAttachments[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(colorAttachments[i], GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
        glTextureParameteri(colorAttachments[i], GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);


        glNamedFramebufferTexture(frameBuffer, GL_COLOR_ATTACHMENT0 + i, colorAttachments[i], 0);
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL Error: " << error << std::endl;
        }
        glNamedFramebufferRenderbuffer(frameBuffer, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, frameBuffer);
        if (error != GL_NO_ERROR) {
            std::cout << "OpenGL Error: " << error << std::endl;
        }
    }

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << error << std::endl;
    }
}

void PhongPipeline::WriteToBackBuffer(Camera *camera) {
    
    if(bloomEnabled)
    {
        downscale.use();
        downscale.setVec4("u_threshold", glm::vec4(m_threshold, m_threshold - m_knee, 2.0f * m_knee, 0.25f * m_knee));
        glBindTextureUnit(0,colorAttachments[2]); //IDK check it
        glm::uvec2 mip_size = glm::uvec2(camera->saved_display_w / 2,camera->saved_display_h / 2);

        for (uint8_t i = 0; i < m_mip_levels - 1; ++i)
        {
            downscale.setVec2("u_texel_size",    1.0f / glm::vec2(mip_size));
            downscale.setInt("u_mip_level",     i);
            downscale.setInt("u_use_threshold", i == 0);

            glBindImageTexture(0, colorAttachments[2], i  + 1, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

            glDispatchCompute(glm::ceil(float(mip_size.x) / 8), glm::ceil(float(mip_size.y) / 8), 1);

            mip_size = mip_size / 2u;

            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
        }

        /* Bloom: upscale */
        upscale.use();
        upscale.setFloat("u_bloom_intensity", m_bloom_intensity);
        upscale.setFloat("u_dirt_intensity",  m_bloom_dirt_intensity);
        glBindTextureUnit(0,colorAttachments[2]); //IDK check it
        bloomDirtTexture->use(GL_TEXTURE1);

        for (uint8_t i = m_mip_levels - 1; i >= 1; --i)
        {
            mip_size.x = glm::max(1.0, glm::floor(float(camera->saved_display_w)  / glm::pow(2.0, i - 1)));
            mip_size.y = glm::max(1.0, glm::floor(float(camera->saved_display_h) / glm::pow(2.0, i - 1)));

            upscale.setVec2("u_texel_size", 1.0f / glm::vec2(mip_size));
            upscale.setInt("u_mip_level",  i);


            glBindImageTexture(0, colorAttachments[2], i - 1, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
            
            glDispatchCompute(glm::ceil(float(mip_size.x) / 8), glm::ceil(float(mip_size.y) / 8), 1);

            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_TEXTURE_FETCH_BARRIER_BIT);
        }
    }

    textureSampler.use();
    glActiveTexture(GL_TEXTURE0); // Work with Texture Unit 0
    glBindTexture(GL_TEXTURE_2D, colorAttachments[0]); // Bind it to GL_TEXTURE_2D   
    glActiveTexture(GL_TEXTURE1); // Work with Texture Unit 0
    glBindTexture(GL_TEXTURE_2D, colorAttachments[1]); // Bind it to GL_TEXTURE_2D
    glActiveTexture(GL_TEXTURE2); // Work with Texture Unit 0
    glBindTexture(GL_TEXTURE_2D, colorAttachments[2]); // Bind it to GL_TEXTURE_2D
    textureSampler.setMatrix4("clip_to_view", false, glm::value_ptr(glm::inverse(camera->GetProjectionMatrix())));  // Here 0 is the texture unit

    textureSampler.setInt("colorTexture", 0);  // Here 0 is the texture unit
    textureSampler.setInt("normals_depth_texture", 1);  // Here 0 is the texture unit

    textureSampler.setFloat("depth_threshold", 1);  // Here 0 is the texture unit
    textureSampler.setFloat("depth_normal_threshold", 1);  // Here 0 is the texture unit
    textureSampler.setFloat("depth_normal_threshold_scale",  0.2);  // Here 0 is the texture unit
    textureSampler.setFloat("normal_threshold",  0.5);  // Here 0 is the texture unit

    textureSampler.setFloat("outline_width", 3);  // Here 0 is the texture unit
    textureSampler.setVec3("outline_color", glm::vec3(0));  // Here 0 is the texture unit

    textureSampler.setFloat("exposure", exposure);  // Here 0 is the texture unit
    textureSampler.setFloat("gamma", gamma);  // Here 0 is the texture unit
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Depends on your needs
    _primitives->renderQuad();
}

void PhongPipeline::CalculateMipmapLevels(int width, int height) {

    uint8_t  mip_levels = 1;

    printf("Mip level %d: %d x %d\n", 0, width, height);
    width  /= 2;
    height /= 2;
    printf("Mip level %d: %d x %d\n", mip_levels, width, height);

    for (uint8_t i = 0; i < m_max_iterations; ++i)
    {
        width  = width  / 2;
        height = height / 2;

        if (width < m_downscale_limit || height < m_downscale_limit) break;

        ++mip_levels;

        printf("Mip level %d: %d x %d\n", mip_levels, width, height);
    }

    m_mip_levels = mip_levels + 1;
}

