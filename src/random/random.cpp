#include <include/random.h>

namespace core {

const uint64_t IRandom::maskDouble = 0xFFFFFFFFFFFFFULL;

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
  uint64_t uniform = getUniform() & maskDouble;
  uint64_t max = getMax() & maskDouble;
  if (bClosed)
    --max;

  return double(uniform) / double(max);
}

////////////////////////////////////////////////////////////////

const double IRandom::getGaussian()
{
  double skipped;
  return getGaussian(skipped);
}

////////////////////////////////////////////////////////////////

const double IRandom::getGaussian(double& secondValue)
{
  while (true)
  {
    const double dX = getUniformDouble();
    const double dY = getUniformDouble();

    const double dS = dX * dX + dY * dY;
    if (dS >= 1.)
      continue;

    const double dT = std::sqrt(-2. * std::log(dS) / dS);
    secondValue = dY * dT;
    return dX * dT;
  }
}

////////////////////////////////////////////////////////////////

}
