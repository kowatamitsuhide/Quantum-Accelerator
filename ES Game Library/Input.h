#pragma once
#include "ESGLib.h"

//◆ボタンの最大数
int const BUTTON_MAX = 31;
//◆ゲームパッドの最大数
int const PAD_MAX = 4;

class Input
{
public:
	Input()          {};
	virtual ~Input() {};

	Input(const Input&)            = delete;
	Input& operator=(const Input&) = delete;
	Input(Input&&)                 = delete;
	Input& operator=(Input&&)      = delete;

	void Input::Init();
	void Input::Update();

	bool Input::GetPadInputDown(int PadID, int KeyID);
	bool Input::GetPadInput    (int PadID, int KeyID);

	bool Input::GetPadandKeybordInputDown(int PadID, int KeyID);
	bool Input::GetPadandKeybordInput    (int PadID, int KeyID);

	Vector3 Input::GetStickVector           (int PadID);
	Vector3 Input::GetArrowkeyVector();
	Vector3 Input::GetStickandArrowkeyVector(int PadID);

	void Input::SetKeybordID                (int PadID);
	void Input::SetPadID                    (int PadID, int newPadID);
	void Input::SetConfigButtonID           (int PadID, int button, int buttonid);
	void Input::SetConfigKeyID               (int key, int keyid);

	void Input::ResetConfigButton(int PadID);
	void Input::ResetConfigKey();

	Vector3 Input::AxisArrowPadVector3(int PadID);

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

