#include"Menu.h"
#include"SceneMgr.h"
#include"DxLib.h"
#include"Input.h"

#define PI 3.1415926535897932384626433832795f



static int mImageCone;	
static int mImagegame;
static int mImagehelp;
static int mImageend;



static int MenuNumber = 0;  //���j���[�J�[�\���Ǘ��p�ϐ�

static int mSoundsSelect;   //���t�@�C���i�[�p�ϐ�
static int mSoundsMove;

// ������
void Menu_Initialize() {
 
    mImageCone = LoadGraph("images/Tmino.png");
    mImagegame = LoadGraph("images/game.png");
    mImagehelp = LoadGraph("images/help.png");
    mImageend = LoadGraph("images/end.png");


    mSoundsSelect = LoadSoundMem("sounds/����A�{�^������8.mp3");    //���艹�̃��[�h
    mSoundsMove = LoadSoundMem("sounds/�J�[�\���ړ�11.mp3");    //�ړ����̃��[�h

    // �a�f�l�Đ�
    PlayMusic("sounds/yamiyouen.mp3", DX_PLAYTYPE_LOOP);
}

// �I������
void Menu_Finalize() {

    
    DeleteGraph(mImageCone);
    
    DeleteGraph(mImagegame);
    DeleteGraph(mImagehelp);
    DeleteGraph(mImageend);


    StopSoundMem(mSoundsSelect);
    StopSoundMem(mSoundsMove);

    // �a�f�l��~
    StopMusic();
}

//�X�V
void Menu_Update() {
    //���j���[�J�[�\���ړ�����
    if (iKeyFlg & PAD_INPUT_DOWN) {
        PlaySoundMem(mSoundsMove, DX_PLAYTYPE_BACK);
        if (++MenuNumber > 2) MenuNumber = 0;
    }
    if (iKeyFlg & PAD_INPUT_UP) {
        PlaySoundMem(mSoundsMove, DX_PLAYTYPE_BACK);
        if (--MenuNumber < 0) MenuNumber = 2;
    }

    if (iKeyFlg == PAD_INPUT_1) { //Z�L�[��������Ă�����
        switch (MenuNumber) {       //�V�[���ɂ���ď����𕪊�
        case 0:    //���݂̉�ʂ����j���[�Ȃ�
            SceneMgr_ChangeScene(eScene_Game); //�V�[�����Q�[����ʂɕύX
            break;
        case 1:
            SceneMgr_ChangeScene(eScene_Help); //�V�[�����w���v��ʂɕύX
            break;
        case 2:
            SceneMgr_ChangeScene(eScene_End);	//�V�[�����G���h��ʂɕύX
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