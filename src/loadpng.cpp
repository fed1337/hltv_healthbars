#include "stdafx.h"

auto load_png_texture(const char *filename, int *width, int *height) -> unsigned int {
    std::vector<unsigned char> image;
    unsigned w = 0;
    unsigned h = 0;

    // Decode PNG directly from file → RGBA8
    unsigned error = lodepng::decode(image, w, h, filename);

    if (error != 0U) {
        // You probably want better logging here but don't silently continue
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

    // Use GL_CLAMP_TO_EDGE for UI elements to prevent bleeding lines at the edges
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei) w, (GLsizei) h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

    glBindTexture(GL_TEXTURE_2D, 0); // Don't leave it bound!
    return texture;
}
