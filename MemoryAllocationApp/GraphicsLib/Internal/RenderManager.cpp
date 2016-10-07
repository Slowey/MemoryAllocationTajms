// This class
#include "RenderManager.h"

RenderManager* RenderManager::m_singleton = nullptr;

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::DEBUGTriangleCreation()
{
    GLuint t_positionBuffer;
    glGenBuffers(1, &t_positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, t_positionBuffer);
    // Hardcoded square
    float t_data[] = {
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, t_data, GL_STREAM_DRAW);
    GLuint programHandle = m_shaderHandler->GetShaderProgram(ShaderProgram::DefaultShader);
    GLint t_positionUniformHandle = glGetAttribLocation(programHandle, "pos");
    glVertexAttribPointer(t_positionUniformHandle, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(t_positionUniformHandle);
}


RenderManager * RenderManager::Get()
{
    // Todo: safer handling when startup not called
    if (m_singleton != nullptr)
        return m_singleton;
    return nullptr;
}

void RenderManager::Startup()
{
    m_singleton = new RenderManager();
    RenderManager::Get()->m_shaderHandler = new ShaderHandler();
    RenderManager::Get()->DEBUGTriangleCreation();
}

void RenderManager::Render()
{
    // Set background color. Probably should be done here
    glClearColor(0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Start render with default shader
    glUseProgram(m_shaderHandler->GetShaderProgram(ShaderProgram::DefaultShader));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}

