#include <Novice.h>
#include <cmath>
#define _USE_MATH_DEFIENS
#include <assert.h>
#include "Matrix4x4.h"
#include <imgui.h>
#include "Vector3.h"
#include <numbers>

const char kWindowTitle[] = "LE2B_23_マスダリュウ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

static const int kColumWidth = 60;

struct Sphere
{
	Vector3 center;
	float radius;
};

Vector3 Add(const Vector3& v1, const Vector3& v2)
{

	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;

}

Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{

	Vector3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;

}

float Dot(const Vector3& v1, const Vector3& v2)
{

	float result;

	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return result;

}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			result.m[y][x] = 0;
			for (int k = 0; k < 4; k++)
			{
				result.m[y][x] += m1.m[y][k] * m2.m[k][x];
			}
		}
	}
	return result;
};

Matrix4x4 MakeRotateXMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = cosf(radian);
	result.m[1][2] = sinf(radian);
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = -sinf(radian);
	result.m[2][2] = cosf(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
};

Matrix4x4 MakeRotateYMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = cosf(radian);
	result.m[0][1] = 0.0f;
	result.m[0][2] = -sinf(radian);
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0.0f;

	result.m[2][0] = sinf(radian);
	result.m[2][1] = 0.0f;
	result.m[2][2] = cosf(radian);
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
};

Matrix4x4 MakeRotateZMatrix(float radian)
{
	Matrix4x4 result;

	result.m[0][0] = cosf(radian);
	result.m[0][1] = sinf(radian);
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = -sinf(radian);
	result.m[1][1] = cosf(radian);
	result.m[1][2] = 0;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
};

Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate)
{

	Matrix4x4 result{};

	Matrix4x4 tempXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 tempYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 tempZMatrix = MakeRotateZMatrix(rotate.z);

	result = Multiply(tempXMatrix, Multiply(tempYMatrix, tempZMatrix));

	return result;

}

Matrix4x4 MakeScaleMatrix(const Vector3& scale)
{
	Matrix4x4 result;

	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
};

Matrix4x4 MakeTranslateMatrix(const Vector3& translate)
{
	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;
};

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 result;

	Matrix4x4 Scale = MakeScaleMatrix(scale);
	Matrix4x4 Rotate = MakeRotateXYZMatrix(rotate);
	Matrix4x4 Translate = MakeTranslateMatrix(translate);

	result.m[0][0] = Scale.m[0][0] * Rotate.m[0][0];
	result.m[0][1] = Scale.m[0][0] * Rotate.m[0][1];
	result.m[0][2] = Scale.m[0][0] * Rotate.m[0][2];
	result.m[0][3] = 0.0f;

	result.m[1][0] = Scale.m[1][1] * Rotate.m[1][0];
	result.m[1][1] = Scale.m[1][1] * Rotate.m[1][1];
	result.m[1][2] = Scale.m[1][1] * Rotate.m[1][2];
	result.m[1][3] = 0.0f;

	result.m[2][0] = Scale.m[2][2] * Rotate.m[2][0];
	result.m[2][1] = Scale.m[2][2] * Rotate.m[2][1];
	result.m[2][2] = Scale.m[2][2] * Rotate.m[2][2];
	result.m[2][3] = 0.0f;

	result.m[3][0] = Translate.m[3][0];
	result.m[3][1] = Translate.m[3][1];
	result.m[3][2] = Translate.m[3][2];
	result.m[3][3] = 1.0f;

	return result;

}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix)
{
	Vector3 result;

	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];

	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
};

