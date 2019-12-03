#include "Character.h"
#include <math.h>
#include "Stage.h"
#include "Weapon.h"
#include "AI.h"

#define GRAVITY 0.3f		// 重力


// コンストラクタ
Character::Character(float x,float y,float z){
	// 初期座標の設定
	StartPos = VGet( x,y,z ) ;
	Position = StartPos;
	hitbox.position = Position;
	// 回転値は０
	Angle = 0.0f ;
	AngleV =0.0f ;
	
	// 緊急回避は最初はfalse
	isRoleRight = false;
	isRoleLeft = false;
	// 回転値は０
	RoleAngle = 0.0f;
	// 弾を初期化
	tama = new std::list<Tama*>(0);
	isJump = false;
	isJet = 0;
	isFire = false;
	jump = 0.0f;
	speed = 1.0f;
	UpMoveVec = VGet(1,0,0);
	LeftMoveVec = VGet(0,0,1);

	MaxHP = 100;
	HP = MaxHP;
	isAlive = true;
	// 名前の設定
	name = "名無しさん";

	HIT_SLIDE_LENGTH = 5.0f;
}

void Character::SetName(std::string name){
	this->name=name;
}

// デストラクタ
Character::~Character(){
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end(); ite++){
		delete *ite;
	}
	delete tama;
}

void Character::Damage(int damage){
	HP -= damage;
	if(HP<0)
		isAlive = false;
}

HitBox Character::GetHitBox(){
	return hitbox;
}

int Character::GetDamage(){
	return weapon->GetDamage();
}



bool Character::CollCheck(Character *chara2){
    HitBox eHitBox = chara2->GetHitBox();
	// 自分の方
	// 回転
	VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
	VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
	// 移動
	hitbox_front = VAdd(Position,hitbox_front);	
	hitbox_back = VAdd(Position,hitbox_back);

	// 相手の方
	// 回転
	VECTOR ehitbox_front = VTransform(eHitBox.front,MGetRotY(eHitBox.angle));
	VECTOR ehitbox_back = VTransform(eHitBox.back,MGetRotY(eHitBox.angle));
	// 移動
	ehitbox_front = VAdd(eHitBox.position,ehitbox_front);	
	ehitbox_back = VAdd(eHitBox.position,ehitbox_back);

	if(HitCheck_Capsule_Capsule(hitbox_front,hitbox_back,hitbox.r,ehitbox_front,ehitbox_back,eHitBox.r)==TRUE){

		// 当たっていたら ch が chk から離れる処理をする
		VECTOR ch_MoveVec = VGet(0,0,0);
		VECTOR ChkChToChVec ;
		VECTOR PushVec ;
		VECTOR ChPosition ;
		float Length ;
		const float CHARA_HIT_PUSH_POWER = 80.0f ;
	
	
		// 移動後の ch の座標を算出
		ChPosition = VAdd( Position, ch_MoveVec ) ;
        
		// chk_ch から ch へのベクトルを算出
		ChkChToChVec = VSub( ChPosition, chara2->GetPosition() ) ;
        
		// Ｙ軸は見ない
		ChkChToChVec.y = 0.0f ;
        
		// 二人の距離を算出
		Length = VSize( ChkChToChVec ) ;
        
		// chk_ch から ch へのベクトルを正規化( ベクトルの長さを 1.0f にする )
		PushVec = VScale( ChkChToChVec, 1.0f / Length ) ;
        
		// 押し出す距離を算出、もし二人の距離から二人の大きさを引いた値に押し出し力を足して離れてしまう場合は、ぴったりくっつく距離に移動する
		//if( Length - hitbox.r * 2.0f + CHARA_HIT_PUSH_POWER > 0.0f )
		if(0)
		{
			float TempY ;
            
			TempY = ChPosition.y ;
			ChPosition = VAdd( chara2->GetPosition(), VScale( PushVec, hitbox.r * 2.0f ) ) ; 
            
			// Ｙ座標は変化させない
			ChPosition.y = TempY ;
		}
		else
		{
			// 押し出し
			ChPosition = VAdd( ChPosition, VScale( PushVec, CHARA_HIT_PUSH_POWER ) ) ;
		}
		// 当たり判定処理後の移動ベクトルをセット
		MoveVec = VSub( ChPosition, Position ) ;
		return true;
	}
	return false;
}



