#include	"TDNLIB.h"
#include	"../system/Framework.h"
#include	"../system/System.h"
#include	"SceneMain.h"
#include	"../../tdn/OKB.h"
#include	"../Sound/SoundManager.h"

tdn2DObj* BG;
tdn2DObj* Youmu;

tdnShader *shader3D;
tdnMesh* TestMesh;

struct Player
{
	tdn2DObj* picture;
	float x, y;

	int Anime;
	int motion;
	int flame;

	enum{ WaitL = 0, WaitR = 1, RunL = 2, RunR = 3 };

	bool invincible_action;
}player;

void PlayerCtrl()
{
	if (KeyBoardTRG(KB_DELETE))
	{
		se->Play("�C�G�A�A");
	}

	if (KeyBoard('Y'))tdnRenderState::Filter(true);
	if (KeyBoard('U'))tdnRenderState::Filter(false);

	if (KeyBoard('Q'))	player.picture->SetScale(player.picture->GetScale() - 0.1f);
	if (KeyBoard('E'))	player.picture->SetScale(player.picture->GetScale() + 0.1f);
	
	if (KeyBoard('R'))player.picture->SetAngle(player.picture->GetAngle() - 0.1f);
	if (KeyBoard('T'))player.picture->SetAngle(player.picture->GetAngle() + 0.1f);

	if (KeyBoard('A'))
	{
		player.x -= 6;
		player.Anime = Player:: RunL;

		// ��ʔ����ŃN���X�t�F�[�h
		if (player.x < tdnSystem::GetScreenSize().right / 2 && player.invincible_action)
		{
			player.invincible_action = false;
			bgm->Cross_fade("EoE_A", "EoE_B", .01f);
		}
	}
	if (KeyBoard('D'))
	{
		player.x += 6;
		player.Anime = Player:: RunR;

		// ��ʔ����ŃN���X�t�F�[�h
		if (player.x > tdnSystem::GetScreenSize().right / 2 && !player.invincible_action)
		{
			player.invincible_action = true;
			bgm->Cross_fade("EoE_B", "EoE_A", .025f);
		}
	}

	if (!KeyBoard('A') && !KeyBoard('D'))
	{
		if (player.Anime == Player:: RunL)
		{
			player.Anime = Player:: WaitL;
		}
		if (player.Anime == Player::RunR)
		{
			player.Anime = Player::WaitR;
		}	
	
	}
};

void PlayerUpdate()
{
	player.flame++;
	if (player.flame >= 6)
	{
		player.motion++;
		player.flame = 0;
	}

	if (player.Anime == Player::WaitL || player.Anime == Player::WaitR)
	{
		if (player.motion>=3)
		{
			player.motion = 0;
		}
	}
	else if (player.Anime == Player::RunL || player.Anime == Player::RunR)
	{
		if (player.motion >= 4)
		{
			player.motion = 0;
		}
	}
	

};

Vector3 cameraPos = Vector3(0, 0, -50);

//******************************************************************
//		�������E���
//******************************************************************
bool sceneMain::Initialize()
{
	tdnView::Init();

	OKB_Init();
	SoundManager::Initialize();

	player.picture = new tdn2DObj("DATA/Player1.png");
	player.x = player.motion = player.Anime=player.flame = 0.0f;
	player.y = 500;
	player.invincible_action = false;
	
	BG = new tdn2DObj("DATA/BG.png");
	Youmu= new tdn2DObj("DATA/Youmu.png");

	// 3D���b�V���쐬
	shader3D = new tdnShader( "DATA/Shader/3D.fx" );
	TestMesh = new tdnMesh;
	//TestMesh->LoadMqo("Data/mqo/box/box.mqo");
	Vector3 posList[]
	{
		{-2, -2, 0},
		{ -2, 2, 0 },
		{ 0, 0, 0 },
		{ 2, -2, 0 },
		{ 2, 2, 0 },
	};
	TestMesh->CreateCube( 1, 1, 1, 0xFFFFFFFF, posList, 5 );

	//TestMesh->CreateCube( 200, 200, 200, 0xFFFFFFFF );
	// �s��쐬
	Matrix viewMatrix;
	D3DXMatrixLookAtLH( &viewMatrix, &D3DXVECTOR3( 0, 0, -10 ), &D3DXVECTOR3( 0, 0, 0 ), &D3DXVECTOR3( 0, 1, 0 ) );
	shader3D->SetValue( "viewMatrix", viewMatrix );
	Matrix projectionMatrix;
	RECT screenSize = tdnSystem::GetScreenSize();
	D3DXMatrixPerspectiveFovLH( &projectionMatrix, PI / 3, screenSize.right / screenSize.bottom, 0.1f, 3000.0f );
	shader3D->SetValue( "projectionMatrix", projectionMatrix );

	// �T�E���h
	bgm->Play("EoE_A");

	return true;
}

