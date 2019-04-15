//使用するヘッダーファイル
#include"GameL\DrawTexture.h"
#include"GameL\HitBoxManager.h"
#include"GameL\Audio.h"
#include"GameHead.h"
#include"ObjArrow.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
 CObjArrow::CObjArrow()
{

}
//イニシャライズ
void CObjArrow::Init()
{
	/*m_eff.m_top = 32;
	m_eff.m_left = 0;
	m_eff.m_right = 32;
	m_eff.m_bottom = 64;
	m_ani = 0;
	m_ani_time = 0;
	m_vx = -1.0f;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_x, m_y, 32, 32, ELEMENT_PLAYER, OBJ_ARROW, 1);*/
}
//アクション
void CObjArrow::Action()
{
	/*//Resourcesの描画物のRECT
	m_eff = GetBulletEffec(&m_ani, &m_ani_time, m_del, 2);

	//弾丸消滅処理 -----
	if (m_del == true)
	{
		//着弾アニメーション終了で本当にオブジェクトを破棄
		if (m_ani == 4)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}

		return;//消滅処理は、ここでアクションメソッドを終了させる
	}

	//弾丸実行処理　-----
	m_vx += 1.0f;
	m_x += m_vx;

	//弾丸のHitBox更新用ポインター取得
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);          //HitBoxの位置を弾丸の位置をに更新

									//当たり判定を行うオブジェクト情報郡
	int data_base[6] =
	{
		OBJ_ENEMY,
		OBJ_ATTACK_ENEMY,
		OBJ_SIN_ENEMY,
		OBJ_DIFFUSION_ENEMY,
		OBJ_HOMING_ENEMY,
		OBJ_BOSS_ENEMY,
	};

	//オブジェクト情報郡と当たり判定行い。当たっていれば削除
	for (int i = 0; i < 6; i++)
	{
		if (hit->CheckObjNameHit(data_base[i]) != nullptr)
		{
			Audio::Start(3);      //着弾音を鳴らす

			m_del = true;                //消滅実行
			hit->SetInvincibility(true);//当たり判定無効
		}
	}*/

}

//ドロー
void CObjArrow::Draw()
{
	//描画カラー情報　R=RED G=Green B=Blue A=alpha(透過情報）
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };


	//アニメーションRECT情報
	RECT_F src;//描画元切り取り位置
	RECT_F dst;//描画先表示位置

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 61.0f;
	dst.m_bottom = 16.0f;

	//弾丸の状態で描画を変更
	//if (m_del == true)
	//{
		//着弾アニメーション描画
		//Draw::Draw(0, &m_eff, &dst, c, 0.0f);
	//}
	//else
	//{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 61.0f;
		src.m_bottom = 16.0f;
		//0番目に登録したグラフィックをsrc・dst・cの情報を元に描画
		Draw::Draw(5, &dst, &src, c, 0.0f);
}
