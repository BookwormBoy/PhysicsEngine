float cubeVertices[120] = {
        //positions            //texture coords

        //front face
        -0.5f, -0.5f,  0.5f,     0.0f, 0.0f, //bottom left
        -0.5f,  0.5f,  0.5f,     0.0f, 1.0f, //top left
         0.5f,  0.5f,  0.5f,     1.0f, 1.0f, //top right
         0.5f, -0.5f,  0.5f,     1.0f, 0.0f, //bottom right

         //left face
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, //bottom left
        -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, //top left
        -0.5f,  0.5f,  0.5f,     1.0f, 1.0f, //top right
        -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, //bottom right

         //right face
         0.5f, -0.5f,  0.5f,     0.0f, 0.0f, //bottom left
         0.5f,  0.5f,  0.5f,     0.0f, 1.0f, //top left
         0.5f,  0.5f, -0.5f,     1.0f, 1.0f, //top right
         0.5f, -0.5f, -0.5f,     1.0f, 0.0f, //bottom right

         //top face
        -0.5f,  0.5f,  0.5f,     0.0f, 0.0f, //bottom left
        -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, //top left
         0.5f,  0.5f, -0.5f,     1.0f, 1.0f, //top right
         0.5f,  0.5f,  0.5f,     1.0f, 0.0f, //bottom right

         //bottom face
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, //bottom left
        -0.5f, -0.5f,  0.5f,     0.0f, 1.0f, //top left
         0.5f, -0.5f,  0.5f,     1.0f, 1.0f, //top right
         0.5f, -0.5f, -0.5f,     1.0f, 0.0f, //bottom right

         //back face
         0.5f, -0.5f, -0.5f,     0.0f, 0.0f, //bottom left
         0.5f,  0.5f, -0.5f,     0.0f, 1.0f, //top left
        -0.5f,  0.5f, -0.5f,     1.0f, 1.0f, //top right
        -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, //bottom right
        

};


unsigned int cubeIndices[36] = {
    //front face
    (4*0)+0, (4*0)+1, (4*0)+3,
    (4*0)+1, (4*0)+2, (4*0)+3,

    //left face
    (4*1)+0, (4*1)+1, (4*1)+3,
    (4*1)+1, (4*1)+2, (4*1)+3,

    //right face
    (4*2)+0, (4*2)+1, (4*2)+3,
    (4*2)+1, (4*2)+2, (4*2)+3,

    //top face
    (4*3)+0, (4*3)+1, (4*3)+3,
    (4*3)+1, (4*3)+2, (4*3)+3,

    //bottom face
    (4*4)+0, (4*4)+1, (4*4)+3,
    (4*4)+1, (4*4)+2, (4*4)+3,

    //back face
    (4*5)+0, (4*5)+1, (4*5)+3,
    (4*5)+1, (4*5)+2, (4*5)+3,
};