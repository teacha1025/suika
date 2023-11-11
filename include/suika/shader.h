#pragma once
#include "def.h"
#include "string.h"
namespace suika {
	const string SHAPE_VERTEX = "shape";
	const string SHAPE_PIXEL  = "shape";
	const string TEXTURE_VERTEX = "texture";
	const string TEXTURE_PIXEL  = "texture";

	/// <summary>
	/// HLSL�t�@�C������o�[�e�b�N�X�V�F�[�_�[���쐬
	/// </summary>
	/// <param name="key_input">�V�F�[�_�[�t�@�C���ւ̃p�X</param>
	/// <param name="name">�V�F�[�_�[�̓o�^��</param>
	void add_vs(const string& key_input, const string& name);
	/// <summary>
	/// �V�F�[�_�[�z�񂩂�o�[�e�b�N�X�V�F�[�_�[���쐬
	/// </summary>
	/// <param name="key_input">�V�F�[�_�[�z��</param>
	/// <param name="size">�V�F�[�_�[�z��̗v�f��</param>
	/// <param name="name">�V�F�[�_�[�̓o�^��</param>
	void add_vs(const void* key_input, size_t size, const string& name);
	/// <summary>
	/// HLSL�t�@�C������s�N�Z���V�F�[�_�[���쐬
	/// </summary>
	/// <param name="key_input">�V�F�[�_�[�t�@�C���ւ̃p�X</param>
	/// <param name="name">�V�F�[�_�[�̓o�^��</param>
	void add_ps(const string& key_input, const string& name);
	/// <summary>
	/// �V�F�[�_�[�z�񂩂�s�N�Z���V�F�[�_�[���쐬
	/// </summary>
	/// <param name="key_input">�V�F�[�_�[�z��</param>
	/// <param name="size">�V�F�[�_�[�z��̗v�f��</param>
	/// <param name="name">�V�F�[�_�[�̓o�^��</param>
	void add_ps(const void* key_input, size_t size, const string& name);

	/// <summary>
	/// �o�[�e�b�N�X�V�F�[�_�[��ݒ肷��
	/// </summary>
	/// <param name="name">�V�F�[�_�[�̓o�^��</param>
	void set_vs(const string& name);
	/// <summary>
	/// �s�N�Z���V�F�[�_�[��ݒ肷��
	/// </summary>
	/// <param name="name">�V�F�[�_�[�̓o�^��</param>
	void set_ps(const string& name);

}