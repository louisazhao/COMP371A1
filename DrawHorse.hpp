//
//  DrawHorse.hpp
//  COMP371A1
//
//  Created by Zhao Rui on 2018-02-07.
//  Copyright © 2018 Zhao Rui. All rights reserved.
//

#include <vector>
#include </usr/local/Cellar/glm/0.9.8.5/include/glm/glm.hpp>
#include </usr/local/Cellar/glm/0.9.8.5/include/glm/gtc/matrix_transform.hpp>
#include </usr/local/Cellar/glm/0.9.8.5/include/glm/gtc/type_ptr.hpp>

#ifndef DrawHorse_h
#define DrawHorse_h

//world space position of different parts of the horse
glm::vec3 bodyPosition=glm::vec3(0.0f,2.5f,0.0f);//body
glm::vec3 fluPosition=glm::vec3(-1.5f,1.5f,-0.5f);//front-left-upper leg
glm::vec3 fllPosition=glm::vec3(-1.5f,0.5f,-0.5f);//front-left-lower leg
glm::vec3 fruPosition=glm::vec3(-1.5f,1.5f,0.5f);//front-right-upper leg
glm::vec3 frlPosition=glm::vec3(-1.5f,0.5f,0.5f);//front-right-lower leg
glm::vec3 bluPosition=glm::vec3(1.5f,1.5f,-0.5f);//back-left-upper leg
glm::vec3 bllPosition=glm::vec3(1.5f,0.5f,-0.5f);//back-left-lower leg
glm::vec3 bruPosition=glm::vec3(1.5f,1.5f,0.5f);//back-right-upper leg
glm::vec3 brlPosition=glm::vec3(1.5f,0.5f,0.5f);//back-right-lower leg
glm::vec3 neckPosition=glm::vec3(-2.5f,3.0f,0.0f);//neck
glm::vec3 headPosition=glm::vec3(-4.0f,3.0f,0.0f);//head

//scale for defferent parts
glm::vec3 bodyScale=glm::vec3(4.0f,1.5f,2.0f);
glm::vec3 legScale=glm::vec3(0.5f,1.0f,0.5f);
glm::vec3 neckScale=glm::vec3(2.5f,1.0f,0.5f);
glm::vec3 headScale=glm::vec3(1.5f,0.5f,0.5f);



enum Horse_Parts{
    BODY, FLU,FLL,FRU,FRL,BLU,BLL,BRU,BRL,NECK,HEAD
};

glm::mat4 drawHorse(Horse_Parts partName, float userRotate, glm::vec3 rotateOri, float userScale, float moveOnX, float moveOnZ)
{
    glm::mat4 model;
    if(partName==BODY)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(bodyPosition[0]+moveOnX,bodyPosition[1],bodyPosition[2]+moveOnZ));
        model=glm::scale(model, bodyScale);
    }
    if(partName==FLU)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(fluPosition[0]+moveOnX,fluPosition[1],fluPosition[2]+moveOnZ));
        model=glm::scale(model, legScale);
    }
    if(partName==FLL)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(fllPosition[0]+moveOnX,fllPosition[1],fllPosition[2]+moveOnZ));
        model=glm::scale(model, legScale);
    }
    if(partName==FRU)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(fruPosition[0]+moveOnX,fruPosition[1],fruPosition[2]+moveOnZ));
        model=glm::scale(model, legScale);
    }
    if(partName==FRL)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(frlPosition[0]+moveOnX,frlPosition[1],frlPosition[2]+moveOnZ));
        model=glm::scale(model, legScale);
    }
    if(partName==BLU)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(bluPosition[0]+moveOnX,bluPosition[1],bluPosition[2]+moveOnZ));
        model=glm::scale(model, legScale);
    }
    if(partName==BLL)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(bllPosition[0]+moveOnX,bllPosition[1],bllPosition[2]+moveOnZ));
        model=glm::scale(model, legScale);
    }
    if(partName==BRU)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(bruPosition[0]+moveOnX,bruPosition[1],bruPosition[2]+moveOnZ));
        model=glm::scale(model, legScale);
    }
    if(partName==BRL)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(brlPosition[0]+moveOnX,brlPosition[1],brlPosition[2]+moveOnZ));
        model=glm::scale(model, legScale);
    }
    if(partName==NECK)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(neckPosition[0]+moveOnX,neckPosition[1],neckPosition[2]+moveOnZ));
        model=glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f,0.0f,1.0f));//neck rotation
        model=glm::scale(model, neckScale);
    }
    if(partName==HEAD)
    {
        model=glm::mat4(1.0f);
        model=glm::rotate(model, glm::radians(userRotate), rotateOri);
        model=glm::scale(model, glm::vec3(userScale,userScale,userScale));
        model=glm::translate(model, glm::vec3(headPosition[0]+moveOnX,headPosition[1],headPosition[2]+moveOnZ));
        model=glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f,0.0f,1.0f));//head rotation
        model=glm::scale(model, headScale);
    }
    return model;
}


#endif /* DrawHorse_h */
