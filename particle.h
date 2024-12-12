#include "core.h"

class Particle{
    protected:
        real inverseMass;
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;
        Vector3 forceAccum;
        real damping;
    public:
        real getMass();
        bool hasFiniteMass();
        void setMass(real mass);
        void setDamping(real damping);
        real getDamping();
        void setPosition(Vector3& position);
        Vector3 getPosition();
        void setVelocity(Vector3& velocity);
        Vector3 getVelocity();
        void setAcceleration(Vector3& acceleration);
        Vector3 getAcceleration();
        void clearAccumulator();
        void addForce(Vector3& force);
        void integrate(real duration);
};