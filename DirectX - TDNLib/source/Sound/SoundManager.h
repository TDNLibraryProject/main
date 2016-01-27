#pragma once

//********************************************************************************************************************
//
//		�N���X�̐錾
//
//********************************************************************************************************************
//		�T�E���h�}�l�[�W���[(�O���[�o�����̂Ŋ֐��Ăяo��)
//****************************************************************************************************************

namespace SoundManager
{
	void Initialize();
	void Release();
	void Update();
}

class iexSoundBase;
class tdnSoundSE;
class tdnSoundBGM;

class SE_Manager
{
private:
	std::map<LPSTR, int> ID;	// char*�^�Ŕԍ���U�蕪����

	tdnSoundSE *play_manager;	// iexSound

	// �f�[�^����
	//int Find_data_no(char *_ID);

	int Play_in(int data_num, bool loop);
	int Play_in(int data_num, float volume, bool loop);
	int Play_in(int data_num, const Vector3 &pos, const Vector3 &front, const Vector3 &move, bool loop);

public:

	//===============================================
	//	���f�[�^
	//===============================================
	struct	DATA{
		LPSTR id;					// �Ăяo���ۂɎg�p���鎯�ʃR�[�h
		LPSTR file_name;			// �t�@�C���p�X
		int play_simultaneously;	// ����̉��𕡐��Đ�����ő�l
		bool b3D;					// 3D�T�E���h�t���O
	};


	//===============================================
	//	�������Ɖ��
	//===============================================
	SE_Manager(){}
	~SE_Manager();
	void Initialize();

	//===============================================
	//	�X		�V
	//===============================================
	void Update();


	//===============================================
	//	��		��
	//===============================================
	int Play(LPSTR _ID, bool loop = false);																											// �ȈՔ�
	int Play(LPSTR _ID, float volume, bool loop);																									// �{�����[���ݒ��
	int Play(LPSTR _ID, const Vector3 &pos, const Vector3 &front = Vector3(0, 0, -1), const Vector3 &move = Vector3(0, 0, 0), bool loop = false);	// 3D�ݒ��
	void Stop(LPSTR _ID, int no);																													// Play�ŕԂ��Ă������l������
	void Stop_all();																																// �S���~�߂�
	
	void Set_listener(const Vector3 &pos, const Vector3 &front, const Vector3 &up, const Vector3 &move);											// ���X�i�[���
};

class BGM_Manager
{
private:
	std::map<LPSTR, int> ID;	// char*�^�Ŕԍ���U�蕪����

	tdnSoundBGM *play_manager;	// iexSound

	// �f�[�^����
	//int Find_data_no(char *_ID);

	void Play_in(int data_num, bool loop);
	void Play_in(int data_num, float volume, bool loop);
	void Play_in(int data_num, const Vector3 &pos, const Vector3 &front, const Vector3 &move, bool loop);

public:

	int effect_no = 0;

	//===============================================
	//	���f�[�^
	//===============================================
	struct	DATA{
		LPSTR id;					// �Ăяo���ۂɎg�p���鎯�ʃR�[�h
		LPSTR file_name;			// �t�@�C���p�X
		bool b3D;
	};


	//===============================================
	//	�������Ɖ��
	//===============================================
	void Initialize();
	~BGM_Manager();

	//===============================================
	//	�X		�V
	//===============================================
	void Update();


	//===============================================
	//	��		��
	//===============================================
	void Play(LPSTR _ID, bool loop = true);																											// �ȈՔ�
	void Play(LPSTR _ID, float volume, bool loop);																									// �{�����[���ݒ��
	void Play(LPSTR _ID, const Vector3 &pos, const Vector3 &front = Vector3(0, 0, -1), const Vector3 &move = Vector3(0, 0, 0), bool loop = true);	// 3D�ݒ��
	void Stop(LPSTR _ID);																															// Play�ŕԂ��Ă������l������
	void Stop_all();																																// �S���~�߂�

	void Fade_in(LPSTR _ID, float fade_speed, bool loop = true);
	void Fade_out(LPSTR _ID, float fade_speed);
	void Cross_fade(LPSTR inID, LPSTR outID, float fade_speed = .0075f, bool loop = true);
	void Cross_fade(LPSTR inID, LPSTR outID, float in_speed, float out_speed, bool loop);

	void Set_listener(const Vector3 &pos, const Vector3 &front, const Vector3 &up, const Vector3 &move);											// ���X�i�[���
};

//===============================================
//	����(�֐��Ăяo���͂������g��)
//===============================================
extern SE_Manager *se;
extern BGM_Manager *bgm;