// 処理
void Character::Fall(){

	// Ｙ軸方向の速度を重力分減算する
	jump -= GRAVITY ;

	// 移動ベクトルのＹ成分をＹ軸方向の速度にする
	MoveVec.y += jump ;
	// 奈落処理
	if(Position.y < -1000.f){
		Position = StartPos;
	}
}

void Character::Jump(){
	if(!isJump){
		// 状態を「ジャンプ」にする
		isJump = true;

		// Ｙ軸方向の速度をセット
		jump = JUMP_POWER;

		MoveVec.y += jump*3;

		MoveFlag = 1;
	}else{
		Jet();
	}
}

void Character::Jet(){
	if(isJet>0){
		jump += 0.35f;
		isJet -= 1;
	}
}

void Character::Attack(){
	if(isFire){
		weapon->CreateTama(Position,Angle,AngleV/2.f,tama);
	}
}

void Character::TamaMove(Stage *stg){
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end(); ite++){
		(*ite)->Move(stg);
	}
}

void Character::Draw(){
	MV1DrawModel(ModelHandle);
	
	

	// 回転
	VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
	VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
	// 移動
	hitbox_front = VAdd(Position,hitbox_front);	
	hitbox_back = VAdd(Position,hitbox_back);	


	// 弾を描画
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end(); ite++){
		if((*ite)->GetAlive())
			(*ite)->Draw();
	}
}

void Character::TamaDeath(){
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end();){
		if(!(*ite)->GetAlive()){
			delete (*ite);
			ite = tama->erase(ite);
		}else{
			ite++;
		}
	}
}

// キャラクターの向きを変える処理
void Character::Rotate( void )
{
	float TargetAngle ;			// 目標角度
	float SaAngle ;				// 目標角度と現在の角度との差

	// 目標の方向ベクトルから角度値を算出する
	TargetAngle = atan2( Direction.x, Direction.z ) ;

	// 目標の角度と現在の角度との差を割り出す
	{
		// 最初は単純に引き算
		SaAngle = TargetAngle - Angle ;

		// ある方向からある方向の差が１８０度以上になることは無いので
		// 差の値が１８０度以上になっていたら修正する
		if( SaAngle < -DX_PI_F )
		{
			SaAngle += DX_TWO_PI_F ;
		}
		else
			if( SaAngle > DX_PI_F )
			{
				SaAngle -= DX_TWO_PI_F ;
			}
	}

	// 角度の差が０に近づける
	if( SaAngle > 0.0f )
	{
		// 差がプラスの場合は引く
		SaAngle -= ANGLE_SPEED ;
		if( SaAngle < 0.0f )
		{
			SaAngle = 0.0f ;
		}
	}
	else
	{
		// 差がマイナスの場合は足す
		SaAngle += ANGLE_SPEED ;
		if( SaAngle > 0.0f )
		{
			SaAngle = 0.0f ;
		}
	}

	// モデルの角度を更新
	Angle = TargetAngle - SaAngle ;
	MV1SetRotationXYZ( ModelHandle, VGet( 0.0f, Angle + DX_PI_F, 0.0f ) ) ;

}

