#pragma once
#define _CRT_SECURE_NO_WARNINGS// (?)�x���𖳌��ɂ���
#define	_CRT_SECURE_NO_DEPRECATE
#define	DIRECTINPUT_VERSION	0x0800 

// �X�^�e�B�b�N�����N
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "winmm.lib" )	// �o�ߎ��Ԃ��������C�u����
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib, "dsound.lib" )
#pragma comment (lib, "dxguid.lib")


// �C���N���[�h 
#include	<windows.h>		// Windows�A�v���P�[�V�������쐬
#include	<d3dx9.h>		// DirectX���������߂̃w�b�_�[
#include	<process.h>		// �X���b�h���������߂̃w�b�_�[
#include	<dinput.h>		// DirectInput���������߂̃w�b�_�[
#include	<dsound.h>		// DirectSound���������߂̃w�b�_�[
#include	<mmsystem.h>	// �������Ԃ��v�Z���邽�߂Ɏg���֐��������Ă���
#include	<stdarg.h>		// �ϒ���������������}�N������`����Ă��܂�
#include	<time.h>		// ��Ɏ��Ԃ��������߂̊֐�����`����Ă��܂�
#include	<math.h>		// �v�Z�ɖ��ɗ��֐���}�N������`����Ă��܂�
#include	<vector>		// ���I�z��������w�b�_�[
#include	<stack>			// 
#include	<map>			// �A�z�z��������w�b�_�[
#include	<queue>
#include	<fstream>		// �t�@�C���������֐��Ȃǂ���`����Ă��܂�
#include	<assert.h>		// �A�T�[�g�������w�b�_�[
#include	<memory>
/********************************************/
//	�萔	
/********************************************/
#define VECTOR_ZERO Vector3(0.0f,0.0f,0.0f)
#define	PI	((FLOAT)  3.141592654f)

/********************************************/
//	�}�N��	
/********************************************/
#define SAFE_DELETE(p) if(p){ delete p;p=nullptr;}
#define SAFE_RELEASE(p) { if(p){ (p)->Release(); (p)=nullptr; } }
#define FOR(len) for (int i = 0; i < len; i++)
#define ARGB(a,r,g,b)	((DWORD)( (a<<24) | (r<<16) | (g<<8) | (b) ) )


/********************************************/
//	�ϐ��^��`
/********************************************/
typedef signed char		s8;			// 8bit
typedef signed short	s16;
typedef signed long		s32;
// unsigned 
typedef unsigned char	u8;		
typedef unsigned short	u16;
typedef unsigned long	u32;		//32�r�b�g����4GB

typedef float	f32;
typedef double	f64;


#define COLOR DWORD
#define null NULL

typedef D3DXVECTOR4		Vector4;
typedef D3DXMATRIX		Matrix;
typedef IDirect3DTexture9 Texture2D;		// IDirect3DTexture9�̗�
typedef IDirect3DSurface9 Surface;			// IDirect3DSurface9�̗�
typedef IDirect3DDevice9 DEVICE, *LPDEVICE;	// IDirect3DDevice9�̗�



/********************************************/
//	�\���̊֘A
/********************************************/

/**
*@brief		float��̍\����
*@author	���c�@�Ђ�䂫
*/
typedef struct float2
{
	float x, y;
	float2() : x(0), y(0){}
}float2;


/**
*@brief	��{�p�x�N�g��.
*@author	Hiroyuki
*/
typedef struct float3
{
	float x, y, z;//!<@brief	�ϐ�.
	float3() :x(0), y(0), z(0){}
} float3, Vector;

