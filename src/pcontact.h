#pragma once
#include "particle.h"
class ParticleContact{
    public:
        Particle* particle[2];  
        real restitution;
        Vector3 contactNormal;
        real penetration;
        real calculateSeparatingVelocity() const;
        void resolve(real duration);
        Vector3 particleMovement [2];
        void resolveVelocity(real duration);
        void resolveInterpenetration(real duration);

};

class ParticleContactResolver{
    protected:
        unsigned iterations;
        unsigned iterationsUsed;
    public:
        ParticleContactResolver(unsigned iterations);
        void setIterations(unsigned iterations);
        void resolveContacts(ParticleContact * contactArray, unsigned numContacts, real duration);
};

class ParticleContactGenerator{
    public:
        virtual unsigned fillContact(ParticleContact *contact, unsigned limit) const = 0;
};


