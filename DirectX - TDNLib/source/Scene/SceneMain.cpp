#include	"TDNLIB.h"
#include	"../system/Framework.h"
#include	"../system/System.h"
#include	"SceneMain.h"
#include	"../../tdn/OKB.h"
#include	"../Sound/SoundManager.h"

tdn2DObj* BG;
tdn2DObj* Youmu;

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
		se->Play("イエアア");
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

		// 画面半分でクロスフェード
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

		// 画面半分でクロスフェード
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
//		初期化・解放
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

	bgm->Play("EoE_A");

	return true;
}

sceneMain::~sceneMain()
{
	OKB_Release();
	SAFE_DELETE(player.picture);
	SAFE_DELETE(BG);
	SAFE_DELETE(Youmu);
	SoundManager::Release();
}


//******************************************************************
//		更新・描画
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
	//ぼかす以外で2D描画でLINERは微妙
	tdnRenderState::Filter(false);
	player.picture->Render((int)player.x, (int)player.y, 64, 64, player.motion * 64, player.Anime * 64, 64, 64, RS::COPY_NOZ);

	LPSTR n;

	switch ((DXA_FX)bgm->effect_no)
	{
	case DXA_FX::DXAFX_CHORUS:n = "コーラス";
		break;
	case DXA_FX::DXAFX_COMPRESSOR:n = "コンプレッサ";
		break;
	case DXA_FX::DXAFX_DISTORTION:n = "ディスト―ション";
		break;
	case DXA_FX::DXAFX_ECHO:n = "エコー";
		break;
	case DXA_FX::DXAFX_FLANGER:n = "フランジ";
		break;
	case DXA_FX::DXAFX_GARGLE:n = "ガーグル";
		break;
	case DXA_FX::DXAFX_ENVREVERB:n = "環境リバーブ";
		break;
	case DXA_FX::DXAFX_PARAMEQ:n = "パラメトリックイコライザ";
		break;
	case DXA_FX::DXAFX_WAVESREVERB:n = "ミュージックリバーブ";
		break;
	case DXA_FX::DXAFX_OFF:n = "なし";
		break;
	}

	tdnText::Draw(10, 300, 0xffff00ff, "1,2,3,4,5,6,7,8,9　: サウンドエフェクト変更", n);
	tdnText::Draw(10, 320, 0xffffff00, "エフェクト:%s", n);
	//picture->Render(640, 0, shader2D, "red");
}
