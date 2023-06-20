#include "Transform.h"

Transform::Transform()
    :matTranslate_(XMMatrixIdentity()), matRotate_(XMMatrixIdentity()), matScale_(XMMatrixIdentity()),
    position_(XMFLOAT3(0, 0, 0)), rotate_(XMFLOAT3(0, 0, 0)), scale_(XMFLOAT3(1, 1, 1))
{
}

Transform::~Transform()
{
}

void Transform::Calclation()
{
    position_.y = 2.0f;

    rotate_.x += 0.03f;
    rotate_.y += 0.03f;

    matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

    matRotate_ = XMMatrixRotationX(XMConvertToRadians(rotate_.x)) *
                 XMMatrixRotationY(XMConvertToRadians(rotate_.y)) *
                 XMMatrixRotationZ(XMConvertToRadians(rotate_.z));

    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
    return matScale_ * matRotate_ * matTranslate_;
}