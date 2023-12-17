/*
* animator
*	�摜��ǂݍ���ŃA�j���[�V������\������
*/

#include "../include/suika.h"
using namespace suika;

//�A�v���P�[�V�����̏�����
void init() {
	//log.log�Ƀ��O���o�͂���
	suika::log.set(true, "log.log");

	//�E�B���h�E�̐ݒ�
	window::background(palette::yellowgreen);
	window::title("APP");
	window::vsync(true);
}

int main() {
	//�摜��ǂݍ����x:4,y:3�ɕ������A�j���[�V�������쐬����
	animator anm("resource/test2.bmp", { 4,3 });

	//id:0�̃A�j���[�V�����Ƀt���[���ԍ�0,1,2,1��8�t���[�����ƂɐؑւŐݒ肷��
	anm.add(0, { 0,1,2,1 }, 8);
	anm.add(1, { 3,4,5,4 }, 8);
	anm.add(2, { 7,8,9 }, 8);

	//�����A�j���[�V������0�ɂ��A��ʒ�����4�{�Ɋg�債�ĕ\������
	anm.at({ 640,480 }).centered(anm.rect().size()/2).extended(4).set(0);

	uint state = 0;
	while (sys::update()) {
		//�X�y�[�X�L�[�ŃA�j���[�V������؂�ւ���
		if (keyboard::Space.down()) {
			state++;
			state %= 3;
			anm.set(state);
		}

		//���t���[���J�E���g��1�i�߂ĕ`�悷��
		anm.updated(1);
		anm.draw();
	}

	return 0;
}