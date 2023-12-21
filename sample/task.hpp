/*
* task
*	�����̋�`���^�X�N���g�p���Ĉړ�������
*/

#include "../include/suika.h"
using namespace suika;

//�A�v���P�[�V�����̏�����
void init() {
	//log.log�Ƀ��O���o�͂���
	suika::log.set(true, "log.log");

	//�E�B���h�E�̐ݒ�
	window::background(palette::black);
	window::title("APP");
	window::vsync(true);
}

// ��`�ړ��̃^�X�N
task<void> task_move(rect& r) {
	point<float> pos = r.position();
	while (true) {
		r.at(pos);
		
		//�����𒆒f
		co_yield{};

		//��`���ړ�
		pos += {1, 1};
	}
}

int main() {
	//128x128�̋�`���쐬
	rect r1({ 128,128 });
	r1.colored(palette::orange).at({ 0,0 });

	rect r2({ 128,128 });
	r2.colored(palette::greenyellow).at({ 640,0 });

	//�^�X�N���쐬
	auto task1 = task_move(r1);
	auto task2 = task_move(r2);

	while (sys::update()) {
		//�^�X�N���ĊJ
		task1.resume();
		task2.resume();

		//��`��`��
		r1.draw();
		r2.draw();
	}

	return 0;
}