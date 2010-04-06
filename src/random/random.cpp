#include <include/random.h>

namespace core {

////////////////////////////////////////////////////////////////

const uint64_t IRandom::getUniform()
{
  return (getNext() - 1);
}

////////////////////////////////////////////////////////////////

const int64_t IRandom::getUniform(int64_t iLow, int64_t iHigh)
{
  double dStart = double(std::min(iLow, iHigh)) - 0.5;
  double dRange = double(std::abs(iHigh - iLow)) + 1.;
  return int64_t(dRange * getUniformDouble() + dStart);
}

////////////////////////////////////////////////////////////////

const double IRandom::getUniformDouble(bool bClosed)
{
  if (bClosed)
    return double(getUniform()) / double(getMax() - 1);
  else
    return double(getUniform()) / double(getMax());
}

////////////////////////////////////////////////////////////////

const void IRandom::getGaussian(double& dZ1, double& dZ2)
{
  while (true)
  {
    const double dX = getUniformDouble();
    const double dY = getUniformDouble();

    const double dS = dX * dX + dY * dY;
    if (dS >= 1.)
      continue;

    const double dT = std::sqrt(-2. * std::log(dS) / dS);
    dZ1 = dX * dT;
    dZ2 = dY * dT;
    break;
  }
}

////////////////////////////////////////////////////////////////

}