// �x�N�g��
typedef struct Vector3 : public Vector
{
public:
	//	�R���X�g���N�^
	Vector3() :Vector(){};

	// Vector(x,y,x)�Ƃł���悤��
	inline Vector3(float x, float y, float z){ this->x = x, this->y = y, this->z = z; }
	inline Vector3(CONST Vector& v){ this->x = v.x, this->y = v.y, this->z = v.z; }

	//	�����v�Z
	inline float Length(){ return sqrtf(x*x + y*y + z*z); }
	inline float LengthSq(){ return x*x + y*y + z*z; }

	//	���K��
	void Normalize()
	{
		float l = Length();
		if (l != .0f){ x /= l; y /= l; z /= l; }
	}

	
	//	�I�y���[�^�[
	
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

	//�ǉ���
	//inline Vector operator *(const float& f){ Vector a = { x * f, y * f, z * f }; return a; }

	// if( Vector3 == Vector3 )
	BOOL operator == (CONST Vector3& v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
	// if( Vector3 != Vector3 )
	BOOL operator != (CONST Vector3& v) const { return (x != v.x) || (y != v.y) || (z != v.z); }


	inline void Set(float x, float y, float z){ this->x = x, this->y = y, this->z = z; }

} Vector3, *LPVECTOR3;

/**
*@brief		2�񎟌��x�N�g��
*@author	���c�@�Ђ�䂫
*/
typedef struct Vector2 :public float2
{
	/**
	*@brief		�R���X�g���N�^
	*@note		�l��0�ŏ���������
	*/
	Vector2() :float2(){};

	/**
	*@brief			�R���X�g���N�^
	*@param[in]	x	��������x�N�g����x����
	*@param[in]	y	��������x�N�g����y����
	*/
	inline Vector2(float x, float y){ this->x = x, this->y = y; }

	/**
	*@brief			�R���X�g���N�^
	*@param[in]	v	��������x�N�g����xy����
	*/
	inline Vector2(CONST float2& v){ this->x = v.x, this->y = v.y; }

	/**
	*@brief		�x�N�g���̒������擾����
	*@return	�x�N�g���̒���
	*/
	inline float Length(){ return sqrtf(x*x + y*y); }
	
	/**
	*@brief		�x�N�g����2��̒������擾����
	*@return	�x�N�g����2��̒���
	*/
	inline float LengthSp(){ return (x*x + y*y); }

	/**
	*@brief ���K��
	*@note �x�N�g���̐��K�������l�ɕύX
	*/
	void Normalize()
	{
		float length = Length();
		if (length != 0.0f){ x /= length, y /= length; }
	}

	// �I�y���[�^�[
	inline Vector2& operator = (CONST Vector2& v){ x = v.x; y = v.y; return *this; }
	inline Vector2& operator = (CONST float2& v){ x = v.x; y = v.y; return *this; }
	inline Vector2& operator += (CONST Vector2& v){ x += v.x; y += v.y; return *this; }
	inline Vector2& operator -= (CONST Vector2& v){ x -= v.x; y -= v.y; return *this; }
	inline Vector2& operator *= (f32 v){ x *= v; y *= v; return *this; }
	inline Vector2& operator /= (f32 v){ x /= v; y /= v; return *this; }

	inline Vector2 operator + () const { Vector2 ret(x, y); return ret; }
	inline Vector2 operator - () const { Vector2 ret(-x, -y); return ret; }

	inline Vector2 operator + (CONST Vector2& v) const { return Vector2(x + v.x, y + v.y); }
	inline Vector2 operator - (CONST Vector2& v) const { return Vector2(x - v.x, y - v.y); }
	inline Vector2 operator * (f32 v) const { Vector2 ret(x * v, y * v); return ret; }
	inline Vector2 operator / (f32 v) const { Vector2 ret(x / v, y / v); return ret; }

	BOOL operator == (CONST Vector2& v) const { return (x == v.x) && (y == v.y); }
	BOOL operator != (CONST Vector2& v) const { return (x != v.x) || (y != v.y); }


} Vector2, *LPVECTOR2;


// ����
inline float Vector3Dot(Vector& v1, Vector& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

// �O��
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

// �N�H�[�^�j�I��
typedef struct  Quaternion : public D3DXQUATERNION
{
public:
	//------------------------------------------------------
	//	�R���X�g���N�^
	//------------------------------------------------------
	Quaternion(){}
	Quaternion(const D3DXQUATERNION& in) :D3DXQUATERNION(in)
	{}
	Quaternion( float sx, float sy, float sz, float sw ) : D3DXQUATERNION( sx, sy, sz, sw ){}

	//------------------------------------------------------
	//	����
	//------------------------------------------------------
	//	�P�ʃN�H�[�^�j�I������
	void Identity(){ x = y = z = 0; w = 1; }

	//	���K��
	inline void normalize()
	{
		float legnth = getLength();
		if (legnth == .0f) return;
		float invL = 1.0f / legnth;
		(*this) *= invL;
	}

	//------------------------------------------------------
	//	���擾
	//------------------------------------------------------
	inline float getLength() const{ return sqrtf(x*x + y*y + z*z + w*w); }
	void toMatrix(Matrix& m);

	//------------------------------------------------------
	//	�I�y���[�^�[
	//------------------------------------------------------
	inline Quaternion operator + () const { Quaternion ret(x, y, z, w); return ret; }
	inline Quaternion operator - () const { Quaternion ret(-x, -y, -z, -w); return ret; }

	//	VS �N�H�[�^�j�I��
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

	//	VS �l
	inline Quaternion& operator *=(float v){ x *= v; y *= v; z *= v; w *= v; return *this; }
	inline Quaternion& operator /=(float v){ x /= v; y /= v; z /= v; w /= v; return *this; }

	inline Quaternion operator *(float v) const{ return Quaternion(x*v, y*v, z*v, w*v); }
	inline Quaternion operator /(float v) const{ return Quaternion(x / v, y / v, z / v, w / v); }

} Quaternion;

//	���ʐ��`���
Quaternion QuaternionSlerp(Quaternion& q, Quaternion& r, float a);

/*************************************************/
//	�s���x�N�g���Ɋւ���v�Z�̃v���g�^�C�v�錾
/*************************************************/
// �ϊ��s��
void	SetTransformMatrixZXY(Matrix *Mat, float posX, float posY, float posZ, float angleX, float angleY, float angleZ);
void	SetTransformMatrixXYZ(Matrix *Mat, float posX, float posY, float posZ, float angleX, float angleY, float angleZ);
// �r���[�ϊ��\��
void	LookAtLH(Matrix& mat, Vector& Eye, Vector& At, Vector& Up);
// ���e�ϊ��\��
void	PerspectiveLH(Matrix& mat, float fovY, float aspect, float zn, float zf);
void	OlthoLH(Matrix& mat, float w, float h, float zn, float zf);
// �����v�Z
inline float Length(float x1, float y1, float x2, float y2);
inline float Length(Vector3 PosA, Vector3 PosB);
bool Collision_Sphere(Vector3 PosA, float RadiusA, Vector3 PosB, float RadiusB);


/********************************************/
//	�O���錾
/********************************************/
//class tdnRenderState;
//typedef tdnRenderState RS;// (?) �������킩���
class tdnShader;
class tdn2DObj;

/********************************************/
//	tdnSystem
/********************************************/
// �X�N���[�����[�h
#define	SCREEN800x450	0
#define	SCREEN1280x720	1
#define	SCREEN1920x1080	2
#define	SCREEN800x600	3

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);			 // �E�B���h�E�v���V�[�W��
//BOOL InitApp(HINSTANCE hInst, int nCmdShow);												 // �Q�[���N�����̍ŏ��̏�����
//BOOL EndApp();																			 // �Q�[���̈�ԍŌ�̌㏈��

extern	Matrix	matView;		//	�J�����s��
extern	Matrix	matProjection;	//	���e�ϊ��s��

class tdnSystem
{
public:
	// �������E���
	static BOOL InitWindow(HINSTANCE hinst, int nCmdShow, char* AppTitle, DWORD ScreenMode, BOOL isFullScreen);

	static void Release();
private:	
	// ����
	static HINSTANCE hinst;				// �C���X�^���X�n���h��	
	static HWND	Window;					// �E�B���h�E�n���h��
	static BOOL WindowActive;			// �E�B���h�E�̏��
private:
	static BOOL InitD3D();				// D3D�������BPrivate�ֈڍs
	static LPDIRECT3D9	lpD3D;			// DirectX9�ɃA�N�Z�X���邽�߂̃|�C���^			
	static LPDEVICE	Device;				// �r�f�I�J�[�h�ɃA�N�Z�X���邽�߂�3D�f�o�C�X		
	static D3DPRESENT_PARAMETERS d3dpp;	// �f�B�X�v���C�p�����[�^�[
	static ID3DXLine* pLine;			// ���`��
	// �X�N���[���̃T�C�Y
	static RECT	 ScreenSize;			// �X�N���[���̃T�C�Y
	static D3DFORMAT ScreenFormat;		// �X�N���[���̃t�H�[�}�b�g
	static BOOL FullScreen;				// �t���X�N���[���̃t���O
public:
	// (?)�Ȃ��l���ς������܂����f�[�^���O���[�o���ɁH	

	// �p�����[�^�[�擾�֐�
	static inline HINSTANCE GetHinst(){ return hinst; }
	static inline HWND GetWindow(){ return Window; }
	static inline LPDIRECT3D9 GetD3D9(){ return lpD3D; };
	static inline LPDEVICE GetDevice(){ return Device; };
	static inline ID3DXLine* GetLine(){ return pLine; };
	static inline RECT GetScreenSize(){ return ScreenSize; }
	static inline D3DFORMAT GetScreenFormat(){ return ScreenFormat; }
	static inline BOOL GetWindowActive(){ return WindowActive; };

	// �E�B���h�E���b�Z�[�W�����֐�
	//static BOOL Message();

	// �X�N���[���̃T�C�Y���擾
	static RECT GetScreenRect(DWORD mode);
	//	�V�[���J�n�E�I��
	static void BeginScene(){ Device->BeginScene(); }		// �`��J�n!
	static void EndScene()									// �`��I��!
	{
		Device->EndScene();
		if (FAILED(Device->Present(NULL, NULL, NULL, NULL))) Device->Reset(&d3dpp);
	}
	// �E�B���h�E���������Ă��邩���Z�b�g����֐�
	static void SetWindowActive(BOOL active){ WindowActive = active; }

	//	�f�o�b�O�E�B���h�E
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
	// ������
	static void Init()
	{
		SetViewport();
		SetProjection(D3DX_PI / 3.0f, 0.1f, 3000.0f);
	}

	//	���E�N���A
	static void Clear(DWORD color = 0, bool bClearZ = true);
	static void ClearZ();

	//	���_�ݒ�
	static void Set(const Vector& pos, const Vector& target);
	static void Set(float x, float y, float z, float ax, float ay, float az);

	//	���e���ʐݒ�
	static void SetViewport();
	static void SetViewport(int x, int y, int w, int h);

	//	���e�ݒ�
	static void SetProjection(float FovY, float Near, float Far);
	static void SetProjection(float FovY, float Near, float Far, float asp);

	// �s��E�r���[�|�[�g�X�V
	static void Activate();

protected:
	static Vector  Pos, Target;			// �n�_�Ɩڐ�	
	// �r���[�|�[�g
	static D3DVIEWPORT9	Viewport;		// Window��ʂ̂ǂ̗̈�܂�3D��`�悷�邩
	static float FovY;					// ����p
	static float Near, Far;				// ���e�̎�O�̈ʒu�ƈ�ԉ��̈ʒu 
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
	static void	Filter(BOOL bFilter);												//	�T���v���[�X�e�[�g�@TRUE�FLINER(���)�@FLASE:POINT(�����͑���)�@
};

/********************************************/
//				tdnArchive				     
/********************************************/


/**
*	�A�[�J�C�o�[
*	�e��t�@�C�����A�[�J�C�u����N���X
*/
class tdnArchiver
{
public:

	// ��A�[�J�C�u�t�@�C�����쐬����
	bool CreateArchiveFile(const char* pHeaderFilename, const char* pDataFilename);

	// �f�[�^�t�@�C�����A�[�J�C�u�t�@�C���ɒǉ�����
	bool AddData(const char* pDataFileName);

	// �A�[�J�C�u�I������(�_�~�[�w�b�_�[�̒ǉ�)
	bool CloseArchiveFile(const char* pArchiveFilename, const char* pHeaderFilename, const char* pDataFilename);

private:
	// ��ɕ����Ă݂��B�݂邵���Ȃ�����.. (TODO)�N���������ɍ���悤�ɂ��Ă�������
	std::ofstream headerOfs;	// �w�b�_�[��
	std::ofstream dataOfs;		// �f�[�^��
	std::ofstream archiverOfs;	// �ŏI�o��


	// ���ݒǉ������t�@�C���̐�(�w�b�_�[����ID�l�Ƃ��Ďg�p)
	char nameID[64];

	// ���̍ő�
	uint32_t HEAD_MAX;

	// �A�[�J�C�u�t�@�C���̍ő�T�C�Y
	enum : uint32_t{ eMaxArchiveFileSize = 4000000000 };
	// ���ݏ�������ł���A�[�J�C�u�t�@�C���̑��T�C�Y
	uint32_t wroteArchiveFileSize;
};

/**
*	�𓀏����N���X�iArchiver�ƃZ�b�g)
*	�A�[�J�C�u�t�@�C���̉𓀂��s��
*/
// �w�b�_�[���\��
class ArchiveHeaderBlock
{
public:
	// �f�[�^�l�[��ID
	char nameID[64];
	// �J�n�ꏊ�f�[�^�̃T�C�Y
	uint32_t wroteDataFileSize;
	// �f�[�^�u���b�N�̃T�C�Y
	uint32_t dataFileSize;

};

// �X�^�e�B�b�J�[
class tdnUnArchiver
{
public:	
	// �A�[�J�C�u���J��
	static char* OpenArchiveFile(const char* pArchiveFilename, const char* pName);
	// �������̃T�C�Y�擾
	static int GetSize(const char* pArchiveFilename, const char* pName);
	// �A�[�J�C�u���J���{�������T�C�Y���擾
	static char* OpenArchiveFile(const char* pArchiveFilename, const char* pName, int& outMemorySize);
};

// �V���O���g���ɂ���(���R)�����͈�ŏ\���B
//class tdnUnArchiver
//{
//private:
//	static tdnUnArchiver* pInstance;
//	// ����
//	tdnUnArchiver(){};
//	~tdnUnArchiver(){};
//public:
//	static tdnUnArchiver& GetInstance();
//	static void Release();
//
//public:	// �@�\
//	// �A�[�J�C�u���J��
//	char* OpenArchiveFile(const char* pArchiveFilename, const char* pName);
//	// �������̃T�C�Y�擾
//	int GetSize(const char* pArchiveFilename, const char* pName);
//	// �A�[�J�C�u���J���{�������T�C�Y���擾
//	char* OpenArchiveFile(const char* pArchiveFilename, const char* pName, int& outMemorySize);
//
//};
//#define UNArchive	(tdnUnArchiver::GetInstance())


/********************************************/
//				tdnTexture				     
/********************************************/
class tdnTexture
{
private:
	static const int MAX_TEXTURE = 512;

	struct TEXINFO {
		char		filename[64];	//	�t�@�C���p�X
		int			UseCount;		//	���̃e�N�X�`���g�p���Ă���J�E���g
		Texture2D*	lpTexture;		//	�e�N�X�`��	
		D3DXIMAGE_INFO info;		//  (�ǉ�)�T�C�Y�̏��擾
	};
	static struct TEXINFO TexInfo[MAX_TEXTURE];

public:
	//	������
	static void Initialize();
	//	�ǂݍ��݁E���
	static Texture2D* Load(const char* filename);
	static Texture2D* LoadMemory(const char* filename, const char* pArchiver);

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
	// �������E���
	tdnShader(char* filename);
	~tdnShader();

	// �V�F�[�_�[���p�J�n�E�I��
	inline UINT Begin(char* name)		// �V�F�[�_�J�n
	{
		UINT pass;
		// �V�F�[�_�[�̓K�p
		pShader->SetTechnique(name);	// �e�N�j�b�N����ݒ肷��
		pShader->Begin(&pass, 0);	
		return pass;
	}
	inline void End(){ pShader->End(); }// �V�F�[�_�I��

	/*	�p�X�̊J�n�E�I��  */	
	inline void BeginPass(int pass){ pShader->BeginPass(pass); }	// �A�N�e�B�u�ȃe�N�j�b�N���Ńp�X���J�n���܂��B
	inline void EndPass(){ pShader->EndPass(); }					// �p�X�I��
	inline void CommitChanges(){ pShader->CommitChanges(); }		// BeginPass�`EndPass���ŃZ�b�^�[��ʂ��Ēl��ύX�����ۂɌĂяo���K�v������֐��ł�

	// �p�����[�^�[�ݒ�
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
	LPD3DXEFFECT pShader;	// �G�t�F�N�g�t�@�C���ւ̃A�N�Z�X�|�C���^

	D3DXHANDLE	hmWVP;		// �ˉe�ϊ��s��@�p�����[�^�[���Q�Ƃ��邽�߂̌����I�Ȏ�i��񋟂��܂��B
	D3DXHANDLE  htexDecale;	// �e�N�X�`��

};

/********************************************/
//				tdn2DObj				     
/********************************************/
//	�����_�[�^�[�Q�b�g�̃t�H�[�}�b�g
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
	tdn2DObj(const char* fileName);							// �t�@�C������摜�ǂݍ���
	tdn2DObj(const char* IDName, const char* pArchiveName);	// �������[����摜�ǂݍ���
	tdn2DObj(UINT width, UINT height, FMT2D fmtFlag);		// �����_�[�^�[�Q�b�g�쐬

	~tdn2DObj();											// �摜or�����_�[�^�[�Q�b�g���

	// ���擾
	void RenderTarget(int index = 0);						// �����_�[�^�[�Q�b�g�ݒ�
	inline Surface*	GetSurface(){ return lpSurface; };		// ��
	inline Texture2D*	GetTexture(){ return lpTexture; };	// �e�N�X�`��

	// �`��
	void Render(int x, int y, u32 dwFlags = RS::COPY);
	void Render(int x, int y, tdnShader* shader, char* name);// shader�K�p
	void Render(int x, int y, int w, int h, int tx, int ty, int tw, int th, u32 dwFlags = RS::COPY);
	void Render(int x, int y, int w, int h, int tx, int ty, int tw, int th, tdnShader* shader, char* name);

	// 3D�`��
	void Render3D(float x, float y, float z, u32 dwFlags = RS::COPY);
	void Render3D(Vector3 pos, u32 dwFlags = RS::COPY);
	void Render3D(float x, float y, float z, int w, int h, int tx, int ty, int tw, int th, u32 dwFlags = RS::COPY);
	void Render3D(Vector3 pos, int w, int h, int tx, int ty, int tw, int th, u32 dwFlags = RS::COPY);

	///	���X�V
	void SetScale(float scale);
	void SetAngle(float angle);
	void SetARGB(BYTE A, BYTE R, BYTE G, BYTE B);
	void SetARGB(int A, int R, int G, int B);
	void SetARGB(DWORD ARGB);
	void SetTurnOver(bool turnFlag);
	void SetShiftCenter(bool ShiftFlag);
	void SetCenter(float x, float y);

	// ���擾
	inline float GetScale(){ return scale; }
	inline float GetAngle(){ return angle; }
	inline float GetCenterX(){ return centerX; }
	inline float GetCenterY(){ return centerY; }
	inline bool GetTurnOver(){ return isTurnOver; };
	inline bool GetShiftCenter(){ return isShiftCenter; };
private:

	// unsigned int�̗��R��GetLevelDesc����󂯎����Ȃǂ�UINT������
	UINT		m_width;				// ��
	UINT		m_height;				// ����

	// �e�N�X�`���Ɖ摜���
	Surface*	lpSurface;			// ��
	Texture2D*	lpTexture;			// �e�N�X�`��

	// �X�e�[�^�X
	float scale, angle;
	DWORD color;
	float centerX, centerY;
	bool isTurnOver;
	bool isShiftCenter;				//xy���摜�̒��S��

};



