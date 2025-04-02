#pragma once
#include "particle.h"
#include "pcontact.h"

class ParticleLink{
    public:
        Particle* particle[2];
    protected:
        real currentLength() const;
    public:
        virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const =0;
};

class ParticleCable : public ParticleLink{
    public:
        real maxLength;
        real restitution;
        virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const;
};

class ParticleRod : public ParticleLink{
    public:
        real length;

    public:
        virtual unsigned addContact(ParticleContact *contact,
                                     unsigned limit) const;
    };