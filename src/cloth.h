#pragma once
#include "particle.h"
#include "plinks.h"
#include "shader.h"
#include "vertexArray.h"
// #include "vertexBufferLayout.h"
#include "pcontact.h"
#include <vector>
class Cloth {
    private:
        int height;
        int width;
        real spacing;
        int iterations;
    public:
        std::vector<Particle*> clothParticles;
        std::vector<Particle*> cardboardParticles;
        std::vector<VerletRod*> clothConstraints;
        std::vector<VerletRod*> cardboardConstraints;
        std::vector<VerletRod*>strings;
        std::vector<VerletAnchor*> anchors;
        Vector3 anchorPoint;
        real stringHeight;
        real anchorHeight;
        float cut=0;
        VertexArray va;
        VertexBuffer vb;
    
        Cloth(int width, int height, real spacing, int iterations, real stringHeight, real anchorHeight);

        void update(real duration);
        void addString(real x, real y, real height);
        void cutString(int offset);
        void render();
    };
    