Matrix4x4 Inverse(const Matrix4x4& m)
{
	Matrix4x4 result;
	float determinant = m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
		+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
		+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
		- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
		- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]
		- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
		- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
		- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]
		+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
		+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
		+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]
		+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
		+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
		+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
		- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]
		- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
		- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
		- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]
		+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
		+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
		+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];
	if (determinant < 0)
	{
		determinant *= -1;
	}

	result.m[0][0] = 1 / determinant * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][2] + m.m[1][3] * m.m[2][1] * m.m[3][2]
		- m.m[1][3] * m.m[2][2] * m.m[3][2] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);

	result.m[0][1] = 1 / determinant * (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][2]) - (m.m[0][3] * m.m[2][1] * m.m[3][2])
		+ m.m[0][3] * m.m[2][2] * m.m[3][2] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);

	result.m[0][2] = 1 / determinant * (m.m[1][1] * m.m[1][2] * m.m[3][3] + m.m[1][2] * m.m[1][3] * m.m[3][2] + m.m[1][3] * m.m[1][1] * m.m[3][2]
		- m.m[1][3] * m.m[1][2] * m.m[3][2] - m.m[1][2] * m.m[1][1] * m.m[3][3] - m.m[1][1] * m.m[1][3] * m.m[3][2]);

	result.m[0][3] = 1 / determinant * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][2] + m.m[0][3] * m.m[1][1] * m.m[3][2]
		- m.m[0][3] * m.m[1][2] * m.m[3][2] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);

	result.m[1][0] = 1 / determinant * (-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][2]) - (m.m[1][3] * m.m[2][1] * m.m[3][2])
		+ m.m[1][3] * m.m[2][2] * m.m[3][0] + m.m[1][2] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][2]);

	result.m[1][1] = 1 / determinant * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][2] + m.m[0][3] * m.m[2][1] * m.m[3][2]
		- m.m[0][3] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][2]);

	result.m[1][2] = 1 / determinant * (-(m.m[0][1] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) - (m.m[0][3] * m.m[1][0] * m.m[3][2])
		+ m.m[0][3] * m.m[1][2] * m.m[3][0] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);

	result.m[1][3] = 1 / determinant * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2]
		- m.m[0][3] * m.m[1][2] * m.m[2][0] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][2]);

	result.m[2][0] = 1 / determinant * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1]
		- m.m[1][3] * m.m[2][1] * m.m[3][0] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);

	result.m[2][1] = 1 / determinant * (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) - (m.m[0][3] * m.m[2][0] * m.m[3][1])
		+ m.m[0][3] * m.m[2][1] * m.m[3][0] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);

	result.m[2][2] = 1 / determinant * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1]
		- m.m[0][3] * m.m[1][1] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);

	result.m[2][3] = 1 / determinant * (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) - (m.m[0][3] * m.m[1][0] * m.m[2][1])
		+ m.m[0][3] * m.m[1][1] * m.m[2][1] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);

	result.m[3][0] = 1 / determinant * (-(m.m[1][0] * m.m[2][1] * m.m[3][2] - (m.m[1][1] * m.m[2][2] * m.m[3][0])) - (m.m[1][2] * m.m[2][0] * m.m[3][1])
		+ m.m[1][2] * m.m[2][1] * m.m[3][0] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);

	result.m[3][1] = 1 / determinant * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1]
		- m.m[0][2] * m.m[2][1] * m.m[3][0] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);

	result.m[3][2] = 1 / determinant * (-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) - (m.m[0][2] * m.m[1][0] * m.m[3][1])
		+ m.m[0][2] * m.m[1][1] * m.m[3][0] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][2] * m.m[1][0] * m.m[3][1]);

	result.m[3][3] = 1 / determinant * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][1] + m.m[0][2] * m.m[1][0] * m.m[2][1]
		- m.m[0][2] * m.m[1][1] * m.m[2][0] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);

	return result;

};

