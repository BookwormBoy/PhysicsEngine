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
        unsigned maxContacts;
        ParticleContactResolver resolver;
        std::vector<ParticleContact> contacts;
        bool calculateIterations;
        int iterations;
    public:
        std::vector<Particle*> particles;
        std::vector<ParticleRod*> constraints;
        std::vector<ParticleRodConstraint*> strings;
        std::vector<VerletRod*> verletConstraints;
        std::vector<VerletAnchor*> verletAnchors;
        float cut=0;
        VertexArray va;
        VertexBuffer vb;
    
        Cloth(int width, int height, real spacing, unsigned maxContacts, int iterations);
        // ~Cloth();

        void update(real duration);
        void addString(real x, real y, real height, std::vector<float> &vertices);
        void cutString();
        void render();
    };
    