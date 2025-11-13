#include "oglib.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



void processInput(GLFWwindow *window);



static float view_right_left = 0.0;
static float view_top_down   = 0.0;
static float view_depth      = -3.0;
static int speed_rotation    = 5;


int main()
{

    GLFWwindow *window = init();

    Shape cube;
    cube.MakeCube();
    glm::vec3 cube_positions[] = {
        glm::vec3( 0.0f,0.0f,0.0f),
        glm::vec3( 2.0f,5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f,-2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f,-3.5f),
        glm::vec3(-1.7f,3.0f,-7.5f),
        glm::vec3( 1.3f, -2.0f,-2.5f),
        glm::vec3( 1.5f,2.0f,-2.5f),
        glm::vec3( 1.5f,0.2f,-1.5f),
        glm::vec3(-1.3f,1.0f,-1.5f)
    };
    Textures text_1(GL_TEXTURE_2D);     
    text_1.texture_wrapping_option(GL_TEXTURE_2D,GL_REPEAT); 
    text_1.texture_filtering_option(GL_TEXTURE_2D,GL_LINEAR);
    text_1.generate_text_img(GL_TEXTURE_2D,"textures/container.jpg", JPG);


    Textures text_2(GL_TEXTURE_2D);
    text_2.texture_wrapping_option(GL_TEXTURE_2D,GL_REPEAT);
    text_2.texture_filtering_option(GL_TEXTURE_2D,GL_LINEAR);
    text_2.generate_text_img(GL_TEXTURE_2D,"textures/awesomeface.png", PNG);

    unsigned int VAO, EBO, VBO; 
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.ind_size(), cube.indeces.begin(), GL_STATIC_DRAW);

    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,cube.ver_size(), cube.vertices.begin(), GL_STATIC_DRAW);
    
    
    Shaders vertex("shaders/vertexshader.glsl", GL_VERTEX_SHADER);    
    Shaders fragment("shaders/fragmentshader.glsl", GL_FRAGMENT_SHADER); 

    std::vector<GLuint> shaders;
    shaders.push_back(vertex.get_id());
    shaders.push_back(fragment.get_id());   

    Shaders Program;
    Program.create_program(shaders);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,sizeof(float) * 5, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glm::mat4 model = glm::mat4(1.0f); 
    model = glm::rotate(model,glm::radians(50.f), glm::vec3(1.0, 1.0, 1.0)); 

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(view_right_left, view_top_down, view_depth));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    
    Program.use();        
    Program.set_int("texture1", 0);
    Program.set_int("texture2", 1);  
    Program.set_mat4("view", glm::value_ptr(view));
    Program.set_mat4("projection", glm::value_ptr(projection));
    Program.set_mat4("model", glm::value_ptr(model));
    
    glEnable(GL_DEPTH_TEST);
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(BG_COLOR);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        processInput(window);
        glfwPollEvents();
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,text_1.get_id());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,text_2.get_id());

        
        Program.use();  
        view = glm::mat4(1.0);
        view = glm::translate(view, glm::vec3(view_right_left, view_top_down, view_depth));
        Program.set_mat4("view", glm::value_ptr(view));

        glBindVertexArray(VAO);
        for(int i=0; i < 10; ++i){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cube_positions[i]);
            if(i < 3){
                model = glm::rotate(model, (float)glfwGetTime() * speed_rotation, glm::vec3(1.0, 0.3, 0.5));
            }
            Program.set_mat4("model", glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        } 

        glBindVertexArray(0); 
        glfwSwapBuffers(window);
    } 
    glfwTerminate();
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    } 
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        view_top_down += 0.1f;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){    
        view_top_down -= 0.1f;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        view_right_left += 0.1f;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        view_right_left -= 0.1f;
    }
    if(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS){
        view_depth += 0.1f;
    }
    if(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS){
        view_depth -= 0.1f;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        speed_rotation += 1;
    }
}
