/*
* keyboard
*	�L�[���͂𗘗p�����I�u�W�F�N�g�̈ړ�
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

int main() {
	// �I�u�W�F�N�g�̍��W
	float2 position = window::center();

	// �I�u�W�F�N�g(��`)�̒�`
	rect object(float2{ 128,128 });

	// �I�u�W�F�N�g�̐F�Ȃǂ�ݒ�
	object.colored(palette::white).centered(object.size() / 2);
	while (sys::update()) {
		// �\���L�[���������Ă���Ԃ�
		if (keyboard::Left.press()) {
			// x���W�𖈃t���[�����炷
			position.x -= 4;
		}

		// �\���L�[���������Ă���Ԃ�
		else if (keyboard::Right.press()) {
			position.x += 4;
		}

		// �\���L�[���������Ă���Ԃ�
		if (keyboard::Up.press()) {
			position.y -= 4;
		}

		// �\���L�[���������Ă���Ԃ�
		else if (keyboard::Down.press()) {
			position.y += 4;
		}

		object.at(position).draw();
	}

	return 0;
}