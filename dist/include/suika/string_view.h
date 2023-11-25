// -----------------------------------------------------------
// 
// string_view
// 
// Copyright 2023 teacha1025
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// -----------------------------------------------------------

#pragma once

#include <string_view>
#include <string>
#include <format>

#include "def.h"
#include "codecvt.h"

namespace suika {
	class string;
	class string_view {
		friend string;
	public:
		using string_view_type = std::u32string_view;
		using traits_type = typename string_view_type::traits_type;
		using value_type = typename string_view_type::value_type;
		using char_t = typename value_type;
		using pointer = typename string_view_type::pointer;
		using const_pointer = typename string_view_type::const_pointer;
		using reference = typename string_view_type::reference;
		using const_reference = typename string_view_type::const_reference;
		using const_iterator = typename string_view_type::const_iterator;
		using iterator = typename string_view_type::iterator;
		using const_reverse_iterator = typename string_view_type::const_reverse_iterator;
		using reverse_iterator = typename string_view_type::reverse_iterator;
		using size_type = typename string_view_type::size_type;
		using difference_type = typename string_view_type::difference_type;

		using str = std::string;
		using wstr = std::wstring;
		using utf8 = std::u8string;
		using utf16 = std::u16string;
		using utf32 = std::u32string;
		using str_view = std::string_view;
		using wstr_view = std::wstring_view;
		using utf8_view = std::u8string_view;
		using utf16_view = std::u16string_view;
		using utf32_view = std::u32string_view;
		static constexpr size_type npos{ static_cast<size_type>(-1) };

		/// <summary>
		/// ��̕�����r���[���쐬
		/// </summary>
		constexpr string_view() noexcept = default;

		/// <summary>
		/// �R�s�[�R���X�g���N�^
		/// </summary>
		/// <param name="str">�R�s�[���镶����r���[</param>
		constexpr string_view(const string_view& str) noexcept = default;

		/// <summary>
		/// UTF32�����񂩂當����r���[���쐬
		/// </summary>
		/// <param name="str">������</param>
		constexpr string_view(const char_t* str) noexcept {
			_str = string_view_type(str);
		}
#if _HAS_CXX23
		constexpr string_view(nullptr_t) = delete;
#endif
		/// <summary>
		/// UTF32������Ƃ��̒������當����r���[���쐬
		/// </summary>
		/// <param name="str">������</param>
		/// <param name="len">����</param>
		constexpr string_view(const char_t* str, size_type len) noexcept {
			_str = string_view_type(str, len);
		}

		/// <summary>
		/// UTF32������C�e���[�^���當����r���[���쐬
		/// </summary>
		/// <typeparam name="_it">�C�e���[�^</typeparam>
		/// <typeparam name="_end">�C�e���[�^</typeparam>
		/// <param name="begin">�n�[</param>
		/// <param name="end">�I�[</param>
		template<class _it, class _end>
		constexpr string_view(_it begin, _end end) noexcept(noexcept(end - begin)) {
			_str = string_view_type(begin, end);
		}

		/// <summary>
		/// UTF32������r���[���當����r���[���쐬
		/// </summary>
		/// <param name="str">������r���[</param>
		constexpr string_view(const string_view_type& str) noexcept {
			_str = str;
		}

		/// <summary>
		/// ���[�u�R���X�g���N�^
		/// </summary>
		/// <param name="str">������r���[</param>
		constexpr string_view(string_view&& str) noexcept = default;

		/// <summary>
		/// �R�s�[������Z�q
		/// </summary>
		/// <param name="str">������r���[</param>
		/// <returns></returns>
		constexpr string_view& operator=(const string_view& str) noexcept = default;

		/// <summary>
		/// �������ϊ�
		/// </summary>
		/// <returns>shift-jis������</returns>
		NODISCARD str to_string() const;

		/// <summary>
		/// �������ϊ�
		/// </summary>
		/// <returns>���C�h������</returns>
		NODISCARD wstr to_wstring() const;

		/// <summary>
		/// �������ϊ�
		/// </summary>
		/// <returns>UTF8������</returns>
		NODISCARD utf8 to_utf8() const;

