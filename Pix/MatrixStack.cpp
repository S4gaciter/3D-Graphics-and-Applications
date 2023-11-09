#include "MatrixStack.h"

MatrixStack* MatrixStack::Get()
{
    static MatrixStack sInstance;
    return &sInstance;
}

MatrixStack::MatrixStack()
{

}

void MatrixStack::OnNewFrame()
{
    mCombinedTransform = Matrix4::Identity();
    mMatrices.clear();
}

void MatrixStack::PushTranslation(const Vector3& d)
{
    Matrix4 translationMatrix = Matrix4::Translation(d);
    mCombinedTransform = translationMatrix * mCombinedTransform;
    mMatrices.push_back(translationMatrix);
}

void MatrixStack::PushRotationX(float rad)
{
    Matrix4 rotationMatrix = Matrix4::RotationX(rad);
    mCombinedTransform = rotationMatrix * mCombinedTransform;
    mMatrices.push_back(rotationMatrix);
}

void MatrixStack::PushRotationY(float rad)
{
    Matrix4 rotationMatrix = Matrix4::RotationY(rad);
    mCombinedTransform = rotationMatrix * mCombinedTransform;
    mMatrices.push_back(rotationMatrix);
}

void MatrixStack::PushRotationZ(float rad)
{
    Matrix4 rotationMatrix = Matrix4::RotationZ(rad);
    mCombinedTransform = rotationMatrix * mCombinedTransform;
    mMatrices.push_back(rotationMatrix);
}

void MatrixStack::PushScaling(const Vector3& s)
{
    Matrix4 scaleMatrix = Matrix4::Scaling(s);
    mCombinedTransform = scaleMatrix * mCombinedTransform;
    mMatrices.push_back(scaleMatrix);
}

void MatrixStack::PopMatrix()
{
    if (!mMatrices.empty())
    {
        Matrix4 matrix = mMatrices.back();
        mCombinedTransform = MathHelper::Inverse(matrix) * mCombinedTransform;
        mMatrices.pop_back();
    }
}