Matrix4x4 MakeViewportMatrix(float left, float top, float widte, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result;

	result.m[0][0] = widte / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -height / 2;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = left + widte / 2;
	result.m[3][1] = top + height / 2;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MakeOrthGraphicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{

	Matrix4x4 result;

	result.m[0][0] = 2 / (right - left);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 2 / (top - bottom);
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[2][3] = 0.0f;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;

	return result;

}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result;

	result.m[0][0] = (1 / aspectRatio) * (1 / tanf(fovY / 2));
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 1 / tanf(fovY / 2);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1;

	result.m[3][0] = 1;
	result.m[3][1] = 1;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.m[3][3] = 0;

	return result;
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	Vector3 worldVertex[2];

	Vector3 screenVertex[2];

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; xIndex++)
	{

		worldVertex[0] = { (float)xIndex * kGridEvery - kGridHalfWidth, 0.0f, -kGridHalfWidth };
		worldVertex[1] = { (float)xIndex * kGridEvery - kGridHalfWidth, 0.0f, kGridHalfWidth };

		screenVertex[0] = Transform(worldVertex[0], viewProjectionMatrix);
		screenVertex[0] = Transform(screenVertex[0], viewportMatrix);
		
		screenVertex[1] = Transform(worldVertex[1], viewProjectionMatrix);
		screenVertex[1] = Transform(screenVertex[1], viewportMatrix);

		Novice::DrawLine((int)screenVertex[0].x, (int)screenVertex[0].y, (int)screenVertex[1].x, (int)screenVertex[1].y, 0xAAAAAAFF);

	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; zIndex++)
	{

		worldVertex[0] = { -kGridHalfWidth, 0.0f,  (float)zIndex * kGridEvery - kGridHalfWidth };
		worldVertex[1] = { kGridHalfWidth, 0.0f, (float)zIndex * kGridEvery - kGridHalfWidth };
		
		screenVertex[0] = Transform(worldVertex[0], viewProjectionMatrix);
		screenVertex[0] = Transform(screenVertex[0], viewportMatrix);
		
		screenVertex[1] = Transform(worldVertex[1], viewProjectionMatrix);
		screenVertex[1] = Transform(screenVertex[1], viewportMatrix);

		Novice::DrawLine((int)screenVertex[0].x, (int)screenVertex[0].y, (int)screenVertex[1].x, (int)screenVertex[1].y, 0xAAAAAAFF);

	}

}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color)
{

	const uint32_t kSubdivison = 30;
	const float kLonEvery = 2.0f * float(std::numbers::pi) / float(kSubdivison);
	const float kLatEvery = float(std::numbers::pi) / float(kSubdivison);

	// 緯度の方向に分割
	for (uint32_t latIndex = 0; latIndex < kSubdivison; latIndex++)
	{
		float lat = float(-std::numbers::pi) / 2.0f + kLatEvery * latIndex;
		// 軽度の方向に分割
		for (uint32_t lonIndex = 0; lonIndex < kSubdivison; lonIndex++)
		{
			float lon = lonIndex * kLonEvery;

			// ワールド座標系でのa, b, cを求める
			Vector3 a, b, c;
			a = { sphere.radius * std::cosf(lat) * std::cosf(lon),sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon) };
			a = Add(a, sphere.center);
			b = { sphere.radius * std::cosf(lat + kLatEvery) * std::cosf(lon), sphere.radius * std::sinf(lat + kLatEvery), sphere.radius * std::cosf(lat + kLatEvery) * std::sinf(lon) };
			b = Add(b, sphere.center);
			c = { sphere.radius * std::cosf(lat) * cosf(lon + kLonEvery), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon + kLonEvery) };
			c = Add(c, sphere.center);

			// a, b, c をスクリーン座標系に変換
			a = Transform(a, viewProjectionMatrix);
			a = Transform(a, viewPortMatrix);
			b = Transform(b, viewProjectionMatrix);
			b = Transform(b, viewPortMatrix);
			c = Transform(c, viewProjectionMatrix);
			c = Transform(c, viewPortMatrix);

			// 線を引く
			Novice::DrawLine(int(a.x), int(a.y), int(b.x), int(b.y), color);
			Novice::DrawLine(int(a.x), int(a.y), int(c.x), int(c.y), color);

		}
	}

}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x);
	Novice::ScreenPrintf(x + kColumWidth, y, "%0.2f", vector.y);
	Novice::ScreenPrintf(x + kColumWidth * 2, y, "%0.2f", vector.z);
	Novice::ScreenPrintf(x + kColumWidth * 3, y, "%s", label);

}

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	Vector3 result;
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);

	return result;

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 rotate = {};
	Vector3 translate = {};

	Vector3 cameraTranslate{ 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };

	Sphere sphere = { 0.0f, 0.0f, 0.0f, 1.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, translate);

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, cameraRotate, cameraTranslate);

		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));

		Matrix4x4 viewPortmatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(worldViewProjectionMatrix, viewPortmatrix);

		DrawSphere(sphere, worldViewProjectionMatrix, viewPortmatrix, 0x000000FF);

		ImGui::Begin("Debug");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
		ImGui::End();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