/********************************************/
//				tdnPolygon	
/********************************************/

//************************************************************
//	��D3DFVF�g�ݍ��킹���_
//	�I���W�i��FVF�}�N���Ƃ��̐ݒ�ɂ������\���̂𑗂邱�Ƃ�
//	���R�Ȓ��_�f�[�^�𑗂��B
//***********************************************************

//	�Q�c�p���_�i���C�e�B���O���g�����X�t�H�[���ς݁j
#define D3DFVF_TLVERTEX		( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )//�@��D3DFVF_XYZRHW(sx, sy, sz, rhw)�� D3DFVF_DIFFUSE(color)��D3DFVF_TEX1(uv)�̑g�ݍ��킹
typedef struct tagTLVERTEX {
	float	sx, sy, sz;
	float	rhw;
	COLOR	color;
	float	tu, tv;
} TLVERTEX, *LPTLVERTEX;

//	�Q�c�p���_�i���C�e�B���O���g�����X�t�H�[���ς݁A�F�Ȃ��j
#define D3DFVF_TLVERTEX2	( D3DFVF_XYZRHW | D3DFVF_TEX1 )
typedef struct tagTLVERTEX2 {
	float	sx, sy, sz;
	float	rhw;
	float	tu, tv;
} TLVERTEX2, *LPTLVERTEX2;