		/// <summary>
		/// �������ϊ�
		/// </summary>
		/// <returns>UTF16������</returns>
		NODISCARD utf16 to_utf16() const;

		/// <summary>
		/// �������ϊ�
		/// </summary>
		/// <returns>UTF32������</returns>
		NODISCARD utf32 to_utf32() const;

#pragma region STD_FUNCTION
		/// <summary>
		/// �n�[�C�e���[�^���擾
		/// </summary>
		/// <returns>�n�[�C�e���[�^</returns>
		NODISCARD constexpr const_iterator begin() const noexcept {
			return _str.begin();
		}

		/// <summary>
		/// �I�[�C�e���[�^���擾
		/// </summary>
		/// <returns>�I�[�C�e���[�^</returns>
		NODISCARD constexpr const_iterator end() const noexcept {
			return _str.end();
		}

		/// <summary>
		/// �n�[�C�e���[�^���擾
		/// </summary>
		/// <returns>�n�[�C�e���[�^</returns>
		NODISCARD constexpr const_iterator cbegin() const noexcept {
			return _str.cbegin();
		}

		/// <summary>
		/// �I�[�C�e���[�^���擾
		/// </summary>
		/// <returns>�I�[�C�e���[�^</returns>
		NODISCARD constexpr const_iterator cend() const noexcept {
			return _str.cend();
		}

		/// <summary>
		/// �t���n�[�C�e���[�^���擾
		/// </summary>
		/// <returns>�t���n�[�C�e���[�^</returns>
		NODISCARD constexpr const_reverse_iterator rbegin() const noexcept {
			return _str.rbegin();
		}

		/// <summary>
		/// �t���I�[�C�e���[�^���擾
		/// </summary>
		/// <returns>�t���I�[�C�e���[�^</returns>
		NODISCARD constexpr const_reverse_iterator rend() const noexcept {
			return _str.rend();
		}

		/// <summary>
		/// �t���n�[�C�e���[�^���擾
		/// </summary>
		/// <returns>�t���n�[�C�e���[�^</returns>
		NODISCARD constexpr const_reverse_iterator crbegin() const noexcept {
			return _str.crbegin();
		}

		/// <summary>
		/// �t���I�[�C�e���[�^���擾
		/// </summary>
		/// <returns>�t���I�[�C�e���[�^</returns>
		NODISCARD constexpr const_reverse_iterator crend() const noexcept {
			return _str.crend();
		}

		/// <summary>
		/// ������̒������擾
		/// </summary>
		/// <returns>������̒���</returns>
		NODISCARD constexpr size_type size() const noexcept {
			return _str.size();
		}

		/// <summary>
		/// ������̒������擾
		/// </summary>
		/// <returns>������̒���</returns>
		NODISCARD constexpr size_type length() const noexcept {
			return _str.length();
		}

		/// <summary>
		/// ������̒������擾
		/// </summary>
		/// <returns>������̒���</returns>
		NODISCARD constexpr size_type max_size() const noexcept {
			return _str.max_size();
		}

		/// <summary>
		/// �����񂪋󂩂ǂ������擾
		/// </summary>
		/// <returns>�����񂪋󂩂ǂ���</returns>
		NODISCARD constexpr bool empty() const noexcept {
			return _str.empty();
		}
		
		/// <summary>
		/// �C�ӂ̈ʒu�̕������擾
		/// </summary>
		/// <param name="pos"></param>
		/// <returns>pos�Ԗڂ̕���</returns>
		NODISCARD constexpr const_reference operator[](size_type pos) const noexcept {
			return _str[pos];
		}

		/// <summary>
		/// �C�ӂ̈ʒu�̕������擾
		/// </summary>
		/// <param name="pos"></param>
		/// <returns>pos�Ԗڂ̕���</returns>
		NODISCARD constexpr const_reference at(size_type pos) const {
			return _str.at(pos);
		}

		/// <summary>
		/// ������̐擪���擾
		/// </summary>
		/// <returns>������̐擪</returns>
		NODISCARD constexpr const_reference front() const noexcept {
			return _str.front();
		}

		/// <summary>
		/// ������̖������擾
		/// </summary>
		/// <returns>������̖���</returns>
		NODISCARD constexpr const_reference back() const noexcept {
			return _str.back();
		}

