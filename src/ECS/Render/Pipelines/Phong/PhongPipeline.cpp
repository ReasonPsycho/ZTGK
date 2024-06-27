//
// Created by redkc on 15/04/2024.
#include "ECS/Utils/Time.h"
#include <filesystem>
#include "PhongPipeline.h"



void PhongPipeline::Init(Camera* camera,Primitives* primitives)  {

    _primitives = primitives;

    phongShader.init();
    phongInstanceShader.init();
    phongInstanceLightShader.init();
    textureSampler.init();
    stencilTest.init();
    foamMaskShader.init();
    spriteRenderShader.init();
    particleShader.init();
    minimap.init();
    
    particle.init();
    downscale.init();
    upscale.init();

    m_mip_levels =4 ; //It doesn't work above it
    //CalculateMipmapLevels(camera->saved_display_w,camera->saved_display_h);

    glCreateFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glCreateFramebuffers(1, &foamFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, foamFrameBuffer);
    
    SetUpTextureBuffers(camera->saved_display_w, camera->saved_display_h);

    bloomDirtTexture = new Texture("res/textures/bloom_dirt_mask.png","");

    Color foamColor = {0, 0, 0, 0};  // Normal map neutral

    std::filesystem::path foamMapTexturesDictionary("res/textures/foamMap"); // Replace with your directory
    if (std::filesystem::exists(foamMapTexturesDictionary) && std::filesystem::is_directory(foamMapTexturesDictionary)) {
        for (const auto &entry: std::filesystem::directory_iterator(foamMapTexturesDictionary)) {
            if (entry.is_regular_file() && entry.path().extension() == ".png") {
                std::cout << "PNG file located: " << entry.path().string() << std::endl;
                foamMaterial.depthTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
                foamMaterial.diffuseTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
                foamMaterial.normalTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
                foamMaterial.specularTextures.push_back(std::make_shared<Texture>(entry.path().string(), ""));
            }
        }
    }

    foamMaterial.mapTextureArrays();
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
    GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3, attachments);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

    glDrawBuffer(GL_COLOR_ATTACHMENT3);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint bindAttachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,GL_COLOR_ATTACHMENT3};
    glDrawBuffers(4, bindAttachments);
    CheckFramebuffer();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Depends on your needs


    phongInstanceShader.use();
    phongInstanceShader.setBool("shadows", true);
    phongInstanceShader.setMatrix4("projection", false, glm::value_ptr(projection));
    phongInstanceShader.setMatrix4("view", false, glm::value_ptr(view));
    phongInstanceShader.setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);
    phongInstanceShader.setFloat("far_plane", 25.0f);

    phongInstanceShader.setFloat("dirtMultiplayer", dirtMultiplayer);
    
    
    phongInstanceShader.setFloat("ambient", ambient);
    phongInstanceShader.setFloat("saturationMultiplayer", saturationMultiplayer);
    phongInstanceShader.setFloat("lightMultiplayer", lightMultiplayer);
    phongInstanceShader.setFloat("diffuse_levels", diffuse_levels);

    phongInstanceShader.setFloat("specular_levels", specular_levels);
    phongInstanceShader.setFloat("light_shade_cutoff", light_shade_cutoff);
    phongInstanceShader.setFloat("dark_shade_cutoff", dark_shade_cutoff);
    phongInstanceShader.setInt("toon_color_levels", toon_color_levels);
    
    phongInstanceShader.setFloat("outlineMapping", instanceShaderOutlineMapping);
    phongInstanceShader.setFloat("u_time", Time::Instance().CurrentTime());

    phongShader.use();

    phongShader.setBool("shadows", true);
    phongShader.setMatrix4("projection", false, glm::value_ptr(projection));
    phongShader.setMatrix4("view", false, glm::value_ptr(view));
    phongShader.setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);
    phongShader.setFloat("far_plane", 25.0f);
    
    phongShader.setFloat("dirtMultiplayer", dirtMultiplayer);

    phongShader.setFloat("ambient", ambient);
    phongShader.setFloat("saturationMultiplayer", saturationMultiplayer);
    phongShader.setFloat("lightMultiplayer", lightMultiplayer);
    phongShader.setFloat("diffuse_levels", diffuse_levels);

    phongShader.setFloat("specular_levels", specular_levels);
    phongShader.setFloat("light_shade_cutoff", light_shade_cutoff);
    phongShader.setFloat("dark_shade_cutoff", dark_shade_cutoff);
    phongShader.setInt("toon_color_levels",toon_color_levels);


    phongShader.setFloat("rim_threshold", rim_threshold);
    phongShader.setFloat("rim_amount", rim_amount);
    phongShader.setFloat("rim_multiplier", rim_multiplier);
    phongShader.setFloat("outlineMapping", normalShaderOutlineMapping);


    phongInstanceLightShader.use();
    phongInstanceLightShader.setMatrix4("projection", false, glm::value_ptr(projection));
    phongInstanceLightShader.setMatrix4("view", false, glm::value_ptr(view));
    phongInstanceLightShader.setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);
    phongInstanceLightShader.setVec3("cameraUp", camera->Up.x, camera->Up.y, camera->Up.z);
    phongInstanceLightShader.setFloat("outlineMapping", lightShaderOutlineMapping);

    particleShader.use();
    particleShader.setMatrix4("projection", false, glm::value_ptr(projection));
    particleShader.setMatrix4("view", false, glm::value_ptr(view));
    particleShader.setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);
    particleShader.setVec3("cameraUp", camera->Up.x, camera->Up.y, camera->Up.z);
    particleShader.setFloat("outlineMapping", particleShaderOutlineMapping);
    
    spriteRenderShader.use();
    spriteRenderShader.setMatrix4("projection", false, glm::value_ptr(projection));
    spriteRenderShader.setMatrix4("view", false, glm::value_ptr(view));
    spriteRenderShader.setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);
    spriteRenderShader.setVec3("cameraUp", camera->Up.x, camera->Up.y, camera->Up.z);
    spriteRenderShader.setFloat("outlineMapping", lightShaderOutlineMapping);
    
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
    glCreateTextures(GL_TEXTURE_2D, 4, colorAttachments);
    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL Error: " << error << std::endl;
    }
    for (int i = 0; i <4; ++i) {
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

    glBindFramebuffer(GL_FRAMEBUFFER,foamFrameBuffer);
    glCreateTextures(GL_TEXTURE_2D, 1,&foamColorAttachment);

    glTextureStorage2D(foamColorAttachment, 1, GL_RGBA32F, width, height); // internalformat = GL_RGB32F
    
    glTextureParameteri(foamColorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(foamColorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(foamColorAttachment, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTextureParameteri(foamColorAttachment, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);


    glNamedFramebufferTexture(foamFrameBuffer, GL_COLOR_ATTACHMENT0, foamColorAttachment, 0);
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
    glActiveTexture(GL_TEXTURE3); // Work with Texture Unit 0
    glBindTexture(GL_TEXTURE_2D, colorAttachments[3]); // Bind it to GL_TEXTURE_2D
    glActiveTexture(GL_TEXTURE4); // Work with Texture Unit 0
    glBindTexture(GL_TEXTURE_2D, foamColorAttachment); // Bind it to GL_TEXTURE_2D
    textureSampler.setMatrix4("clip_to_view", false, glm::value_ptr(glm::inverse(camera->GetProjectionMatrix())));  // Here 0 is the texture unit

    textureSampler.setInt("colorTexture", 0);  // Here 0 is the texture unit
    textureSampler.setInt("normals_depth_texture", 1);  // Here 0 is the texture unit
    textureSampler.setInt("FogOfWarMask", 3);  // Here 0 is the texture unit
    textureSampler.setInt("foamMask", 4);  // Here 0 is the texture unit
    
    textureSampler.setFloat("depth_threshold", depth_threshold);  // Here 0 is the texture unit
    textureSampler.setFloat("depth_normal_threshold", depth_normal_threshold);  // Here 0 is the texture unit
    textureSampler.setFloat("depth_normal_threshold_scale",  depth_normal_threshold_scale);  // Here 0 is the texture unit
    textureSampler.setFloat("normal_threshold",  normal_threshold);  // Here 0 is the texture unit

    textureSampler.setFloat("outline_width", outline_width);  // Here 0 is the texture unit
    textureSampler.setVec3("outline_color",outline_color);  // Here 0 is the texture unit

    textureSampler.setFloat("exposure", exposure);  // Here 0 is the texture unit
    textureSampler.setFloat("gamma", 1.5f);  // Here 0 is the texture unit
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

void PhongPipeline::PrepareFoamMap(Camera* camera) {

    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 view = camera->GetViewMatrix();
    glm::vec3 cameraPos = camera->Position;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


    glBindFramebuffer(GL_FRAMEBUFFER, foamFrameBuffer);
    GLuint attachments[1] = { GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, attachments);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    CheckFramebuffer();

    glClear(GL_COLOR_BUFFER_BIT ); //Depends on your needs

    foamMaskShader.use();

    foamMaskShader.setBool("shadows", true);
    foamMaskShader.setMatrix4("projection", false, glm::value_ptr(projection));
    foamMaskShader.setMatrix4("view", false, glm::value_ptr(view));
    foamMaskShader.setVec3("camPos", cameraPos.x, cameraPos.y, cameraPos.z);
    foamMaskShader.setFloat("far_plane", 25.0f);

    foamMaskShader.setFloat("saturationMultiplayer", ztgk::game::saturationMultiplayer);
    foamMaskShader.setFloat("lightMultiplayer", ztgk::game::lightMultiplayer);
    foamMaskShader.setFloat("diffuse_levels", diffuse_levels);

    foamMaskShader.setFloat("specular_levels", specular_levels);
    foamMaskShader.setFloat("light_shade_cutoff", light_shade_cutoff);
    foamMaskShader.setFloat("dark_shade_cutoff", dark_shade_cutoff);
    foamMaskShader.setInt("toon_color_levels", ztgk::game::toon_color_levels);


    foamMaskShader.setFloat("rim_threshold", rim_threshold);
    foamMaskShader.setFloat("rim_amount", rim_amount);
    
    foamMaskShader.setFloat("repeatFactor", 30);
    foamMaskShader.setFloat("u_time",Time::Instance().CurrentTime());

    glm::mat4x4 model = glm::mat4x4 (1);
    model = glm::translate(model,glm::vec3(100,1, 100));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
    model = glm::scale(model,glm::vec3(100));
    foamMaskShader.setMatrix4("model", false, glm::value_ptr(model));
    foamMaterial.loadReapetedInstancedMaterial(&foamMaskShader);
    _primitives->renderQuad();
    
    glDisable(GL_BLEND);
}

PhongPipeline::PhongPipeline() {
    name = "Phong pipeline";
}

void PhongPipeline::addComponent(void *component) {

}

void PhongPipeline::removeComponent(void *component) {

}

void PhongPipeline::showImGuiDetailsImpl(Camera *camera) {
    if (ImGui::CollapsingHeader("Exposure Settings"))
    {
        ImGui::Indent();
        ImGui::DragFloat("Exposure", &exposure, 0.1f);
        ImGui::DragFloat("Gamma", &gamma, 0.1f);
        ImGui::Unindent();
    }

    if (ImGui::CollapsingHeader("Dirt mask"))
    {
        ImGui::Indent();
        ImGui::DragFloat("Dirt multiplayer", &dirtMultiplayer, 0.01f);
        ImGui::Unindent();
    }


    if (ImGui::CollapsingHeader("Bloom Settings"))
    {
        ImGui::Indent();
        ImGui::Checkbox("Bloom Enabled", &bloomEnabled);
        ImGui::DragFloat("Threshold", &m_threshold, 0.1f);
        ImGui::DragFloat("Knee", &m_knee, 0.1f);
        ImGui::DragFloat("Bloom Intensity", &m_bloom_intensity, 0.1f);
        ImGui::DragFloat("Bloom Dirt Intensity", &m_bloom_dirt_intensity, 0.1f);
        ImGui::Unindent();
    }

    if (ImGui::CollapsingHeader("Toon Shader Settings"))
    {
        ImGui::Indent();
        ImGui::DragFloat("Ambient light", &ambient, 0.1f);
        ImGui::DragFloat("Diffuse Levels", &diffuse_levels, 0.1f);
        ImGui::DragFloat("Specular Levels", &specular_levels, 0.1f);
        ImGui::DragFloat("Light Shade Cutoff", &light_shade_cutoff, 0.1f);
        ImGui::DragFloat("Dark Shade Cutoff", &dark_shade_cutoff, 0.1f);
        ImGui::DragFloat("Saturation Multiplier", &saturationMultiplayer, 0.1f);
        ImGui::DragFloat("Light Multiplier", &lightMultiplayer, 0.1f);
        ImGui::Unindent();
    }

    if (ImGui::CollapsingHeader("Rim Light Settings"))
    {
        ImGui::Indent();
        ImGui::DragFloat("Rim Threshold", &rim_threshold, 0.05f);
        ImGui::DragFloat("Rim Amount", &rim_amount, 0.05f);
        ImGui::DragFloat("Rim multiplier", &rim_multiplier, 0.05f);
        ImGui::Unindent();
    }

    if (ImGui::CollapsingHeader("Outlines Settings"))
    {
        ImGui::Indent();
        ImGui::DragFloat("Depth Threshold", &depth_threshold, 0.1f);
        ImGui::DragFloat("Depth Normal Threshold", &depth_normal_threshold, 0.1f);
        ImGui::DragFloat("Depth Normal Threshold Scale", &depth_normal_threshold_scale, 0.1f);
        ImGui::SliderFloat("Normal Threshold", &normal_threshold, 0.0f, 1.0f);
        ImGui::DragFloat("Outline Width", &outline_width, 0.1f);
        ImGui::ColorEdit3("Outline Color", glm::value_ptr(outline_color));


        ImGui::Checkbox("Normal shader outline mapping", &normalShaderOutlineMapping);
        ImGui::Checkbox("Light shader outline mapping", &lightShaderOutlineMapping);
        ImGui::Checkbox("Particle shader outline mapping", &particleShaderOutlineMapping);
        ImGui::Checkbox("Instance shader outline mapping", &instanceShaderOutlineMapping);
        ImGui::Unindent();
    }
}

void PhongPipeline::UpdateImpl() {

}

void PhongPipeline::CheckFramebuffer() {
    GLenum fb_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch (fb_status) {
        case GL_FRAMEBUFFER_COMPLETE:
            //std::cout << "SUCCESS::FRAMEBUFFER:: Framebuffer is complete." << std::endl;
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
}

