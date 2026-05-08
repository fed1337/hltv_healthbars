#include "stdafx.h"

auto load_png_texture(const char *filename, int *width, int *height) -> unsigned int {
    std::vector<unsigned char> image;
    unsigned w = 0;
    unsigned h = 0;

    // Decode PNG directly from file → RGBA8
    unsigned error = lodepng::decode(image, w, h, filename);

    if (error != 0U) {
        // You probably want better logging here
        // but don't silently continue
        return 0;
    }

    if (width != nullptr) {
        *width = static_cast<int>(w);
    }
    if (height != nullptr) {
        *height = static_cast<int>(h);
    }

    // Create OpenGL texture
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(w), static_cast<GLsizei>(h), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image.data());

    return texture;
}