//	�R�c�p���_(�@���Ȃ��j
#define D3DFVF_VERTEX		( D3DFVF_XYZ | D3DFVF_TEX1 )
typedef struct tagVERTEX {
	float	x, y, z;
	float	tu, tv;
} VERTEX, *LPVERTEX;

//	�R�c�p���_(���C�e�B���O�ς݁j
#define D3DFVF_LVERTEX		( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) // 3�̃I�u�W�F�N�g�`���}�N�������킹��
typedef struct tagLVERTEX {
	float	x, y, z;	// ���_���W
	COLOR	color;		// ���_�̐F
	float	tu, tv;		// �e�N�X�`���̍��W
} LVERTEX, *LPLVERTEX;

//	�R�c���b�V���p���_
#define D3DFVF_MESHVERTEX		( D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1 )
typedef struct tagMESHVERTEX {
	float	x, y, z;
	float	nx, ny, nz;
	float	tu, tv;
} MESHVERTEX, *LPMESHVERTEX;

//	�R�c�p���_(���C�e�B���O�ς݁j
#define D3DFVF_MESHVERTEX2		( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
typedef struct tagLNVERTEX {
	float	x, y, z;
	float	nx, ny, nz;
	COLOR	color;
	float	tu, tv;
} MESHVERTEX2, *LPMESHVERTEX2;

// ���C���p�̒��_
struct VECTOR_LINE
{
	float x, y, z; // ���_ 
	DWORD color;
};

//	�Q�c�I�u�W�F�N�g
//typedef tdn2DObj *LPtdn2DObj;

class tdnPolygon
{
public:
	// 3D
	static void Render3D(LPLVERTEX lpVertex, int Num, tdn2DObj* lpObj, u32 dwFlags);										// 3D�Œ�
	static void Render3D(LPLVERTEX lpVertex, int Num, tdn2DObj* lpObj, u32 dwFlags, D3DXMATRIX mat);// �ǉ�
	static void Render3D(LPLVERTEX lpVertex, int Num, tdn2DObj* lpObj, tdnShader* shader, char* name);					// 3D�V�F�[�_
	// 2D
	static void Render2D(LPTLVERTEX lpVertex, int Num, tdn2DObj* lpObj, u32 dwFlags);										// 2D�Œ�
	static void Render2D(LPTLVERTEX lpVertex, int Num, tdn2DObj* lpObj, tdnShader* shader, char* name);					// 2D�V�F�[�_	
	// ��`
	static void Rect(int DstX, int DstY, int DstW, int DstH, u32 dwFlags, COLOR color, float z = .0f);
	static void Rect(int DstX, int DstY, int DstW, int DstH, tdnShader* shader, char* name, COLOR color, float z = .0f);
	// ��
	static void DrawLine(float x1, float y1, float x2, float y2, DWORD color = 0xFFFFFFFF, float size = 1.0f);
	static void DrawLine3D(Vector3 pos1, Vector3 pos2, DWORD color = 0xFFFFFFFF, float size = 1.0f, u32 dwFlag = RS::COPY);

private:

};


// 3D�I�u�W�F�N�g
class tdnMesh
{
public:
	tdnMesh();
	~tdnMesh();

	/********/
	/* �쐬 */
	/********/

	struct CreateData
	{
		unsigned int      numVertexes;  // ���_�̐�
		unsigned int      vertexSize;   // ���_�\���̂̃o�C�g��
		void              *vertexArray; // ���_���i���_���j�z��

		unsigned int      numIndexes;   // �C���f�b�N�X�̐�
		DWORD             *indexArray;  // �C���f�b�N�X�̔z��
		
		unsigned int      numStream;    // �X�g���[���\���̂̐�
		unsigned int      streamSize;   // �X�g���[���\���̂̃o�C�g��
		void              *streamArray; // ���_���i�C���f�b�N�X���j�̔z��

