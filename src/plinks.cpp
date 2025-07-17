#include "plinks.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

ParticleLink::ParticleLink(Particle* p1, Particle* p2){
    particle[0]=p1;
    particle[1]=p2;
}

real ParticleLink::currentLength() const{
    Vector3 relativePos = particle[0]->getPosition() -
                          particle[1]->getPosition();
    return relativePos.magnitude();
}

unsigned ParticleCable::fillContact(ParticleContact *contact,
                                    unsigned limit) const
{
    real length = currentLength();

    if (length < maxLength)
    {
        return 0;
    }

    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
    normal.normalize();
    contact->contactNormal = normal;

    contact->penetration = length-maxLength;
    contact->restitution = restitution;

    return 1;
}

ParticleRod::ParticleRod(Particle* p1, Particle* p2, real length): length(length), ParticleLink(p1, p2){};

unsigned ParticleRod::fillContact(ParticleContact *contact, unsigned limit) const{
    real currentLen = currentLength();

    if (currentLen == length){
        return 0;
    }

    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    Vector3 normal = particle[1]->getPosition() - particle[0]->getPosition();
    normal.normalize();

    if (currentLen > length) {
        contact->contactNormal = normal;
        contact->penetration = currentLen - length;
    } 
    else {
        contact->contactNormal = normal * -1;
        contact->penetration = length - currentLen;
    }
    

    contact->restitution = 0;

    return 1;
}

real ParticleConstraint::currentLength() const
{
    Vector3 relativePos = particle->getPosition() - anchor;
    return relativePos.magnitude();
}

unsigned ParticleRodConstraint::fillContact(ParticleContact *contact,unsigned limit) const{
    real currentLen = currentLength();

    if (currentLen == length)
    {
    return 0;
    }

    contact->particle[0] = particle;
    contact->particle[1] = nullptr;
    
    Vector3 normal = anchor - particle->getPosition();
    normal.normalize();

    if (currentLen > length) {
    contact->contactNormal = normal;
    contact->penetration = currentLen - length;
    } else {
    contact->contactNormal = normal * -1;
    contact->penetration = length - currentLen;
    }

    contact->restitution = 0;

    return 1;
}

VerletRod::VerletRod(Particle* p1, Particle* p2, real length): length(length){
    particle[0]=p1;
    particle[1]=p2;
}


void VerletRod::solveConstraint(){
    Vector3 delta = particle[0]->getPosition() - particle[1]->getPosition();
    real error = delta.magnitude() - length;
    // std::cout<<fabs(error)<<particle[0]->getPosition()<<" "<<particle[1]->getPosition()<<delta.magnitude()<<" "<<length<<std::endl;
    if(fabs(error)< 1e-6) return;
    // std::cout<<"HIIIIIIIIIII"<<std::endl;
    delta.normalize();
    delta*=error/2.0f;
    particle[0]->setPosition(particle[0]->getPosition()-delta);
    particle[1]->setPosition(particle[1]->getPosition()+delta);
}

VerletAnchor::VerletAnchor(Particle* p1, Vector3 anchor, real length): length(length), anchor(anchor){
    p=p1;
}


void VerletAnchor::solveConstraint(){
    Vector3 delta = p->getPosition() - anchor;

    real error = delta.magnitude() - length;
    // std::cout<<error<<std::endl;

    delta.normalize();
    delta*=error;
    p->setPosition(p->getPosition()-delta);
}


