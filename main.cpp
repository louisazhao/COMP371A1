//
//  main.cpp
//  COMP371A1
//
//  Created by Zhao Rui on 2018-02-02.
//  Copyright © 2018 Zhao Rui. All rights reserved.
//

#include <iostream>
#include "ShaderProg.h"
#include "DrawHorse.hpp"


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

unsigned int WIDTH=800, HEIGHT=800;
float moveOnX=0,moveOnZ=0;
const float minMove=-40.0f,maxMove=40.0f;
float userScale=1.0f;
float userRotate=0.0f;
glm::vec3 rotateOri=glm::vec3(0.0f,1.0f,0.0f);
float cameraRotate=10.0f;

//camera attributes
float yaw=-90.0f;
float pitch=0.0f;
float lastX=WIDTH/2.0f;//camera first set to the origin
float lastY=HEIGHT/2.0f;//camera first set to the origin
float fov=45.0f;//perspective angle
bool leftMouseButton=false, middleMouseButton=false, rightMouseButton=false;//varibles for detecting the mouse button action
bool firstMouse=true;


// ---- VIEW MATRIX global variables -----
glm::vec3 c_pos = glm::vec3(0.0f,10.0f, 30.0f); // camera position
glm::vec3 c_dir = glm::normalize(glm::vec3(0.0f, -10.0f, -30.0f)); // camera direction
glm::vec3 c_up = glm::vec3(0, 1, 0); // tell the camera which way is 'up'
glm::mat4 view;
glm::mat4 projection;
glm::mat4 model;

void updateView()
{
    view = glm::lookAt(c_pos, c_pos + c_dir, c_up);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    //projection=glm::perspective(fov, (float)width/(float)height, 0.1f, 100.0f);
    WIDTH=width;
    HEIGHT=height;
    int width_,height_;
    glfwGetFramebufferSize(window, &width_, &height_);
    glViewport(0, 0, width_, height_);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if(key==GLFW_KEY_LEFT)//world orientation to right
    {
        c_pos-=glm::normalize(glm::cross(c_dir, c_up));
        //updateView();
    }
    if(key==GLFW_KEY_RIGHT)//world orientation to left
    {
        c_pos+=glm::normalize(glm::cross(c_dir, c_up));
        //updateView();
    }
    if (key == GLFW_KEY_DOWN)//world orientation Ry
    {
        c_pos.y+=1;
        //updateView();
    }
    if (key == GLFW_KEY_UP)//world orientation -Ry
    {
        c_pos.y-=1;
        //updateView();
    }
    if(key==GLFW_KEY_TAB)//reset to the initial world position and orientation.because I'm using Mac, which doesn't have "Home" button, I used "tab" instead
    {
        c_pos = glm::vec3(0.0f,10.0f, 30.0f);
        c_dir = glm::vec3(0.0f, -10.0f, -30.0f); // camera direction
        c_up = glm::vec3(0, 1, 0);
        yaw=-90.0f;
        pitch=0.0f;
        lastX=WIDTH/2.0f;//camera first set to the origin
        lastY=HEIGHT/2.0f;//camera first set to the origin
        rotateOri=glm::vec3(0.0f,1.0f,0.0f);
        fov=45.0f;
        moveOnX=0;
        moveOnZ=0;
        userScale=1.0f;
        userRotate=0.0f;
        model=glm::mat4(1.0f);
        
        //updateView();
    }
    if(key==GLFW_KEY_SPACE&& action == GLFW_PRESS)//randomly change the position of the horse on the grid
    {
        //generating random location in the grid
        moveOnX=minMove + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxMove-minMove)));
        moveOnZ=minMove + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxMove-minMove)));
    }
    if(key==GLFW_KEY_U&&action==GLFW_PRESS)//scale up
    {
        userScale+=0.5;
    }
    if(key==GLFW_KEY_J&&action==GLFW_PRESS)//scale down
    {
        userScale-=0.5;
    }
    if(key==GLFW_KEY_A&&action==GLFW_PRESS)
    {
        if (mode == GLFW_MOD_SHIFT)//move to left by 1 unit grid
        {
            //uppercase
            moveOnX+=-1.0f;
        }
        else //rotate to left by 5 degrees related to y axis
        {
            //lowercase
            userRotate+=5.0f;
            rotateOri=glm::vec3(0.0f,1.0f,0.0f);
        }
    }
    if(key==GLFW_KEY_D&&action==GLFW_PRESS)
    {
        if (mode == GLFW_MOD_SHIFT) {////move to right by 1 unit grid
            //uppercase
            moveOnX+=1.0f;
        }
        else//rotate to left by 5 degrees related to y axis
        {
            //lowercase
            userRotate-=5.0f;
            rotateOri=glm::vec3(0.0f,1.0f,0.0f);
        }
    }
    if(key==GLFW_KEY_W&&action==GLFW_PRESS)
    {
        if (mode == GLFW_MOD_SHIFT) {//move up by 1 unit grid
            //uppercase
            moveOnZ+=-1.0f;
        }
        else {//rise head by 5 degrees
            //lowercase
            userRotate-=5.0f;
            rotateOri=glm::vec3(0.0f,0.0f,1.0f);
        }
    }
    if(key==GLFW_KEY_S&&action==GLFW_PRESS)
    {
        if (mode == GLFW_MOD_SHIFT) {//move down by 1 unit grid
            //uppercase
            moveOnZ+=1.0f;
        }
        else {//rise rear by 5 degrees
            //lowercase
            userRotate+=5.0f;
            rotateOri=glm::vec3(0.0f,0.0f,1.0f);
        }
    }
    if(key==GLFW_KEY_P&&action==GLFW_PRESS)
    {
        glPointSize(10.0f);//make the points more visible
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);//point mode
    }
    if(key==GLFW_KEY_L&&action==GLFW_PRESS)
    {
        glLineWidth(10.0f);//make the lines more visible
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//point mode
    }
    
    if(key==GLFW_KEY_T&&action==GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//wireframe mode
    }
}

