#include"Menu.h"
#include"SceneMgr.h"
#include"DxLib.h"
#include"Input.h"

#define PI 3.1415926535897932384626433832795f



static int mImageCone;	
static int mImagegame;
static int mImagehelp;
static int mImageend;



static int MenuNumber = 0;  //メニューカーソル管理用変数

static int mSoundsSelect;   //音ファイル格納用変数
static int mSoundsMove;

// 初期化
void Menu_Initialize() {
 
    mImageCone = LoadGraph("images/Tmino.png");
    mImagegame = LoadGraph("images/game.png");
    mImagehelp = LoadGraph("images/help.png");
    mImageend = LoadGraph("images/end.png");


    mSoundsSelect = LoadSoundMem("sounds/決定、ボタン押下8.mp3");    //決定音のロード
    mSoundsMove = LoadSoundMem("sounds/カーソル移動11.mp3");    //移動音のロード

    // ＢＧＭ再生
    PlayMusic("sounds/yamiyouen.mp3", DX_PLAYTYPE_LOOP);
}

// 終了処理
void Menu_Finalize() {

    
    DeleteGraph(mImageCone);
    
    DeleteGraph(mImagegame);
    DeleteGraph(mImagehelp);
    DeleteGraph(mImageend);


    StopSoundMem(mSoundsSelect);
    StopSoundMem(mSoundsMove);

    // ＢＧＭ停止
    StopMusic();
}

//更新
void Menu_Update() {
    //メニューカーソル移動処理
    if (iKeyFlg & PAD_INPUT_DOWN) {
        PlaySoundMem(mSoundsMove, DX_PLAYTYPE_BACK);
        if (++MenuNumber > 2) MenuNumber = 0;
    }
    if (iKeyFlg & PAD_INPUT_UP) {
        PlaySoundMem(mSoundsMove, DX_PLAYTYPE_BACK);
        if (--MenuNumber < 0) MenuNumber = 2;
    }

    if (iKeyFlg == PAD_INPUT_1) { //Zキーが押されていたら
        switch (MenuNumber) {       //シーンによって処理を分岐
        case 0:    //現在の画面がメニューなら
            SceneMgr_ChangeScene(eScene_Game); //シーンをゲーム画面に変更
            break;
        case 1:
            SceneMgr_ChangeScene(eScene_Help); //シーンをヘルプ画面に変更
            break;
        case 2:
            SceneMgr_ChangeScene(eScene_End);	//シーンをエンド画面に変更
            break;

        }
    }

}


void Menu_Draw() {
   
    
    DrawGraph(350, 330, mImagegame, FALSE);
    DrawGraph(350, 370, mImagehelp, FALSE);
    DrawGraph(350, 410, mImageend, FALSE);
    SetFontSize(100);
    DrawString(200, 100, "spartan", GetColor(255, 255, 255));
    
    DrawRotaGraph(320, 345 + MenuNumber * 40, 0.7f, PI / 2, mImageCone, TRUE);
}