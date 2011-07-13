/*
** Author(s):
**  - Chris Kilner
**  - Cyrille Collette
**  - David Gouaillier
**
** Copyright (C) 2011 Aldebaran Robotics
*/

#pragma once

#ifndef _LIB_ALMATH_ALMATH_ALTRANSFORMHELPERS_H_
#define _LIB_ALMATH_ALMATH_ALTRANSFORMHELPERS_H_

#include <almath/types/alposition3d.h>
#include <almath/types/alposition6d.h>
#include <almath/types/alrotation.h>
#include <almath/types/alrotation3d.h>
#include <almath/types/alvelocity6d.h>
#include <almath/types/altransform.h>
#include <almath/types/alaxismask.h>
#include <almath/types/alpose2d.h>

namespace AL {
  namespace Math {

    /// <summary>
    /// Create a Transform from 3D cartesian coordiantes and a Rotation.
    /**
      * \f$ T = \left[\begin{array}{cccc}
      * pRot.r1c1 & pRot.r1c2 & pRot.r1c3 & pX \\
      * pRot.r2c1 & pRot.r2c2 & pRot.r2c3 & pY \\
      * pRot.r3c1 & pRot.r3c2 & pRot.r3c3 & pZ \\
      * 0.0 & 0.0 & 0.0 & 1.0 \end{array}\right] \f$
      */
    /// </summary>
    /// <param name="pX"> the translation along x axis </param>
    /// <param name="pY"> the translation along y axis </param>
    /// <param name="pZ"> the translation along z axis </param>
    /// <param name="pRot"> the given Rotation </param>
    /// <returns>
    /// the Transform result.
    /// </returns>
    /// \ingroup Tools
    Transform transformFromPosition3DAndRotation(
      const float&              pX,
      const float&              pY,
      const float&              pZ,
      const Rotation& pRot);

    /// <summary>
    /// Create a Transform from a Position3D and a Rotation.
    /** \f$ T = \left[\begin{array}{cccc}
      * pRot.r1c1 & pRot.r1c2 & pRot.r1c3 & pPos.x \\
      * pRot.r2c1 & pRot.r2c2 & pRot.r2c3 & pPos.y \\
      * pRot.r3c1 & pRot.r3c2 & pRot.r3c3 & pPos.z \\
      * 0.0 & 0.0 & 0.0 & 1.0 \end{array}\right] \f$
      */
    /// </summary>
    /// <param name="pPos"> the given Position3D </param>
    /// <param name="pRot"> the given Rotation </param>
    /// <returns>
    /// the Transform result.
    /// </returns>
    /// \ingroup Tools
    Transform transformFromPosition3DAndRotation(
      const Position3D& pPos,
      const Rotation&   pRot);

    /// <summary>
    /// Compute the logarithme of a transform.
    /// Angle must be between \f$\left[-\pi+0.001, \pi-0.001\right].\f$
    /**
      * Cette fonction calcule le
      * logarithme associe a une matrice de type Deplacement -
      * matrice homogene 4x4 (SE3)
      * La sortie est un torseur cinematique de se3.
      * Le resultat n'est garanti que pour des angles dans [-pi+0.001,pi-0.001].
      * cette fonction calcule la differentielle du logarithme associe
      * a une matrice de type Deplacement - matrice homogene 4x4 (SE3).
      */
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// <returns>
    /// the Velocity6D logarithme: kinematic screw in se3
    /// </returns>
    /// \ingroup Tools
    Velocity6D transformLogarithme(const Transform& pT);

    /// <summary>
    /// Compute the logarithme of a transform.
    /// Angle must be between \f$\left[-\pi+0.001, \pi-0.001\right].\f$
    /**
      * Cette fonction calcule le
      * logarithme associe a une matrice de type Deplacement -
      * matrice homogene 4x4 (SE3)
      * La sortie est un torseur cinematique de se3.
      * Le resultat n'est garanti que pour des angles dans [-pi+0.001,pi-0.001].
      * cette fonction calcule la differentielle du logarithme associe
      * a une matrice de type Deplacement - matrice homogene 4x4 (SE3).
      */
    /// </summary>
    /// <param name="pT"> the given Transform </param>
    /// <param name="pVel"> the given Transform </param>
    /// <returns>
    /// the Velocity6D logarithme: kinematic screw in se3
    /// </returns>
    /// \ingroup Tools
    void transformLogarithme(
      const Transform& pT,
      Velocity6D&      pVel);

