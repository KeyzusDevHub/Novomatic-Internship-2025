#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "config.hpp"
#include "Triangle.hpp"

class Renderer {
    private:
        GLuint shaderProgram;
        GLuint colorLoc;
        GLuint transformLoc;
        std::vector<GLuint> VAOs, VBOs;
        GLFWwindow* window;
        int bufferSize;
        float moveSpeed, rotSpeed;

        GLuint loadShader(const std::string& filePath, GLenum type);
        void setupShaders();
        void setupBuffers(std::vector<std::shared_ptr<triangle>> triangles);
        void updateColor(bool isColliding);
        void updateVertexData(std::shared_ptr<triangle> tri, GLuint VBO);
        void drawTriangle(GLuint vao);
        
    public:
        Renderer();
        ~Renderer();

        GLFWwindow* init(std::vector<std::shared_ptr<triangle>> triangles);
        void processInput(std::shared_ptr<triangle> tri);
        void render(std::vector<std::shared_ptr<triangle>> triangles);

};

#endif
