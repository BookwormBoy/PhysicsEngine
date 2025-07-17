#include "cloth.h"
#include "vertexBufferLayout.h"
#include "plinks.h"
#include <algorithm>
#include <random>


Cloth::Cloth(int width, int height, real spacing, int iterations, real stringHeight, real anchorHeight): width(width), height(height), spacing(spacing), vb(nullptr, 0), iterations(iterations), stringHeight(stringHeight), anchorHeight(anchorHeight){


    //adding cloth particles
    for(int j=0;j<width;j++){
        for(int i=0;i<height;i++){
            Particle* p = new Particle(5, Vector3(i*spacing - (width-1)/2.0f*spacing,0, j*spacing - (height-1)/2.0f*spacing), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, -2.0f, 0.0f), 0.995f);
            this->clothParticles.push_back(p);
        }

    }

    //top main anchor
    this->anchorPoint = Vector3(0.0f, this->anchorHeight+this->stringHeight, 0.0f);

    int freq=1;

    //adding strings, cardboardParticles and anchors together with the addString function
    for (int i = 0; i < width; i+=freq) {
        addString(i, height-1, stringHeight);
    }

    for (int j = height - 2; j >= 0; j-=freq) {
        addString(width-1, j, stringHeight);
    }

    for (int i = width - 2; i >= 0; i-=freq) {
        addString(i, 0, stringHeight);
    }

    for (int j = 1; j < height - 1; j+=freq) {
        addString(0, j, stringHeight);
    }


    //adding clothConstraints
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            Particle* current = clothParticles[j * width + i];

            if (i < width - 1) {
                Particle* right = clothParticles[j * width + (i + 1)];
                clothConstraints.push_back(new VerletRod(current, right, spacing));
            }
    
            if (j < height - 1) {
                Particle* down = clothParticles[(j + 1) * width + i];
                clothConstraints.push_back(new VerletRod(current, down, spacing));
            }
        }
    }

    // adding cardboardConstraints

    // along the perimeter
    for(int i=0;i<cardboardParticles.size();i++){
        Particle* p1 = cardboardParticles[i];
        Particle* p2 = cardboardParticles[(i+1)%cardboardParticles.size()];

        VerletRod* c = new VerletRod(p1, p2, spacing);
        cardboardConstraints.push_back(c);
    }

    //vertical constraints (front to back)
    for(int i=0;i<width;i++){
        Particle* p1 = cardboardParticles[i];
        int index = width + height - 1 + width -1 - i - 1;
        Particle* p2 = cardboardParticles[index];
        VerletRod* rod = new VerletRod(p1, p2, (height-1) * spacing);
        cardboardConstraints.push_back(rod);
    }

    //horizontal constraints (left to right)
    for(int i=0;i<height;i++){
        Particle* p1 = cardboardParticles[width - 1 + i];
        int index = (width + height - 1 + width - 1 + height-1 - i-1)%(cardboardParticles.size());
        Particle* p2 = cardboardParticles[index];
        VerletRod* rod = new VerletRod(p1, p2, (width-1) * spacing);
        cardboardConstraints.push_back(rod);
    }
    // std::cout<<"Initial Constraints"<<std::endl;
    // for(auto* rod: cardboardConstraints){
    //     std::cout<<rod->particle[0]->getPosition()<<" "<<rod->particle[1]->getPosition()<<std::endl;
    // }

    for (int i = 0; i < 50; ++i) {
        for (auto* anchor : anchors) {
            anchor->solveConstraint();
        }
        for (auto* rod : strings) {
            rod->solveConstraint();
        }
    }
    //diagonals
    Vector3 diag = cardboardParticles[0]->getPosition() - cardboardParticles[width + height - 2]->getPosition();
    real diagLen = diag.magnitude();
    cardboardConstraints.push_back(new VerletRod(cardboardParticles[0], cardboardParticles[width + height - 2], diagLen));
    cardboardConstraints.push_back(new VerletRod(cardboardParticles[width -1], cardboardParticles[width + height - 2 + width -1], diagLen));

    VertexBufferLayout layout;
    layout.push<float>(3);
    va.addBuffer(vb, layout);
    vb.unbind();
    va.unbind();    
}


void Cloth::addString(real x, real y, real height) {
    int index = y * width + x;
    Particle* p = clothParticles[index];
    Vector3 anchorPos = p->getPosition() + Vector3(0.0f, height, 0.0f);

    Particle* cardboardPoint = new Particle(5, anchorPos, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, -2.0f, 0.0f), 0.995f);
    cardboardParticles.push_back(cardboardPoint);

    VerletRod* string = new VerletRod(p, cardboardPoint, height);
    strings.push_back(string);

    Vector3 tempAnchor = anchorPos + Vector3(0.0f, this->anchorHeight, 0.0f);
    // std::cout<<anchorPos<<std::endl;
    VerletAnchor* anchor = new VerletAnchor(cardboardPoint, this->anchorPoint, (this->anchorPoint-anchorPos).magnitude());
    // VerletAnchor* anchor = new VerletAnchor(cardboardPoint, tempAnchor, this->anchorHeight);

    anchors.push_back(anchor);
}

void Cloth::cutString(int offset) {
    int toRemove = std::min(10, static_cast<int>(strings.size()) - offset);

    if (toRemove <= 0) {
        std::cout << "Invalid offset or not enough strings to remove.\n";
        return;
    }

    // Erase from the back to avoid shifting indices
    for (int i = toRemove - 1; i >= 0; --i) {
        strings.erase(strings.begin() + offset + i);
    }


}

void Cloth::update(real duration){
    for (auto* p : clothParticles) {
        p->verletIntegrate(duration);
    }

    for(auto* p : cardboardParticles){
        p->verletIntegrate(duration);
    }
    for(int i=0;i<iterations;i++){

        for(auto* rod: clothConstraints){
            rod->solveConstraint();
        }
        // std::random_device rd; // Obtain a random number from hardware
        // std::mt19937 g(rd());
        // std::shuffle(cardboardConstraints.begin(), cardboardConstraints.end(), g);
        for(auto* rod: cardboardConstraints){
            rod->solveConstraint();
        }

        for(auto* rod: strings){
            rod->solveConstraint();
        }

        for(auto* anchor: anchors){
            anchor->solveConstraint();
        }

        
        // anchors[0]->solveConstraint();
    }

}

void Cloth::render(){
    std::vector<float> vertices;

    auto addLine = [&](const Vector3& p1, const Vector3& p2) {
        vertices.push_back(p1.x);
        vertices.push_back(p1.y);
        vertices.push_back(p1.z);
        vertices.push_back(p2.x);
        vertices.push_back(p2.y);
        vertices.push_back(p2.z);
    };
    
    for (auto* rod : clothConstraints) {
        addLine(rod->particle[0]->getPosition(), rod->particle[1]->getPosition());
    }
    
    for (auto* rod : cardboardConstraints) {
        addLine(rod->particle[0]->getPosition(), rod->particle[1]->getPosition());
    }
    
    for (auto* rod : strings) {
        addLine(rod->particle[0]->getPosition(), rod->particle[1]->getPosition());
    }
    
    for (auto* rod : anchors) {
        addLine(rod->p->getPosition(), rod->anchor);
    }
    // addLine(anchors[0]->p->getPosition(), this->anchorPoint);

    
    vb.update(vertices.data(), vertices.size() * sizeof(float));

    va.bind();
    GLCall(glDrawArrays(GL_LINES, 0, clothConstraints.size() * 2 + anchors.size()*2 + cardboardConstraints.size()*2 + strings.size()*2));
    va.unbind();

}

