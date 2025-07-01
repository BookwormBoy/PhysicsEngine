#include "cloth.h"
#include "vertexBufferLayout.h"
#include "plinks.h"


Cloth::Cloth(int width, int height, real spacing, unsigned maxContacts, int iterations): width(width), height(height), spacing(spacing), vb(nullptr, 0), resolver(10), maxContacts(maxContacts), iterations(iterations){

    calculateIterations = (iterations == 0);

    contacts.resize(maxContacts);

    std::vector<float> vertices;
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            Particle* p = new Particle();
            p->setMass(5);
            p->setPosition(Vector3(i*spacing - width/2.0f,0, j*spacing - height/2.0f));
            p->setPrevPosition(p->getPosition());
            p->setAcceleration(Vector3(0.0f, -2.0f, 0.0f));
            p->setVelocity(Vector3(0.0f, 0.0f, 0.0f));
            p->setDamping(0.995f);
            this->particles.push_back(p);
        }

    }

    addString(width - 1, 0, 2.0f, vertices);
    addString(width - 1, height - 1, 2.0f, vertices); // Top-right
    addString(0, height - 1, 2.0f, vertices);       // Top-left
    addString(0, 0, 2.0f, vertices);                // Bottom-left

    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            Particle* current = particles[j * width + i];

            // Horizontal rod
            if (i < width - 1) {
                Particle* right = particles[j * width + (i + 1)];
                // constraints.push_back(new ParticleRod(current, right, spacing));
                verletConstraints.push_back(new VerletRod(current, right, spacing));

                vertices.push_back(current->getPosition().x);
                vertices.push_back(current->getPosition().y);
                vertices.push_back(current->getPosition().z);

                vertices.push_back(right->getPosition().x);
                vertices.push_back(right->getPosition().y);
                vertices.push_back(right->getPosition().z);
            }
    
            // Vertical rod
            if (j < height - 1) {
                Particle* down = particles[(j + 1) * width + i];
                // constraints.push_back(new ParticleRod(current, down, spacing));
                verletConstraints.push_back(new VerletRod(current, down, spacing));

                vertices.push_back(current->getPosition().x);
                vertices.push_back(current->getPosition().y);
                vertices.push_back(current->getPosition().z);

                vertices.push_back(down->getPosition().x);
                vertices.push_back(down->getPosition().y);
                vertices.push_back(down->getPosition().z);
            }
        }
    }
    // std::cout<<vertices.size()<<std::endl;
    this->vb.update(vertices.data(), vertices.size() * sizeof(float));
    VertexBufferLayout layout;
    layout.push<float>(3);
    va.addBuffer(vb, layout);
    vb.unbind();
    va.unbind();

    
}


void Cloth::addString(real x, real y, real height, std::vector<float> &vertices) {
    int index = y * width + x;
    Particle* p = particles[index];
    Vector3 anchorPos = p->getPosition() + Vector3(0.0f, height, 0.0f);

    // ParticleRodConstraint* string = new ParticleRodConstraint(p, anchorPos, height);
    VerletAnchor* string = new VerletAnchor(p, anchorPos, height);

    verletAnchors.push_back(string);
    // strings.push_back(string);
    vertices.push_back(p->getPosition().x);
    vertices.push_back(p->getPosition().y);
    vertices.push_back(p->getPosition().z);

    vertices.push_back(anchorPos.x);
    vertices.push_back(anchorPos.y);
    vertices.push_back(anchorPos.z);
}

void Cloth::cutString(){
    // if(strings.size()>0) strings.erase(strings.begin());
    if(verletAnchors.size()>0) verletAnchors.erase(verletAnchors.begin());

}

void Cloth::update(real duration){
    for (auto* p : particles) {
        // p->verletIntegrate(duration);
        p->verletIntegrate(duration);
        // std::cout<<p->getPosition().y<<std::endl;
    }

    // unsigned limit = maxContacts;
    // ParticleContact *nextContact = contacts.data();

    

    // for (auto* rod : constraints){
    //     unsigned used =rod->fillContact(nextContact, limit);
    //     limit -= used;
    //     nextContact += used;

    //     if (limit <= 0) break;
    // }

    // for (auto* rod : strings){
    //     unsigned used =rod->fillContact(nextContact, limit);
    //     limit -= used;
    //     nextContact += used;

    //     if (limit <= 0) break;
    // }

    // int usedContacts = maxContacts - limit;

    // if (usedContacts)
    // {
    //     if (calculateIterations) resolver.setIterations(usedContacts * 2);
    //     resolver.resolveContacts(contacts.data(), usedContacts, duration);
    // }

    for(int i=0;i<iterations;i++){

        for(auto* rod: verletConstraints){
            rod->solveConstraint();
        }

        for(auto* anchor: verletAnchors){
            anchor->solveConstraint();
        }
    }

}

void Cloth::render(){
    std::vector<float> vertices;

    for (auto* rod : verletConstraints) {
        Vector3 p1 = rod->particle[0]->getPosition();
        Vector3 p2 = rod->particle[1]->getPosition();

        vertices.push_back(p1.x);
        vertices.push_back(p1.y);
        vertices.push_back(p1.z);

        vertices.push_back(p2.x);
        vertices.push_back(p2.y);
        vertices.push_back(p2.z);
    }

    for (auto* rod : verletAnchors) {
        Vector3 p1 = rod->p->getPosition();
        Vector3 p2 = rod->anchor;

        vertices.push_back(p1.x);
        vertices.push_back(p1.y);
        vertices.push_back(p1.z);

        vertices.push_back(p2.x);
        vertices.push_back(p2.y);
        vertices.push_back(p2.z);
    }

//     std::cout << "=== Vertex Buffer Contents ===" << std::endl;
// for (size_t i = 0; i < vertices.size(); i += 6) {
//     std::cout << "Line from ("
//               << vertices[i] << ", " << vertices[i + 1] << ", " << vertices[i + 2] << ") to ("
//               << vertices[i + 3] << ", " << vertices[i + 4] << ", " << vertices[i + 5] << ")"
//               << std::endl;
// }
// std::cout << "==============================" << std::endl;
    vb.update(vertices.data(), vertices.size() * sizeof(float));

    va.bind();
    GLCall(glDrawArrays(GL_LINES, 0, verletConstraints.size() * 2 + verletAnchors.size()*2));
    va.unbind();

}

