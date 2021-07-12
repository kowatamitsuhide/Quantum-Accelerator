#pragma once

// インターフェースクラス
class State {
private:
   //経過フレーム
   int _timef = 0;
   //次に移行する状態
   State* _nextState = nullptr;
public:
   // 仮想デストラクタ 
   // 更新
   virtual void Update() {}; 

  void  State::AddTime() { _timef++; };
  int      State::GetTime() { return _timef; };

};
//ステート管理クラス
class StateProcessor {
private:
   State* _state=nullptr; //現在の状態
public:
   StateProcessor::StateProcessor() : _state(nullptr) {
   }
   StateProcessor::~StateProcessor() {
	delete _state;
   }

   void StateProcessor::Update() {
	_state->AddTime();
	_state->Update();

   }

   void  StateProcessor::ChangeState(State* state) {
	   if (_state == state) return;
	delete _state;
	_state = state;
   }

   State* StateProcessor::NowState() {
	return _state;
   }  
};
