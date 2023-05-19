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

static Matrix4x4 MakePerspectiveFovMatrix(float rad);
static Matrix4x4 MakeOrthographicMatrix(float rad);
static Matrix4x4 MakeViewportMatrix(float rad);

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip, float rad) {

	return Matrix4x4{
		1 / aspectRatio * std::tan(rad) * (fovY / 2), 0, 0, 0,


	};

}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

Matrix4x4 orthographicMatrix = MakeOrthographicMatrix(-160.f, 160.f, 200.0f, 300.0f, 0.0f, 1000.0f);

Matrix4x4 perspectiveFovMatrix = MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);

Matrix4x4 viewportMatrix = MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);

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

		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");

		MatrixScreenPrintf(0, kRowHeight * 5, perspectiveFovMatrix, "perspectiveFovMatrix");

		MatrixScreenPrintf(0, kRowHeight * 10, viewportMatrix, "viewportMatrix");

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