		/// <summary>
		/// �����z��\�����擾
		/// </summary>
		/// <returns>�����z��\��</returns>
		NODISCARD constexpr const_pointer data() const noexcept {
			return _str.data();
		}

		/// <summary>
		/// �擪�̕������폜
		/// </summary>
		/// <param name="n">�폜���镶����</param>
		NODISCARD constexpr void remove_prefix(size_type n) noexcept {
			_str.remove_prefix(n);
		}

		/// <summary>
		/// �����̕������폜
		/// </summary>
		/// <param name="n">�폜���镶����</param>
		NODISCARD constexpr void remove_suffix(size_type n) noexcept {
			_str.remove_suffix(n);
		}

		/// <summary>
		/// ����string_view�ƃf�[�^�����ւ���
		/// </summary>
		/// <param name="str">����ւ���string_view</param>
		NODISCARD constexpr void swap(string_view& str) noexcept {
			_str.swap(str._str);
		}

		/// <summary>
		/// ���̕�����ɁA���g�̕�������R�s�[����
		/// </summary>
		/// <param name="dest">�R�s�[��</param>
		/// <param name="count">�R�s�[���镶����</param>
		/// <param name="pos">�R�s�[���镶����̈ʒu</param>
		/// <returns>�R�s�[����������</returns>
		NODISCARD constexpr size_type copy(char_t* dest, size_type count, size_type pos = 0) const {
			return _str.copy(dest, count, pos);
		}

		/// <summary>
		/// ������̈ꕔ���擾
		/// </summary>
		/// <param name="pos">�擾���镶����̈ʒu</param>
		/// <param name="count">�擾���镶����</param>
		/// <returns>�擾����������</returns>
		NODISCARD constexpr string_view substr(size_type pos = 0, size_type count = string_view::npos) const {
			return _str.substr(pos, count);
		}

		/// <summary>
		/// ������̔�r
		/// </summary>
		/// <param name="str">��r���镶����</param>
		/// <returns>��r����</returns>
		NODISCARD constexpr int compare(string_view str) const noexcept {
			return _str.compare(str._str);
		}

		/// <summary>
		/// ������̔�r
		/// </summary>
		/// <param name="pos">��r���镶����̈ʒu</param>
		/// <param name="count">��r���镶����</param>
		/// <param name="str">��r���镶����</param>
		/// <returns>��r����</returns>
		NODISCARD constexpr int compare(size_type pos, size_type count, string_view str) const {
			return _str.compare(pos, count, str._str);
		}

		/// <summary>
		/// ������̔�r
		/// </summary>
		/// <param name="pos">��r���镶����̈ʒu</param>
		/// <param name="count">��r���镶����</param>
		/// <param name="str">��r���镶����</param>
		/// <param name="subpos">��r���镶����̈ʒu</param>
		/// <param name="subcount">��r���镶����</param>
		/// <returns>��r����</returns>
		NODISCARD constexpr int compare(size_type pos, size_type count, string_view str, size_type subpos, size_type subcount) const {
			return _str.compare(pos, count, str._str, subpos, subcount);
		}

		/// <summary>
		/// ������̔�r
		/// </summary>
		/// <param name="str">��r���镶����</param>
		/// <returns>��r����</returns>
		NODISCARD constexpr int compare(const_pointer str) const {
			return _str.compare(str);
		}

		/// <summary>
		/// ������̔�r
		/// </summary>
		/// <param name="pos">��r���镶����̈ʒu</param>
		/// <param name="count">��r���镶����</param>
		/// <param name="str">��r���镶����</param>
		NODISCARD constexpr int compare(size_type pos, size_type count, const_pointer str) const {
			return _str.compare(pos, count, str);
		}

		/// <summary>
		/// ������̔�r
		/// </summary>
		/// <param name="pos">��r���镶����̈ʒu</param>
		/// <param name="count">��r���镶����</param>
		/// <param name="str">��r���镶����</param>
		/// <param name="subcount">��r���镶����</param>
		NODISCARD constexpr int compare(size_type pos, size_type count, const_pointer str, size_type subcount) const {
			return _str.compare(pos, count, str, subcount);
		}

