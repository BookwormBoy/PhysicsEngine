#include "pfgen.h"

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator *fg){
    registrations.push_back({particle, fg});
}
void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator *fg){
    for(unsigned int i=0;i<registrations.size();i++){
        if(registrations[i].particle==particle && registrations[i].fg==fg){
            registrations.erase(registrations.begin()+i);
            break;
        }
    }
}
void ParticleForceRegistry::clear(){
    registrations.clear();

}
void ParticleForceRegistry::updateForces(real duration){
    for(unsigned int i=0;i<registrations.size();i++){
        registrations[i].fg->updateForce(registrations[i].particle, duration);
    }
}

ParticleGravity::ParticleGravity(const Vector3 &gravity){
    this->gravity = gravity;
}
void ParticleGravity::updateForce(Particle *particle, real duration){
    if (!particle->hasFiniteMass()) return;
    particle->addForce(gravity * particle->getMass());
}

ParticleDrag::ParticleDrag(real k1, real k2) : k1(k1), k2(k2){}

void ParticleDrag::updateForce(Particle *particle, real duration){
    Vector3 force = particle->getVelocity();
    real dragCoeff = force.magnitude();
    dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;
    force.normalize();
    force *= -dragCoeff;
    particle->addForce(force);
}