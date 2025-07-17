#include "particle.h"
#include<math.h>
#include <float.h>
#include<iostream>

#define real_pow powf

Particle::Particle(real mass, Vector3 position, Vector3 velocity, Vector3 acceleration, real damping){
    setMass(mass);
    setPosition(position);
    setPrevPosition(position);
    setVelocity(velocity);
    setAcceleration(acceleration);
    setDamping(damping);
}


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

real Particle::getInverseMass(){
    return inverseMass;
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

void Particle::setPrevPosition(Vector3 pos){
    this->prevPosition=pos;
}

Vector3 Particle::getPrevPosition(){
    return this->prevPosition;
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
    if (inverseMass <= 0.0f) return;

    // assert(duration > 0.0);

    position.addScaledVector(velocity, duration);

    Vector3 resultingAcc = acceleration;
    resultingAcc.addScaledVector(forceAccum, inverseMass);
    // std::cout<<resultingAcc.y<<std::endl;

    velocity.addScaledVector(resultingAcc, duration);

    velocity *= real_pow(damping, duration);

    clearAccumulator();
}

void Particle::verletIntegrate(real duration){
    Vector3 temp=position;
    position = position + (position-prevPosition)*damping + acceleration*damping*duration*duration;
    prevPosition=temp;
}