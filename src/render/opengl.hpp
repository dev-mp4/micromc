#ifndef MICROMC_OPENGL_HPP
#define MICROMC_OPENGL_HPP

class OpenGL {
public:
    static bool init(int width, int height);
    static void clear(float r, float g, float b);
    static void enableDepth();
    static void disableDepth();
    static void enableCulling();
    static void disableCulling();
    static void toggleWireframe();
    static void updateWireframe();
    
    static bool wireframe;
};

#endif // MICROMC_OPENGL_HPP