		/// <summary>
		/// �w��̕�����Ŏn�܂邩����
		/// </summary>
		/// <param name="str">���߂̕�����</param>
		/// <returns>�w��̕�����Ŏn�܂邩</returns>
		NODISCARD constexpr bool starts_with(string_view str) const noexcept {
			return _str.starts_with(str._str);
		}

		/// <summary>
		/// �w��̕�����Ŏn�܂邩����
		/// </summary>
		/// <param name="str">���߂̕���</param>
		/// <returns>�w��̕�����Ŏn�܂邩</returns>
		NODISCARD constexpr bool starts_with(char_t str) const noexcept {
			return _str.starts_with(str);
		}

		/// <summary>
		/// �w��̕�����Ŏn�܂邩����
		/// </summary>
		/// <param name="str">���߂̕�����</param>
		/// <returns>�w��̕�����Ŏn�܂邩</returns>
		NODISCARD constexpr bool starts_with(const_pointer str) const noexcept {
			return _str.starts_with(str);
		}

		/// <summary>
		/// �w��̕�����ŏI��邩����
		/// </summary>
		/// <param name="str">�I���̕�����</param>
		/// <returns>�w��̕�����ŏI��邩</returns>
		NODISCARD constexpr bool ends_with(string_view str) const noexcept {
			return _str.ends_with(str._str);
		}

		/// <summary>
		/// �w��̕�����ŏI��邩����
		/// </summary>
		/// <param name="str">�I���̕���</param>
		/// <returns>�w��̕�����ŏI��邩</returns>
		NODISCARD constexpr bool ends_with(char_t str) const noexcept {
			return _str.ends_with(str);
		}

		/// <summary>
		/// �w��̕�����ŏI��邩����
		/// </summary>
		/// <param name="str">�I���̕�����</param>
		/// <returns>�w��̕�����ŏI��邩</returns>
		NODISCARD constexpr bool ends_with(const_pointer str) const noexcept {
			return _str.ends_with(str);
		}

		/// <summary>
		/// �w��̕�������܂ނ�����
		/// </summary>
		/// <param name="str">�܂ޕ�����</param>
		/// <returns>�w��̕�������܂ނ�</returns>
		NODISCARD constexpr bool contains(string_view str) const noexcept {
			return _str.find(str._str) != string_view::npos;
		}

		/// <summary>
		/// �w��̕������܂ނ�����
		/// </summary>
		/// <param name="str">�܂ޕ���</param>
		/// <returns>�w��̕������܂ނ�</returns>
		NODISCARD constexpr bool contains(char_t str) const noexcept {
			return _str.find(str) != string_view::npos;
		}

		/// <summary>
		/// �w��̕�������܂ނ�����
		/// </summary>
		/// <param name="str">�܂ޕ�����</param>
		/// <returns>�w��̕�������܂ނ�</returns>
		NODISCARD constexpr bool contains(const_pointer str) const {
			return _str.find(str) != string_view::npos;
		}

		/// <summary>
		/// �w��̕����������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos����A*this�Ɋ܂܂�镔��������str���ŏ��Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find(string_view str, size_type pos = 0) const noexcept {
			return _str.find(str._str, pos);
		}