//call back funtion for mouse button and movement
void mouse_button_callback(GLFWwindow* window, int key, int action, int mode)
{
    if(key==GLFW_MOUSE_BUTTON_RIGHT&&action==GLFW_PRESS)
    {
        rightMouseButton=true;
    }
    if(key==GLFW_MOUSE_BUTTON_MIDDLE&&action==GLFW_PRESS)
    {
        middleMouseButton=true;
    }
    if(key==GLFW_MOUSE_BUTTON_LEFT&&action==GLFW_PRESS)
    {
        leftMouseButton=true;
    }
    if(key==GLFW_MOUSE_BUTTON_RIGHT&&action==GLFW_RELEASE)
    {
        rightMouseButton=false;
    }
    if(key==GLFW_MOUSE_BUTTON_MIDDLE&&action==GLFW_RELEASE)
    {
        middleMouseButton=false;
    }
    if(key==GLFW_MOUSE_BUTTON_LEFT&&action==GLFW_RELEASE)
    {
        leftMouseButton=false;
    }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)//keep track of the position of the cursor
{
    //cout<<"here"<<endl;
    
    if(firstMouse)
    {
        cout<<"here"<<endl;
        lastX=xPos;
        lastY=yPos;
        firstMouse=false;
    }
     
    
    float xOffset=xPos-lastX;
    float yOffset=lastY-yPos;
    lastX=xPos;
    lastY=yPos;
    
    float sensitivity=0.05f;
    xOffset*=sensitivity;
    yOffset*=sensitivity;
    
    if(rightMouseButton)//yaw
    {
        //cout<<"here"<<endl;
        yaw+=xOffset;
    }
    if(middleMouseButton)//pitch
    {
        //cout<<"here"<<endl;
        pitch+=yOffset;
        if(pitch>89.0f)
        {
            pitch=89.0f;
        }
        if(pitch<-89.0f)
        {
            pitch=-89.0f;
        }
    }
    if(leftMouseButton)//zoom in and out by adjusting the fov degree
    {
        //cout<<"here"<<endl;
        if(fov>=1.0f&&fov<=45.0f)
            fov-=yOffset*0.1;
        if(fov<=1.0f)
            fov=1.0f;
        if(fov>=45.0f)
            fov=45.0f;
    }
    
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    c_dir = glm::normalize(front);
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
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    /*
    //configure viewport
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);
     */
    
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
    
    float coordinate[]={
        
        0.0f,0.0f,0.0f,//x axis
        1.0f,0.0f,0.0f,
        
        
        0.0f,0.0f,0.0f,//y axis
        0.0f,1.0f,0.0f,
        
        0.0f,0.0f,0.0f,//z axis
        0.0f,0.0f,1.0f
        
        
    };
    
    ShaderProg groundShader("squarevs.vs","squarefs.fs");//shader program for ground
    ShaderProg horseShader("horsevs.vs","horsefs.fs");//shader program for horse
    ShaderProg coordinateShader("squarevs.vs","squarefs.fs");//shader program for coordinate
    
    
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
    
    
    //VAO
    GLuint VAOs[3], VBOs[3];//two VAOs and VBOs, one for the ground, one for the horse
    glGenVertexArrays(3,VAOs);
    glGenBuffers(3,VBOs);
    
    
    //ground
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(square),square,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    
    //coordinates
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(coordinate),coordinate,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    
    //horse
    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[2]);
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
        projection=glm::mat4(1.0f);
        projection=glm::perspective(fov, (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

        
        //initialize model matrix
        model=glm::mat4(1.0f);
        
        
        //draw ground
        glBindVertexArray(VAOs[0]);
        groundShader.use();
        groundShader.setMat4("view", view);
        groundShader.setMat4("projection", projection);
        for(int row=0;row<100;row++)
        {
            for(int column=0;column<100;column++)
            {
                model=glm::mat4(1.0f);
                model=glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f,0.0f,0.0f));
                model=glm::translate(model, glm::vec3(-49.5f+(float)column,-49.5f+(float)row,0.0f));
                //we want the center of the grid at the world origin, therefore, the left bottom point should be at (-50,-50,0), consequently, the first offset is -50-(-0.5)=-49.5, same for the row
                groundShader.setVec4("lineColor", 1.0f,1.0f,1.0f,1.0f);
                groundShader.setMat4("model", model);
                glDrawArrays(GL_LINE_LOOP, 0, 4);
            }
        }
        
        
        //draw coordinates
        glBindVertexArray(VAOs[1]);
        coordinateShader.use();
        coordinateShader.setMat4("view", view);
        coordinateShader.setMat4("projection", projection);
        for(int i=0;i<5;i++)
        {
            model=glm::mat4(1.0f);
            coordinateShader.setVec4("lineColor", 1.0, 0.0f, 0.0f, 1.0f);
            model=glm::translate(model, glm::vec3(0.0f+(float)i,0.0f+0.02,0.0f));//give the transform a little offset on Y axis, so it wont be hiden from the grid
            coordinateShader.setMat4("model", model);
            glDrawArrays(GL_LINES, 0, 2);
        }
        for(int i=0;i<5;i++)
        {
            model=glm::mat4(1.0f);
            coordinateShader.setVec4("lineColor", 0.0, 1.0f, 0.0f, 1.0f);
            model=glm::translate(model, glm::vec3(0.0f,0.0f+(float)i+0.02,0.0f));//give the transform a little offset on Y axis, so it wont be hiden from the grid
            coordinateShader.setMat4("model", model);
            glDrawArrays(GL_LINES, 2, 2);
        }
        for(int i=0;i<5;i++)
        {
            model=glm::mat4(1.0f);
            coordinateShader.setVec4("lineColor", 0.0, 0.0f, 1.0f, 1.0f);
            model=glm::translate(model, glm::vec3(0.0f,0.0f+0.02,0.0f+(float)i));//give the transform a little offset on Y axis, so it wont be hiden from the grid
            coordinateShader.setMat4("model", model);
            glDrawArrays(GL_LINES, 4, 2);
        }

        
        //draw horse
        glBindVertexArray(VAOs[2]);
        horseShader.use();
        horseShader.setMat4("view", view);
        horseShader.setMat4("projection", projection);
        //--------------------------------------------------
        //body
        model=drawHorse(BODY,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.2f,0.1f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //flu
        model=drawHorse(FLU,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.4f,0.5f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //fll
        model=drawHorse(FLL,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.6f,0.6f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //fru
        model=drawHorse(FRU,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.4f,0.5f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //frl
        model=drawHorse(FRL,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.6f,0.6f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //blu
        model=drawHorse(BLU,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.4f,0.5f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //bll
        model=drawHorse(BLL,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.6f,0.6f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //bru
        model=drawHorse(BRU,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.4f,0.5f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //brl
        model=drawHorse(BRL,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.2f,0.6f,0.6f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //neck
        model=drawHorse(NECK,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.4f,0.2f,0.6f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //head
        model=drawHorse(HEAD,userRotate,rotateOri,userScale,moveOnX,moveOnZ);
        horseShader.setMat4("model", model);
        horseShader.setVec4("partColor", glm::vec4(0.4f,0.3f,0.3f,1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glDeleteVertexArrays(3,VAOs);
    glDeleteBuffers(3,VBOs);
    
    glfwTerminate();
    return 0;
}
