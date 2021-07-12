#include "C_SE.h"

bool C_SE::Initialize()
{
	se.clear();
	se.reserve(4);

	SoundDevice.ReleaseAllMusics();
	SoundDevice.ReleaseAllSounds();

	return true;
}

int C_SE::LoadSE(TCHAR* filename, const UINT multiple)
{
	std::vector<SOUND> se_vec;
	se_vec.assign(multiple, nullptr);

	SoundDevice.CreateSharedSoundFromFile(filename, &se_vec[0], multiple, false);
	se.push_back(se_vec);

	return se.size() - 1;
}

void C_SE::PlaySE(int index)
{
	if (se[index].size() <= 1) {
		se[index][0]->Play();
		return;
	}

	for (UINT i = 0; i < se[index].size(); i++) {
		if (!se[index][i]->IsPlaying()) {
			se[index][i]->Play();
			return;
		}
	}

	se[index][0]->Play();
}

bool C_SE::PlayBGM()
{
	if (bgm->IsPlaying())return FALSE;
	bgm->Play();
	return TRUE;
}
