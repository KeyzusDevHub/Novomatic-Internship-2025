#include "Renderer.hpp"

int main() {

    float L = 0.3f;
    float h = std::sqrt(3) / 2.0f * L;

    auto t1 = std::make_shared<triangle>(
        -L / 2.0f, -h / 3.0f,
         L / 2.0f, -h / 3.0f,
         0.0f,      2 * h / 3.0f
    );

    auto t2 = std::make_shared<triangle>(-0.8f, -0.8f,
                                         -0.6f, -0.8f,
                                         -0.7f,  -0.6f);

    auto t3 = std::make_shared<triangle>(0.8f, 0.8f,
                                        0.6f, 0.8f,
                                        0.5f,  0.6f);

    auto t4 = std::make_shared<triangle>(-0.8f, 0.81f,
                                        -0.45f, 0.83f,
                                        -0.55f,  0.62f);
                                        
    auto t5 = std::make_shared<triangle>(0.8f, -0.74f,
                                        0.22f, -0.92f,
                                        0.14f,  -0.77f);

    std::vector<std::shared_ptr<triangle>> triangles;
    triangles.push_back(t1);
    triangles.push_back(t2);
    triangles.push_back(t3);
    triangles.push_back(t4);
    triangles.push_back(t5);

    auto renderer = std::make_unique<Renderer>();
    GLFWwindow* window = renderer->init(triangles);

    while (!glfwWindowShouldClose(window)) {

        renderer->processInput(triangles[0]);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer->render(triangles);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
