#pragma once
#include "GameLoader.h"
#include "GameController.h"
#include "BlockEffect.h"

class GameSystem {
private:
	unsigned int objShape[7][4]; // contain pattern of dropping obj　ブロックの配置データ
	unsigned int pointerRef[16]; // use to point to map array address　マップ内のブロックの配置ポイント
	unsigned int prepointerRef[16]; //ブロックの配置ポイントを一個前に戻す
	unsigned int startpoint; //new generate point　ブロック配置の参照ポイント
	unsigned int lastpoint; // prev generate point　一個前の参照ポイント
	unsigned int objtype; //生成するブロックのインデックス
	unsigned int objcolor;
	unsigned int score; // print on console　点数
	bool rotatechecker; // check if rotated　回転したかどうか
	std::vector<int> storeline;
	
public:
	GameSystem();
	~GameSystem();
	bool GameReset; //ゲームオーバー判定
	bool ClearEffect;
	std::vector<int>outputindex;
	void GenerateObj(unsigned int map[300],unsigned int tmpmap[300]); // use pointer to combine obj and map　当たり判定とマップ更新
	void ObjFall(int index); // make obj auto falling (use rotate)　ブロックの落ち
	void FixObj(unsigned int map[300], unsigned int tmpmap[300]); //移動できるブロックをマップに書き込み
	void RollBackRotate(); //回転を取り消し
	void ColliderCheck(unsigned int index, unsigned int tmpmap[300]);
	void Scoring();
	void CLearStroke( unsigned int tmpmap[300]); //行数クリア
	void MoveLine(unsigned int map[300],unsigned int tmpmap[300]);
	void ProgressIndex(int input,unsigned int tmpmap[300]);

};