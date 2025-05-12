#include "Renderer.hpp"

Renderer::Renderer() : moveSpeed(0.01f), rotSpeed(1.0f) {}

GLFWwindow* Renderer::init(std::vector<std::shared_ptr<triangle>> triangles) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle Collision", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(-1);
    }
    
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    
    bufferSize = triangles.size();
    VAOs.resize(bufferSize);
    VBOs.resize(bufferSize);

    setupShaders();
    setupBuffers(triangles);
    
    colorLoc = glGetUniformLocation(shaderProgram, "uColor");
    
    return window;
}

GLuint Renderer::loadShader(const std::string& filePath, GLenum type) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Failed to load shader: " << filePath << std::endl;
        exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();
    
    GLuint shader = glCreateShader(type);
    const char* codeCStr = code.c_str();
    glShaderSource(shader, 1, &codeCStr, nullptr);
    glCompileShader(shader);
    
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compile error:\n" << infoLog << std::endl;
    }
    return shader;
}

void Renderer::setupShaders() {
    GLuint vs = loadShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
    GLuint fs = loadShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Renderer::setupBuffers(std::vector<std::shared_ptr<triangle>> triangles) {
    
    glGenVertexArrays(triangles.size(), VAOs.data());
    glGenBuffers(triangles.size(), VBOs.data());
    
    for (int i : std::views::iota(0, static_cast<int>(triangles.size()))) {
        std::array<float, 6> vertices = triangles[i]->arrayRepresentation();
    
        glBindVertexArray(VAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
}

void Renderer::processInput(std::shared_ptr<triangle> tri) {
    float x = 0;
    float y = 0;
    float rotation = 0;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) y += moveSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) y -= moveSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) x -= moveSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) x += moveSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) rotation += rotSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) rotation -= rotSpeed;
    
    if (x != 0 || y != 0) tri->changePosition(x, y);
    if (rotation != 0)    tri->changeRotation(rotation);
}

void Renderer::updateColor(bool isColliding) {
    if (isColliding) {
        glUniform3f(colorLoc, 1.0f, 0.0f, 0.0f);
    } else {
        glUniform3f(colorLoc, 0.0f, 1.0f, 0.0f);
    }
}

void Renderer::updateVertexData(std::shared_ptr<triangle> tri, GLuint VBO) {
    std::array<float, 6> vertices = tri->arrayRepresentation();
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
}

void Renderer::drawTriangle(GLuint vao) {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::render(std::vector<std::shared_ptr<triangle>> triangles) {
    glUseProgram(shaderProgram);
    
    for (int i : std::views::iota(0, static_cast<int>(triangles.size()))){
        updateVertexData(triangles[i], VBOs[i]);
    }
    
    bool colliding = std::ranges::any_of(
        triangles | std::views::drop(1),
        [&](const auto& tri) {
            return isColliding(*triangles[0], *tri);
        }
    );
    
    updateColor(colliding);
    
    drawTriangle(VAOs[0]);
    
    for (auto vao : VAOs | std::views::drop(1)) {
        glUniform3f(colorLoc, 0.f, 0.f, 1.0f);
        drawTriangle(vao);
    }
    
}

Renderer::~Renderer() {
    glDeleteVertexArrays(bufferSize, VAOs.data());
    glDeleteBuffers(bufferSize, VBOs.data());
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}