void Character::CheckStageColl(Stage *stg){
	//if(!isRoleRight && !isRoleLeft) {
		int i, j, k ;						// 汎用カウンタ変数
		int MoveFlag ;						// 水平方向に移動したかどうかのフラグ( ０:移動していない  １:移動した )
		int HitFlag ;						// ポリゴンに当たったかどうかを記憶しておくのに使う変数( ０:当たっていない  １:当たった )
		MV1_COLL_RESULT_POLY_DIM HitDim ;			// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
		int KabeNum ;						// 壁ポリゴンと判断されたポリゴンの数
		int YukaNum ;						// 床ポリゴンと判断されたポリゴンの数
		MV1_COLL_RESULT_POLY *Poly ;				// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )
		HITRESULT_LINE LineRes ;				// 線分とポリゴンとの当たり判定の結果を代入する構造体
		VECTOR OldPos ;						// 移動前の座標	
		VECTOR NowPos ;						// 移動後の座標
		std::vector<MV1_COLL_RESULT_POLY*> Kabe;
		std::vector<MV1_COLL_RESULT_POLY*> Yuka; 

		// 移動前の座標を保存
		OldPos = Position ;

		// 移動後の座標を算出
		NowPos = VAdd( Position, MoveVec ) ;

		// プレイヤーの周囲にあるステージポリゴンを取得する
		// ( 検出する範囲は移動距離も考慮する )
		HitDim = stg->GetStagePoly(Position,ENUM_DEFAULT_SIZE + VSize( MoveVec ));


		//VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle )));
		//VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle )));

		// 回転
		VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
		VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
		// 移動
		hitbox_front = VAdd(NowPos,hitbox_front);	
		hitbox_back = VAdd(NowPos,hitbox_back);	
		//VECTOR hitbox_front = hitbox.front;
		//VECTOR hitbox_back = hitbox.back;



		
		// (1) 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断する
		JudgeFlootOrWall(HitDim,&Kabe,&Yuka);


		// (2) 壁ポリゴンとの当たり判定処理
		NowPos = AttachWall(&Kabe);


		YukaNum = Yuka.size();
		// (3) 床ポリゴンとの当たり判定
		if( YukaNum != 0 ){
			float MaxY ;

			// 床ポリゴンに当たったかどうかのフラグを倒しておく
			HitFlag = 0 ;

			// 一番高い床ポリゴンにぶつける為の判定用変数を初期化
			MaxY = 0.0f ;

			// 床ポリゴンの数だけ繰り返し
			for( i = 0 ; i < YukaNum ; i ++ ){
				// i番目の床ポリゴンのアドレスを床ポリゴンポインタ配列から取得
				Poly = Yuka[ i ] ;

				// 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
				LineRes = HitCheck_Line_Triangle( VAdd( NowPos, VGet( 0.0f, HIT_HEIGHT, 0.0f ) ), 
					VAdd( NowPos, VGet( 0.0f, -40.0f, 0.0f ) ), Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) ;

				// 当たっていなかったら何もしない
				if( LineRes.HitFlag == FALSE ) continue ;

				// 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
				if( HitFlag == 1 && MaxY > LineRes.Position.y ) continue ;

				// ポリゴンに当たったフラグを立てる
				HitFlag = 1 ;

				// 接触したＹ座標を保存する
				MaxY = LineRes.Position.y ;
			}

			// 床ポリゴンに当たったかどうかで処理を分岐
			if( HitFlag == 1 && MoveVec.y < 0){
				// 当たった場合
				// Ｙ軸方向の移動速度は０に
				MoveVec.y = 0.0f ;
				jump = 0.0f;

				// もしジャンプ中だった場合は着地状態にする
				if(isJump)
				{
					isJump = false; 
				}	
				// 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
				NowPos.y = MaxY ;
			}
			else{
				// 床コリジョンに当たっていなくて且つジャンプ状態ではなかった場合は
				if( !isJump)
				{
					// ジャンプ中にする
					isJump = true;
					jump = 0;
				}

			}

		}
		// 新しい座標を保存する
		Position = NowPos ;

		// プレイヤーのモデルの座標を更新する
		MV1SetPosition( ModelHandle, Position ) ;

		// 検出したプレイヤーの周囲のポリゴン情報を開放する
		MV1CollResultPolyDimTerminate( HitDim ) ;
	//}
}


void Character::JudgeFlootOrWall(MV1_COLL_RESULT_POLY_DIM &HitDim,
	std::vector<MV1_COLL_RESULT_POLY*> *Kabe,
	std::vector<MV1_COLL_RESULT_POLY*> *Yuka){

		// 検出されたポリゴンの数だけ繰り返し
		for(int i = 0 ; i < HitDim.HitNum ; i ++ )
		{
			// ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
			// if( HitDim.Dim[ i ].Normal.y < 0.000001f && HitDim.Dim[ i ].Normal.y > -0.000001f )
			// if( HitDim.Dim[ i ].Normal.y < 0.1f && HitDim.Dim[ i ].Normal.y > -0.1f )
			if( HitDim.Dim[ i ].Normal.y < 0.0f)
			{
				// 壁ポリゴンと判断された場合でも、プレイヤーのＹ座標＋１．０ｆより高いポリゴンのみ当たり判定を行う
				if( HitDim.Dim[ i ].Position[ 0 ].y > Position.y + 1.0f ||
					HitDim.Dim[ i ].Position[ 1 ].y > Position.y + 1.0f ||
					HitDim.Dim[ i ].Position[ 2 ].y > Position.y + 1.0f )
				{

					// ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
					Kabe->push_back( &HitDim.Dim[ i ]);
				}
			}
			else
			{
				// ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
				Yuka->push_back(&HitDim.Dim[ i ] );
			}
		}
}