    /// <summary>
    /// Compute the logarithme of a transform.
    /// Angle must be between \f$\left[-\pi+0.001, \pi-0.001\right].\f$
    /**
      * Function Velocity Exponential : compute homogenous matrix
      * displacement from a dt * 6D velocity vector.
      */
    /// </summary>
    /// <param name="pVel"> the given Velocity6D </param>
    /// <returns>
    /// the Velocity6D logarithme: kinematic screw in se3
    /// </returns>
    /// \ingroup Tools
    Transform velocityExponential(const Velocity6D& pVel);

    // TODO: Add to doc or set private.
    void velocityExponential(
      const Velocity6D& pVel,
      Transform&        pT);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pVOut.xd  \\
      * pVOut.yd  \\
      * pVOut.zd  \\
      * pVOut.wxd \\
      * pVOut.wyd \\
      * pVOut.wzd \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cccccc}
      * r_1c_1 & r_1c_2 & r_1c_3 & 0 & 0 & 0 \\
      * r_2c_1 & r_2c_2 & r_2c_3 & 0 & 0 & 0 \\
      * r_3c_1 & r_3c_2 & r_3c_3 & 0 & 0 & 0 \\
      * 0 & 0 & 0 & r_1c_1 & r_1c_2 & r_1c_3 \\
      * 0 & 0 & 0 & r_2c_1 & r_2c_2 & r_2c_3 \\
      * 0 & 0 & 0 & r_3c_1 & r_3c_2 & r_3c_3 \\
      * \end{array}\right]
      *
      * \left[\begin{array}{c}
      * pVIn.yd  \\
      * pVIn.yd  \\
      * pVIn.yd  \\
      * pVIn.wyd \\
      * pVIn.wyd \\
      * pVIn.wyd \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pVelIn"> a Velocity6D containing the velocity
    /// to change
    /// </param>
    /// <param name = "pVelOut">  a Velocity6D containing the changed velocity
    /// </param>
    /// \ingroup Tools
    void changeRepereVelocity6D(
      const Transform&  pT,
      const Velocity6D& pVelIn,
      Velocity6D&       pVelOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pPOut.x  \\
      * pPOut.y  \\
      * pPOut.z  \\
      * pPOut.wx \\
      * pPOut.wy \\
      * pPOut.wz \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cccccc}
      * r_1c_1 & r_1c_2 & r_1c_3 & 0 & 0 & 0 \\
      * r_2c_1 & r_2c_2 & r_2c_3 & 0 & 0 & 0 \\
      * r_3c_1 & r_3c_2 & r_3c_3 & 0 & 0 & 0 \\
      * 0 & 0 & 0 & r_1c_1 & r_1c_2 & r_1c_3 \\
      * 0 & 0 & 0 & r_2c_1 & r_2c_2 & r_2c_3 \\
      * 0 & 0 & 0 & r_3c_1 & r_3c_2 & r_3c_3 \\
      * \end{array}\right]
      *
      * \left[\begin{array}{c}
      * pPIn.z  \\
      * pPIn.z  \\
      * pPIn.z  \\
      * pPIn.wz \\
      * pPIn.wz \\
      * pPIn.wz \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pPosIn"> a Position6D containing the position
    /// to change
    /// </param>
    /// <param name = "pPosOut">  a Position6D containing the changed position
    /// </param>
    /// \ingroup Tools
    void changeReperePosition6D(
      const Transform&  pT,
      const Position6D& pPosIn,
      Position6D&       pPosOut);

    // TODO: rename argument.
    void changeReperePosition3D(
      const Transform& pT,
      Position3D&      pPosOut);

    // TODO: rename argument.
    void changeRepereTransposePosition3D(
      const Transform& pT,
      Position3D&      pPosOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pPosOut.x \\
      * pPosOut.y \\
      * pPosOut.z \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{ccc}
      * r_1c_1 & r_1c_2 & r_1c_3\\
      * r_2c_1 & r_2c_2 & r_2c_3\\
      * r_3c_1 & r_3c_2 & r_3c_3\\
      * \end{array}\right]
      *
      * \left[\begin{array}{c}
      * pPosIn.x \\
      * pPosIn.y \\
      * pPosIn.z \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pPosIn"> a Position3D containing the position
    /// to change
    /// </param>
    /// <param name = "pPosOut">  a Position3D containing the changed position
    /// </param>
    /// \ingroup Tools
    void changeReperePosition3D(
      const Transform&  pT,
      const Position3D& pPosIn,
      Position3D&       pPosOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pTOut \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{c}
      * pT
      * \end{array}\right]
      * \left[\begin{array}{c}
      * pTIn \\
      * \end{array}\right]^T
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pPosIn"> a Position3D containing the position to change
    /// </param>
    /// <param name = "pPosOut"> a Position3D containing the changed position
    /// </param>
    /// \ingroup Tools
    void changeRepereTransposePosition3D(
      const Transform&  pT,
      const Position3D& pPosIn,
      Position3D&       pPosOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pTOut \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{c}
      * pT
      * \end{array}\right]
      * \left[\begin{array}{c}
      * pTIn \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pTIn"> the Transform to change
    /// </param>
    /// <param name = "pTOut"> the changed Transform
    /// </param>
    /// \ingroup Tools
    void changeRepereTransform(
      const Transform& pT,
      const Transform& pTIn,
      Transform&       pTOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pTOut \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{c}
      * pT
      * \end{array}\right]
      * \left[\begin{array}{c}
      * pTIn \\
      * \end{array}\right]^T
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pTIn"> the Transform to change
    /// </param>
    /// <param name = "pTOut"> the changed Transform
    /// </param>
    /// \ingroup Tools
    void changeRepereTransposeTransform(
      const Transform& pT,
      const Transform& pTIn,
      Transform&       pTOut);


    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pVOut.xd  \\
      * pVOut.yd  \\
      * pVOut.zd  \\
      * pVOut.wxd \\
      * pVOut.wyd \\
      * pVOut.wzd \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cccccc}
      * r_1c_1 & r_2c_1 & r_3c_1 & 0 & 0 & 0 \\
      * r_1c_2 & r_2c_2 & r_3c_2 & 0 & 0 & 0 \\
      * r_1c_3 & r_2c_3 & r_3c_3 & 0 & 0 & 0 \\
      * 0 & 0 & 0 & r_1c_1 & r_2c_1 & r_3c_1 \\
      * 0 & 0 & 0 & r_1c_2 & r_2c_2 & r_3c_2 \\
      * 0 & 0 & 0 & r_1c_3 & r_2c_3 & r_3c_3 \\
      * \end{array}\right]
      *
      * \left[\begin{array}{c}
      * pVIn.yd  \\
      * pVIn.yd  \\
      * pVIn.yd  \\
      * pVIn.wyd \\
      * pVIn.wyd \\
      * pVIn.wyd \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pVelIn"> a Velocity6D containing the velocity
    /// to change
    /// </param>
    /// <param name = "pVelOut">  a Velocity6D containing the changed velocity
    /// </param>
    /// \ingroup Tools
    void changeRepereTransposeVelocity6D(
      const Transform&  pT,
      const Velocity6D& pVelIn,
      Velocity6D&       pVelOut);

    /// <summary>
    /** \f$ \left[\begin{array}{c}
      * pPOut.x  \\
      * pPOut.y  \\
      * pPOut.z  \\
      * pPOut.wx \\
      * pPOut.wy \\
      * pPOut.wz \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cccccc}
      * r_1c_1 & r_2c_1 & r_3c_1 & 0 & 0 & 0 \\
      * r_1c_2 & r_2c_2 & r_3c_2 & 0 & 0 & 0 \\
      * r_1c_3 & r_2c_3 & r_3c_3 & 0 & 0 & 0 \\
      * 0 & 0 & 0 & r_1c_1 & r_2c_1 & r_3c_1 \\
      * 0 & 0 & 0 & r_1c_2 & r_2c_2 & r_3c_2 \\
      * 0 & 0 & 0 & r_1c_3 & r_2c_3 & r_3c_3 \\
      * \end{array}\right]
      *
      * \left[\begin{array}{c}
      * pPIn.z  \\
      * pPIn.z  \\
      * pPIn.z  \\
      * pPIn.wz \\
      * pPIn.wz \\
      * pPIn.wz \\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pT"> the given Transform </param>
    /// <param name = "pPosIn"> a Position6D containing the position
    /// to change
    /// </param>
    /// <param name = "pPosOut">  a Position6D containing the changed position
    /// </param>
    /// \ingroup Tools
    void changeRepereTransposePosition6D(
      const Transform&  pT,
      const Position6D& pPosIn,
      Position6D&       pPosOut);

    /// <summary>
    /// Preform a logarithmic mean of pTIn1 and pTIn2 and put it in pTout.
    /// </summary>
    /// <param name = "pTIn1"> the first given Transform </param>
    /// <param name = "pTIn2"> the second given Transform </param>
    /// <param name = "pVal"> the value between 0 and 1 used in the logarithmic
    /// mean </param>
    /// <param name = "pTOut">  the output Transform.
    /// </param>
    /// \ingroup Tools
    void transformMean(
      const Transform& pTIn1,
      const Transform& pTIn2,
      const float&     pVal,
      Transform&       pTOut);

    /// <summary>
    /// Preform a logarithmic mean of pTIn1 and pTIn2.
    /// </summary>
    /// <param name = "pTIn1"> cartesian coordinates </param>
    /// <param name = "pTIn2"> the given Transform </param>
    /// <param name = "pVal"> the value between 0 and 1 used in the logarithmic
    /// mean, 0.5 by default </param>
    /// <returns>
    /// a Transform with the mean of pTIn1 and pTIn2
    /// </returns>
    /// \ingroup Tools
    Transform transformMean(
      const Transform& pTIn1,
      const Transform& pTIn2,
      const float&     pVal = 0.5f);

    /// <summary>
    /// Modify pTransform to set the translation part to pPosition.
    /** \f$
      * \left[\begin{array}{c}
      *   Transform \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cc}
      *   pRotation& *_{3,1}\\
      *   0_{1,3} & 1\\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pPosition"> a Position3D cartesian coordinates </param>
    /// <param name = "pTransform"> the given Transform </param>
    /// \ingroup Tools
    void transformFromPosition3D(
      const Position3D& pPosition,
      Transform&        pTransform);

    /// <summary>
    /// Create a 4*4 transform matrix from cartesian coordinates
    /// given in pPosition.
    /** \f$
      * \left[\begin{array}{c}
      *   Transform \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cc}
      *   pRotation& *_{3,1}\\
      *   0_{1,3} & 1\\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pPosition"> position in cartesian coordinates </param>
    /// <returns>
    /// a Transform with the translation part initialized to pPosition, rotation
    /// part is set to identity
    /// </returns>
    /// \ingroup Tools
    Transform transformFromPosition3D(const Position3D& pPosition);

    /// <summary>
    /// Modify the rotation part of the transform.
    /// The translation part of the transform is not modified.
    /** \f$
      * \left[\begin{array}{c}
      *   Transform \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cc}
      *   pRotation& *_{3,1}\\
      *   0_{1,3} & 1\\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pRotation"> the given Rotation </param>
    /// <param name = "pTransform"> the Transform to modify </param>
    /// \ingroup Tools
    void rotationToTransform(
      const Rotation& pRotation,
      Transform&      pTransform);

    /// <summary>
    /** \f$
      * \left[\begin{array}{c}
      *   Transform \\
      * \end{array}\right]
      * =
      * \left[\begin{array}{cc}
      *   pRotation& 0_{3,1}\\
      *   0_{1,3} & 1\\
      * \end{array}\right]
      * \f$
      */
    /// </summary>
    /// <param name = "pRotation"> the given Rotation </param>
    /// <returns>
    /// a Transform with the rotation part initialized to pRotation
    /// </returns>
    /// \ingroup Tools
    Transform rotationToTransform(const Rotation& pRotation);

    /// <summary>
    /// Extract the position coordinates from a Transform.
    /// </summary>
    /// <param name = "pTransform"> the given transform </param>
    /// <param name = "pRotation"> a Rotation to be set with the reslut </param>
    /// \ingroup Tools
    void rotationFromTransform(
      const Transform& pTransform,
      Rotation&        pRotation);

    /// <summary>
    ///
    /// </summary>
    /// <param name = "pTransform"> position in cartesian coordinates </param>
    /// <returns>
    /// the Rotation extracted from the Transform
    /// </returns>
    /// \ingroup Tools
    Rotation rotationFromTransform(const Transform& pTransform);

    /// <summary>
    ///
    /// </summary>
    /// <param name = "pRotation"> the Rotation to extract </param>
    /// <returns>
    /// the Rotation3D extracted from pRotation
    /// </returns>
    /// \ingroup Tools
    Rotation3D rotation3DFromRotation(const Rotation& pRotation);

    /// <summary>
    /// Extracts the position coordinates from a Transform.
    /// into a Position3D struct
    /// </summary>
    /// <param name = "pTransform"> The transform you want to extract </param>
    /// <param name = "pPosition"> Position3D in cartesian coordinates </param>
    /// \ingroup Tools
    void transformToPosition3D(
      const Transform& pTransform,
      Position3D&      pPosition);

    /// <summary>
    /// Extract the Position3D cartesian coordinates from a Transform.
    /// </summary>
    /// <param name = "pTransform"> the transform you want to extract </param>
    /// <returns> a Position3D with the translation part of the Transform
    /// </returns>
    /// \ingroup Tools
    Position3D transformToPosition3D(const Transform& pTransform);

    /// <summary>
    /// Compute Position6D corresponding to the Transform.
    /// </summary>
    /// <param name = "pT"> the transform you want to extract </param>
    /// <param name = "pPos"> the transform you want to extract </param>
    /// \ingroup Tools
    void position6DFromTransform(
        const Transform& pT,
        Position6D&      pPos);

    /// <summary>
    /// Compute Position6D corresponding to 4*4 Homogenous Transform.
    /// </summary>
    /// <param name = "pT"> the transform you want to extract </param>
    /// <returns> the extracted Position6D </returns>
    /// \ingroup Tools
    Position6D position6DFromTransform(const Transform& pT);

    /// <summary>
    /// Compute a Transform from a Pose2D.
    /// </summary>
    /// <param name = "pPose"> the Pose2D to extract </param>
    /// <param name = "pT"> the result Transform </param>
    /// \ingroup Tools
    void transformFromPose2D(
        const Pose2D& pPose,
        Transform&    pT);

    /// <summary>
    /// Create a Transform from a Pose2D.
    /// </summary>
    /// <param name = "pPose"> the pose2D you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform transformFromPose2D(const Pose2D& pPose);

    /// <summary>
    /// Compute a Pose2D from a Transform.
    /// </summary>
    /// <param name = "pT"> the Transform you want to extract </param>
    /// <param name = "pPos"> the result Pose2D </param>
    /// \ingroup Tools
    void pose2DFromTransform(
        const Transform& pT,
        Pose2D&          pPos);

    /// <summary>
    /// Create a Pose2D from a Transform.
    /// </summary>
    /// <param name = "pT"> the transform you want to extract </param>
    /// <returns> the Pose2D extracted from the Transform </returns>
    /// \ingroup Tools
    Pose2D pose2DFromTransform(const Transform& pT);

    /// <summary>
    /// Create a Transform from a Rotation3D.
    /// </summary>
    /// <param name = "pRotation"> the Rotation you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform transformFromRotation3D(const Rotation3D& pRotation);

    /// <summary>
    /// Create a Transform from a Position6D.
    /// </summary>
    /// <param name = "pPosition6D"> the Position6D you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform transformFromPosition6D(const Position6D& pPosition6D);

    /// <summary>
    /// Computes a 6 differential motion require to move
    /// from a 4*4 Homogenous transform matrix Current to
    /// a 4*4 Homogenous transform matrix target.
    /// </summary>
    /// <param name = "pCurrent"> the Position6D you want to extract </param>
    /// <param name = "pTarget"> the Position6D you want to extract </param>
    /// <param name = "result"> the result Position6D </param>
    /// \ingroup Tools
    void transformDiffToPosition(
      const Transform& pCurrent,
      const Transform& pTarget,
      Position6D&      result);

    /// <summary>
    /// Computes a 6 differential motion require to move
    /// from a 4*4 Homogenous transform matrix Current to
    /// a 4*4 Homogenous transform matrix target.
    /// </summary>
    /// <param name = "pCurrent"> the Position6D you want to extract </param>
    /// <param name = "pTarget"> the Position6D you want to extract </param>
    /// <returns> the result Position6D </returns>
    /// \ingroup Tools
    Position6D transformDiffToPosition(
      const Transform& pCurrent,
      const Transform& pTarget);

    /// <summary>
    /// Compute a Position3D from a Transform.
    /// </summary>
    /// <param name = "pT"> the Transform you want to extract </param>
    /// <param name = "pOut"> the result Position3D </param>
    /// \ingroup Tools
    void position3DFromTransformInPlace(
      const Transform& pT,
      Position3D&      pOut);

    /// <summary>
    /// Create a Position3D from a Transform.
    /// </summary>
    /// <param name = "pT"> the Transform you want to extract </param>
    /// <returns> the result Position6D </returns>
    /// \ingroup Tools
    Position3D position3DFromTransform(const Transform& pT);

    /// <summary>
    /// Create a Transform from a Rotation and a Position3D.
    /// </summary>
    /// <param name = "pRot"> the Rotation you want to extract </param>
    /// <param name = "pPos"> the Position3D you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform rotationPosition3DToTransform(
      const Rotation&   pRot,
      const Position3D& pPos);

    /// <summary>
    /// Create a Rotation3D (Roll, Pitch, Yaw) corresponding to the rotational
    /// part of the Transform.
    /// </summary>
    /// <param name = "pT"> the Transform you want to extract </param>
    /// <returns> the result Rotation3D </returns>
    /// \ingroup Tools
    Rotation3D rotation3DFromTransform(const Transform& pT);

    /// <summary>
    /// Compute a Transform from
    /// </summary>
    /// <param name = "pAxis"> the Rotation you want to extract </param>
    /// <param name = "pTheta"> the rotation you want to extract </param>
    /// <param name = "pPos"> the Position3D you want to extract </param>
    /// <param name = "pT"> the Rotation you want to extract </param>
    /// \ingroup Tools
    void rotVecToTransform(
      const int         pAxis,
      const float       pTheta,
      const Position3D& pPos,
      Transform&        pT);

    /// <summary>
    /// Compute a Transform from a Rotation3D.
    /// </summary>
    /// <param name = "pAxis"> the Rotation you want to extract </param>
    /// <param name = "pTheta"> the Rotation you want to extract </param>
    /// <param name = "pPos"> the Rotation you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform rotVecToTransform(
      const int         pAxis,
      const float       pTheta,
      const Position3D& pPos);


    /// <summary>
    /// Compute a Transform from a Rotation3D.
    /// </summary>
    /// <param name = "pPos"> the Rotation you want to extract </param>
    /// <param name = "pT"> the Rotation you want to extract </param>
    /// \ingroup Tools
    void rotVecToTransform(
      const Position3D& pPos,
      Transform&        pT);

    /// <summary>
    /// Compute a Transform from a Rotation3D.
    /// </summary>
    /// <param name = "pPos"> the Rotation you want to extract </param>
    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform rotVecToTransform(const Position3D& pPos);

    /// <summary>
    /// Compute a Transform from a Rotation3D.
    /// </summary>
    /// <param name = "pAxis"> the Rotation you want to extract </param>
    /// <param name = "pTheta"> the Rotation you want to extract </param>

    /// <returns> the result Transform </returns>
    /// \ingroup Tools
    Transform rotVecToTransform(
      const int&   pAxis,
      const float& pTheta);

    Position3D operator*(
      const Transform&  pT,
      const Position3D& pPos);

    Transform& operator+=(
      Transform&        pT,
      const Position3D& pPos);

    /**
    * finding the closest rotation Rw of R around an axis (Position3D)
    * @param Transform : useful only for Rotation part
    * @param Position3D : axis of rotation
    * @return Transform
    **/
    void axisRotationProjection(
      const Position3D& pAxis,
      Transform&        pH);


    Transform axisRotationProjection(
      const Transform&  pH,
      const Position3D& pAxis);

    /**
    * Function AxisRotationProjection :
    * finding the closest rotation Rw of R around an axis (Position3D)
    * @param Transform : useful only for Rotation part
    * @param Position3D : axis of rotation
    * @return Transform
    **/
    Rotation axisRotationProjection(
      const Rotation&   pRot,
      const Position3D& pAxis);

    /**
    * Function axisRotationProjectionInPlace :
    * finding the closest rotation Rw of R around an axis (Position3D)
    * @param Position3D : axis of rotation
    * @param pH: a transform
    **/
    void axisRotationProjectionInPlace(
      const Position3D& pAxis,
      Transform&        pT);

    /**
    * Function axisRotationProjectionInPlace :
    * finding the closest rotation Rw of R around an axis (Position3D)
    * @param pRot : a rotation
    * @param Position3D : axis of rotation
    **/
    void axisRotationProjectionInPlace(
      Rotation&         pRot,
      const Position3D& pPos);

  } // namespace Math
} // namespace AL
#endif  // _LIB_ALMATH_ALMATH_ALTRANSFORMHELPERS_H_
