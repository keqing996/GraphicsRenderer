#include "Math.h"

namespace Math
{
    Eigen::Matrix4f Translate(const Eigen::Vector3f& pos)
    {
        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();
        result.col(3) = Eigen::Vector4f{pos.x(), pos.y(), pos.z(), 1};
        return result;
    }

    Eigen::Matrix4f Rotate(const Eigen::Quaternionf& rot)
    {
        float x = rot.x();
        float y = rot.y();
        float z = rot.z();
        float w = rot.w();

        Eigen::Matrix4f result = Eigen::Matrix4f::Zero();

        float v2xx = 2 * x * x;
        float v2yy = 2 * y * y;
        float v2zz = 2 * z * z;
        float v2xy = 2 * x * y;
        float v2zw = 2 * z * w;
        float v2xz = 2 * x * z;
        float v2yw = 2 * y * w;
        float v2yz = 2 * y * z;
        float v2xw = 2 * x * w;

        result(0, 0) = 1 - v2yy - v2zz;
        result(0, 1) = v2xy - v2zw;
        result(0, 2) = v2xz + v2yw;

        result(1, 0) = v2xy + v2zw;
        result(1, 1) = 1 - v2xx - v2zz;
        result(1, 2) = v2yz - v2xw;

        result(2, 0) = v2xz - v2yw;
        result(2, 1) = v2yz + v2xw;
        result(2, 2) = 1 - v2xx - v2yy;

        result(3, 3) = 1;

        return result;
    }

    Eigen::Matrix4f Scale(const Eigen::Vector3f& scale)
    {
        Eigen::Matrix4f result = Eigen::Matrix4f::Identity();
        result(0, 0) = scale.x();
        result(1, 1) = scale.y();
        result(2, 2) = scale.z();
        return result;
    }

    Eigen::Matrix4f LookAt(const Eigen::Vector3f& forward, const Eigen::Vector3f& up)
    {
        Eigen::Vector3f rightNorm = forward.cross(up).normalized();
        Eigen::Vector3f forwardNorm = forward.normalized();
        Eigen::Vector3f upNorm = up.normalized();

        Eigen::Matrix4f rotateMatrix;
        rotateMatrix <<
                rightNorm.x(),      rightNorm.y(),      rightNorm.z(),      0,
                upNorm.x(),         upNorm.y(),         upNorm.z(),         0,
                forwardNorm.x(),    forwardNorm.y(),    forwardNorm.z(),    0,
                0,                  0,                  0,                  1;

        return rotateMatrix;
    }

    Eigen::Matrix4f MakeModelMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot, const Eigen::Vector3f& scale)
    {
        return Scale(scale) * Rotate(rot) * Translate(pos);
    }

    Eigen::Matrix4f MakeViewMatrix(const Eigen::Vector3f& pos, const Eigen::Quaternionf& rot)
    {
        Eigen::Matrix4f translationMatrix = Translate(-pos);
        Eigen::Matrix4f rotationMatrix = Rotate(rot.conjugate());

        return rotationMatrix * translationMatrix;
    }

    Eigen::Matrix4f MakeOrthoProjectionMatrix(RendererApi ndcApi, float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ)
    {
        float left = -nearPlaneHalfX;
        float right = nearPlaneHalfX;
        float top = nearPlaneHalfY;
        float bottom = -nearPlaneHalfY;
        float near = nearPlaneZ;
        float far = farPlaneZ;

        Eigen::Matrix4f translationMatrix = Translate({
            - (right + left) / 2,
            - (top + bottom) / 2,
            - (near + far) / 2
        });

        Eigen::Matrix4f scaleMatrix = Scale({
            2 / (right - left),
            2 / (top - bottom),
            2 / (near - far)
        });

        Eigen::Matrix4f standardOrthoProj = scaleMatrix * translationMatrix;

        if (ndcApi == RendererApi::OpenGL)
        {
            Eigen::Matrix4f zReverse = Eigen::Matrix4f::Identity();
            //zReverse(2, 2) = -1;
            return zReverse * standardOrthoProj;
        }

        return standardOrthoProj;
    }

    Eigen::Matrix4f MakePerspectiveProjectionMatrix(RendererApi ndcApi, float nearPlaneHalfX, float nearPlaneHalfY, float nearPlaneZ, float farPlaneZ)
    {
        float left = -nearPlaneHalfX;
        float right = nearPlaneHalfX;
        float top = nearPlaneHalfY;
        float bottom = -nearPlaneHalfY;
        float near = nearPlaneZ;
        float far = farPlaneZ;

        Eigen::Matrix4f translationMatrix = Translate({
            - (right + left) / 2,
            - (top + bottom) / 2,
            - (near + far) / 2
        });

        Eigen::Matrix4f scaleMatrix = Scale({
            2 / (right - left),
            2 / (top - bottom),
            2 / (near - far)
         });

        Eigen::Matrix4f standardOrthoProj = scaleMatrix * translationMatrix;

        Eigen::Matrix4f compressMatrix;
        compressMatrix <<
                        near,        0,          0,              0,
                        0,           near,       0,              0,
                        0,           0,          near + far,     - far * near,
                        0,           0,          1,              0;

        if (ndcApi == RendererApi::OpenGL)
        {
            compressMatrix(3, 2) = -1;
        }

        return scaleMatrix * translationMatrix * compressMatrix;
    }
}