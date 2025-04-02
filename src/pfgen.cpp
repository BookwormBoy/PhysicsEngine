#include "pfgen.h"
#include <cmath>

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

ParticleSpring::ParticleSpring(Particle *other, real sc, real rl) : other(other), springConstant(sc), restLength(rl){}

void ParticleSpring::updateForce(Particle *particle, real duration){
    Vector3 force = particle->getPosition();
    force -= other->getPosition();

    real magnitude = force.magnitude();
    magnitude = std::fabs(magnitude - restLength);
    magnitude *= springConstant;

    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
}

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3* anchor, real sc, real rl) : anchor(anchor), springConstant(sc), restLength(rl){}

void ParticleAnchoredSpring::updateForce(Particle *particle, real duration){
    Vector3 force = particle->getPosition();
    force -= *anchor;

    real magnitude = force.magnitude();
    magnitude = std::fabs(magnitude - restLength);
    magnitude *= springConstant;

    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
}

ParticleBungee::ParticleBungee(Particle *other, real sc, real rl) : other(other), springConstant(sc), restLength(rl){}

void ParticleBungee::updateForce(Particle *particle, real duration){
    Vector3 force = particle->getPosition();
    force -= other->getPosition();

    real magnitude = force.magnitude();
    if(magnitude <=restLength) return;
    magnitude = std::fabs(magnitude - restLength);
    magnitude *= springConstant;

    force.normalize();
    force *= -magnitude;
    particle->addForce(force);
}

ParticleBuoyancy::ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity) : maxDepth(maxDepth), volume(volume), waterHeight(waterHeight), liquidDensity(liquidDensity){}

void ParticleBuoyancy::updateForce(Particle* particle, real duration){
    real depth = particle->getPosition().y;

    if (depth >= waterHeight + maxDepth) return;

    Vector3 force(0,0,0);
    if (depth <= waterHeight - maxDepth){
        force.y = liquidDensity * volume;
        particle->addForce(force);
        return;
    }

    force.y = liquidDensity * volume * (depth - maxDepth - waterHeight) / 2 * maxDepth;
    particle->addForce(force);

}
