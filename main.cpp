//
//  main.cpp
//  COMP371A1
//
//  Created by Zhao Rui on 2018-02-02.
//  Copyright © 2018 Zhao Rui. All rights reserved.
//

#include <iostream>
#include "ShaderProg.h"

// GLEW
#define GLEW_STATIC
#include </usr/local/Cellar/glew/2.1.0/include/GL/glew.h>

//GLFW
#include </usr/local/Cellar/glfw-master/include/GLFW/glfw3.h>

//glm
#include </usr/local/Cellar/glm/0.9.8.5/include/glm/glm.hpp>
#include </usr/local/Cellar/glm/0.9.8.5/include/glm/gtc/matrix_transform.hpp>
#include </usr/local/Cellar/glm/0.9.8.5/include/glm/gtc/type_ptr.hpp>
using namespace std;

const unsigned int WIDTH=800, HEIGHT=800;
// ---- VIEW MATRIX global variables -----
glm::vec3 c_pos = glm::vec3(0, 0, 10); // camera position
glm::vec3 c_dir = glm::normalize(glm::vec3(0, 0, -10)); // camera direction
glm::vec3 c_up = glm::vec3(0, 1, 0); // tell the camera which way is 'up'
glm::mat4 view;

void updateView()
{
    view = glm::lookAt(c_pos, c_pos + c_dir, c_up);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if (key == GLFW_KEY_DOWN)
    {
        //c_pos.z += 1;
        c_pos.y-=1;
        updateView();
    }
    
    if (key == GLFW_KEY_UP)
    {
        //c_pos.z -= 1;
        c_pos.y+=1;
        updateView();
    }
}

int main() {
    //initialize glfw
    if(!glfwInit())
    {
        cout<<"Failed to initialize glfw."<<endl;
        return EXIT_FAILURE;
    }
    
    //glfw configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //create a window
    GLFWwindow *window=glfwCreateWindow(WIDTH,HEIGHT, "assignment1", nullptr, nullptr);
    if(!window)
    {
        cout<<"Failed to open a glfw window."<<endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glewExperimental=GL_TRUE;
    glfwSetKeyCallback(window, key_callback);
    
    //configure viewport
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);
    
    //initialize glew
    if(GLEW_OK!=glewInit())
    {
        cout<<"Failed to initialize glew."<<endl;
        return EXIT_FAILURE;
    }
    
    //enable z-buffer
    glEnable(GL_DEPTH_TEST);
    
    
    //vertices for the ground square
    float square[]={
        
        -0.5f,-0.5f,0.0f,//left bottom
        0.5f,-0.5f,0.0f,//right bottom
        0.5f,0.5f,0.0f,//right top
        -0.5f,0.5f,0.0f,//left top

        
    };
    
    ShaderProg groundShader("squarevs.vs","squarefs.fs");//shader program for ground
    ShaderProg horseShader("horsevs.vs","horsefs.fs");//shader program for horse
    
    
    //vertices for a cube
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
    
    //world space position of different parts of the horse
    glm::vec3 bodyPosition=glm::vec3(0.0f,3.0f,0.0f);//body
    glm::vec3 fluPosition=glm::vec3(-1.5f,2.0f,-0.5f);//front-left-upper leg
    glm::vec3 fllPosition=glm::vec3(-1.5f,1.0f,-0.5f);//front-left-lower leg
    glm::vec3 fruPosition=glm::vec3(-1.5f,2.0f,0.5f);//front-right-upper leg
    glm::vec3 frlPosition=glm::vec3(-1.5f,1.0f,0.5f);//front-right-lower leg
    glm::vec3 bluPosition=glm::vec3(1.5f,2.0f,-0.5f);//back-left-upper leg
    glm::vec3 bllPosition=glm::vec3(1.5f,1.0f,-0.5f);//back-left-lower leg
    glm::vec3 bruPosition=glm::vec3(1.5f,2.0f,0.5f);//back-right-upper leg
    glm::vec3 brlPosition=glm::vec3(1.5f,1.0f,0.5f);//back-right-lower leg
    glm::vec3 neckPosition=glm::vec3(-2.5f,3.5f,0.0f);//neck
    glm::vec3 headPosition=glm::vec3(-4.0f,3.5f,0.0f);//head
    
    //VAO
    GLuint VAOs[2], VBOs[2];//two VAOs and VBOs, one for the ground, one for the horse
    glGenVertexArrays(2,VAOs);
    glGenBuffers(2,VBOs);
    
    
    //ground
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(square),square,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    
    //horse
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    

    
    
    
    //game loop
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//wireframe mode

        
        //view matrix
        view=glm::lookAt(c_pos, c_pos+c_dir, c_up);

        
        //projection matrix
        glm::mat4 projection=glm::mat4(1.0f);
        projection=glm::perspective(45.0f, (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

        
        //initialize model matrix
        glm::mat4 model=glm::mat4(1.0f);
        
        
        //draw ground
        glBindVertexArray(VAOs[0]);
        groundShader.use();
        groundShader.setMat4("view", view);
        groundShader.setMat4("projection", projection);
        model=glm::translate(model, glm::vec3(0.5f,0.5f,0.0f));
        model=glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f,0.0f,0.0f));
        groundShader.setMat4("model", model);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        
        
        //draw horse
        glBindVertexArray(VAOs[1]);
        horseShader.use();
        horseShader.setMat4("view", view);
        horseShader.setMat4("projection", projection);
        //----------------
        //body
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, bodyPosition);
        model=glm::scale(model, glm::vec3(4.0f,1.5f,2.0f));
        horseShader.setMat4("model", model);
        //horseShader.setMat4("view", view);
        //horseShader.setMat4("projection", projection);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.2f,0.1f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //flu
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, fluPosition);
        model=glm::scale(model, glm::vec3(0.5f,1.0f,0.5f));
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.4f,0.5f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //fll
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, fllPosition);
        model=glm::scale(model, glm::vec3(0.5f,1.0f,0.5f));
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.6f,0.6f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //fru
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, fruPosition);
        model=glm::scale(model, glm::vec3(0.5f,1.0f,0.5f));
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.4f,0.5f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //frl
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, frlPosition);
        model=glm::scale(model, glm::vec3(0.5f,1.0f,0.5f));
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.6f,0.6f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //blu
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, bluPosition);
        model=glm::scale(model, glm::vec3(0.5f,1.0f,0.5f));
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.4f,0.5f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //bll
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, bllPosition);
        model=glm::scale(model, glm::vec3(0.5f,1.0f,0.5f));
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.6f,0.6f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //bru
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, bruPosition);
        model=glm::scale(model, glm::vec3(0.5f,1.0f,0.5f));
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.4f,0.5f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //brl
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, brlPosition);
        model=glm::scale(model, glm::vec3(0.5f,1.0f,0.5f));
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.6f,0.6f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //neck
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, neckPosition);
        model=glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f,0.0f,1.0f));
        model=glm::scale(model, glm::vec3(2.5f,1.0f,0.5f));
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.4f,0.2f,0.6f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //head
        model=glm::mat4(1.0f);//reset
        model=glm::translate(model, headPosition);
        model=glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f,0.0f,1.0f));
        model=glm::scale(model, glm::vec3(1.5f,0.5f,0.5f));
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.4f,0.3f,0.3f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        
        
        
        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //glDeleteVertexArrays(1,&VAO);
    //glDeleteBuffers(1,&VBO);
    
    glfwTerminate();
    return 0;
}