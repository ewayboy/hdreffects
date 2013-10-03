#include "renderer.h"

Renderer::Renderer(int width, int height, Camera* camera_) {
	shaderLibrary = new ShaderLibrary();

    camera = camera_;

	_shader = NULL;
}

Renderer::~Renderer() {
	delete shaderLibrary;
    delete cubemap;
}

void Renderer::LoadShaders() {
	shaderLibrary->AddShader(string("basic"));
    shaderLibrary->AddShader(string("cubemap"));
}

void Renderer::LoadCubeMap() {
    HDRTextureCube* hdrTextureCube = new HDRTextureCube();
    hdrTextureCube->Load(string("uffizi_cross"));
    
    MaterialCubeMap* materialCubeMap = new MaterialCubeMap(shaderLibrary->GetShader("cubemap"), hdrTextureCube);

    cubemap = new CubeMap(materialCubeMap);
    cubemap->CreateBufferData();
}

void Renderer::Init() {
	glClearColor(1, 1, 1, 1);

    LoadShaders();
    LoadCubeMap();
}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderCubeMap();
}

void Renderer::RenderCubeMap() {
    _shader = cubemap->GetMaterial()->Bind();
    //_shader->SendUniform("camPosition", camera->GetPosition());
    SendDefaultUniforms();

    cubemap->Draw();
}

void Renderer::SendDefaultUniforms() {
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp = projection * view * model;

    _shader->SendUniform("mvp", mvp);
}

void Renderer::CreateFrameBuffer(GLuint renderTexture) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // attach the render texture to the frame buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTexture, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Renderer::CreateTexture(int width, int height, bool isDepth) {
    GLuint textureId;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    GLenum internalFormat = isDepth ? GL_DEPTH_COMPONENT : GL_RGBA8;
    GLenum format = isDepth ? GL_DEPTH_COMPONENT : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_FLOAT, NULL);                

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureId;
}
