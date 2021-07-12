#include"HitStop.h"

void HitStop::Init() {
  
}

void HitStop::Update() {
   if (this->p_taget == nullptr) return;
  this-> _count = this->_count > 0 ? this->_count - 1 : 0;
   p_taget->SetActive(!this->IsStop());
}

void HitStop::SetStopCount(int damage) {
	this->_count = MathHelper_Min(20, damage / 3 + 3);
}

bool HitStop::IsStop() {
   return this->_count > 0;
}