		D3DVERTEXELEMENT9 *decl;        // �V�F�[�_�[�ɑ��钸�_�\���̂̒�`
	};
	bool Create( const CreateData &data );
	bool CreateVertex(
		unsigned int numVertex,    // ���_��
		unsigned int vertexSize,   // ���_�\���̂̃o�C�g��
		void *vertexArray );       // ���_�z��
	bool CreateIndexes(
		unsigned int numIndexes,   // �C���f�b�N�X�̐�
		const DWORD *indexArray ); // �C���f�b�N�X�z��
	bool CreateStream( unsigned int numData, unsigned int dataSize, void *dataArray );
	bool CreateDeclaration(
		unsigned int declArySize,  // ���_�\���̂̃o�C�g��
		D3DVERTEXELEMENT9 *decl ); // �V�F�[�_�[��ł̒��_�\���̂̐錾

	// xy���ʂɐ��O�p�`�쐬
	bool CreateTriangle(
		float radius,    // �O�ډ~�̔��a
		DWORD color ); 
	// xy���ʂɒ����`�쐬
	bool CreateRectangle(
		float width,
		float height,
		DWORD color );
	// ���l�ʑ̍쐬
	bool CreateTriangular(
		float radius, // �O�ډ~�̔��a
		DWORD color );
	// �����̍쐬
	bool CreateCube(
		float width,
		float height,
		float depth,
		DWORD color,
		Vector3 *posList = nullptr,
		unsigned int numPos = 0 );

	/************/
	/* �ǂݍ��� */
	/************/

	bool LoadMqo( char *filename );

	/********/
	/* �X�V */
	/********/

	// pos, scale, rot ����worldMatrix�쐬
	void UpdateWorldMatrix();

	/********/
	/* �`�� */
	/********/

	void Render( tdnShader *shader, char *technique );

	/*********************/
	/* �Z�b�^�[ �Q�b�^�[ */
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
	IDirect3DVertexDeclaration9* decl;         // ���_�f�R���[�V�����iFVF�j
	unsigned int                 declSize;     // ���_�\���̂̃o�C�g��

	IDirect3DVertexBuffer9*      vertexBuffer;
	unsigned int                 numVertexes;

	IDirect3DIndexBuffer9*       indexBuffer;
	unsigned int                 numIndexes;

	IDirect3DVertexBuffer9*      streamBuffer; // �I�u�W�F�N�g���̏��
	unsigned int                 streamSize;   // streamBuffer �̈�̃f�[�^�̃o�C�g��
	unsigned int                 numStream;   // streamBuffer �̌�

	unsigned int                 numFaces;     // �O�p�|���S����

	Vector3    pos;
	Vector3    scale;
	Quaternion rot;
	Matrix     worldMatrix;
	public:
	Texture2D *texture;
};

//*****************************************************************************************************************************
//		tdnInput
//*****************************************************************************************************************************
//-----------------------------------------------------------------------------
//		���͊֘A�̒萔
//-----------------------------------------------------------------------------
namespace tdnInputEnum
{
	static const int INPUT_DEVICE_MAX = 4;
	static const int STICK_WIDTH = 1000;
	static const int DEFAULT_KEY_CONFIG = -1;
	static const float MIN_MOVE_STICK = .35f;
	static const int NUM_ID_GROUPS = 5;
	static const LPSTR ID_GOURPS[NUM_ID_GROUPS] =
	{
		"DEFAULT", "XBOX", "PS3", "GAMEPAD", "NORI_GAMEPAD"
	};
}


//-----------------------------------------------------------------------------
//		���̓f�o�C�X�Ǘ�
//-----------------------------------------------------------------------------
class tdnInputManager
{
private:
	static LPDIRECTINPUT8 lpDI;
	static int num_device;
	static DIDEVICEINSTANCE	device_instances[tdnInputEnum::INPUT_DEVICE_MAX];
	static char groupID[tdnInputEnum::INPUT_DEVICE_MAX][16];

	static BOOL CALLBACK EnumDeviceCallback(const DIDEVICEINSTANCE* pdidi, VOID* pContext);
	static BOOL CALLBACK EnumAxes(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

public:
	static void Initialize();
	static void Release()
	{
		if (lpDI)
		{
			delete lpDI;
			lpDI = nullptr;
		}
	}
	static LPDIRECTINPUTDEVICE8 GetDevice(int no);
	static LPSTR GetGroupID(int no){ return groupID[no]; }
};

enum KEYCODE
{
	KEY_UP = 0,
	KEY_DOWN = 1,
	KEY_LEFT = 2,
	KEY_RIGHT = 3,

	KEY_A = 4,
	KEY_B = 5,
	KEY_C = 6,
	KEY_D = 7,
	KEY_X = 6,
	KEY_Y = 7,

	KEY_L = 8,
	KEY_L1 = 8,
	KEY_L2 = 10,
	KEY_L3 = 12,

	KEY_R = 9,
	KEY_R1 = 9,
	KEY_R2 = 11,
	KEY_R3 = 13,

	KEY_START = 14,
	KEY_SELECT = 15,

	KEY_ENTER = 14,
	KEY_SPACE = 15,

	AXIS_X = 0,
	AXIS_Y = 1,
	AXIS_Z = 2,
	AXIS_RX = 3,
	AXIS_RY = 4,
	AXIS_RZ = 5
};

typedef struct tagKEYSET
{
	u8	up, down, left, right;
	u8	A, B, X, Y;
	u8	L1, L2, L3;
	u8	R1, R2, R3;
	u8	START, SELECT;
} KEYSET, *LPKEYSET;

typedef struct tagPADSET
{
	u8	lx, ly, rx, ry;
	u8	A, B, X, Y;
	u8	L1, L2, L3;
	u8	R1, R2, R3;
	u8	START, SELECT;
} PADSET, *LPPADSET;

class tdnInputDevice
{
private:
	LPDIRECTINPUTDEVICE8 lpDevice;
	LPDIRECTINPUTEFFECT	 pEffect;

	// �f�t�H���g�̃L�[�z�u
	static const int default_key_map[20];
	static const int default_joy_map[20];

	// ���͂ɉ������l���i�[�����(==3�Ƃ���3�̒l�������Ă�)
	u8	key_info[20], joy_info[20];

	int key_map[20];
	int joy_map[20];
	int	pad_axisX, pad_axisY;
	int	pad_axisX2, pad_axisY2;
public:
	tdnInputDevice(int n);
	~tdnInputDevice();

	void Update();
	void PadAsign(const PADSET &padset);
	int tdnInputDevice::Get(KEYCODE key){ return key_info[key]; }
	int tdnInputDevice::GetAxisX(){ return (pad_axisX*pad_axisX > tdnInputEnum::MIN_MOVE_STICK*(tdnInputEnum::STICK_WIDTH*tdnInputEnum::STICK_WIDTH)) ? pad_axisX : 0; }
	int tdnInputDevice::GetAxisY(){ return (pad_axisY*pad_axisY > tdnInputEnum::MIN_MOVE_STICK*(tdnInputEnum::STICK_WIDTH*tdnInputEnum::STICK_WIDTH)) ? pad_axisY : 0; }
	int tdnInputDevice::GetAxisX2(){ return (pad_axisX2*pad_axisX2 > tdnInputEnum::MIN_MOVE_STICK*(tdnInputEnum::STICK_WIDTH*tdnInputEnum::STICK_WIDTH)) ? pad_axisX2 : 0; }
	int tdnInputDevice::GetAxisY2(){ return (pad_axisX2*pad_axisY2 > tdnInputEnum::MIN_MOVE_STICK*(tdnInputEnum::STICK_WIDTH*tdnInputEnum::STICK_WIDTH)) ? pad_axisY2 : 0; }
};

class tdnInput
{
private:
	static tdnInputDevice *device[tdnInputEnum::INPUT_DEVICE_MAX];

public:
	static void Initialize();
	static void Release();
	static void Update();
	static void PadAsign(LPSTR config, int no = 0);

