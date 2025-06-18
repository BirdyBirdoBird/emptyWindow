#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    constexpr int SCREEN_WIDTH = 800;
    constexpr int SCREEN_HEIGHT = 600;
    constexpr float VERTICES[] = {
        // front face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // top right
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // bottom right
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // bottom left
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  // top left

        // back face
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // top right
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  // bottom right
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom left
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // top left

        // left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // top right
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // bottom right
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom left
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // top left

        // right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // top right
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // bottom right
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom left
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // top left

         // top face
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  // top right
         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  // top left
         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // bottom left
          0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // bottom right

          // bottom face
           0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  // top right
          -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // top left
          -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom left
           0.5f, -0.5f, -0.5f,  1.0f, 1.0f   // bottom right
    };

    constexpr unsigned int INDICES[] = {
        // front face
        0, 3, 1,
        1, 3, 2,

        // back face
        4, 5, 7,
        5, 6, 7,

        // left face
        8, 11, 9,
        9, 11, 10,

        // right face
        12, 13, 15,
        13, 14, 15,

        // top face
        16, 19, 17,
        17, 19, 18,

        // bottom face
        20, 21, 23,
        21, 22, 23
    };
}

#endif 