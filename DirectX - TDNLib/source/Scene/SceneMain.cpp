#include	"TDNLIB.h"
#include	"../system/Framework.h"
#include	"../system/System.h"
#include	"SceneMain.h"
#include	"../Sound/SoundManager.h"

tdn2DObj* BG;
tdn2DObj* Youmu;

tdnShader *shader3D;
tdnMesh* TestMesh;

tdnArchiver* arc;
tdn2DObj* arcYoumu;

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

	if (KeyBoard(KB_Y))tdnRenderState::Filter(true);
	if (KeyBoard(KB_U))tdnRenderState::Filter(false);

	if (KeyBoard(KB_Q))	player.picture->SetScale(player.picture->GetScale() - 0.1f);
	if (KeyBoard(KB_E))	player.picture->SetScale(player.picture->GetScale() + 0.1f);
	
	if (KeyBoard(KB_R))player.picture->SetAngle(player.picture->GetAngle() - 0.1f);
	if (KeyBoard(KB_T))player.picture->SetAngle(player.picture->GetAngle() + 0.1f);

	if (KEY(KEY_LEFT, 0) == 1)
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
	if (KEY(KEY_RIGHT, 0) == 1)
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

	if (tdnInput::KeyGet(KEY_LEFT) != 1 && tdnInput::KeyGet(KEY_RIGHT) != 1)
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

	SoundManager::Initialize();

	float3 f3;
	f3.x = 0;;

	Vector a;

	//// �A�[�J�C�u
	//arc = new tdnArchiver();
	//arc->CreateArchiveFile("Data/Archive/HeaderArchive.bin", "Data/Archive/DataArchive.bin");

	////�@�d���p�b�N
	//arc->AddData("DATA/youmu.png");
	////	A��ԃp�b�N
	//arc->AddData("DATA/A.png");

	//arc->CloseArchiveFile("Data/Archive/Archive.tdn", "Data/Archive/HeaderArchive.bin", "Data/Archive/DataArchive.bin");
	//delete arc;
	//arc = nullptr;
	//// �A�[�J�C�u�I���

	// ����������
	arcYoumu = new tdn2DObj("DATA/A.png", "Data/Archive/Archive.tdn");


	player.picture = new tdn2DObj("DATA/Player1.png");
	player.motion = player.Anime=player.flame = 0;
	player.x = .0f;
	player.y = 500;
	player.invincible_action = false;
	
	BG = new tdn2DObj("DATA/BG.png");
	Youmu= new tdn2DObj("DaTA/Youmu.png");

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
	D3DXMatrixPerspectiveFovLH( &projectionMatrix, PI / 3, (float)screenSize.right / screenSize.bottom, 0.1f, 3000.0f );
	shader3D->SetValue( "projectionMatrix", projectionMatrix );

	// �T�E���h
	bgm->Play("EoE_A");

	//	�K�v�ȏꍇ�L�[�R���t�B�O�ݒ肵�܂�
	//tdnInput::PadAsign(1,0);

	return true;
}

sceneMain::~sceneMain()
{
	SAFE_DELETE(player.picture);
	SAFE_DELETE(BG);
	SAFE_DELETE(Youmu);
	SAFE_DELETE( TestMesh );
	SAFE_DELETE( shader3D );
	SAFE_DELETE(arcYoumu);
	SoundManager::Release();
}


//******************************************************************
//		�X�V�E�`��
//******************************************************************
bool sceneMain::Update()
{
	PlayerCtrl();
	PlayerUpdate();
	SoundManager::Update();

	if (KeyBoard(KB_F))cameraPos.z += 1;
	if (KeyBoard(KB_G))cameraPos.z -= 1;
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

	// �p�b�N�����ꂽ�d��
	static int movex = 0;
	movex++;
	arcYoumu->Render(movex, 0);

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

	if (tdnInput::KeyGet(KEY_A) == 1) tdnText::Draw(10, 340, 0xffffff00, "Input : A");
	if (tdnInput::KeyGet(KEY_B) == 1) tdnText::Draw(10, 360, 0xffffff00, "Input : B");
	if (tdnInput::KeyGet(KEY_C) == 1) tdnText::Draw(10, 380, 0xffffff00, "Input : C");
	if (tdnInput::KeyGet(KEY_D) == 1) tdnText::Draw(10, 400, 0xffffff00, "Input : D");
	if (tdnInput::KeyGet(KEY_L1) == 1) tdnText::Draw(10, 420, 0xffffff00, "Input : L1");
	if (tdnInput::KeyGet(KEY_L2) == 1) tdnText::Draw(10, 440, 0xffffff00, "Input : L2");
	if (tdnInput::KeyGet(KEY_L3) == 1) tdnText::Draw(10, 460, 0xffffff00, "Input : L3");
	if (tdnInput::KeyGet(KEY_R1) == 1) tdnText::Draw(10, 480, 0xffffff00, "Input : R1");
	if (tdnInput::KeyGet(KEY_R2) == 1) tdnText::Draw(10, 500, 0xffffff00, "Input : R2");
	if (tdnInput::KeyGet(KEY_R3) == 1) tdnText::Draw(10, 520, 0xffffff00, "Input : R3");
	if (tdnInput::KeyGet(KEY_START) == 1) tdnText::Draw(10, 540, 0xffffff00, "Input : START");
	if (tdnInput::KeyGet(KEY_SELECT) == 1) tdnText::Draw(10, 560, 0xffffff00, "Input : SELECT");
	if (tdnInput::KeyGet(KEY_LEFT) == 1) tdnText::Draw(10, 580, 0xffffff00, "Input : LEFT");
	if (tdnInput::KeyGet(KEY_RIGHT) == 1) tdnText::Draw(10, 580, 0xffffff00, "Input : RIGHT");
	if (tdnInput::KeyGet(KEY_UP) == 1) tdnText::Draw(10, 600, 0xffffff00, "Input : UP");
	if (tdnInput::KeyGet(KEY_DOWN) == 1) tdnText::Draw(10, 600, 0xffffff00, "Input : DOWN");
}
