#pragma once

//------------------------------------------------------------------------------
//	インクルードファイル
//------------------------------------------------------------------------------
#include "../../ESGLib.h"
#include <vector>

//------------------------------------------------------------------------------
//	SEManagerクラス定義
//------------------------------------------------------------------------------

class C_SE 
{
public:
	C_SE() {};
	virtual ~C_SE(){};

	// シングルトンインスタンスの取得
	static C_SE& GetInstance()
	{ 
		static C_SE theSEManager;
		return theSEManager;
	}
	bool Initialize();

	int  LoadSE(TCHAR* filename, const UINT multiple = 1);
	void PlaySE(int index);
	
	void LoadBGM(TCHAR* filename) { bgm = SoundDevice.CreateMusicFromFile(filename); };
	bool PlayBGM();

private:
	
	MUSIC bgm;

	// メンバ変数
	std::vector< std::vector<SOUND> > se;

	C_SE(const C_SE&) = delete;
	C_SE& operator=(const C_SE&) = delete;
	C_SE(C_SE&&) = delete;
	C_SE& operator=(C_SE&&) = delete;
};

//------------------------------------------------------------------------------
//	インライン関数定義
//------------------------------------------------------------------------------
#define SNDMANAGER C_SE::GetInstance()