VECTOR Character::AttachWall(std::vector<MV1_COLL_RESULT_POLY*> *Kabe){
	int HitFlag;
	int KabeNum = Kabe->size();
	int j;
	MV1_COLL_RESULT_POLY *Poly ;				// ポリゴンの構造体にアクセスするために使用するポインタ( 使わなくても済ませられますがプログラムが長くなるので・・・ )
	int MoveFlag;
	VECTOR OldPos ;						// 移動前の座標	
	VECTOR NowPos ;						// 移動後の座標

	// x軸かz軸方向に 0.01f 以上移動した場合は「移動した」フラグを１にする
	if( fabs( MoveVec.x ) > 0.01f || fabs( MoveVec.z ) > 0.01f )
	{
		MoveFlag = 1 ;
	}
	else
	{
		MoveFlag = 0 ;
	}

	// 移動前の座標を保存
	OldPos = Position ;

	// 移動後の座標を算出
	NowPos = VAdd( Position, MoveVec ) ;

	// 回転
	VECTOR hitbox_front = VTransform(hitbox.front,MGetRotY(hitbox.angle));
	VECTOR hitbox_back = VTransform(hitbox.back,MGetRotY(hitbox.angle));
	// 移動
	hitbox_front = VAdd(NowPos,hitbox_front);	
	hitbox_back = VAdd(NowPos,hitbox_back);	

	if( KabeNum != 0 )
	{
		// 壁に当たったかどうかのフラグは初期状態では「当たっていない」にしておく
		HitFlag = 0 ;

		// 移動したかどうかで処理を分岐
		if( MoveFlag == 1 )
		{
			// 壁ポリゴンの数だけ繰り返し
			for( int i = 0 ; i < KabeNum ; i ++ )
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				Poly = (*Kabe)[i];

				// ポリゴンとプレイヤーが当たっていなかったら次のカウントへ
				if( HitCheck_Capsule_Triangle(  hitbox_front,hitbox_back,
					HIT_WIDTH, Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) == FALSE ) continue ;

				// ここにきたらポリゴンとプレイヤーが当たっているということなので、ポリゴンに当たったフラグを立てる
				HitFlag = 1 ;

				// 壁に当たったら壁に遮られない移動成分分だけ移動する
				{
					VECTOR SlideVec ;	// プレイヤーをスライドさせるベクトル

					// 進行方向ベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出
					SlideVec = VCross( MoveVec, Poly->Normal ) ;

					// 算出したベクトルと壁ポリゴンの法線ベクトルに垂直なベクトルを算出、これが
					// 元の移動成分から壁方向の移動成分を抜いたベクトル
					SlideVec = VCross( Poly->Normal, SlideVec ) ;

					// それを移動前の座標に足したものを新たな座標とする
					NowPos = VAdd( OldPos, SlideVec ) ;
				}
				hitbox_front = VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle )));
				hitbox_back = VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle )));

				// 新たな移動座標で壁ポリゴンと当たっていないかどうかを判定する
				
				for( j = 0 ; j < KabeNum ; j ++ )
				{
					// j番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					Poly = (*Kabe)[ j ] ;

					// 当たっていたらループから抜ける
					if( HitCheck_Capsule_Triangle( hitbox_front,hitbox_back,
						HIT_WIDTH, Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) == TRUE ) break ;
				}

				// j が KabeNum だった場合はどのポリゴンとも当たらなかったということなので
				// 壁に当たったフラグを倒した上でループから抜ける
				if( j == KabeNum )
				{
					HitFlag = 0 ;
					break ;
				}
			}
		}
		else
		{
			// 移動していない場合の処理

			// 壁ポリゴンの数だけ繰り返し
			for( int i = 0 ; i < KabeNum ; i ++ )
			{
				// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
				Poly = (*Kabe)[ i ] ;

				// ポリゴンに当たっていたら当たったフラグを立てた上でループから抜ける
				if( HitCheck_Capsule_Triangle( hitbox_front,hitbox_back,
					HIT_WIDTH, Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) == TRUE )
				{
					HitFlag = 1 ;
					break ;
				}
			}
		}

		// 壁に当たっていたら壁から押し出す処理を行う
		if( HitFlag == 1 )
		{
			// 壁からの押し出し処理を試みる最大数だけ繰り返し
			for(int k = 0 ; k < HIT_TRYNUM ; k ++ )
			{
				int i;
				// 壁ポリゴンの数だけ繰り返し
				for(i = 0 ; i < KabeNum ; i ++ )
				{
					// i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
					Poly = (*Kabe)[ i ] ;

					// プレイヤーと当たっているかを判定
					if( HitCheck_Capsule_Triangle(hitbox_front,hitbox_back,
						HIT_WIDTH, Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) == FALSE ) continue ;

					// 当たっていたら規定距離分プレイヤーを壁の法線方向に移動させる
					NowPos = VAdd( NowPos, VScale( Poly->Normal, HIT_SLIDE_LENGTH ) ) ;
					hitbox_front = VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,0.0f), MGetRotY(  Angle )));
					hitbox_back = VAdd(NowPos, VTransform( VGet(0.0f,HIT_HORIZON,-HIT_HEIGHT), MGetRotY( Angle )));


					// 移動した上で壁ポリゴンと接触しているかどうかを判定
					for( j = 0 ; j < KabeNum ; j ++ )
					{
						// 当たっていたらループを抜ける
						Poly = (*Kabe)[ j ] ;
						if( HitCheck_Capsule_Triangle( hitbox_front,hitbox_back,
							HIT_WIDTH, Poly->Position[ 0 ], Poly->Position[ 1 ], Poly->Position[ 2 ] ) == TRUE ) break ;
					}

					// 全てのポリゴンと当たっていなかったらここでループ終了
					if( j == KabeNum ) break ;
				}

				// i が KabeNum ではない場合は全部のポリゴンで押し出しを試みる前に全ての壁ポリゴンと接触しなくなったということなのでループから抜ける
				if( i != KabeNum ) break ;
			}
		}
	}

	return NowPos;
}