	static int KeyGet(KEYCODE key, int no = 0){ return device[no]->Get(key); }
	static int GetAxisX(int no=0) { return device[no]->GetAxisX(); }
	static int GetAxisY(int no=0) { return device[no]->GetAxisY(); }
	static int GetAxisX2(int no=0){ return device[no]->GetAxisX2(); }
	static int GetAxisY2(int no=0){ return device[no]->GetAxisY2(); }
	static void GetAxisXYf(float *outX, float *outY, int no = 0);
	static void GetAxisXY2f(float *outX, float *outY, int no = 0);
};

#define KEY(x,n) ( tdnInput::KeyGet(x,n) )
#define KEY_TRG(x,n) ( tdnInput::KeyGet(x,n)==3 )

//-----------------------------------------------------------------------------
//		OKB
//-----------------------------------------------------------------------------
enum VK_CODE
{
	//=============================
	// ��{�L�[�{�[�h
	KB_A = 0x41,
	KB_B = 0x42,
	KB_C = 0x43,
	KB_D = 0x44,
	KB_E = 0x45,
	KB_F = 0x46,
	KB_G = 0x47,
	KB_H = 0x48,
	KB_I = 0x49,
	KB_J = 0x4A,
	KB_K = 0x4B,
	KB_L = 0x4C,
	KB_M = 0x4D,
	KB_N = 0x4E,
	KB_O = 0x4F,
	KB_P = 0x50,
	KB_Q = 0x51,
	KB_R = 0x52,
	KB_S = 0x53,
	KB_T = 0x54,
	KB_U = 0x55,
	KB_V = 0x56,
	KB_W = 0x57,
	KB_X = 0x58,
	KB_Y = 0x59,
	KB_Z = 0x5A,
	KB_ENTER = 0x0D,
	KB_SPACE = 0x20,
	KB_LEFT = 0x25,	/* �� */
	KB_UP = 0x26,	/* �� */
	KB_RIGHT = 0x27,	/* �� */
	KB_DOWN = 0x28,	/* �� */

	KB_0 = 0x30,
	KB_1 = 0x31,
	KB_2 = 0x32,
	KB_3 = 0x33,
	KB_4 = 0x34,
	KB_5 = 0x35,
	KB_6 = 0x36,
	KB_7 = 0x37,
	KB_8 = 0x38,
	KB_9 = 0x39,

	KB_COLON = 0xBA,	/* : */
	KB_SEMICORON = 0xBB,	/* ; */
	KB_COMMA = 0xBC,	/* , */
	KB_HYPHEN = 0xBD,	/* - */
	KB_DOT = 0xBE,	/* . */
	KB_SLASH = 0xBF,	/* / */
	KB_AT_SIGN = 0xC0,	/* @ */
	KB_SQUARE_L = 0xDB,	/* [ */
	KB_YEN = 0xDC,	/* \ */
	KB_SQUARE_R = 0xDD,	/* ] */
	KB_CARET = 0xDE,	/* ^ */
	KB_UNDER_BAR = 0xE2,	/* _ */


	//=============================
	// �e���L�[�֘A
	KB_NUMPAD0 = 0x60,	/* 0 */
	KB_NUMPAD1 = 0x61,	/* 1 */
	KB_NUMPAD2 = 0x62,	/* 2 */
	KB_NUMPAD3 = 0x63,	/* 3 */
	KB_NUMPAD4 = 0x64,	/* 4 */
	KB_NUMPAD5 = 0x65,	/* 5 */
	KB_NUMPAD6 = 0x66,	/* 6 */
	KB_NUMPAD7 = 0x67,	/* 7 */
	KB_NUMPAD8 = 0x68,	/* 8 */
	KB_NUMPAD9 = 0x69,	/* 9 */
	KB_MULT = 0x6A,	/* * */
	KB_ADD = 0x6B,	/* + */
	KB_SUBTRACT = 0x6D,	/* - */
	KB_DECIMAL = 0x6E,	/* . */
	KB_DIVIDE = 0x6F,	/* / */



	//=============================
	// ���܂�g�����Ƃ͂Ȃ������c
	KB_BACK = 0x08,
	KB_TAB = 0x09,
	KB_CLEAR = 0x0c,

	KB_SHIFT = 0x10,
	KB_CTRL = 0x11,
	KB_ALT = 0x12,
	KB_PAUSE = 0x13,
	KB_CAPITAL = 0x14,	/* Shift + CapsLock */
	KB_ESC = 0x1B,
	KB_NON_CONV = 0x1D,	/* ���ϊ� */

	KB_PGUP = 0x21,
	KB_PGDN = 0x22,
	KB_END = 0x23,
	KB_HOME = 0x24,
	KB_PRT_SC = 0x2C,
	KB_INSERT = 0x2D,
	KB_DELETE = 0x2E,

	//=============================
	// �}�E�X(�L�[�ł͂Ȃ���)
	MOUSE_LEFT = 0x01,
	MOUSE_RIGHT = 0x02,
	MOUSE_CENTAR = 0x04		/* �z�C�[���N���b�N(���邮��ł͂Ȃ�) */

};

class OwatasoKeyBoard
{
public:
	OwatasoKeyBoard();

	// �L�[�{�[�h�̏�Ԃ��i�[
	BYTE info[256];

	// �L�[�{�[�h�̉����Ă鎞��
	UINT on_frame[256];

	void Update();

	BYTE AnyTRG();
};


//====================================
//		�������Ɖ��
void OKB_Init();
void OKB_Release();
//====================================
//		�L�[�{�[�h���X�V
void OKB_Update();

// �Ή����Ă���L�[��������Ă���t���[������Ԃ�( �������ςȂ�����ɂǂ��� )
UINT KeyBoard(BYTE KeyCode);

// �L�[�̃t���[��������frame�Ɠ����ɂȂ�����true�A����ȊO����false( �������u�Ԕ���ɂǂ��� )
bool KeyBoardTRG(BYTE KeyCode, UINT frame = 1);

// �����L�[�������ꂽ�Ƃ��A1�t���[���������̃L�[�̃L�[�R�[�h���Ԃ��Ă���( �^�C�s���O�Q�[���Ƃ��Ŏg������ )
BYTE KeyBoardAnyTRG();



//*****************************************************************************
//		tdnAudio
//*****************************************************************************

#include "ogg/vorbisfile.h"

#define	STR_NORMAL	0
#define	STR_FADEIN	1
#define	STR_FADEOUT	2

#define	TYPE_WAV	0
#define	TYPE_OGG	1

enum class DXA_FX
{
	DXAFX_OFF = 0,		// �G�t�F�N�g�I�t
	DXAFX_CHORUS = 1 << 0,	// �R�[���X
	DXAFX_COMPRESSOR = 1 << 1,	// �R���v���b�T
	DXAFX_DISTORTION = 1 << 2,	// �f�B�X�g�\�V����
	DXAFX_ECHO = 1 << 3,	// �G�R�[
	DXAFX_FLANGER = 1 << 4,	// �t�����W
	DXAFX_GARGLE = 1 << 5,	// �K�[�O��
	DXAFX_ENVREVERB = 1 << 6,	// �����o�[�u
	DXAFX_PARAMEQ = 1 << 7,	// �p�����g���b�N�C�R���C�U
	DXAFX_WAVESREVERB = 1 << 8,	// �~���[�W�b�N���o�[�u(16bit�̃I�[�f�B�I�t�H�[�}�b�g�̂�)
	DXAFX_MAX = 1 << 9
};

class tdnSoundBuffer
{
protected:
	LPDIRECTSOUNDBUFFER8	lpBuf;
	LPDIRECTSOUND3DBUFFER8	lpBuf3D;
	LPBYTE LoadFile(LPSTR fname, LPDWORD size, LPWAVEFORMATEX wfx);
	LPBYTE LoadWAV(LPSTR fname, LPDWORD size, LPWAVEFORMATEX wfx);
	LPBYTE LoadOWD(LPSTR fname, LPDWORD size, LPWAVEFORMATEX wfx);	// Owataso Wave Data