sceneMain::~sceneMain()
{
	OKB_Release();
	SAFE_DELETE(player.picture);
	SAFE_DELETE(BG);
	SAFE_DELETE(Youmu);
	SAFE_DELETE( TestMesh );
	SAFE_DELETE( shader3D );
	SoundManager::Release();
}


//******************************************************************
//		�X�V�E�`��
//******************************************************************
bool sceneMain::Update()
{
	PlayerCtrl();
	PlayerUpdate();
	OKB_Update();
	SoundManager::Update();

	if (KeyBoard('F'))cameraPos.z += 1;
	if (KeyBoard('G'))cameraPos.z -= 1;
	tdnView::Set(cameraPos, VECTOR_ZERO);

	// ���b�V���e�X�g
	shader3D->SetValue( "viewPosition", cameraPos );
	static float meshAngle = 0;
	meshAngle += 0.01f;
	TestMesh->Rot( *D3DXQuaternionRotationYawPitchRoll( &Quaternion(), meshAngle, meshAngle * 0.9f, meshAngle * 0.7f ) );
	TestMesh->Pos( Vector3( 0.0f, 0.0f, 0.0f ) );
	TestMesh->UpdateWorldMatrix();

	return true;	
}

void sceneMain::Render()
{
	tdnView::Activate();
	tdnView::Clear(0xff005522);

	BG->Render(0, 0, RS::COPY_NOZ);
	Youmu->Render3D(0, 0, 0);
	Youmu->Render3D(-3, 0, -20);
	Youmu->Render3D(3, 0, -40);


	//�ڂ����ȊO��2D�`���LINER�͔���
	tdnRenderState::Filter(false);
	player.picture->Render((int)player.x, (int)player.y, 64, 64, player.motion * 64, player.Anime * 64, 64, 64, RS::COPY_NOZ);

	 //���b�V���e�X�g
	TestMesh->Render( shader3D, "linecopy" );

	// ��
	LPSTR n;

	switch ((DXA_FX)bgm->effect_no)
	{
	case DXA_FX::DXAFX_CHORUS:n = "�R�[���X";
		break;
	case DXA_FX::DXAFX_COMPRESSOR:n = "�R���v���b�T";
		break;
	case DXA_FX::DXAFX_DISTORTION:n = "�f�B�X�g�\�V����";
		break;
	case DXA_FX::DXAFX_ECHO:n = "�G�R�[";
		break;
	case DXA_FX::DXAFX_FLANGER:n = "�t�����W";
		break;
	case DXA_FX::DXAFX_GARGLE:n = "�K�[�O��";
		break;
	case DXA_FX::DXAFX_ENVREVERB:n = "�����o�[�u";
		break;
	case DXA_FX::DXAFX_PARAMEQ:n = "�p�����g���b�N�C�R���C�U";
		break;
	case DXA_FX::DXAFX_WAVESREVERB:n = "�~���[�W�b�N���o�[�u";
		break;
	case DXA_FX::DXAFX_OFF:n = "�Ȃ�";
		break;
	}

	tdnText::Draw(10, 300, 0xffff00ff, "1,2,3,4,5,6,7,8,9�@: �T�E���h�G�t�F�N�g�ύX", n);
	tdnText::Draw(10, 320, 0xffffff00, "�G�t�F�N�g:%s", n);
	//picture->Render(640, 0, shader2D, "red");
}
