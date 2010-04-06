#ifndef CORE_RANDOM_H
#define CORE_RANDOM_H

#include "../includes.h"

namespace core {

////////////////////////////////////////////////////////////////

class IRandom
{
  ////////////////////////////////////////////////////////////////
  // Class members
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  // Class Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    virtual ~IRandom() {}

  ////////////////////////////////////////////////////////////////
  // Class functions
  ////////////////////////////////////////////////////////////////
  private:
    /// Get the next pseudo-random number
    /// @return a value in the range [1, uimax]
    virtual const uint64_t getNext() = 0;

    /// Maximum number returned by the generator
    virtual const uint64_t getMax() const = 0;

  public:
    /// Get the next number according to uniform distribution
    /// @return a number in the range [0, uiMax-1]
    const uint64_t getUniform();

    /// Get the next number according to uniform distribution
    /// @return a number in the range [iLow, iHigh]
    const int64_t getUniform(int64_t iLow, int64_t iHigh);

    /// Get the next number as double
    /// @param bClosed defines the right bracket: ) for false, ] for true
    /// @return a number in the range [0, 1) or [0, 1]
    const double getUniformDouble(bool bClosed = false);

    /// Get the next number as gaussian of center 0 and sigma^2 = 1
    const void getGaussian(double& dZ1, double& dZ2);
};

////////////////////////////////////////////////////////////////

}

#endif
