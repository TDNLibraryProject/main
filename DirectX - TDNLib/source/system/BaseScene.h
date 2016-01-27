#pragma once

/*****************************/
//		�x�[�X�V�[��
/*****************************/
class BaseScene
{
public:
	//	�����E���
	BaseScene(){}
	virtual ~BaseScene(){}
	//	������
	virtual bool Initialize(){ return true; }
	//	�X�V�E�`��
	virtual bool Update(){ return false; }
	virtual void Render(){}
};