	DWORD PlayCursor;
	DWORD BufferSize;
	WAVEFORMATEX format;

	// Load����Ƃ��Ɏg���ϐ�(���[�J���˃����o�ϐ�)
	WAVEFORMATEX	wfx;
	LPBYTE			lpWBuf;
	DWORD			size;

	char			wav_file_path[128];	/*	WAVE�t�@�C���ւ̃p�X*/
	bool			loop_flag;

	static const int READBYTE;

public:
	tdnSoundBuffer(LPDIRECTSOUND8 lpDS, char* filename, bool b3D);
	void Initialize(LPDIRECTSOUND8 lpDS, unsigned char* data, DWORD size, LPWAVEFORMATEX fmt, bool b3D);
	tdnSoundBuffer(){}
	~tdnSoundBuffer();

	// �����̂𕡐��ǂݍ��݂����Ƃ��Ɏg��
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
	//	�T�E���h�G�t�F�N�g
	//------------------------------------------------------
	void SetFX(DXA_FX flag);

	//------------------------------------------------------
	//	3D�֌W
	//------------------------------------------------------
	void SetDist(float max_dist = DS3D_DEFAULTMAXDISTANCE, float min_dist = DS3D_DEFAULTMINDISTANCE);	// �ő咴����Ƃ����������Ȃ��A�ŏ��͕��ʂ�1�Ƃ��ł����Ǝv��
	void SetPos(const Vector3 &pos);																	// ��������������W
	void SetFront(const Vector3 &front);																// ���̌���
	void SetRange(int degreeIn = DS3D_DEFAULTCONEANGLE);												// ���͈͓̔��p�x�̐ݒ�(�x)
	void SetOutRange_volume(int out_vol = DS3D_DEFAULTCONEOUTSIDEVOLUME);								// �p�x�͈͊O�̏ꍇ�̉�(-10000(�ŏ�)�`0(�ő�))
	void SetMove(const Vector3 &move);																	// ���ʂ͓����Ȃ����ǃh�b�v���[���ʂŎg��
	void SetAll3D(float max_dist, float min_dist, const Vector3 &pos, const Vector3 &front, int degreeIn, int out_vol, const Vector3 &move);
};

class tdnStreamSound
{
private:
	static const int STRSECOND = 1;
	int		rate;
	LPDIRECTSOUNDBUFFER	lpStream;		// �X�g���[���p�񎟃o�b�t�@
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
//		�T�E���h�Ǘ��̊��(�p���Ŏg�������ŁA�Q�[�����l�͎g�p���Ȃ�)
//
//*****************************************************************************
class tdnSoundBase
{
protected:
	static const int WavNum = 128;	// �o�b�t�@�ő�l

	HWND	hWndWAV;

	LPDIRECTSOUND8			lpDS;		// DirectSound�I�u�W�F�N�g
	LPDIRECTSOUNDBUFFER	lpPrimary;		// �ꎟ�o�b�t�@

	LPDIRECTSOUND3DLISTENER8 lp3DListener;	// 3D�T�E���h��ŁA�����ƕ�������l�Ƃ̊֌W�ł����ƕ�������l�̏��

public:
	//------------------------------------------------------
	//	�������E���
	//------------------------------------------------------
	tdnSoundBase();
	virtual ~tdnSoundBase();

	//------------------------------------------------------
	// ��3D�T�E���h���� ���X�i�[���ݒ�
	//------------------------------------------------------
	void SetListenerPos(const Vector3 &pos);
	void SetListenerOrientation(const Vector3 &fornt, const Vector3 &up);
	void SetListenerMove(const Vector3 &move);
	void SetListenerAll(const Vector3 &pos, const Vector3 &fornt, const Vector3 &up, const Vector3 &velocity);
	void UpdateListener();	// 3D�T�E���h���g�p����ꍇ�A���񂱂���Ăяo���Ă�������
};


//*****************************************************************************
//
//		�T�E���h�Ǘ�(SE�p)
//
//*****************************************************************************

class tdnSoundSE : public tdnSoundBase
{
private:
	struct SEData
	{
		bool b3D;					// 3D�t���O
		tdnSoundBuffer* buffer;	// �T�E���h�o�b�t�@
	};
	std::vector<SEData*> data[WavNum];

public:
	tdnSoundSE();
	~tdnSoundSE();

	//------------------------------------------------------------------------------------------------------------------------------------------------------
	//	�����cID:�ԍ��A num_of_play_simultaneously:�����Đ��\��(����܂葽���ƃ������H���̂łقǂقǂɁB5�`10�O��)�A�@�t�@�C�����A�@3D�T�E���h�t���O
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	void Set(int ID, int num_of_play_simultaneously, char* filename, bool b3D = false);

	/* �Đ� */
	int Play(int ID, bool loop = false);

	/* ��~:no�ɂ�Play�ŕԂ��Ă����l�������œ���� */
	void Stop(int ID, int no);
	void AllStop();

	/* �e�T�E���h�p�����[�^�ݒ�E�擾�֐� */
	void	SetVolume(int ID, int volume);
	void	SetVolume(int ID, float volume);	// 0�`1
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
	// ���ȉ��̊֐����ĂԂɂ�Set�̈�����b3D��true�ɂ���K�v������܂�
	//---------------------------------------------------------------
	int Play(int ID, const Vector3 &pos, const Vector3 &front = Vector3(0, 0, -1), const Vector3 &move = Vector3(0, 0, 0), bool loop = false);// �������ݒ肵�Đ�
	void SetDist(int ID, int no, float max_dist = DS3D_DEFAULTMAXDISTANCE, float min_dist = DS3D_DEFAULTMINDISTANCE);				// �ő咴����Ƃ����������Ȃ��A�ŏ��͕��ʂ�0�Ƃ��ł����Ǝv��
	void SetPos(int ID, int no, const Vector3 &pos);																				// ��������������W
	void SetFront(int ID, int no, const Vector3 &front);																			// ���̌���
	void SetRange(int ID, int no, int degreeIn = DS3D_DEFAULTCONEANGLE);															// ���͈͓̔��p�x�̐ݒ�(�x)
	void SetOutRange_volume(int ID, int no, int out_vol = DS3D_DEFAULTCONEOUTSIDEVOLUME);											// �p�x�͈͊O�̏ꍇ�̉�(-10000(�ŏ�)�`0(�ő�))
	void SetMove(int ID, int no, const Vector3 &move);																				// ���ʂ͓����Ȃ����ǃh�b�v���[���ʂŎg��
	void SetAll3D(int ID, int no, float max_dist, float min_dist, const Vector3 &pos, const Vector3 &front, int degreeIn, int out_vol, const Vector3 &move);
};



//*****************************************************************************
//
//		�T�E���h�Ǘ�(BGM�p)	�����̃N���X�̂݁A���t���[��Update���Ăяo���Ă�������
//
//*****************************************************************************

class tdnSoundBGM : public tdnSoundBase
{
private:
	static const int MinVolume = -2500;	// ���ʍŏ��l

