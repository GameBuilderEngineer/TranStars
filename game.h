#pragma once
#include "main.h"

enum SceneList {
	TITLE,
	//////////////// ����ǉ�
	SELECT_MODE,
	CHOOSE_STAGE,
	//////////////// �����܂�
	STAGE,
	RESULT,
	SCENE_NUM,
};

void initializeGame();
void updateGame();
void drawGame();
void printGame();
void unInitializeGame();
//�@����ǉ�
void changeScene(SceneList newscene);
//�u�����܂����F����
//void changeScene(SceneList newscene);//����0518 ++�ȊO�̕��@�ŃV�[���J�� �X�e�[�W�ɓ��钼�O�E����ɂ�������������������̂�game��ʂ����ɃV�[����ς��Ȃ��łق���
int getScene();//�|�C���^���擾���āA���ڃV�[����ς���͖̂����ŁBkanno
//�@�����܂