#include "particle.h"
#include<math.h>
#include <float.h>
#include<iostream>

#define real_pow powf

void Particle::setMass(real mass){
    if(mass==FLT_MAX){
        inverseMass=0;
    }
    else{
        inverseMass = (1/mass);
    }
}

real Particle::getMass(){
    if(inverseMass==0){
        return FLT_MAX;
    }
    else{
        return ((real)1.0)/inverseMass;
    }
}

bool Particle::hasFiniteMass(){
    return inverseMass>0;
}

void Particle::setDamping(real damping){
    this->damping=damping;
}

real Particle::getDamping(){
    return this->damping;
}

void Particle::setPosition(Vector3 position){
    this->position=position;
}

Vector3 Particle::getPosition(){
    return this->position;
}

void Particle::setVelocity(Vector3 velocity){
    this->velocity=velocity;
}

Vector3 Particle::getVelocity(){
    return this->velocity;
}

void Particle::setAcceleration(Vector3 acceleration){
    this->acceleration=acceleration;
}

Vector3 Particle::getAcceleration(){
    return this->acceleration;
}

void Particle::clearAccumulator(){
    forceAccum.clear();
}

void Particle::addForce(const Vector3& force){
    this->forceAccum+=force;
}

void Particle::integrate(real duration){
    position.addScaledVector(velocity, duration);

    Vector3 resultingAcc = acceleration;
    resultingAcc.addScaledVector(forceAccum, inverseMass);

    velocity.addScaledVector(resultingAcc, duration);
    velocity *= real_pow(damping, duration);

    clearAccumulator();
}