// 緊急回避
void Character::Role(){
	float AngleSpeed = 0.f;
	if(isRoleRight){
		AngleSpeed = -ROLE_SPEED ;
	}
	else if(isRoleLeft){
		AngleSpeed = ROLE_SPEED;
	}else{
		// 関数を抜ける
		return ;
	}
	RoleAngle += AngleSpeed;

	MATRIX addPos = MGetTranslate(VGet(0.f,-3.2f,0.f));
	MATRIX temp = MMult(addPos,MGetRotZ(AngleSpeed));
	temp = MMult(temp ,MInverse(addPos));
	temp = MMult(temp, MV1GetMatrix(ModelHandle));
	MATRIX roleMove;
	if(AngleSpeed < 0){
		roleMove =  MGetTranslate(VScale(LeftMoveVec,2.0f));
	}else{
		roleMove =  MGetTranslate(VScale(LeftMoveVec,-2.0f));
	}
	temp = MMult(temp,roleMove);
	Position = VTransform(Position,roleMove);
	MV1SetMatrix(ModelHandle,temp);

	if(isRoleRight && RoleAngle <= -DX_TWO_PI_F ){
		RoleAngle = 0.0f;
		isRoleRight=false;
		MV1SetMatrix(ModelHandle,MGetIdent());
	}
	else if(isRoleLeft && RoleAngle >= DX_TWO_PI_F ){
		RoleAngle = 0.0f;
		isRoleLeft=false;
		MV1SetMatrix(ModelHandle,MGetIdent());
	}
}

VECTOR Character::GetPosition(){
	return Position;
}

// 考える
void Character::Think(){
	directionFlag = ai->decideMove();
	isFire = ai->doFire();
}

bool Character::GetisAlive(){
	return isAlive;
}

