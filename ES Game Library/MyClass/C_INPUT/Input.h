#pragma once
#include "../../ESGLib.h"

//◆ボタンの最大数
int const BUTTON_MAX = 31;
//◆ゲームパッドの最大数
int const PAD_MAX = 4;

class CInput
{
public:
	CInput()          {};
	virtual ~CInput() {};

	CInput(const CInput&)            = delete;
	CInput& operator=(const CInput&) = delete;
	CInput(CInput&&)                 = delete;
	CInput& operator=(CInput&&)      = delete;

	static CInput& GetInstance()
	{
		static CInput _input;
		return _input;
	}

	void CInput::Init();
	void CInput::Update();

	bool CInput::GetPadInputDown(int PadID, int KeyID);
	bool CInput::GetPadInput    (int PadID, int KeyID);

	bool CInput::GetPadandKeybordInputDown(int PadID, int KeyID);
	bool CInput::GetPadandKeybordInput    (int PadID, int KeyID);

	Vector3 CInput::GetStickVector           (int PadID);
	Vector3 CInput::GetArrowkeyVector();
	Vector3 CInput::GetStickandArrowkeyVector(int PadID);

	void CInput::SetKeybordID                (int PadID);
	void CInput::SetPadID                    (int PadID, int newPadID);
	void CInput::SetConfigButtonID           (int PadID, int button, int buttonid);
	void CInput::SetConfigKeyID               (int key, int keyid);

	void CInput::ResetConfigButton(int PadID);
	void CInput::ResetConfigKey();

	bool CInput::GetKeybordInputDown(int KeyID);
	bool CInput::GetKeybordInput    (int KeyID);

	Vector3 CInput::AxisArrowPadVector3(int PadID);

private:
	int PadPadID[PAD_MAX];
	int KeyBordPlayerID;

	BYTE buttonID[PAD_MAX][BUTTON_MAX];
	int  keybordID[BUTTON_MAX];

	GamePadBuffer  _padbuf[PAD_MAX];
	KeyboardBuffer _keybuf;
	GamePadState   _padstate[PAD_MAX];
	KeyboardState  _keystate;
};
#define Input CInput::GetInstance()