		/// <summary>
		/// �w��̕����������
		/// </summary>
		/// <param name="c">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos����A*this�Ɋ܂܂�镶��c���ŏ��Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find(char_t c, size_type pos = 0) const noexcept {
			return _str.find(c, pos);
		}

		/// <summary>
		/// �w��̕����������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <param name="n">�������镶����</param>
		/// <returns> �w�肵���ʒupos����A*this�Ɋ܂܂�镔��������str�̐擪n�������ŏ��Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.find(str, pos, n);
		}

		/// <summary>
		/// �w��̕����������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos����A*this�Ɋ܂܂�镔��������str���ŏ��Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find(const_pointer str, size_type pos) const noexcept {
			return _str.find(str, pos);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶���������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos���O�ŁA*this�Ɋ܂܂�镔��������str���Ō�Ɍ����ʒu</returns>
		NODISCARD constexpr size_type rfind(string_view str, size_type pos) const noexcept {
			return _str.rfind(str._str, pos);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶���������
		/// </summary>
		/// <param name="c">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos���O�ŁA*this�Ɋ܂܂�镶��c���Ō�Ɍ����ʒu</returns>
		NODISCARD constexpr size_type rfind(char_t c, size_type pos) const noexcept {
			return _str.rfind(c, pos);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶���������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <param name="n">�������镶����</param>
		/// <returns>�w�肵���ʒupos���O�ŁA*this�Ɋ܂܂�镔��������str�̐擪n�������Ō�Ɍ����ʒu</returns>
		NODISCARD constexpr size_type rfind(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.rfind(str, pos);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶���������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos���O�ŁA*this�Ɋ܂܂�镔��������str���Ō�Ɍ����ʒu</returns>
		NODISCARD constexpr size_type rfind(const_pointer str, size_type pos = 0) const noexcept{
			return _str.rfind(str, pos);
		}

		/// <summary>
		/// �ŏ��Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos����A������str���̂����ꂩ�̕������ŏ��Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find_first_of(string_view str, size_type pos = 0) const noexcept {
			return _str.find_first_of(str._str, pos);
		}

		/// <summary>
		/// �ŏ��Ɍ����w�蕶��������
		/// </summary>
		/// <param name="c">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos����A����c���ŏ��Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find_first_of(char_t c, size_type pos = 0) const noexcept {
			return _str.find_first_of(c, pos);
		}

		/// <summary>
		/// �ŏ��Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <param name="n">�������镶����</param>
		/// <returns> �w�肵���ʒupos����A������str�̐擪n�����̂����ꂩ�̕������ŏ��Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find_first_of(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.find_first_of(str, pos, n);
		}

		/// <summary>
		/// �ŏ��Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos����A������str���̂����ꂩ�̕������ŏ��Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find_first_of(const_pointer str, size_type pos) const noexcept {
			return _str.find_first_of(str, pos);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos���O�ŁA������str���̂����ꂩ�̕������Ō�Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find_last_of(string_view str, size_type pos = 0) const noexcept {
			return _str.find_last_of(str._str, pos);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶��������
		/// </summary>
		/// <param name="c">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos���O�ŁA����c���Ō�Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find_last_of(char_t c, size_type pos = 0) const noexcept {
			return _str.find_last_of(c, pos);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <param name="n">�������镶����</param>
		/// <returns> �w�肵���ʒupos���O�ŁA������str�̐擪n�����̂����ꂩ�̕������Ō�Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find_last_of(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.find_last_of(str, pos, n);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos���O�ŁA������str���̂����ꂩ�̕������Ō�Ɍ����ʒu</returns>
		NODISCARD constexpr size_type find_last_of(const_pointer str, size_type pos) const noexcept {
			return _str.find_last_of(str, pos);
		}

		/// <summary>
		/// �ŏ��Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos����A������str���̂�����̕����ɂ���v���Ȃ��ʒu</returns>
		NODISCARD constexpr size_type find_first_not_of(string_view str, size_type pos = 0) const noexcept {
			return _str.find_first_not_of(str._str, pos);
		}

		/// <summary>
		/// �ŏ��Ɍ����w�蕶��������
		/// </summary>
		/// <param name="c">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos����A����c�Ɉ�v���Ȃ��ŏ��̈ʒu</returns>
		NODISCARD constexpr size_type find_first_not_of(char_t c, size_type pos = 0) const noexcept {
			return _str.find_first_not_of(c, pos);
		}

		/// <summary>
		/// �ŏ��Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <param name="n">�������镶����</param>
		/// <returns> �w�肵���ʒupos����A������str�̐擪n�����̂����ꂩ�̕����ɂ���v���Ȃ��ŏ��̈ʒu</returns>
		NODISCARD constexpr size_type find_first_not_of(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.find_first_not_of(str, pos, n);
		}

		/// <summary>
		/// �ŏ��Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos����A������str���̂����ꂩ�̕����ɂ���v���Ȃ��ŏ��̈ʒu</returns>
		NODISCARD constexpr size_type find_first_not_of(const_pointer str, size_type pos) const noexcept {
			return _str.find_first_not_of(str, pos);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos���O�ŁA������str���̂����ꂩ�̕����ɂ���v���Ȃ��Ō�̈ʒu</returns>
		NODISCARD constexpr size_type find_last_not_of(string_view str, size_type pos = 0) const noexcept {
			return _str.find_last_not_of(str._str, pos);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶��������
		/// </summary>
		/// <param name="c">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos���O�ŁA����c�Ɉ�v���Ȃ��Ō�̈ʒu</returns>
		NODISCARD constexpr size_type find_last_not_of(char_t c, size_type pos = 0) const noexcept {
			return _str.find_last_not_of(c, pos);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <param name="n">�������镶����</param>
		/// <returns> �w�肵���ʒupos���O�ŁA������str�̐擪n�����̂����ꂩ�̕����ɂ���v���Ȃ��Ō�̈ʒu</returns>
		NODISCARD constexpr size_type find_last_not_of(const_pointer str, size_type pos, size_type n) const noexcept {
			return _str.find_last_not_of(str, pos, n);
		}

		/// <summary>
		/// �Ō�Ɍ����w�蕶��������
		/// </summary>
		/// <param name="str">�������镶����</param>
		/// <param name="pos">�������镶����̈ʒu</param>
		/// <returns>�w�肵���ʒupos���O�ŁA������str���̂����ꂩ�̕����ɂ���v���Ȃ��Ō�̈ʒu</returns>
		NODISCARD constexpr size_type find_last_not_of(const_pointer str, size_type pos) const noexcept {
			return _str.find_last_not_of(str, pos);
		}
#pragma endregion
#if __cpp_lib_three_way_comparison

		/// <summary>
		/// 3����r���Z�q
		/// </summary>
		/// <param name="rhs">��r�Ώ�</param>
		/// <returns>��r����</returns>
		NODISCARD constexpr std::strong_ordering operator <=>(const string_view& rhs) const noexcept = default;

#else
		/// <summary>
		/// ��r���Z�q
		/// </summary>
		/// <param name="rhs">��r�Ώ�</param>
		/// <returns>��r����</returns>
		NODISCARD friend constexpr bool operator ==(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) == 0);
		}

		/// <summary>
		/// ��r���Z�q
		/// </summary>
		/// <param name="rhs">��r�Ώ�</param>
		/// <returns>��r����</returns>
		NODISCARD friend constexpr bool operator !=(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) != 0);
		}

		/// <summary>
		/// ��r���Z�q
		/// </summary>
		/// <param name="rhs">��r�Ώ�</param>
		/// <returns>��r����</returns>
		NODISCARD friend constexpr bool operator <(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) < 0);
		}

		/// <summary>
		/// ��r���Z�q
		/// </summary>
		/// <param name="rhs">��r�Ώ�</param>
		/// <returns>��r����</returns>
		NODISCARD friend constexpr bool operator <=(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) <= 0);
		}

		/// <summary>
		/// ��r���Z�q
		/// </summary>
		/// <param name="rhs">��r�Ώ�</param>
		/// <returns>��r����</returns>
		NODISCARD friend constexpr bool operator >(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) > 0);
		}

		/// <summary>
		/// ��r���Z�q
		/// </summary>
		/// <param name="rhs">��r�Ώ�</param>
		/// <returns>��r����</returns>
		NODISCARD friend constexpr bool operator >=(string_view lhs, string_view rhs) noexcept {
			return (lhs.compare(rhs) >= 0);
		}

#endif

		size_t hash() const noexcept{
			return std::hash<string_view_type>()(_str);
		}
	private:
		string_view_type _str;
	};
}

namespace std {
	template <>
	inline void swap(suika::string_view& a, suika::string_view& b) noexcept {
		a.swap(b);
	}

	template <>
	struct hash<suika::string_view> {
		[[nodiscard]]
		size_t operator ()(const suika::string_view& value) const noexcept {
			return value.hash();
		}
	};

	template<>
	struct formatter<suika::string_view> : formatter<suika::string_view::str, suika::string_view::str::value_type> {
		auto format(suika::string_view str, format_context& ctx) const {
			return formatter<suika::string_view::str, suika::string_view::str::value_type>::format(str.to_string(), ctx);
		}
	};
}