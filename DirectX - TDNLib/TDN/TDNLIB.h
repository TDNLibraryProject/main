#pragma once
#define _CRT_SECURE_NO_WARNINGS// (?)警告を無効にする
#define	_CRT_SECURE_NO_DEPRECATE

// スタティックリンク
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib" )	// 経過時間を扱うライブラリ
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib, "dsound.lib" )
#pragma comment (lib, "dxguid.lib")


// インクルード 
#include	<windows.h>		// Windowsアプリケーションを作成
#include	<d3dx9.h>		// DirectXを扱うためのヘッダー
#include	<process.h>		// スレッドを扱うためのヘッダー
#include	<dinput.h>		// DirectInputを扱うためのヘッダー
#include	<dsound.h>		// DirectSoundを扱うためのヘッダー
#include	<mmsystem.h>	// 処理時間を計算するために使う関数が入っている
#include	<stdarg.h>		// 可変長引数を処理するマクロが定義されています
#include	<time.h>		// 主に時間を扱うための関数が定義されています
#include	<math.h>		// 計算に役に立つ関数やマクロが定義されています
#include	<vector>		// 動的配列を扱うヘッダー
#include	<stack>			// 
#include	<map>			// 連想配列を扱うヘッダー
#include	<queue>
#include	<fstream>		// ファイルを扱う関数などが定義されています
#include	<assert.h>		// アサートを扱うヘッダー

/********************************************/
//	定数	
/********************************************/
#define VECTOR_ZERO Vector3(0.0f,0.0f,0.0f)
#define	PI	((FLOAT)  3.141592654f)

/********************************************/
//	マクロ	
/********************************************/
#define SAFE_DELETE(p) if(p){ delete p;p=nullptr;}
#define SAFE_RELEASE(p) { if(p){ (p)->Release(); (p)=NULL; } }
#define FOR(len) for (int i = 0; i < len; i++)
#define ARGB(a,r,g,b)	((DWORD)( (a<<24) | (r<<16) | (g<<8) | (b) ) )


/********************************************/
//	変数型定義
/********************************************/
#define u8	unsigned char
#define u16	unsigned short
#define u32 unsigned long
#define COLOR DWORD
#define null NULL

typedef D3DXVECTOR4		Vector4;
typedef D3DXMATRIX		Matrix;
typedef IDirect3DTexture9 Texture2D;		// IDirect3DTexture9の略
typedef IDirect3DSurface9 Surface;			// IDirect3DSurface9の略
typedef IDirect3DDevice9 DEVICE, *LPDEVICE;	// IDirect3DDevice9の略

// ハンガリアン記法
/**
*	p または lp ->	ポインタ型
*	m_			->	メンバ変数
*	g_			->	グローバル変数
*	dw			->	double word型　
*	tag			->	構造体
*	by			->	バイナリ
*/

/********************************************/
//	構造体関連
/********************************************/
// 基本ベクトル
typedef struct Vector
{
	float x, y, z;
	Vector() :x(0), y(0), z(0){}
} Vector;