// 移動
void Character::Move() {
	MoveFlag  = 0;			// 移動したかどうかのフラグ( 1:移動した  0:移動していない )
	MoveVec = VGet( 0.0f, 0.0f, 0.0f ) ;				// このフレームの移動ベクトル


	// ルートフレームのＺ軸方向の移動パラメータを無効にする
	{
		MATRIX LocalMatrix ;

		// ユーザー行列を解除する
		MV1ResetFrameUserLocalMatrix( ModelHandle, 2 ) ;

		// 現在のルートフレームの行列を取得する
		LocalMatrix = MV1GetFrameLocalMatrix( ModelHandle, 2 ) ;

		// Ｚ軸方向の平行移動成分を無効にする
		LocalMatrix.m[ 3 ][ 2 ] = 0.0f ;

		// ユーザー行列として平行移動成分を無効にした行列をルートフレームにセットする
		MV1SetFrameUserLocalMatrix( ModelHandle, 2, LocalMatrix ) ;
	}

	// プレイヤーの移動処理
	// 左方向
	if( directionFlag.left )
	{
		float move = -(float)directionFlag.left/1000.0f;
		move *= speed;
		// 移動ベクトルに「←」が入力された時の移動ベクトルを加算する
		MoveVec = VAdd( MoveVec, VScale( LeftMoveVec, move )) ;
		// 移動したかどうかのフラグを「移動した」にする
		MoveFlag = 1 ;
	}

	//右方向
	if( directionFlag.right)
	{
		float move = (float)directionFlag.right /1000.0f;
		move *= speed;
		// 移動ベクトルに「←」が入力された時の移動ベクトルを反転したものを加算する
		MoveVec = VAdd( MoveVec, VScale( LeftMoveVec, move )) ;
		// 移動したかどうかのフラグを「移動した」にする
		MoveFlag = 1 ;
	}

	// 前方向
	if( directionFlag.front )
	{
		float move = (float)directionFlag.front /1000.0f;
		move *= speed;
		// 移動ベクトルに「↑」が入力された時の移動ベクトルを加算する
		MoveVec = VAdd( MoveVec, VScale( UpMoveVec, move ) ) ;
		// 移動したかどうかのフラグを「移動した」にする
		MoveFlag = 1 ;
	}

	// 後方向
	if( directionFlag.back )
	{
		float move = -(float)directionFlag.back/1000.0f;
		move *= speed;
		// 移動ベクトルに「↑」が入力された時の移動ベクトルを反転したものを加算する
		MoveVec = VAdd( MoveVec, VScale(UpMoveVec,move)) ;
		// 移動したかどうかのフラグを「移動した」にする
		MoveFlag = 1 ;
	}
	// 緊急回避キーが押された
	if(!isRoleRight &&  directionFlag.roleRight){
		isRoleRight = true;	// 緊急回避フラグをonにする
	}
	if(!isRoleLeft && directionFlag.roleLeft ){
		isRoleLeft = true;
	}

	// プレイヤーの状態が「ジャンプ」ではなく、且つボタン2が押されていたらジャンプする
	if( directionFlag.jump )
	{
		Jump();

	}
	// 方向を設定
	if(MoveFlag){
		Direction = VNorm(MoveVec);
	}
}

// 移動更新
void Character::UpdatePosition(){
	if(!isRoleRight && !isRoleLeft) {
		// 移動ボタンが押された場合に移動処理
		if( MoveFlag )
		{
			// 方向を指定
			Direction = VNorm( UpMoveVec ) ;
			// 移動
			Position = VAdd(Position,MoveVec);	
		}
		// プレイヤーのモデルの座標を更新する
		MV1SetPosition( ModelHandle, Position ) ;
		hitbox.position = Position;
		hitbox.angle = Angle;
	}
}



bool Character::TamaCollCheck(Character* target){
	bool flag = false;
	std::list<Tama*>::iterator ite;
	for(ite = tama->begin();ite != tama->end();ite++){
		if((*ite)->CollCheck(target)){
			flag = true;
			target->Damage(weapon->GetDamage());
		}
	}
	return flag;
}


void Character::SetWeapon(Weapon* w){
	if(weapon)
		delete weapon;
	weapon = w;
}