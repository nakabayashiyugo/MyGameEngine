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
}

XMMATRIX Transform::GetWorldMatrix()
{
    return XMMATRIX();
}