	enum class MODE
	{
		NONE, FADE_IN, FADE_OUT, MAX
	};
	void None(int no);
	void In(int no);
	void Out(int no);
	void(tdnSoundBGM::*Fade_funk[(int)MODE::MAX])(int);

	struct tagBGMData
	{
		bool b3D;			// 3D�T�E���h�t���O
		MODE fade_mode;		// �t�F�[�h�C�����A�E�g���������Ȃ���
		float volume;		// ����(0�`1)
		float fade_speed;		// �t�F�[�h���x
		tdnSoundBuffer* buffer;
	};
	std::vector<tagBGMData*> data;

public:
	tdnSoundBGM();
	~tdnSoundBGM();

	//////////////////////////////////////////////
	/* �����t���[��Update���Ăяo���Ă��������I */
	void Update();
	//////////////////////////////////////////////

	//------------------------------------------------------------------------------------------------------------------------------------------------------
	//	�����cID:�ԍ��A�t�@�C�����A3D�T�E���h�t���O(BGM�̏ꍇ�A�g���@��͂قڂȂ�)
	//------------------------------------------------------------------------------------------------------------------------------------------------------
	void Set(int ID, char* filename, bool b3D = false);
	void Set(int ID, unsigned char *data, unsigned long size, LPWAVEFORMATEX wfx, bool b3D = false);

	/* �Đ� */
	void Play(int ID, bool loop = true, DWORD cursor = 0);

	/* ��~ */
	void Stop(int ID);
	void AllStop();
	void Pause(int ID);

	/* �t�F�[�h�֌W(BGM��SE�ŕ������v����1��) */
	void FadeOut(int ID, float fade_speed);	// fade_speed��0�`1�͈̔́B0.01�Ƃ��̒l�ɂȂ�
	void FadeIn(int ID, float fade_speed, bool loop = true, DWORD cursor = 0);

	enum class CROSS_FADE_TYPE
	{
		NORMAL,			// ���ʂɍŏ�����Đ�
		END_OF_ETERNITY	// EoE�`��(�C��������BGM���A�E�g������BGM�Ɠ����J�[�\������Đ�������)
	};
	void CrossFade(int inID, int outID, float fade_speed, CROSS_FADE_TYPE type = CROSS_FADE_TYPE::NORMAL, bool loop = true);
	void CrossFade(int inID, int outID, float in_speed, float out_speed, CROSS_FADE_TYPE type, bool loop);

	/* �e�T�E���h�p�����[�^�ݒ�E�擾�֐� */
	void	SetVolume(int ID, int volume);
	void	SetVolume(int ID, float volume);	// 0�`1
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
	// ���ȉ��̊֐����ĂԂɂ�Set�̈�����b3D��true�ɂ���K�v������܂�
	//---------------------------------------------------------------
	void Play(int ID, const Vector3 &pos, const Vector3 &front = Vector3(0, 0, -1), const Vector3 &move = Vector3(0, 0, 0), bool loop = true);// �������ݒ肵�Đ�
	void SetDist(int ID, int no, float max_dist = DS3D_DEFAULTMAXDISTANCE, float min_dist = DS3D_DEFAULTMINDISTANCE);				// �ő咴����Ƃ����������Ȃ��A�ŏ��͕��ʂ�0�Ƃ��ł����Ǝv��
	void SetPos(int ID, int no, const Vector3 &pos);																				// ��������������W
	void SetFront(int ID, int no, const Vector3 &front);																			// ���̌���
	void SetRange(int ID, int no, int degreeIn = DS3D_DEFAULTCONEANGLE);															// ���͈͓̔��p�x�̐ݒ�(�x)
	void SetOutRange_volume(int ID, int no, int out_vol = DS3D_DEFAULTCONEOUTSIDEVOLUME);											// �p�x�͈͊O�̏ꍇ�̉�(-10000(�ŏ�)�`0(�ő�))
	void SetMove(int ID, int no, const Vector3 &move);																				// ���ʂ͓����Ȃ����ǃh�b�v���[���ʂŎg��
	void SetAll3D(int ID, int no, float max_dist, float min_dist, const Vector3 &pos, const Vector3 &front, int degreeIn, int out_vol, const Vector3 &move);
};


// ��Ԃ�݂���
LPBYTE LoadWavData(LPSTR filename, LPDWORD size, LPWAVEFORMATEX wfx);


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
//	��������̓G���[�`�F�b�N�̂��߂ɒǉ�
/*****************************************/

#ifndef __IT_DEBUG_H__
#define __IT_DEBUG_H__

#define _IT_DEBUG

#ifdef _IT_DEBUG

//*****************************************************************
//new�I�[�o�[���[�h
//*****************************************************************

#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <cassert>
#include <crtdbg.h>
#include <new>
#include <memory>

//*****************************************************************
//�������[���[�N�����`�F�b�N
//*****************************************************************
#define MyMemoryLeakCheck _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

//*****************************************************************
//		��O�ɂ���đ��o�����N���X
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
		const char* errstr,				//�G���[���b�Z�[�W
		const ERROR_TYPE_VALUE& data):	//error�l
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

//�Q�[�������I��error
typedef ErrorHandlerBase<int> Error_GameExit;


//*****************************************************************
//printf�Ɠ����`���ŏo�̓E�B���h�E�ɕ\��
//*****************************************************************
#define MyDebugString(str,...)\
{\
	TCHAR temp[512]; \
	sprintf_s<512>(temp, str, __VA_ARGS__); \
	OutputDebugString(temp); \
}

//*****************************************************************
//	���b�Z�[�W�{�b�N�X��printf�݂����ɕ\������
//*****************************************************************
#define MessageBoxPlus(str,...)\
{\
	char t[512]; \
	sprintf_s<512>(t, str, __VA_ARGS__);\
	MessageBox(0, t, "MessageBoxPlus", MB_OK);\
}

//*****************************************************************
//printf�Ɠ����`���ŃA�T�[�g�ɕ������\��������
//*****************************************************************
#define MyAssert(expr,str,...)\
{\
if (!(expr)){\
\
	\
	char t[256], ti[600]; \
	sprintf_s<256>(t, str, __VA_ARGS__); \
	sprintf_s<600>(ti, "�@%s�@�̍s�ԍ��@%d�@�ŃG���[���������܂��� \n %s \n��(%s) \n���s�𑱂��܂����H", __FILE__, __LINE__, t, #expr); \
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