// ベクトル
typedef struct Vector3 : public Vector
{
public:
	//	コンストラクタ
	Vector3() :Vector(){};
	// Vector(x,y,x)とできるように
	inline Vector3(float x, float y, float z){ this->x = x, this->y = y, this->z = z; }
	inline Vector3(CONST Vector& v){ this->x = v.x, this->y = v.y, this->z = v.z; }

	//	距離計算
	inline float Length(){ return sqrtf(x*x + y*y + z*z); }
	inline float LengthSq(){ return x*x + y*y + z*z; }

	//	正規化
	void Normalize()
	{
		float l = Length();
		if (l != .0f){ x /= l; y /= l; z /= l; }
	}

	
	//	オペレーター
	
	// this+=vector
	inline Vector3& operator = (CONST Vector& v){ x = v.x; y = v.y; z = v.z; return *this; }
	// this+=Vector3
	inline Vector3& operator += (CONST Vector3& v){ x += v.x; y += v.y; z += v.z; return *this; }
	// this-=Vector3
	inline Vector3& operator -= (CONST Vector3& v){ x -= v.x; y -= v.y; z -= v.z; return *this; }
	// this*=Vector3
	//inline Vector3& operator *= (CONST Vector3& v){ x *= v.x; y *= v.y; z *= v.z; return *this; }
	// this*=flaot
	inline Vector3& operator *= (FLOAT v){ x *= v; y *= v; z *= v; return *this; }
	// this/=flaot
	inline Vector3& operator /= (FLOAT v){ x /= v; y /= v; z /= v; return *this; }

	inline Vector3 operator + () const { Vector3 ret(x, y, z); return ret; }
	inline Vector3 operator - () const { Vector3 ret(-x, -y, -z); return ret; }

	// Vector3 = Vector3 + Vector3
	inline Vector3 operator + (CONST Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
	// Vector3 = Vector3 - Vector3
	inline Vector3 operator - (CONST Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
	// Vector3 = Vector3 * float
	inline Vector3 operator * (FLOAT v) const { Vector3 ret(x*v, y*v, z*v); return ret; }
	// Vector3 = Vector3 / float
	inline Vector3 operator / (FLOAT v) const { Vector3 ret(x / v, y / v, z / v); return ret; }

	//追加分
	//inline Vector operator *(const float& f){ Vector a = { x * f, y * f, z * f }; return a; }

	// if( Vector3 == Vector3 )
	BOOL operator == (CONST Vector3& v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
	// if( Vector3 != Vector3 )
	BOOL operator != (CONST Vector3& v) const { return (x != v.x) || (y != v.y) || (z != v.z); }


	inline void Set(float x, float y, float z){ this->x = x, this->y = y, this->z = z; }

} Vector3, *LPVECTOR3;

// 内積
inline float Vector3Dot(Vector& v1, Vector& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

// 外積
inline void Vector3Cross(Vector& out, Vector& v1, Vector& v2)
{
	out.x = v1.y*v2.z - v1.z*v2.y;
	out.y = v1.z*v2.x - v1.x*v2.z;
	out.z = v1.x*v2.y - v1.y*v2.x;
}
inline Vector Vector3Cross(Vector& v1, Vector& v2)
{
	Vector3 out;
	out.x = v1.y*v2.z - v1.z*v2.y;
	out.y = v1.z*v2.x - v1.x*v2.z;
	out.z = v1.x*v2.y - v1.y*v2.x;
	return out;
}

// クォータニオン
typedef struct  Quaternion : public D3DXQUATERNION
{
public:
	//------------------------------------------------------
	//	コンストラクタ
	//------------------------------------------------------
	Quaternion(){}
	Quaternion(const D3DXQUATERNION& in) :D3DXQUATERNION(in)
	{}
	Quaternion( float sx, float sy, float sz, float sw ) : D3DXQUATERNION( sx, sy, sz, sw ){}

	//------------------------------------------------------
	//	生成
	//------------------------------------------------------
	//	単位クォータニオン生成
	void Identity(){ x = y = z = 0; w = 1; }

	//	正規化
	inline void normalize()
	{
		float legnth = getLength();
		if (legnth == .0f) return;
		float invL = 1.0f / legnth;
		(*this) *= invL;
	}

	//------------------------------------------------------
	//	情報取得
	//------------------------------------------------------
	inline float getLength() const{ return sqrtf(x*x + y*y + z*z + w*w); }
	void toMatrix(Matrix& m);

	//------------------------------------------------------
	//	オペレーター
	//------------------------------------------------------
	inline Quaternion operator + () const { Quaternion ret(x, y, z, w); return ret; }
	inline Quaternion operator - () const { Quaternion ret(-x, -y, -z, -w); return ret; }

	//	VS クォータニオン
	inline Quaternion& operator +=(const Quaternion& v){ x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	inline Quaternion& operator -=(const Quaternion& v){ x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	inline Quaternion& operator *=(const Quaternion& v)
	{
		x = y * v.z - z * v.y + x * v.w + w * v.x;
		y = z * v.x - x * v.z + y * v.w + w * v.y;
		z = x * v.y - y * v.x + z * v.w + w * v.z;
		w = w * v.w - x * v.x - y * v.y - z * v.z;
		return *this;
	}

	inline Quaternion operator +(const Quaternion& v) const{ return Quaternion(x + v.x, y + v.y, z + v.z, w + v.w); }
	inline Quaternion operator -(const Quaternion& v) const{ return Quaternion(x - v.x, y - v.y, z - v.z, w - v.w); }
	inline Quaternion operator *(const Quaternion& v) const
	{
		return Quaternion(
			y * v.z - z * v.y + x * v.w + w * v.x,
			z * v.x - x * v.z + y * v.w + w * v.y,
			x * v.y - y * v.x + z * v.w + w * v.z,
			w * v.w - x * v.x - y * v.y - z * v.z
			);
	}

	//	VS 値
	inline Quaternion& operator *=(float v){ x *= v; y *= v; z *= v; w *= v; return *this; }
	inline Quaternion& operator /=(float v){ x /= v; y /= v; z /= v; w /= v; return *this; }

	inline Quaternion operator *(float v) const{ return Quaternion(x*v, y*v, z*v, w*v); }
	inline Quaternion operator /(float v) const{ return Quaternion(x / v, y / v, z / v, w / v); }

} Quaternion;

//	球面線形補間
Quaternion QuaternionSlerp(Quaternion& q, Quaternion& r, float a);

/*************************************************/
//	行列やベクトルに関する計算のプロトタイプ宣言
/*************************************************/
// 変換行列
void	SetTransformMatrixZXY(Matrix *Mat, float posX, float posY, float posZ, float angleX, float angleY, float angleZ);
void	SetTransformMatrixXYZ(Matrix *Mat, float posX, float posY, float posZ, float angleX, float angleY, float angleZ);
// ビュー変換表列
void	LookAtLH(Matrix& mat, Vector& Eye, Vector& At, Vector& Up);
// 投影変換表列
void	PerspectiveLH(Matrix& mat, float fovY, float aspect, float zn, float zf);
void	OlthoLH(Matrix& mat, float w, float h, float zn, float zf);
// 距離計算
inline float Length(float x1, float y1, float x2, float y2);
inline float Length(Vector3 PosA, Vector3 PosB);
bool Collision_Sphere(Vector3 PosA, float RadiusA, Vector3 PosB, float RadiusB);

/********************************************/
//	前方宣言
/********************************************/
//class tdnRenderState;
//typedef tdnRenderState RS;// (?) 書き方わからん
class tdnShader;
class tdn2DObj;

/********************************************/
//	tdnSystem
/********************************************/
// スクリーンモード
#define	SCREEN800x450	0
#define	SCREEN1280x720	1
#define	SCREEN1920x1080	2
#define	SCREEN800x600	3

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);			 // ウィンドウプロシージャ
//BOOL InitApp(HINSTANCE hInst, int nCmdShow);												 // ゲーム起動時の最初の初期化
//BOOL EndApp();																			 // ゲームの一番最後の後処理

extern	Matrix	matView;		//	カメラ行列
extern	Matrix	matProjection;	//	投影変換行列

class tdnSystem
{
public:
	// 初期化・解放
	static BOOL InitWindow(HINSTANCE hinst, int nCmdShow, char* AppTitle, DWORD ScreenMode, BOOL isFullScreen);

	static void Release();
private:	
	// お約束
	static HINSTANCE hinst;				// インスタンスハンドル	
	static HWND	Window;					// ウィンドウハンドル
	static BOOL WindowActive;			// ウィンドウの状態
private:
	static BOOL InitD3D();				// D3D初期化。Privateへ移行
	static LPDIRECT3D9	lpD3D;			// DirectX9にアクセスするためのポインタ			
	static LPDEVICE	Device;				// ビデオカードにアクセスするための3Dデバイス		
	static D3DPRESENT_PARAMETERS d3dpp;	// ディスプレイパラメーター
	static ID3DXLine* pLine;			// 線描画
	// スクリーンのサイズ
	static RECT	 ScreenSize;			// スクリーンのサイズ
	static D3DFORMAT ScreenFormat;		// スクリーンのフォーマット
	static BOOL FullScreen;				// フルスクリーンのフラグ
public:
	// (?)なぜ値が変わったらまずいデータがグローバルに？	

	// パラメーター取得関数
	static inline HINSTANCE GetHinst(){ return hinst; }
	static inline HWND GetWindow(){ return Window; }
	static inline LPDIRECT3D9 GetD3D9(){ return lpD3D; };
	static inline LPDEVICE GetDevice(){ return Device; };
	static inline ID3DXLine* GetLine(){ return pLine; };
	static inline RECT GetScreenSize(){ return ScreenSize; }
	static inline D3DFORMAT GetScreenFormat(){ return ScreenFormat; }
	static inline BOOL GetWindowActive(){ return WindowActive; };

	// ウィンドウメッセージ処理関数
	//static BOOL Message();

	// スクリーンのサイズを取得
	static RECT GetScreenRect(DWORD mode);
	//	シーン開始・終了
	static void BeginScene(){ Device->BeginScene(); }		// 描画開始!
	static void EndScene()									// 描画終了!
	{
		Device->EndScene();
		if (FAILED(Device->Present(NULL, NULL, NULL, NULL))) Device->Reset(&d3dpp);
	}
	// ウィンドウが今動いているかをセットする関数
	static void SetWindowActive(BOOL active){ WindowActive = active; }

	//	デバッグウィンドウ
	static void OpenDebugWindow();
	static void CloseDebugWindow();
	static void printf(const char* format, ...);

};


/********************************************/
//				tdnView				     
/********************************************/
class tdnView
{
public:
	// 初期化
	static void Init()
	{
		SetViewport();
		SetProjection(D3DX_PI / 3.0f, 0.1f, 3000.0f);
	}

	//	視界クリア
	static void Clear(DWORD color = 0, bool bClearZ = true);
	static void ClearZ();

	//	視点設定
	static void Set(const Vector& pos, const Vector& target);
	static void Set(float x, float y, float z, float ax, float ay, float az);

	//	投影平面設定
	static void SetViewport();
	static void SetViewport(int x, int y, int w, int h);

	//	投影設定
	static void SetProjection(float FovY, float Near, float Far);
	static void SetProjection(float FovY, float Near, float Far, float asp);

	// 行列・ビューポート更新
	static void Activate();

protected:
	static Vector  Pos, Target;			// 始点と目線	
	// ビューポート
	static D3DVIEWPORT9	Viewport;		// Window画面のどの領域まで3Dを描画するか
	static float FovY;					// 視野角
	static float Near, Far;				// 投影の手前の位置と一番奥の位置 
	static float Aspect;				// 


};


/********************************************/
//				tdnRenderState				     
/********************************************/
typedef enum RS
{
	COPY = 1,
	COPY_NOZ = 2,
	ADD = 3,
	SUB = 4,
	MUL = 5,
	NEGA = 6,
	INVERT = 7
}RM;

class tdnRenderState
{
public:
	//static const unsigned long COPY = 0;
	//static const unsigned long COPY_NOZ = 32;
	//static const unsigned long ADD = 1;
	//static const unsigned long SUB = 2;
	//static const unsigned long MUL = 4;
	//static const unsigned long NEGA = 8;
	//static const unsigned long INVERT = 16;

	static void Initialize();
	static void Set(DWORD state, D3DMATERIAL9* lpMaterial, Texture2D* lpTexture);
	static void	Filter(BOOL bFilter);												//	サンプラーステート　TRUE：LINER(補間)　FLASE:POINT(処理は早い)　
};

/********************************************/
//				tdnTexture				     
/********************************************/
class tdnTexture
{
private:
	static const int MAX_TEXTURE = 512;

	struct TEXINFO {
		char		filename[64];	//	ファイルパス
		int			UseCount;		//	このテクスチャ使用しているカウント
		Texture2D*	lpTexture;		//	テクスチャ	
		D3DXIMAGE_INFO info;		//  (追加)サイズの情報取得
	};
	static struct TEXINFO TexInfo[MAX_TEXTURE];

public:
	//	初期化
	static void Initialize();
	//	読み込み・解放
	static Texture2D* Load(const char* filename);
	static void	Release(Texture2D* lpTexture);

};
/********************************************/
//				tdnLight				     
/********************************************/
class tdnLight
{
public:
private:

};


/********************************************/
//				tdnShader				     
/********************************************/

class tdnShader
{

public:
	// 初期化・解放
	tdnShader(char* filename);
	~tdnShader();

	// シェーダー利用開始・終了
	inline UINT Begin(char* name)		// シェーダ開始
	{
		UINT pass;
		// シェーダーの適用
		pShader->SetTechnique(name);	// テクニック名を設定する
		pShader->Begin(&pass, 0);	
		return pass;
	}
	inline void End(){ pShader->End(); }// シェーダ終了

	/*	パスの開始・終了  */	
	inline void BeginPass(int pass){ pShader->BeginPass(pass); }	// アクティブなテクニック内でパスを開始します。
	inline void EndPass(){ pShader->EndPass(); }					// パス終り
	inline void CommitChanges(){ pShader->CommitChanges(); }		// BeginPass～EndPass内でセッターを通して値を変更した際に呼び出す必要がある関数です

	// パラメーター設定
	void SetWVPMatrix(Matrix* wvpMat);
	void SetWVPMatrix(Matrix& wvpMat);

	void SetDecaleTexture(Texture2D* decaleTex);
	void SetDecaleTexture(Texture2D& decaleTex);

	void SetValue(char* name, Texture2D* tex);
	void SetValue(char* name, Texture2D& tex);

	void SetValue(char* name, Matrix* mat);
	void SetValue(char* name, Matrix& mat);

	void SetValue(char* name, D3DXVECTOR4* v);
	void SetValue(char* name, D3DXVECTOR4& v);

	void SetValue(char* name, Vector3* v);
	void SetValue(char* name, Vector3& v);

	void SetValue(char* name, float f);
	void SetValue(char* name, int d);
	void SetValue(char* name, DWORD d);

private:
	LPD3DXEFFECT pShader;	// エフェクトファイルへのアクセスポインタ

	D3DXHANDLE	hmWVP;		// 射影変換行列　パラメーターを参照するための効率的な手段を提供します。
	D3DXHANDLE  htexDecale;	// テクスチャ

};

/********************************************/
//				tdn2DObj				     
/********************************************/
//	レンダーターゲットのフォーマット
typedef enum FMT2D
{
	RENDERTARGET = 1,
	FLOAT1 = 2,
	FLOAT2 = 3,
	USEALPHA = 4,
	SYSTEMMEM = 5,
	HDR = 6,
	SYSTEMMEM_HDR = 7
}tdn2D;

class tdn2DObj
{
public:
	tdn2DObj(char* fileName);								// ファイルから画像読み込み
	tdn2DObj(UINT width, UINT height, FMT2D fmtFlag);		// レンダーターゲット作成

	~tdn2DObj();											// 画像orレンダーターゲット解放

	// 情報取得
	void RenderTarget(int index = 0);						// レンダーターゲット設定
	Surface*	GetSurface(){ return lpSurface; };			// 板
	Texture2D*	GetTexture(){ return lpTexture; };			// テクスチャ

	// 描画
	void Render(int x, int y, u32 dwFlags = RS::COPY);
	void Render(int x, int y, tdnShader* shader, char* name);// shader適用
	void Render(int x, int y, int w, int h, int tx, int ty, int tw, int th, u32 dwFlags = RS::COPY);
	void Render(int x, int y, int w, int h, int tx, int ty, int tw, int th, tdnShader* shader, char* name);

	// 3D描画
	void Render3D(float x, float y, float z, u32 dwFlags = RS::COPY);
	void Render3D(Vector3 pos, u32 dwFlags = RS::COPY);
	void Render3D(float x, float y, float z, int w, int h, int tx, int ty, int tw, int th, u32 dwFlags = RS::COPY);
	void Render3D(Vector3 pos, int w, int h, int tx, int ty, int tw, int th, u32 dwFlags = RS::COPY);

	///	情報更新
	void SetScale(float scale);
	void SetAngle(float angle);
	void SetARGB(BYTE A, BYTE R, BYTE G, BYTE B);
	void SetARGB(int A, int R, int G, int B);
	void SetARGB(DWORD ARGB);
	void SetTurnOver(bool turnFlag);
	void SetShiftCenter(bool ShiftFlag);
	void SetCenter(float x, float y);

	// 情報取得
	inline float GetScale(){ return scale; }
	inline float GetAngle(){ return angle; }
	inline float GetCenterX(){ return centerX; }
	inline float GetCenterY(){ return centerY; }
	inline bool GetTurnOver(){ return isTurnOver; };
	inline bool GetShiftCenter(){ return isShiftCenter; };
private:

	// unsigned intの理由はGetLevelDescから受け取る情報などがUINTだから
	UINT		m_width;				// 幅
	UINT		m_height;				// 高さ

	// テクスチャと画像情報
	Surface*	lpSurface;			// 板
	Texture2D*	lpTexture;			// テクスチャ

	// ステータス
	float scale, angle;
	DWORD color;
	float centerX, centerY;
	bool isTurnOver;
	bool isShiftCenter;				//xyを画像の中心に

};



/********************************************/
//				tdnPolygon	
/********************************************/

//************************************************************
//	■D3DFVF組み合わせ頂点
//	オリジナルFVFマクロとその設定にあった構造体を送ることで
//	自由な頂点データを送れる。
//***********************************************************

//	２Ｄ用頂点（ライティング＆トランスフォーム済み）
#define D3DFVF_TLVERTEX		( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )//　←D3DFVF_XYZRHW(sx, sy, sz, rhw)と D3DFVF_DIFFUSE(color)とD3DFVF_TEX1(uv)の組み合わせ
typedef struct tagTLVERTEX {
	float	sx, sy, sz;
	float	rhw;
	COLOR	color;
	float	tu, tv;
} TLVERTEX, *LPTLVERTEX;

//	２Ｄ用頂点（ライティング＆トランスフォーム済み、色なし）
#define D3DFVF_TLVERTEX2	( D3DFVF_XYZRHW | D3DFVF_TEX1 )
typedef struct tagTLVERTEX2 {
	float	sx, sy, sz;
	float	rhw;
	float	tu, tv;
} TLVERTEX2, *LPTLVERTEX2;

//	３Ｄ用頂点(法線なし）
#define D3DFVF_VERTEX		( D3DFVF_XYZ | D3DFVF_TEX1 )
typedef struct tagVERTEX {
	float	x, y, z;
	float	tu, tv;
} VERTEX, *LPVERTEX;

//	３Ｄ用頂点(ライティング済み）
#define D3DFVF_LVERTEX		( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) // 3つのオブジェクト形式マクロを合わせた
typedef struct tagLVERTEX {
	float	x, y, z;	// 頂点座標
	COLOR	color;		// 頂点の色
	float	tu, tv;		// テクスチャの座標
} LVERTEX, *LPLVERTEX;

//	３Ｄメッシュ用頂点
#define D3DFVF_MESHVERTEX		( D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1 )
typedef struct tagMESHVERTEX {
	float	x, y, z;
	float	nx, ny, nz;
	float	tu, tv;
} MESHVERTEX, *LPMESHVERTEX;

//	３Ｄ用頂点(ライティング済み）
#define D3DFVF_MESHVERTEX2		( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
typedef struct tagLNVERTEX {
	float	x, y, z;
	float	nx, ny, nz;
	COLOR	color;
	float	tu, tv;
} MESHVERTEX2, *LPMESHVERTEX2;

// ライン用の頂点
struct VECTOR_LINE
{
	float x, y, z; // 頂点 
	DWORD color;
};

//	２Ｄオブジェクト
//typedef tdn2DObj *LPtdn2DObj;

class tdnPolygon
{
public:
	// 3D
	static void Render3D(LPLVERTEX lpVertex, int Num, tdn2DObj* lpObj, u32 dwFlags);										// 3D固定
	static void Render3D(LPLVERTEX lpVertex, int Num, tdn2DObj* lpObj, u32 dwFlags, D3DXMATRIX mat);// 追加
	static void Render3D(LPLVERTEX lpVertex, int Num, tdn2DObj* lpObj, tdnShader* shader, char* name);					// 3Dシェーダ
	// 2D
	static void Render2D(LPTLVERTEX lpVertex, int Num, tdn2DObj* lpObj, u32 dwFlags);										// 2D固定
	static void Render2D(LPTLVERTEX lpVertex, int Num, tdn2DObj* lpObj, tdnShader* shader, char* name);					// 2Dシェーダ	
	// 矩形
	static void Rect(int DstX, int DstY, int DstW, int DstH, u32 dwFlags, COLOR color, float z = .0f);
	static void Rect(int DstX, int DstY, int DstW, int DstH, tdnShader* shader, char* name, COLOR color, float z = .0f);
	// 線
	static void DrawLine(float x1, float y1, float x2, float y2, DWORD color = 0xFFFFFFFF, float size = 1.0f);
	static void DrawLine3D(Vector3 pos1, Vector3 pos2, DWORD color = 0xFFFFFFFF, float size = 1.0f, u32 dwFlag = RS::COPY);

private:

};


// 3Dオブジェクト
class tdnMesh
{
public:
	tdnMesh();
	~tdnMesh();

	/********/
	/* 作成 */
	/********/

	struct CreateData
	{
		unsigned int      numVertexes;  // 頂点の数
		unsigned int      vertexSize;   // 頂点構造体のバイト数
		void              *vertexArray; // 頂点情報（頂点毎）配列

		unsigned int      numIndexes;   // インデックスの数
		DWORD             *indexArray;  // インデックスの配列
		
		unsigned int      numStream;    // ストリーム構造体の数
		unsigned int      streamSize;   // ストリーム構造体のバイト数
		void              *streamArray; // 頂点情報（インデックス毎）の配列

		D3DVERTEXELEMENT9 *decl;        // シェーダーに送る頂点構造体の定義
	};
	bool Create( const CreateData &data );
	bool CreateVertex(
		unsigned int numVertex,    // 頂点数
		unsigned int vertexSize,   // 頂点構造体のバイト数
		void *vertexArray );       // 頂点配列
	bool CreateIndexes(
		unsigned int numIndexes,   // インデックスの数
		const DWORD *indexArray ); // インデックス配列
	bool CreateStream( unsigned int numData, unsigned int dataSize, void *dataArray );
	bool CreateDeclaration(
		unsigned int declArySize,  // 頂点構造体のバイト数
		D3DVERTEXELEMENT9 *decl ); // シェーダー上での頂点構造体の宣言

	// xy平面に正三角形作成
	bool CreateTriangle(
		float radius,    // 外接円の半径
		DWORD color ); 
	// xy平面に長方形作成
	bool CreateRectangle(
		float width,
		float height,
		DWORD color );
	// 正四面体作成
	bool CreateTriangular(
		float radius, // 外接円の半径
		DWORD color );
	// 直方体作成
	bool CreateCube(
		float width,
		float height,
		float depth,
		DWORD color,
		Vector3 *posList = nullptr,
		unsigned int numPos = 0 );

	/************/
	/* 読み込み */
	/************/

	bool LoadMqo( char *filename );

	/********/
	/* 更新 */
	/********/

	// pos, scale, rot からworldMatrix作成
	void UpdateWorldMatrix();

	/********/
	/* 描画 */
	/********/

	void Render( tdnShader *shader, char *technique );

	/*********************/
	/* セッター ゲッター */
	/*********************/

	const Vector3& Pos();
	void Pos( const Vector3& in );
	const Vector3& Scale();
	void Scale( const Vector3& in );
	const Quaternion& Rot();
	void Rot( const Quaternion& in );
	const Matrix& WorldMatrix();
	void WorldMatrix( const Matrix& in );

private:
	IDirect3DVertexDeclaration9* decl;         // 頂点デコレーション（FVF）
	unsigned int                 declSize;     // 頂点構造体のバイト数

	IDirect3DVertexBuffer9*      vertexBuffer;
	unsigned int                 numVertexes;

	IDirect3DIndexBuffer9*       indexBuffer;
	unsigned int                 numIndexes;

	IDirect3DVertexBuffer9*      streamBuffer; // オブジェクト毎の情報
	unsigned int                 streamSize;   // streamBuffer の一つのデータのバイト数
	unsigned int                 numStream;   // streamBuffer の個数

	unsigned int                 numFaces;     // 三角ポリゴン数

	Vector3    pos;
	Vector3    scale;
	Quaternion rot;
	Matrix     worldMatrix;
	public:
	Texture2D *texture;
};

//*****************************************************************************
//
//		オーディオ関連
//
//*****************************************************************************

#include "ogg/vorbisfile.h"

#define	STR_NORMAL	0
#define	STR_FADEIN	1
#define	STR_FADEOUT	2

#define	TYPE_WAV	0
#define	TYPE_OGG	1

enum class DXA_FX
{
	DXAFX_OFF = 0,		// エフェクトオフ
	DXAFX_CHORUS = 1 << 0,	// コーラス
	DXAFX_COMPRESSOR = 1 << 1,	// コンプレッサ
	DXAFX_DISTORTION = 1 << 2,	// ディスト―ション
	DXAFX_ECHO = 1 << 3,	// エコー
	DXAFX_FLANGER = 1 << 4,	// フランジ
	DXAFX_GARGLE = 1 << 5,	// ガーグル
	DXAFX_ENVREVERB = 1 << 6,	// 環境リバーブ
	DXAFX_PARAMEQ = 1 << 7,	// パラメトリックイコライザ
	DXAFX_WAVESREVERB = 1 << 8,	// ミュージックリバーブ(16bitのオーディオフォーマットのみ)
	DXAFX_MAX = 1 << 9
};

class tdnSoundBuffer
{
protected:
	LPDIRECTSOUNDBUFFER8	lpBuf;
	LPDIRECTSOUND3DBUFFER8	lpBuf3D;
	LPBYTE LoadWAV(LPSTR fname, LPDWORD size, LPWAVEFORMATEX wfx);

	DWORD PlayCursor;
	DWORD BufferSize;
	WAVEFORMATEX format;

	// Loadするときに使う変数(ローカル⇒メンバ変数)
	WAVEFORMATEX	wfx;
	LPBYTE			lpWBuf;
	DWORD			size;

	char			wav_file_path[128];	/*	WAVEファイルへのパス*/
	bool			loop_flag;

public:
	tdnSoundBuffer(LPDIRECTSOUND8 lpDS, char* filename, bool b3D);
	void Initialize(LPDIRECTSOUND8 lpDS, unsigned char* data, DWORD size, LPWAVEFORMATEX fmt, bool b3D);
	tdnSoundBuffer(){}
	~tdnSoundBuffer();

	// 同じのを複数読み込みたいときに使う
	static void Create_and_copy(LPDIRECTSOUND8 lpDS, char* filename, bool b3D, tdnSoundBuffer **buffers, int dst, int count);

	LPDIRECTSOUNDBUFFER8 GetBuf(){ return lpBuf; }
	void Play(bool loop, DWORD cursor = 0);
	void Stop();
	void Pause();
	void PauseOff();

	void	SetVolume(int volume);
	int		GetVolume();
	void	SetPan(int pan);
	int		GetPan();
	void	SetFrequency(int pitch);
	int		GetFrequency();
	bool	isPlay();
	void	SetSpeed(float speed);
	float	GetSpeed();

	DWORD GetPlayCursor();
	void SetPlayCursor(DWORD new_position);
	DWORD GetPlayFrame();
	int GetPlaySecond();
	void SetPlaySecond(int sec);
	DWORD GetPlayMSecond();
	DWORD GetSize();
	int GetLengthSecond();

	void Get_file_path(char out[]){ sprintf_s(out, sizeof(out), "%s", wav_file_path); }


	//------------------------------------------------------
	//	サウンドエフェクト
	//------------------------------------------------------
	void SetFX(DXA_FX flag);

	//------------------------------------------------------
	//	3D関係
	//------------------------------------------------------
	void SetDist(float max_dist = DS3D_DEFAULTMAXDISTANCE, float min_dist = DS3D_DEFAULTMINDISTANCE);	// 最大超えるともう聞こえない、最少は普通に1とかでいいと思う
	void SetPos(const Vector3 &pos);																	// 音が発生する座標
	void SetFront(const Vector3 &front);																// 音の向き
	void SetRange(int degreeIn = DS3D_DEFAULTCONEANGLE);												// 音の範囲内角度の設定(度)
	void SetOutRange_volume(int out_vol = DS3D_DEFAULTCONEOUTSIDEVOLUME);								// 角度範囲外の場合の音(-10000(最少)～0(最大))
	void SetMove(const Vector3 &move);																	// 普通は動かないけどドップラー効果で使う
	void SetAll3D(float max_dist, float min_dist, const Vector3 &pos, const Vector3 &front, int degreeIn, int out_vol, const Vector3 &move);
};

class tdnStreamSound
{
private:
	static const int STRSECOND = 1;
	int		rate;
	LPDIRECTSOUNDBUFFER	lpStream;		// ストリーム用二次バッファ
	DSBPOSITIONNOTIFY	pn[3];

	HANDLE	hStrThread;
	unsigned long dwThreadId;
	unsigned long dwThrdParam;

	FILE*	hStrFile;
	OggVorbis_File	vf;
	DWORD StrSize;
	DWORD StrPos;
	DWORD LoopPtr;

	BYTE mode;
	int	param;
	int volume;

	void Initialize(LPDIRECTSOUND lpDS, int rate);

	BOOL	OGGRead(LPBYTE dst, unsigned long size);

public:
	BYTE	type;
	HANDLE	hEvent[3];
	LPDIRECTSOUNDNOTIFY	lpStrNotify;


	tdnStreamSound(LPDIRECTSOUND lpDS, LPSTR filename, BYTE mode, int param);
	~tdnStreamSound();

	BOOL	SetBlockOGG(int block);
	BOOL	SetBlockWAV(int block);

	BOOL	SetWAV(LPDIRECTSOUND lpDS, char* filename);
	BOOL	SetOGG(LPDIRECTSOUND lpDS, char* filename);

	void	Stop();
	void	SetVolume(int volume);
	int		GetVolume(){ return volume; }

	void SetMode(BYTE mode, int param);
	BYTE GetMode(){ return mode; }
	int GetParam(){ return param; }

};

typedef tdnStreamSound tdn_DSSTREAM, *tdn_LPDSSTREAM;




//*****************************************************************************
//
//		サウンド管理の基底(継承で使うだけで、ゲーム作る人は使用しない)
//
//*****************************************************************************
class tdnSoundBase
{
protected:
	static const int WavNum = 128;	// バッファ最大値

	HWND	hWndWAV;

	LPDIRECTSOUND8			lpDS;		// DirectSoundオブジェクト
	LPDIRECTSOUNDBUFFER	lpPrimary;		// 一次バッファ

	LPDIRECTSOUND3DLISTENER8 lp3DListener;	// 3Dサウンド上で、音源と聞こえる人との関係でいうと聞こえる人の情報

public:
	//------------------------------------------------------
	//	初期化・解放
	//------------------------------------------------------
	tdnSoundBase();
	virtual ~tdnSoundBase();

	//------------------------------------------------------
	// ※3Dサウンド限定 リスナー情報設定
	//------------------------------------------------------
	void SetListenerPos(const Vector3 &pos);
	void SetListenerOrientation(const Vector3 &fornt, const Vector3 &up);
	void SetListenerMove(const Vector3 &move);
	void SetListenerAll(const Vector3 &pos, const Vector3 &fornt, const Vector3 &up, const Vector3 &velocity);
	void UpdateListener();	// 3Dサウンドを使用する場合、毎回これを呼び出してください
};


//*****************************************************************************
//
//		サウンド管理(SE用)
//
//*****************************************************************************
#include<vector>

class tdnSoundSE : public tdnSoundBase
{
private:
	struct SEData
	{
		bool b3D;					// 3Dフラグ
		tdnSoundBuffer* buffer;	// サウンドバッファ
	};
	std::vector<SEData*> data[WavNum];

public:
	tdnSoundSE();
	~tdnSoundSE();

	//------------------------------------------------------------------------------------------------------------------------------------------------------
	//	引数…ID:番号、 num_of_play_simultaneously:同時再生可能数(あんまり多いとメモリ食うのでほどほどに。5～10前後)、　ファイル名、　3Dサウンドフラグ
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	void Set(int ID, int num_of_play_simultaneously, char* filename, bool b3D = false);

	/* 再生 */
	int Play(int ID, bool loop = false);

	/* 停止:noにはPlayで返ってきた値を自分で入れる */
	void Stop(int ID, int no);
	void AllStop();

	/* 各サウンドパラメータ設定・取得関数 */
	void	SetVolume(int ID, int volume);
	void	SetVolume(int ID, float volume);	// 0～1
	int		GetVolume(int ID);
	void	SetPan(int ID, int pan);
	int		GetPan(int ID);
	void	SetFrequency(int ID, int pitch);
	void	SetFrequency(int ID, int no, int pitch);
	int		GetFrequency(int ID, int no);
	void	SetSpeed(int ID, float speed);
	void	SetSpeed(int ID, int no, float speed);
	bool	isPlay(int ID, int no);
	void	SetFX(DXA_FX flag);
	void	SetFX(int ID, DXA_FX flag);


	//---------------------------------------------------------------
	// ※以下の関数を呼ぶにはSetの引数のb3Dをtrueにする必要があります
	//---------------------------------------------------------------
	int Play(int ID, const Vector3 &pos, const Vector3 &front = Vector3(0, 0, -1), const Vector3 &move = Vector3(0, 0, 0), bool loop = false);// 音源情報設定しつつ再生
	void SetDist(int ID, int no, float max_dist = DS3D_DEFAULTMAXDISTANCE, float min_dist = DS3D_DEFAULTMINDISTANCE);				// 最大超えるともう聞こえない、最少は普通に0とかでいいと思う
	void SetPos(int ID, int no, const Vector3 &pos);																				// 音が発生する座標
	void SetFront(int ID, int no, const Vector3 &front);																			// 音の向き
	void SetRange(int ID, int no, int degreeIn = DS3D_DEFAULTCONEANGLE);															// 音の範囲内角度の設定(度)
	void SetOutRange_volume(int ID, int no, int out_vol = DS3D_DEFAULTCONEOUTSIDEVOLUME);											// 角度範囲外の場合の音(-10000(最少)～0(最大))
	void SetMove(int ID, int no, const Vector3 &move);																				// 普通は動かないけどドップラー効果で使う
	void SetAll3D(int ID, int no, float max_dist, float min_dist, const Vector3 &pos, const Vector3 &front, int degreeIn, int out_vol, const Vector3 &move);
};



//*****************************************************************************
//
//		サウンド管理(BGM用)	※このクラスのみ、毎フレームUpdateを呼び出してください
//
//*****************************************************************************

class tdnSoundBGM : public tdnSoundBase
{
private:
	static const int MinVolume = -2500;	// 音量最少値

	enum class MODE
	{
		NONE, FADE_IN, FADE_OUT, MAX
	};
	void None(int no);
	void In(int no);
	void Out(int no);
	void(tdnSoundBGM::*Fade_funk[(int)MODE::MAX])(int);

	struct BGMData
	{
		bool b3D;			// 3Dサウンドフラグ
		MODE fade_mode;		// フェードインかアウトか何もしないか
		float volume;		// 音量(0～1)
		float fade_speed;		// フェード速度
		tdnSoundBuffer* buffer;
	};
	std::vector<BGMData*> data;

public:
	tdnSoundBGM();
	~tdnSoundBGM();

	//////////////////////////////////////////////
	/* ※毎フレームUpdateを呼び出してください！ */
	void Update();
	//////////////////////////////////////////////

	//------------------------------------------------------------------------------------------------------------------------------------------------------
	//	引数…ID:番号、ファイル名、3Dサウンドフラグ(BGMの場合、使う機会はほぼない)
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	void Set(int ID, char* filename, bool b3D = false);
	void Set(int ID, unsigned char *data, unsigned long size, LPWAVEFORMATEX wfx, bool b3D = false);

	/* 再生 */
	void Play(int ID, bool loop = true, DWORD cursor = 0);

	/* 停止 */
	void Stop(int ID);
	void AllStop();
	void Pause(int ID);

	/* フェード関係(BGMとSEで分けた要因の1つ) */
	void FadeOut(int ID, float fade_speed);	// fade_speedは0～1の範囲。0.01とかの値になる
	void FadeIn(int ID, float fade_speed, bool loop = true, DWORD cursor = 0);

	enum class CROSS_FADE_TYPE
	{
		NORMAL,			// 普通に最初から再生
		END_OF_ETERNITY	// EoE形式(インさせるBGMをアウトさせるBGMと同じカーソルから再生させる)
	};
	void CrossFade(int inID, int outID, float fade_speed, CROSS_FADE_TYPE type = CROSS_FADE_TYPE::NORMAL, bool loop = true);
	void CrossFade(int inID, int outID, float in_speed, float out_speed, CROSS_FADE_TYPE type, bool loop);

	/* 各サウンドパラメータ設定・取得関数 */
	void	SetVolume(int ID, int volume);
	void	SetVolume(int ID, float volume);	// 0～1
	int		GetVolume(int ID);
	void	SetPan(int ID, int pan);
	int		GetPan(int ID);
	void	SetFrequency(int ID, int pitch);
	int		GetFrequency(int ID, int no);
	void	SetSpeed(int ID, float speed);
	void	SetSpeed(int ID, int no, float speed);
	bool	isPlay(int ID);
	DWORD	GetPlayCursor(int ID);
	DWORD	GetPlayFrame(int ID);
	int 	GetPlaySecond(int ID);
	DWORD	GetPlayMSecond(int ID);
	void	SetPlaySecond(int ID, int sec);
	DWORD	GetSize(int ID);
	int		GetLengthSecond(int ID);
	void	SetFX(DXA_FX flag);
	void	SetFX(int ID, DXA_FX flag);

	tdnStreamSound* PlayStream(char* filename);
	tdnStreamSound* PlayStream(char* filename, BYTE mode, int param);


	//---------------------------------------------------------------
	// ※以下の関数を呼ぶにはSetの引数のb3Dをtrueにする必要があります
	//---------------------------------------------------------------
	void Play(int ID, const Vector3 &pos, const Vector3 &front = Vector3(0, 0, -1), const Vector3 &move = Vector3(0, 0, 0), bool loop = true);// 音源情報設定しつつ再生
	void SetDist(int ID, int no, float max_dist = DS3D_DEFAULTMAXDISTANCE, float min_dist = DS3D_DEFAULTMINDISTANCE);				// 最大超えるともう聞こえない、最少は普通に0とかでいいと思う
	void SetPos(int ID, int no, const Vector3 &pos);																				// 音が発生する座標
	void SetFront(int ID, int no, const Vector3 &front);																			// 音の向き
	void SetRange(int ID, int no, int degreeIn = DS3D_DEFAULTCONEANGLE);															// 音の範囲内角度の設定(度)
	void SetOutRange_volume(int ID, int no, int out_vol = DS3D_DEFAULTCONEOUTSIDEVOLUME);											// 角度範囲外の場合の音(-10000(最少)～0(最大))
	void SetMove(int ID, int no, const Vector3 &move);																				// 普通は動かないけどドップラー効果で使う
	void SetAll3D(int ID, int no, float max_dist, float min_dist, const Vector3 &pos, const Vector3 &front, int degreeIn, int out_vol, const Vector3 &move);
};


// わぶよみこみ
unsigned char* LoadWavData(char *filename, unsigned long *size, LPWAVEFORMATEX wfx);

/********************************************/
//				tdnText				     
/********************************************/
class tdnText{
private:
	static LPD3DXFONT font;
public:
	static void Init();
	static void CleanUpModule();
	static void Draw(int x, int y, DWORD color, const char * _Format, ...);
};




/*****************************************/
//	ここからはエラーチェックのために追加
/*****************************************/

#ifndef __IT_DEBUG_H__
#define __IT_DEBUG_H__

#define _IT_DEBUG

#ifdef _IT_DEBUG

//*****************************************************************
//newオーバーロード
//*****************************************************************

#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <cassert>
#include <crtdbg.h>
#include <new>
#include <memory>

//*****************************************************************
//メモリーリーク自動チェック
//*****************************************************************
#define MyMemoryLeakCheck _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

//*****************************************************************
//		例外によって送出されるクラス
//*****************************************************************

template<class _error_type>
class ErrorHandlerBase
{
	typedef _error_type ERROR_TYPE_VALUE;
private:
	char				str[512];
	ERROR_TYPE_VALUE	data;
public:
	ErrorHandlerBase(
		const char* errstr,				//エラーメッセージ
		const ERROR_TYPE_VALUE& data):	//error値
		data(data)
	{
		str[0] = '\0';
		if (errstr)
		{
			strcpy_s(str, 512, errstr);
		}
	}
	~ErrorHandlerBase()
	{

	}
	ErrorHandlerBase(const ErrorHandlerBase& errh)
	{
		strcpy_s(str, 512, errh.GetStr());
	}
public:
	const char*	GetStr()const
	{
		return str;
	}
	const ERROR_TYPE_VALUE&	GetErrData()const
	{
		return data;
	}
};

//ゲーム強制終了error
typedef ErrorHandlerBase<int> Error_GameExit;


//*****************************************************************
//printfと同じ形式で出力ウィンドウに表示
//*****************************************************************
#define MyDebugString(str,...)\
{\
	TCHAR temp[512]; \
	sprintf_s<512>(temp, str, __VA_ARGS__); \
	OutputDebugString(temp); \
}

//*****************************************************************
//	メッセージボックスをprintfみたいに表示する
//*****************************************************************
#define MessageBoxPlus(str,...)\
{\
	char t[512]; \
	sprintf_s<512>(t, str, __VA_ARGS__);\
	MessageBox(0, t, "MessageBoxPlus", MB_OK);\
}

//*****************************************************************
//printfと同じ形式でアサートに文字列を表示させる
//*****************************************************************
#define MyAssert(expr,str,...)\
{\
if (!(expr)){\
\
	\
	char t[256], ti[600]; \
	sprintf_s<256>(t, str, __VA_ARGS__); \
	sprintf_s<600>(ti, "　%s　の行番号　%d　でエラーが発生しました \n %s \n式(%s) \n実行を続けますか？", __FILE__, __LINE__, t, #expr); \
	MessageBeep(MB_OK); \
if (MessageBox(0, ti, "MyAssertError!!!", MB_YESNO) == IDNO){\
	Error_GameExit err("GameExitError", 0);\
	throw err; \
}\
}\
}

#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)

#else

#define MyDebugString(str,...)
#define MyAssert(expr,str,...) expr
#define MyMemoryLeakCheck

#endif	//_IT_DEBUG

#endif	//eof