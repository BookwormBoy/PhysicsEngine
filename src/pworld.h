#pragma once
#include <vector>
#include "particle.h"
#include "pfgen.h"
#include "pcontact.h"
#include "plinks.h"

class ParticleWorld
{
public:
    typedef std::vector<Particle*> Particles;
    typedef std::vector<ParticleContactGenerator*> ContactGenerators;
    typedef std::vector<ParticleLink*> ParticleLinks;

protected:
    Particles particles;
    bool calculateIterations;
    ParticleForceRegistry registry;
    ParticleContactResolver resolver;
    ContactGenerators contactGenerators;
    ParticleContact *contacts;
    unsigned maxContacts;

public:

    ParticleWorld(unsigned maxContacts, unsigned iterations=0);
    ~ParticleWorld();
    unsigned generateContacts();
    void integrate(real duration);
    void runPhysics(real duration);
    void startFrame();
    Particles& getParticles();
    ContactGenerators& getContactGenerators();
    ParticleForceRegistry& getForceRegistry();
};