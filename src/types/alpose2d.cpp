/*
 * Copyright (c) 2012 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */

#include <almath/types/alpose2d.h>
#include <cmath>
#include <stdexcept>

namespace AL {
  namespace Math {

    Pose2D::Pose2D():x(0.0f), y(0.0f), theta(0.0f) {}

    Pose2D::Pose2D(float pInit):x(pInit), y(pInit), theta(pInit) {}

    Pose2D::Pose2D(
      float pX,
      float pY,
      float pTheta):
      x(pX),
      y(pY),
      theta(pTheta) {}

    Pose2D::Pose2D (const std::vector<float>& pFloats)
    {
      if (pFloats.size() == 3)
      {
        x = pFloats[0];
        y = pFloats[1];
        theta = pFloats[2];
      }
      else
      {
        x = 0.0f;
        y = 0.0f;
        theta = 0.0f;
      }
    }

    Pose2D Pose2D::operator+ (const Pose2D& pPos2) const
    {
      Pose2D res;
      res.x = x + pPos2.x;
      res.y = y + pPos2.y;
      res.theta = theta + pPos2.theta;
      return res;
    }

    Pose2D Pose2D::operator- (const Pose2D& pPos2) const
    {
      Pose2D res;
      res.x = x - pPos2.x;
      res.y = y - pPos2.y;
      res.theta = theta - pPos2.theta;
      return res;
    }

    Pose2D Pose2D::operator+ () const
    {
      Pose2D res;
      res.x = x;
      res.y = y;
      res.theta = theta;
      return res;
    }

    Pose2D Pose2D::operator- () const
    {
      Pose2D res;
      res.x = -x;
      res.y = -y;
      res.theta = -theta;
      return res;
    }

    Pose2D Pose2D::operator* (const Pose2D& pPos2) const
    {
      Pose2D pOut;
      pOut.x = x + cosf(theta) * pPos2.x - sinf(theta) * pPos2.y;
      pOut.y = y + sinf(theta) * pPos2.x + cosf(theta) * pPos2.y;
      pOut.theta = theta + pPos2.theta;

      return pOut;
    }

    Pose2D& Pose2D::operator*= (const Pose2D& pPos2)
    {
      x += cosf(theta) * pPos2.x - sinf(theta) * pPos2.y;
      y += sinf(theta) * pPos2.x + cosf(theta) * pPos2.y;
      theta += pPos2.theta;

      return *this;
    }

    Pose2D& Pose2D::operator+= (const Pose2D& pPos2)
    {
      x     += pPos2.x;
      y     += pPos2.y;
      theta += pPos2.theta;
      return *this;
    }

    Pose2D& Pose2D::operator-= (const Pose2D& pPos2)
    {
      x     -= pPos2.x;
      y     -= pPos2.y;
      theta -= pPos2.theta;
      return *this;
    }

    bool Pose2D::operator==(const Pose2D& pPos2) const
    {
       if (
         (x == pPos2.x) &&
         (y == pPos2.y) &&
         (theta == pPos2.theta) )
       {
        return true;
      }
      else
      {
        return false;
      }
    }

    bool Pose2D::operator!=(const Pose2D& pPos2) const
    {
      return ! (*this==pPos2);
    }

    float Pose2D::distanceSquared(const Pose2D& pPos) const
    {
      return Math::distanceSquared(*this, pPos);
    }

    float Pose2D::distance(const Pose2D& pPos2) const
    {
      return Math::distance(*this, pPos2);
    }


    Pose2D Pose2D::operator* (float pVal) const
    {
      Pose2D res;
      res.x     = x * pVal;
      res.y     = y * pVal;
      res.theta = theta * pVal;
      return res;
    }

    Pose2D Pose2D::operator/ (float pVal) const
    {
      if (pVal == 0.0f)
      {
        throw std::runtime_error(
          "ALPose2D: operator/ Division by zeros.");
      }
      return *this * (1.0f/pVal);
    }

    Pose2D& Pose2D::operator*= (const float pVal)
    {
      x     *= pVal;
      y     *= pVal;
      theta *= pVal;
      return *this;
    }

    Pose2D& Pose2D::operator/= (float pVal)
    {
      if (pVal == 0.0f)
      {
        throw std::runtime_error(
          "ALPose2D: operator/= Division by zeros.");
      }
      *this *= (1.0f/pVal);
      return *this;
    }


    std::vector<float> Pose2D::toVector() const
    {
      std::vector<float> returnVector;
      returnVector.resize(3);
      returnVector[0] = x;
      returnVector[1] = y;
      returnVector[2] = theta;

      return returnVector;
    }

    float distanceSquared(
      const Pose2D& pPos1,
      const Pose2D& pPos2)
    {
      return (pPos1.x-pPos2.x)*(pPos1.x-pPos2.x)+(pPos1.y-pPos2.y)*(pPos1.y-pPos2.y);
    }

    float distance(
      const Pose2D& pPos1,
      const Pose2D& pPos2)
    {
      return sqrtf(distanceSquared(pPos1, pPos2));
    }


    bool Pose2D::isNear(
      const Pose2D& pPos2,
      const float&  pEpsilon) const
    {

      if (
        (fabsf(x - pPos2.x) > pEpsilon) ||
        (fabsf(y - pPos2.y) > pEpsilon) ||
        (fabsf(theta - pPos2.theta) > pEpsilon))
      {
        return false;
      }
      else
      {
        return true;
      }
    }

    Pose2D Pose2D::inverse() const
    {
      return Math::pose2DInverse(*this);
    }

    void pose2DInverse(
      const Pose2D& pIn,
      Pose2D&       pOut)
    {
      pOut.theta = -pIn.theta;

      float cos = cosf(pOut.theta);
      float sin = sinf(pOut.theta);

      pOut.x = -( pIn.x*cos - pIn.y*sin);
      pOut.y = -( pIn.y*cos + pIn.x*sin);
    }

    Pose2D pose2DInverse(const Pose2D& pIn)
    {
      Pose2D pOut;
      pose2DInverse(pIn, pOut);
      return pOut;
    }
  } // end namespace math
} // end namespace AL
