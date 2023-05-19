#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "LE2B_23_マスダリュウ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

typedef struct Matrix4x4 {
	float m[4][4];
	float m1[4][4];
	float m2[4][4];
};

struct Vector3 final {
	float x;
	float y;
	float z;
};

static Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

static Matrix4x4 MakeRoatateXMatrix(float rad);

static Matrix4x4 MakeRoatateYMatrix(float rad);

static Matrix4x4 MakeRoatateZMatrix(float rad);

Matrix4x4 m1 = {
	3.2f, 0.7f, 9.6f, 4.4f,
	5.5f, 1.3f, 7.8f, 2.1f,
	6.9f, 8.0f, 2.6f, 1.0f,
	0.5f, 7.2f, 5.1f, 3.3f
};

Matrix4x4 m2 = {
	4.1f, 6.5f, 3.3f, 2.2f,
	8.8f, 0.6f, 9.9f, 7.7f,
	1.1f, 5.5f, 6.6f, 0.0f,
	3.3f, 9.9f, 8.8f, 2.2f
};

Matrix4x4 Multiply(Matrix4x4 matrix1, Matrix4x4 matrix2)
{
	return Matrix4x4{
	m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0],
	m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1],
	m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2],
	m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3],
	m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0],
	m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1],
	m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2],
	m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3],
	m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0],
	m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1],
	m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2],
	m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3],
	m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0],
	m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1],
	m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2],
	m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3],
	};
}

// 回転行列の作成(X軸周り：YZ平面)
Matrix4x4 MakeRoatateXMatrix(float rad) {

	return Matrix4x4{
		1,0,0,0,
		0,std::cos(rad),std::sin(rad), 0,
		0,-std::sin(rad),std::cos(rad),0,
		0,0,0,1,
	};

}

// 回転行列の作成(Y軸周り：XZ平面)
Matrix4x4 MakeRoatateYMatrix(float rad) {

	return Matrix4x4{
		std::cos(rad),0,-std::sin(rad),0,
		0,1,0,0,
		std::sin(rad),0,std::cos(rad),0,
		0,0,0,1,
	};

}

// 回転行列の作成(Z軸周り：XY平面)
Matrix4x4 MakeRoatateZMatrix(float rad) {

	return Matrix4x4{
		std::cos(rad),std::sin(rad),0,0,
		-std::sin(rad),std::cos(rad),0,0,
		0,0,1,0,
		0,0,0,1,
	};

}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	// 回転行列を作成
	Matrix4x4 rotatExMatrix = MakeRoatateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRoatateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRoatateZMatrix(rotate.z);
	Matrix4x4 rotatExYZMatrix = Multiply(rotatExMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	return Matrix4x4{
		scale.x * rotatExYZMatrix.m[0][0],	scale.x * rotatExYZMatrix.m[0][1],	scale.x * rotatExYZMatrix.m[0][2],0,
		scale.y * rotatExYZMatrix.m[1][0],	scale.y * rotatExYZMatrix.m[1][1],	scale.y * rotatExYZMatrix.m[1][2],0,
		scale.z * rotatExYZMatrix.m[2][0],	scale.z * rotatExYZMatrix.m[2][1],	scale.z * rotatExYZMatrix.m[2][2],0,
		translate.x,translate.y,translate.z,1
	};

}

Vector3 scale{ 1.2f,0.79f,-2.1f };
Vector3 rotate{ 0.4f,1.43f,-0.8f };
Vector3 translate{ 2.7f,-4.15f,1.57f };

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

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

		Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");

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
