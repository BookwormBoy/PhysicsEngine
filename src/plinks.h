#pragma once
#include "particle.h"
#include "pcontact.h"

class ParticleLink: public ParticleContactGenerator{
    public:
        Particle* particle[2];
    protected:
        real currentLength() const;
    public:
        ParticleLink(Particle* p1, Particle* p2);
        virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const =0;
};

class ParticleCable : public ParticleLink{
    public:
        real maxLength;
        real restitution;
        virtual unsigned fillContact(ParticleContact* contact, unsigned limit) const override;
};

class ParticleRod : public ParticleLink{
    public:
        real length;
    public:
        ParticleRod(Particle* p1, Particle* p2, real length);
        virtual unsigned fillContact(ParticleContact *contact, unsigned limit) const override;
};

class ParticleConstraint: public ParticleContactGenerator
    {
    public:
        Particle* particle;

        Vector3 anchor;

    protected:
        ParticleConstraint(Particle* p, Vector3 anchor): particle(p), anchor(anchor){};
        real currentLength() const;

    public:

        virtual unsigned fillContact(ParticleContact *contact,
            unsigned limit) const = 0;
    };


class ParticleRodConstraint : public ParticleConstraint
{
public:
   
    real length;

public:
   ParticleRodConstraint(Particle* p, Vector3 anchor, real length) : length(length), ParticleConstraint(p, anchor){};
    virtual unsigned fillContact(ParticleContact *contact,
        unsigned limit) const override;
};

class VerletRod{
    public:
        Particle* particle[2];
        VerletRod(Particle* p1, Particle* p2, real length);
        void solveConstraint();
    private:
        real length;
};

class VerletAnchor{
    public:
        Particle* p;
        VerletAnchor(Particle* p, Vector3 anchor, real length);
        void solveConstraint();
    private:
        Vector3 anchor;
        real length;
};