#ifndef CORE_RANDOM_LINEAR_CONGRUENTIAL_H
#define CORE_RANDOM_LINEAR_CONGRUENTIAL_H

#include "../random.h"

namespace core {

////////////////////////////////////////////////////////////////

class LinearCongruential : public IRandom
{
  ////////////////////////////////////////////////////////////////
  // Class members
  ////////////////////////////////////////////////////////////////
  private:
    /// The current value of the PRNG
    uint64_t uiCurrent_;

  ////////////////////////////////////////////////////////////////
  // Class Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    LinearCongruential(uint64_t uiSeed);

    virtual ~LinearCongruential() {}

  ////////////////////////////////////////////////////////////////
  // Class functions
  ////////////////////////////////////////////////////////////////
  private:
    /// Get the next number according to uniform distribution [0, uiMax - 1)
    virtual const uint64_t getNext();

    /// Get the upper limit of getUniform
    virtual const uint64_t getMax() const;

  public:
    void reseed(uint64_t uiSeed);

  ////////////////////////////////////////////////////////////////
  // Class statics
  ////////////////////////////////////////////////////////////////
  private:
    static const uint64_t s_uiMod;
};

////////////////////////////////////////////////////////////////

}

#endif
