#include "pch.h"
#include "CppUnitTest.h"
#include <DirectXMath.h>
#include <suika.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace suika;

#define MES(t) std::cout << t << std::endl;
constexpr double eps_d = 1e-14;
constexpr float eps_f = 1e-7f;
#define EQ_F(A,B) std::abs((((A)) - ((B)))) < eps_f, suika::to_wstring(std::format("A:{}={}, B:{}={}, diff:{}", #A, A, #B, B, math::abs((((A)) - ((B)))))).c_str()
#define EQ_D(A,B) std::abs((((A)) - ((B)))) < eps_d, suika::to_wstring(std::format("A:{}={}, B:{}={}, diff:{}", #A, A, #B, B, math::abs((((A)) - ((B)))))).c_str()

namespace string_test
{
	TEST_CLASS(Split) {
	public:
		TEST_METHOD(SplitUTF8) {
			using string = std::u8string;
			string              src = u8"abc,defg,hijkl,";
			std::vector<string> splited_a = suika::split(src, u8',', true);
			std::vector<string> splited_b = suika::split(src, u8',', false);

			std::vector<string> data_a = { u8"abc", u8"defg", u8"hijkl", u8"" };
			std::vector<string> data_b = { u8"abc", u8"defg", u8"hijkl" };

			Assert::IsTrue(data_a == splited_a);
			Assert::IsTrue(data_b == splited_b);
			Assert::IsTrue(data_a != splited_b);
			Assert::IsTrue(data_b != splited_a);
		}
		TEST_METHOD(SplitUTF16) {
			using string = std::u16string;
			string              src = u"abc,defg,hijkl,";
			std::vector<string> splited_a = suika::split(src, u',', true);
			std::vector<string> splited_b = suika::split(src, u',', false);

			std::vector<string> data_a = { u"abc", u"defg", u"hijkl", u"" };
			std::vector<string> data_b = { u"abc", u"defg", u"hijkl" };

			Assert::IsTrue(data_a == splited_a);
			Assert::IsTrue(data_b == splited_b);
			Assert::IsTrue(data_a != splited_b);
			Assert::IsTrue(data_b != splited_a);
		}
		TEST_METHOD(SplitUFT32) {
			using string = std::u32string;
			string              src = U"abc,defg,hijkl,";
			std::vector<string> splited_a = suika::split(src, U',', true);
			std::vector<string> splited_b = suika::split(src, U',', false);

			std::vector<string> data_a = { U"abc", U"defg", U"hijkl", U"" };
			std::vector<string> data_b = { U"abc", U"defg", U"hijkl" };

			Assert::IsTrue(data_a == splited_a);
			Assert::IsTrue(data_b == splited_b);
			Assert::IsTrue(data_a != splited_b);
			Assert::IsTrue(data_b != splited_a);
		}
		TEST_METHOD(SplitString) {
			using string = std::string;
			string              src = "abc,defg,hijkl,";
			std::vector<string> splited_a = suika::split(src, ',', true);
			std::vector<string> splited_b = suika::split(src, ',', false);

			std::vector<string> data_a = { "abc", "defg", "hijkl", "" };
			std::vector<string> data_b = { "abc", "defg", "hijkl" };

			Assert::IsTrue(data_a == splited_a);
			Assert::IsTrue(data_b == splited_b);
			Assert::IsTrue(data_a != splited_b);
			Assert::IsTrue(data_b != splited_a);
		}
		TEST_METHOD(SplitWString) {
			using string = std::wstring;
			string              src = L"abc,defg,hijkl,";
			std::vector<string> splited_a = suika::split(src, L',', true);
			std::vector<string> splited_b = suika::split(src, L',', false);

			std::vector<string> data_a = { L"abc", L"defg", L"hijkl", L"" };
			std::vector<string> data_b = { L"abc", L"defg", L"hijkl" };

			Assert::IsTrue(data_a == splited_a);
			Assert::IsTrue(data_b == splited_b);
			Assert::IsTrue(data_a != splited_b);
			Assert::IsTrue(data_b != splited_a);
		}
	};
	TEST_CLASS(Replace) {
	public:
		TEST_METHOD(ReplaceUTF8) {
			using string = std::u8string;
			string src = u8"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O";
			Assert::IsTrue(std::u8string(u8"ABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u8"abc", u8""));
			Assert::IsTrue(std::u8string(u8"abcabc‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u8"ABC", u8"abc"));
			Assert::IsTrue(std::u8string(u8"abcABC‚í‚ğ‚ñ123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u8"‚ ‚¢‚¤", u8"‚í‚ğ‚ñ"));
			Assert::IsTrue(std::u8string(u8"abcABC‚ ‚¢‚¤456‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u8"123", u8"456"));
			Assert::IsTrue(std::u8string(u8"abcABC‚ ‚¢‚¤123‚S‚T‚Uˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u8"‚P‚Q‚R", u8"‚S‚T‚U"));
			Assert::IsTrue(std::u8string(u8"abcABC‚ ‚¢‚¤123‚P‚Q‚RlŒÜ˜Z a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u8"ˆê“ñO", u8"lŒÜ˜Z"));
			Assert::IsTrue(std::u8string(u8"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO abc A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u8"a b c", u8"abc"));
			Assert::IsTrue(std::u8string(u8"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u8"A B C ", u8""));
			Assert::IsTrue(std::u8string(u8"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñOabcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO") == suika::replace_string(src, u8" ", u8""));
			Assert::IsTrue(std::u8string(u8"abcABC‚ i‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  i ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u8"‚¢", u8"i"));
		}
		TEST_METHOD(ReplaceUTF16) {
			using string = std::u16string;
			string src = u"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O";
			Assert::IsTrue(std::u16string(u"ABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u"abc", u""));
			Assert::IsTrue(std::u16string(u"abcabc‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u"ABC", u"abc"));
			Assert::IsTrue(std::u16string(u"abcABC‚í‚ğ‚ñ123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u"‚ ‚¢‚¤", u"‚í‚ğ‚ñ"));
			Assert::IsTrue(std::u16string(u"abcABC‚ ‚¢‚¤456‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u"123", u"456"));
			Assert::IsTrue(std::u16string(u"abcABC‚ ‚¢‚¤123‚S‚T‚Uˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u"‚P‚Q‚R", u"‚S‚T‚U"));
			Assert::IsTrue(std::u16string(u"abcABC‚ ‚¢‚¤123‚P‚Q‚RlŒÜ˜Z a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u"ˆê“ñO", u"lŒÜ˜Z"));
			Assert::IsTrue(std::u16string(u"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO abc A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u"a b c", u"abc"));
			Assert::IsTrue(std::u16string(u"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u"A B C ", u""));
			Assert::IsTrue(std::u16string(u"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñOabcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO") == suika::replace_string(src, u" ", u"").c_str());
			Assert::IsTrue(std::u16string(u"abcABC‚ i‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  i ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, u"‚¢", u"i"));
		}
		TEST_METHOD(ReplaceUTF32) {
			using string = std::u32string;
			string src = U"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O";
			Assert::IsTrue(std::u32string(U"ABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, U"abc", U""));
			Assert::IsTrue(std::u32string(U"abcabc‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, U"ABC", U"abc"));
			Assert::IsTrue(std::u32string(U"abcABC‚í‚ğ‚ñ123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, U"‚ ‚¢‚¤", U"‚í‚ğ‚ñ"));
			Assert::IsTrue(std::u32string(U"abcABC‚ ‚¢‚¤456‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, U"123", U"456"));
			Assert::IsTrue(std::u32string(U"abcABC‚ ‚¢‚¤123‚S‚T‚Uˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, U"‚P‚Q‚R", U"‚S‚T‚U"));
			Assert::IsTrue(std::u32string(U"abcABC‚ ‚¢‚¤123‚P‚Q‚RlŒÜ˜Z a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, U"ˆê“ñO", U"lŒÜ˜Z"));
			Assert::IsTrue(std::u32string(U"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO abc A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, U"a b c", U"abc"));
			Assert::IsTrue(std::u32string(U"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, U"A B C ", U""));
			Assert::IsTrue(std::u32string(U"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñOabcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO") == suika::replace_string(src, U" ", U"").c_str());
			Assert::IsTrue(std::u32string(U"abcABC‚ i‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  i ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O") == suika::replace_string(src, U"‚¢", U"i"));
		}
		TEST_METHOD(ReplaceString) {
			using string = std::string;
			string src = "abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O";
			Assert::AreEqual("ABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, "abc", "").c_str());
			Assert::AreEqual("abcabc‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, "ABC", "abc").c_str());
			Assert::AreEqual("abcABC‚í‚ğ‚ñ123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, "‚ ‚¢‚¤", "‚í‚ğ‚ñ").c_str());
			Assert::AreEqual("abcABC‚ ‚¢‚¤456‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, "123", "456").c_str());
			Assert::AreEqual("abcABC‚ ‚¢‚¤123‚S‚T‚Uˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, "‚P‚Q‚R", "‚S‚T‚U").c_str());
			Assert::AreEqual("abcABC‚ ‚¢‚¤123‚P‚Q‚RlŒÜ˜Z a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, "ˆê“ñO", "lŒÜ˜Z").c_str());
			Assert::AreEqual("abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO abc A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, "a b c", "abc").c_str());
			Assert::AreEqual("abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, "A B C ", "").c_str());
			Assert::AreEqual("abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñOabcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO", suika::replace_string(src, " ", "").c_str());
			Assert::AreEqual("abcABC‚ i‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  i ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, "‚¢", "i").c_str());
		}
		TEST_METHOD(ReplaceWString) {
			using string = std::wstring;
			string src = L"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O";
			Assert::AreEqual(L"ABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, L"abc", L"").c_str());
			Assert::AreEqual(L"abcabc‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, L"ABC", L"abc").c_str());
			Assert::AreEqual(L"abcABC‚í‚ğ‚ñ123‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, L"‚ ‚¢‚¤", L"‚í‚ğ‚ñ").c_str());
			Assert::AreEqual(L"abcABC‚ ‚¢‚¤456‚P‚Q‚Rˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, L"123", L"456").c_str());
			Assert::AreEqual(L"abcABC‚ ‚¢‚¤123‚S‚T‚Uˆê“ñO a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, L"‚P‚Q‚R", L"‚S‚T‚U").c_str());
			Assert::AreEqual(L"abcABC‚ ‚¢‚¤123‚P‚Q‚RlŒÜ˜Z a b c A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, L"ˆê“ñO", L"lŒÜ˜Z").c_str());
			Assert::AreEqual(L"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO abc A B C ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, L"a b c", L"abc").c_str());
			Assert::AreEqual(L"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO a b c ‚  ‚¢ ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, L"A B C ", L"").c_str());
			Assert::AreEqual(L"abcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñOabcABC‚ ‚¢‚¤123‚P‚Q‚Rˆê“ñO", suika::replace_string(src, L" ", L"").c_str());
			Assert::AreEqual(L"abcABC‚ i‚¤123‚P‚Q‚Rˆê“ñO a b c A B C ‚  i ‚¤ 1 2 3 ‚P ‚Q ‚R ˆê “ñ O", suika::replace_string(src, L"‚¢", L"i").c_str());
		}
		};
	TEST_CLASS(Convert) {
	public:
		TEST_METHOD(ToUTF8) {
			using utf8 = std::u8string;
			using utf16 = std::u16string;
			using utf32 = std::u32string;
			using string = std::string;
			using wstring = std::wstring;

			utf8    u8 = u8"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			utf16   u16 = u"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			utf32   u32 = U"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			string  s = "‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			wstring w = L"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";

			utf8 c16 = suika::to_u8string(u16);
			utf8 c32 = suika::to_u8string(u32);
			utf8 cst = suika::to_u8string(s);
			utf8 cws = suika::to_u8string(w);

			Assert::IsTrue(u8 == c16);
			Assert::IsTrue(u8 == c32);
			Assert::IsTrue(u8 == cst);
			Assert::IsTrue(u8 == cws);

			//Assert::AreEqual(u8.c_str(), c16.c_str());
			//Assert::AreEqual(u8.c_str(), c32.c_str());
			//Assert::AreEqual(u8.c_str(), cst.c_str());
			//Assert::AreEqual(u8.c_str(), cws.c_str());
		}
		TEST_METHOD(ToUTF16) {
			using utf8 = std::u8string;
			using utf16 = std::u16string;
			using utf32 = std::u32string;
			using string = std::string;
			using wstring = std::wstring;

			utf8    u8 = u8"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			utf16   u16 = u"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			utf32   u32 = U"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			string  s = "‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			wstring w = L"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";

			auto c8 = suika::to_u16string(u8);
			auto c32 = suika::to_u16string(u32);
			auto cst = suika::to_u16string(s);
			auto cws = suika::to_u16string(w);

			Assert::IsTrue(u16 == c8);
			Assert::IsTrue(u16 == c32);
			Assert::IsTrue(u16 == cst);
			Assert::IsTrue(u16 == cws);

			//Assert::AreEqual(u16.c_str(), c8.c_str());
			//Assert::AreEqual(u16.c_str(), c32.c_str());
			//Assert::AreEqual(u16.c_str(), cst.c_str());
			//Assert::AreEqual(u16.c_str(), cws.c_str());
		}
		TEST_METHOD(ToUTF32) {
			using utf8 = std::u8string;
			using utf16 = std::u16string;
			using utf32 = std::u32string;
			using string = std::string;
			using wstring = std::wstring;

			utf8    u8 = u8"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			utf16   u16 = u"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			utf32   u32 = U"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			string  s = "‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			wstring w = L"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";

			auto c8 = suika::to_u32string(u8);
			auto c16 = suika::to_u32string(u16);
			auto cst = suika::to_u32string(s);
			auto cws = suika::to_u32string(w);

			Assert::IsTrue(u32 == c8);
			Assert::IsTrue(u32 == c16);
			Assert::IsTrue(u32 == cst);
			Assert::IsTrue(u32 == cws);
		}
		TEST_METHOD(ToString) {
			using utf8 = std::u8string;
			using utf16 = std::u16string;
			using utf32 = std::u32string;
			using string = std::string;
			using wstring = std::wstring;

			utf8    u8 = u8"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			utf16   u16 = u"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			utf32   u32 = U"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			string  s = "‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			wstring w = L"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";

			string c8 = suika::to_string(u8);
			string c16 = suika::to_string(u16);
			string c32 = suika::to_string(u32);
			string cw = suika::to_string(w);

			Assert::AreEqual(s, c8);
			Assert::AreEqual(s.c_str(), c8.c_str());
			Assert::AreEqual(s, c16);
			Assert::AreEqual(s.c_str(), c16.c_str());
			Assert::AreEqual(s, c32);
			Assert::AreEqual(s.c_str(), c32.c_str());
			Assert::AreEqual(s, cw);
			Assert::AreEqual(s.c_str(), cw.c_str());
		}
		TEST_METHOD(ToWString) {
			using utf8 = std::u8string;
			using utf16 = std::u16string;
			using utf32 = std::u32string;
			using string = std::string;
			using wstring = std::wstring;

			utf8    u8 = u8"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			utf16   u16 = u"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			utf32   u32 = U"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			string  s = "‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";
			wstring w = L"‚ ‚ß‚ñ‚Ú ‚ ‚©‚¢‚È@‚ ‚¢‚¤‚¦‚¨-123,‚S‚T‚Uµ”ª‹ã";

			wstring c8 = suika::to_wstring(u8);
			wstring c16 = suika::to_wstring(u16);
			wstring c32 = suika::to_wstring(u32);
			wstring cs = suika::to_wstring(s);

			Assert::AreEqual(w, c8);
			Assert::AreEqual(w.c_str(), c8.c_str());
			Assert::AreEqual(w, c16);
			Assert::AreEqual(w.c_str(), c16.c_str());
			Assert::AreEqual(w, c32);
			Assert::AreEqual(w.c_str(), c32.c_str());
			Assert::AreEqual(w, cs);
			Assert::AreEqual(w.c_str(), cs.c_str());
		}
	};
}

namespace vector_test {
	template<concepts::numbers T>
	matrix<T> to_matrix(DirectX::XMMATRIX m) {
		matrix<T> ret(4, 4, 0);
		for (int i = 0; i < 4; i++) {
			ret.at(i, 0) = m.r[i].m128_f32[0];
			ret.at(i, 1) = m.r[i].m128_f32[1];
			ret.at(i, 2) = m.r[i].m128_f32[2];
			ret.at(i, 3) = m.r[i].m128_f32[3];
		}
		return ret;
	}

	bool eq_f(matrix<float> a, matrix<float> b) {
		if (a.size() != b.size()) return false;
		for (uint i = 0; i < a.size().y; i++) {
			for (uint j = 0; j < a.size().x; j++) {
				if (std::abs(a.at(i, j) - b.at(i, j)) >= eps_f * 100) {
					return false;
				}
			}
		}

		return true;
	}
	bool eq_d(matrix<double> a, matrix<double> b) {
		if (a.size() != b.size()) return false;
		for (uint i = 0; i < a.size().y; i++) {
			for (uint j = 0; j < a.size().x; j++) {
				if (std::abs(a.at(i, j) - b.at(i, j)) >= eps_f * 100) {
					return false;
				}
			}
		}

		return true;
	}

	TEST_CLASS(MatrixOperation) {
public:
	TEST_METHOD(Mul_Vec2) {
		suika::vector2<int> v(1, 2);
		suika::vector2<int> a(5, 11);
		suika::matrix<int> m(2, 2, {
			1,2,
			3,4
			});
		Assert::IsTrue(m*v == a);

		suika::vector2<float> vf(1.0f, 2.0f);
		suika::vector2<float> af(5.0f, 11.0f);
		suika::matrix<float> mf(2, 2, {
			1.0f,2.0f,
			3.0f,4.0f
			});
		Assert::IsTrue(mf*vf == af);

		suika::vector2<double> vd(1.0, 2.0);
		suika::vector2<double> ad(5.0, 11.0);
		suika::matrix<double> md(2, 2, {
			1.0,2.0,
			3.0,4.0
			});
		Assert::IsTrue(md*vd == ad);
	}

	TEST_METHOD(Mul_Vec3) {
		suika::vector3<int> v(1, 2, 3);
		suika::vector3<int> a(14, 32, 50);
		suika::matrix<int> m(3, 3, {
			1,2,3,
			4,5,6,
			7,8,9
			});
		Assert::IsTrue(m * v == a);

		suika::vector3<float> vf(1.0f, 2.0f, 3.0f);
		suika::vector3<float> af(14.0f, 32.0f, 50.0f);
		suika::matrix<float> mf(3, 3, {
			1.0f,2.0f,3.0f,
			4.0f,5.0f,6.0f,
			7.0f,8.0f,9.0f
			});
		Assert::IsTrue(mf * vf == af);

		suika::vector3<double> vd(1.0, 2.0, 3.0);
		suika::vector3<double> ad(14.0, 32.0, 50.0);
		suika::matrix<double> md(3, 3, {
			1.0,2.0,3.0,
			4.0,5.0,6.0,
			7.0,8.0,9.0
			});
		Assert::IsTrue(md * vd == ad);
	}

	TEST_METHOD(Mul_Matrix) {
		suika::matrix<int> m1(2, 3, {
			1,2,3,
			4,5,6
			});
		suika::matrix<int> m2(3, 2, {
			7,8,
			9,10,
			11,12
			});
		suika::matrix<int> a(2, 2, {
			58,64,
			139,154
			});
		Assert::IsTrue(vector::mul(m1, m2) == a);

		suika::matrix<float> m1f(2, 3, {
			1.0f,2.0f,3.0f,
			4.0f,5.0f,6.0f
			});
		suika::matrix<float> m2f(3, 2, {
			7.0f,8.0f,
			9.0f,10.0f,
			11.0f,12.0f
			});
		suika::matrix<float> af(2, 2, {
			58.0f,64.0f,
			139.0f,154.0f
			});
		Assert::IsTrue(vector::mul(m1f, m2f) == af);

		suika::matrix<double> m1d(2, 3, {
			1.0,2.0,3.0,
			4.0,5.0,6.0
			});
		suika::matrix<double> m2d(3, 2, {
			7.0,8.0,
			9.0,10.0,
			11.0,12.0
			});
		suika::matrix<double> ad(2, 2, {
			58.0,64.0,
			139.0,154.0
			});
		Assert::IsTrue(vector::mul(m1d, m2d) == ad);
	}

	TEST_METHOD(Transpose) {
		suika::matrix<int> m(2, 3, {
			1,2,3,
			4,5,6
			});
		suika::matrix<int> a(3, 2, {
			1,4,
			2,5,
			3,6
			});
		Assert::IsTrue(vector::transpose(m) == a);

		suika::matrix<float> mf(2, 3, {
			1.0f,2.0f,3.0f,
			4.0f,5.0f,6.0f
			});
		suika::matrix<float> af(3, 2, {
			1.0f,4.0f,
			2.0f,5.0f,
			3.0f,6.0f
			});
		Assert::IsTrue(vector::transpose(mf) == af);

		suika::matrix<double> md(2, 3, {
			1.0,2.0,3.0,
			4.0,5.0,6.0
			});
		suika::matrix<double> ad(3, 2, {
			1.0,4.0,
			2.0,5.0,
			3.0,6.0
			});
		Assert::IsTrue(vector::transpose(md) == ad);
	}

	TEST_METHOD(Identity) {
		suika::matrix<int> i1(1, 1, { 1 });
		suika::matrix<int> i2(2, 2, {
					1,0,
					0,1
			});
		suika::matrix<int> i3(3, 3, {
					1,0,0,
					0,1,0,
					0,0,1
			});
		suika::matrix<int> i4(4, 4, {
					1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					0,0,0,1
			});
		Assert::IsTrue(vector::identity<int>(1) == i1);
		Assert::IsTrue(vector::identity<int>(2) == i2);
		Assert::IsTrue(vector::identity<int>(3) == i3);
		Assert::IsTrue(vector::identity<int>(4) == i4);


		suika::matrix<float> i1f(1, 1, { 1.0f });
		suika::matrix<float> i2f(2, 2, {
					1.0f,0.0f,
					0.0f,1.0f
			});
		suika::matrix<float> i3f(3, 3, {
					1.0f,0.0f,0.0f,
					0.0f,1.0f,0.0f,
					0.0f,0.0f,1.0f
			});
		suika::matrix<float> i4f(4, 4, {
					1.0f,0.0f,0.0f,0.0f,
					0.0f,1.0f,0.0f,0.0f,
					0.0f,0.0f,1.0f,0.0f,
					0.0f,0.0f,0.0f,1.0f
			});
		Assert::IsTrue(vector::identity<float>(1) == i1f);
		Assert::IsTrue(vector::identity<float>(2) == i2f);
		Assert::IsTrue(vector::identity<float>(3) == i3f);
		Assert::IsTrue(vector::identity<float>(4) == i4f);

		suika::matrix<double> i1d(1, 1, { 1.0 });
		suika::matrix<double> i2d(2, 2, {
					1.0,0.0,
					0.0,1.0
			});
		suika::matrix<double> i3d(3, 3, {
					1.0,0.0,0.0,
					0.0,1.0,0.0,
					0.0,0.0,1.0
			});
		suika::matrix<double> i4d(4, 4, {
					1.0,0.0,0.0,0.0,
					0.0,1.0,0.0,0.0,
					0.0,0.0,1.0,0.0,
					0.0,0.0,0.0,1.0
			});
		Assert::IsTrue(vector::identity<double>(1) == i1d);
		Assert::IsTrue(vector::identity<double>(2) == i2d);
		Assert::IsTrue(vector::identity<double>(3) == i3d);
		Assert::IsTrue(vector::identity<double>(4) == i4d);
	}

	TEST_METHOD(Inverse) {
		suika::matrix<int> m(1, 1, { 2 });
		suika::matrix<int> a(1, 1, { 0 });
		Assert::IsTrue(vector::inverse(m) == a);

		suika::matrix<float> mf(1, 1, { 2.0f });
		suika::matrix<float> af(1, 1, { 0.5f });
		Assert::IsTrue(vector::inverse(mf) == af);

		suika::matrix<double> md(1, 1, { 2.0 });
		suika::matrix<double> ad(1, 1, { 0.5 });
		Assert::IsTrue(vector::inverse(md) == ad);

		m = suika::matrix<int>(2, 2, {
			2,1,
			5,3
			});
		a = suika::matrix<int>(2, 2, {
			3,-1,
			-5,2
			});
		Assert::IsTrue(vector::inverse(m) == a);

		mf = suika::matrix<float>(2, 2, {
			2.0f, 1.0f,
			5.0f, 3.0f
			});
		af = suika::matrix<float>(2, 2, {
			3.0f,-1.0f,
			-5.0f, 2.0f
			});
		Assert::IsTrue(vector::inverse(mf) == af);

		md = suika::matrix<double>(2, 2, {
			2.0,1.0,
			5.0,3.0
			});
		ad = suika::matrix<double>(2, 2, {
			3.0,-1.0,
			-5.0,2.0
			});
		Assert::IsTrue(vector::inverse(md) == ad);



		m = suika::matrix<int>(3, 3, {
			0,-1,1,
			-1,4,-2,
			1,-2,1
			});
		a = suika::matrix<int>(3, 3, {
			0,1,2,
			1,1,1,
			2,1,1
			});
		matrix<int> t = vector::inverse(m);
		Assert::IsTrue(t == a);

		mf = suika::matrix<float>(3, 3, {
			0.0f,-1.0f,1.0f,
			-1.0f,4.0f,-2.0f,
			1.0f,-2.0f,1.0f
			});
		af = suika::matrix<float>(3, 3, {
			0.0f,1.0f,2.0f,
			1.0f,1.0f,1.0f,
			2.0f,1.0f,1.0f
			});
		matrix<float> tf = vector::inverse(mf);
		Assert::IsTrue(tf == af);

		md = suika::matrix<double>(3, 3, {
			0.0,-1.0,1.0,
			-1.0,4.0,-2.0,
			1.0,-2.0,1.0
			});
		ad = suika::matrix<double>(3, 3, {
			0.0,1.0,2.0,
			1.0,1.0,1.0,
			2.0,1.0,1.0
			});
		matrix<double> td = vector::inverse(md);
		Assert::IsTrue(td == ad);

		m = suika::matrix<int>(4, 4, {
			1,1,1,-1,
			1,1,-1,1,
			1,-1,1,1,
			-1,1,1,1
			});
		a = suika::matrix<int>(4, 4, 0);
		Assert::IsTrue(vector::inverse(m) == a);

		mf = suika::matrix<float>(4, 4, {
			1.0f,1.0f,1.0f,-1.0f,
			1.0f,1.0f,-1.0f,1.0f,
			1.0f,-1.0f,1.0f,1.0f,
			-1.0f,1.0f,1.0f,1.0f
			});
		af = suika::matrix<float>(4, 4, {
			0.25f,0.25f,0.25f,-0.25f,
			0.25f,0.25f,-0.25f,0.25f,
			0.25f,-0.25f,0.25f,0.25f,
			-0.25f,0.25f,0.25f,0.25f
			});
		Assert::IsTrue(vector::inverse(mf) == af);

		md = suika::matrix<double>(4, 4, {
			1.0,1.0,1.0,-1.0,
			1.0,1.0,-1.0,1.0,
			1.0,-1.0,1.0,1.0,
			-1.0,1.0,1.0,1.0
			});
		ad = suika::matrix<double>(4, 4, {
			0.25,0.25,0.25,-0.25,
			0.25,0.25,-0.25,0.25,
			0.25,-0.25,0.25,0.25,
			-0.25,0.25,0.25,0.25
			});
		Assert::IsTrue(vector::inverse(md) == ad);
	}

	TEST_METHOD(Determinant) {
		suika::matrix<int> m(1, 1, { 2 });
		double a = 2;
		Assert::IsTrue(a == vector::determinant(m));

		suika::matrix<float> mf(1, 1, { 2.0f });
		double af = 2.0;
		Assert::IsTrue(af == vector::determinant(mf));

		suika::matrix<double> md(1, 1, { 2.0 });
		double ad = 2.0;
		Assert::IsTrue(ad == vector::determinant(md));

		m = suika::matrix<int>(2, 2, {
			2,1,
			5,3
			});
		a = 1;
		Assert::IsTrue(a == vector::determinant(m));

		mf = suika::matrix<float>(2, 2, {
			2.0f, 1.0f,
			5.0f, 3.0f
			});
		af = 1.0f;
		Assert::IsTrue(af == vector::determinant(mf));

		md = suika::matrix<double>(2, 2, {
			2.0,1.0,
			5.0,3.0
			});
		ad = 1.0;
		Assert::IsTrue(ad == vector::determinant(md));

		m = suika::matrix<int>(3, 3, {
			0,-1,1,
			-1,4,-2,
			1,-2,1
			});
		a = -1;
		auto t = vector::determinant(m);
		Assert::IsTrue(a == t);

		mf = suika::matrix<float>(3, 3, {
			0.0f,-1.0f,1.0f,
			-1.0f,4.0f,-2.0f,
			1.0f,-2.0f,1.0f
			});
		af = -1.0f;
		Assert::IsTrue(af == vector::determinant(mf));

		md = suika::matrix<double>(3, 3, {
			0.0,-1.0,1.0,
			-1.0,4.0,-2.0,
			1.0,-2.0,1.0
			});
		ad = -1.0;
		Assert::IsTrue(ad == vector::determinant(md));

		m = suika::matrix<int>(4, 4, {
			1,1,1,-1,
			1,1,-1,1,
			1,-1,1,1,
			-1,1,1,1
			});
		a = -16;
		Assert::IsTrue(a == vector::determinant(m));

		mf = suika::matrix<float>(4, 4, {
			1.0f,1.0f,1.0f,-1.0f,
			1.0f,1.0f,-1.0f,1.0f,
			1.0f,-1.0f,1.0f,1.0f,
			-1.0f,1.0f,1.0f,1.0f
			});
		af = -16.0f;
		Assert::IsTrue(af == vector::determinant(mf));

		md = suika::matrix<double>(4, 4, {
			1.0,1.0,1.0,-1.0,
			1.0,1.0,-1.0,1.0,
			1.0,-1.0,1.0,1.0,
			-1.0,1.0,1.0,1.0
			});
		ad = -16.0;
		Assert::IsTrue(ad == vector::determinant(md));
	}
	};

	TEST_CLASS(Transform) {
		TEST_METHOD(Rotation) {
			matrix<int> mi(4, 1, {
				1,
				1,
				1,
				1,
				});
			matrix<float> mf(4, 1, {
				1.0f,
				1.0f,
				1.0f,
				1.0f,
				});
			matrix<double> md(4, 1, {
				1.0,
				1.0,
				1.0,
				1.0,
				});

			float roll = PI_F, pitch = PI_F, yaw = PI_F;
			matrix<int> ri = vector::rotation<int>(roll, pitch, yaw);
			auto ai = to_matrix<int>(DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll));
			Assert::IsTrue(ai == ri);

			auto rf = vector::rotation<float>(roll, pitch, yaw);
			auto af = to_matrix<float>(DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll));
			Assert::IsTrue(eq_f(rf,af));

			auto rd = vector::rotation<double>(roll, pitch, yaw);
			auto ad = to_matrix<double>(DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll));
			Assert::IsTrue(eq_d(rd,ad));

			roll = 0, pitch = 0, yaw = 0;
			ri = vector::rotation<int>(roll, pitch, yaw);
			ai = to_matrix<int>(DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll));
			
			Assert::IsTrue(ai == ri);

			rf = vector::rotation<float>(roll, pitch, yaw);
			af = to_matrix<float>(DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll));
			
			Assert::IsTrue(eq_f(rf, af));

			rd = vector::rotation<double>(roll, pitch, yaw);
			ad = to_matrix<double>(DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll));
			
			Assert::IsTrue(eq_d(rd, ad));

			roll = PI / 2, pitch = PI / 2, yaw = PI / 2;
			ri = vector::rotation<int>(roll, pitch, yaw);
			ai = to_matrix<int>(DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll));
			
			Assert::IsTrue(ai == ri);

			rf = vector::rotation<float>(roll, pitch, yaw);
			af = to_matrix<float>(DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll));
			
			Assert::IsTrue(eq_f(rf, af));

			rd = vector::rotation<double>(roll, pitch, yaw);
			ad = to_matrix<double>(DirectX::XMMatrixRotationRollPitchYaw(pitch,yaw,roll));
			
			Assert::IsTrue(eq_d(rd, ad));
		}

		TEST_METHOD(Scalling) {
			matrix<int> mi(4, 1, {
				1,
				1,
				1,
				1,
				});
			matrix<float> mf(4, 1, {
				1.0f,
				1.0f,
				1.0f,
				1.0f,
				});
			matrix<double> md(4, 1, {
				1.0,
				1.0,
				1.0,
				1.0,
				});


			double x = 1.3, y = 1.4, z = 1.5;
			matrix<int> ri = vector::scalling<int>(x, y, z);
			auto ai = to_matrix<int>(DirectX::XMMatrixScaling(x, y, z));
			Assert::IsTrue(ai == ri);

			auto rf = vector::scalling<float>(x, y, z);
			auto af = to_matrix<float>(DirectX::XMMatrixScaling(x, y, z));
			Assert::IsTrue(eq_f(rf, af));

			auto rd = vector::scalling<double>(x, y, z);
			auto ad = to_matrix<double>(DirectX::XMMatrixScaling(x, y, z));
			Assert::IsTrue(eq_d(rd, ad));

			x = 0.3, y = 0.8, z = 0.2;
			ri = vector::scalling<int>(x, y, z);
			ai = to_matrix<int>(DirectX::XMMatrixScaling(x, y, z));
			
			Assert::IsTrue(ai == ri);

			rf = vector::scalling<float>(x, y, z);
			af = to_matrix<float>(DirectX::XMMatrixScaling(x, y, z));
			
			Assert::IsTrue(eq_f(rf, af));

			rd = vector::scalling<double>(x, y, z);
			ad = to_matrix<double>(DirectX::XMMatrixScaling(x, y, z));
			
			Assert::IsTrue(eq_d(rd, ad));

			x = 0, y = 0, z = 0;
			ri = vector::scalling<int>(x, y, z);
			ai = to_matrix<int>(DirectX::XMMatrixScaling(x, y, z));
			
			Assert::IsTrue(ai == ri);

			rf = vector::scalling<float>(x, y, z);
			af = to_matrix<float>(DirectX::XMMatrixScaling(x, y, z));
			
			Assert::IsTrue(eq_f(rf, af));

			rd = vector::scalling<double>(x, y, z);
			ad = to_matrix<double>(DirectX::XMMatrixScaling(x, y, z));
			
			Assert::IsTrue(eq_d(rd, ad));

			x = 1, y = 1, z = 1;
			ri = vector::scalling<int>(x, y, z);
			ai = to_matrix<int>(DirectX::XMMatrixScaling(x, y, z));
			
			Assert::IsTrue(ai == ri);

			rf = vector::scalling<float>(x, y, z);
			af = to_matrix<float>(DirectX::XMMatrixScaling(x, y, z));
			
			Assert::IsTrue(eq_f(rf, af));

			rd = vector::scalling<double>(x, y, z);
			ad = to_matrix<double>(DirectX::XMMatrixScaling(x, y, z));
			
			Assert::IsTrue(eq_d(rd, ad));
		}

		TEST_METHOD(Affine) {
			vector3<double> origine(0, 0, 0);
			vector3<double> position(1, 2, 3);
			vector3<double> rotation(PI / 4.0, PI / 3.0, PI / 2.0);
			vector3<double> scale(1, 2, 4);

			DirectX::XMVECTOR origine_v = { 0,0,0 };
			DirectX::XMVECTOR position_v = { 1,2,3 };
			DirectX::XMVECTOR rotation_v = DirectX::XMQuaternionRotationRollPitchYawFromVector({ PI / 4.0, PI / 3.0, PI / 2.0 });
			DirectX::XMVECTOR scale_v = { 1,2,4 };

			auto ri = vector::affine_transformation<int>(origine, position, rotation, scale);
			auto ai = to_matrix<int>(DirectX::XMMatrixAffineTransformation(scale_v, origine_v, rotation_v, position_v));
			Assert::IsTrue(ai == ri);

			auto rf = vector::affine_transformation<float>(origine, position, rotation, scale);
			auto af = to_matrix<float>(DirectX::XMMatrixAffineTransformation(scale_v, origine_v, rotation_v, position_v));
			Assert::IsTrue(eq_f(rf, af));

			auto rd = vector::affine_transformation<double>(origine, position, rotation, scale);
			auto ad = to_matrix<double>(DirectX::XMMatrixAffineTransformation(scale_v, origine_v, rotation_v, position_v));
			Assert::IsTrue(eq_d(rd, ad));
		}
	};
}

namespace math_test {
	TEST_CLASS(Found) {
	public:
		TEST_METHOD(Exp) {
			define INF_I = std::numeric_limits<int32>::max();
			define INF_F = std::numeric_limits<float>::infinity();
			define INF_D = std::numeric_limits<double>::infinity();
			define E_F = std::numbers::e_v<float>;
			define E_D = std::numbers::e_v<double>;


			Assert::AreEqual(1.0, math::exp(0));
			Assert::AreEqual(1.0, math::exp(0.0));
			Assert::AreEqual(1.0f, math::exp(0.0f));

			Assert::AreEqual(E_D, math::exp(1));
			Assert::AreEqual(E_D, math::exp(1.0));
			Assert::AreEqual(E_F, math::exp(1.0f));

			Assert::AreEqual(INF_D, math::exp(INF_I));
			Assert::AreEqual(INF_D, math::exp(INF_D));
			Assert::AreEqual(INF_F, math::exp(INF_F));

			int32  i = 1;
			float  f = 1.0f;
			double d = 1.0;
			Assert::IsTrue(EQ_D(std::exp(i), math::exp(i)));
			Assert::IsTrue(EQ_D(std::exp(d), math::exp(d)));
			Assert::IsTrue(EQ_F(std::exp(f), math::exp(f)));
			Assert::IsTrue(EQ_D(std::exp(-i), math::exp(-i)));
			Assert::IsTrue(EQ_D(std::exp(-d), math::exp(-d)));
			Assert::IsTrue(EQ_F(std::exp(-f), math::exp(-f)));


			//45ˆÈ~failed
			i = 40;
			f = 40.0f;
			d = 40.0;
			Assert::IsTrue(EQ_D(std::exp(-i), math::exp(-i)));
			Assert::IsTrue(EQ_D(std::exp(-d), math::exp(-d)));
			Assert::IsTrue(EQ_F(std::exp(-f), math::exp(-f)));

			Assert::IsTrue(abs(std::exp(i) - math::exp(i)) < 60);
			Assert::IsTrue(abs(std::exp(f) - math::exp(f)) < 60);
			Assert::IsTrue(abs(std::exp(d) - math::exp(d)) < 60);

			f = 0.1f;
			d = 0.1;
			Assert::IsTrue(EQ_D(std::exp(d), math::exp(d)));
			Assert::IsTrue(EQ_F(std::exp(f), math::exp(f)));
			Assert::IsTrue(EQ_D(std::exp(-d), math::exp(-d)));
			Assert::IsTrue(EQ_F(std::exp(-f), math::exp(-f)));

			f = 0.0000000015f;
			d = 0.0000000015;
			Assert::IsTrue(EQ_D(std::exp(d), math::exp(d)));
			Assert::IsTrue(EQ_F(std::exp(f), math::exp(f)));
			Assert::IsTrue(EQ_D(std::exp(-d), math::exp(-d)));
			Assert::IsTrue(EQ_F(std::exp(-f), math::exp(-f)));
		}
		TEST_METHOD(Log) {
			define INF_I = std::numeric_limits<int32>::max();
			define INF_F = std::numeric_limits<float>::infinity();
			define INF_D = std::numeric_limits<double>::infinity();
			define E_F = std::numbers::e_v<float>;
			define E_D = std::numbers::e_v<double>;

			int32  i = 0;
			float  f = 0.0f;
			double d = 0.0;
			{
				auto fi = [&]() {math::log(i); };
				auto ff = [&]() {math::log(f); };
				auto fd = [&]() {math::log(d); };
				Assert::ExpectException<int>(fi);
				Assert::ExpectException<int>(ff);
				Assert::ExpectException<int>(fd);
			}
			{
				i = -10;
				f = -10.0f;
				d = -10.0;
				auto fi = [&]() {math::log(i); };
				auto ff = [&]() {math::log(f); };
				auto fd = [&]() {math::log(d); };
				Assert::ExpectException<int>(fi);
				Assert::ExpectException<int>(ff);
				Assert::ExpectException<int>(fd);
			}
			f = E_F;
			d = E_D;
			Assert::IsTrue(EQ_D(1.0, math::log(d)));
			Assert::IsTrue(EQ_D(1.0f, math::log(f)));


			i = INF_I;
			f = INF_F;
			d = INF_D;
			Assert::AreEqual(static_cast<double>(INF_I), math::log(INF_I));
			Assert::AreEqual(INF_D, math::log(INF_D));
			Assert::AreEqual(INF_F, math::log(INF_F));


			i = 5;
			f = 5.0f;
			d = 5.0;
			Assert::IsTrue(EQ_D(std::log(i), math::log(i)));
			Assert::IsTrue(EQ_D(std::log(d), math::log(d)));
			Assert::IsTrue(EQ_F(std::log(f), math::log(f)));


			i = 500;
			f = 500.0f;
			d = 500.0;
			Assert::IsTrue(EQ_D(std::log(i), math::log(i)));
			Assert::IsTrue(EQ_D(std::log(d), math::log(d)));
			Assert::IsTrue(EQ_F(std::log(f), math::log(f)));

			int32  ni = 2;
			float  nf = 2.0f;
			double nd = 2.0;
			Assert::IsTrue(EQ_D(std::log2(i), math::log_n(i, ni)));
			Assert::IsTrue(EQ_D(std::log2(d), math::log_n(d, nd)));
			Assert::IsTrue(EQ_F(std::log2(f), math::log_n(f, nf)));

			ni = 10;
			nf = 10.0f;
			nd = 10.0;
			Assert::IsTrue(EQ_D(std::log10(i), math::log_n(i, ni)));
			Assert::IsTrue(EQ_D(std::log10(d), math::log_n(d, nd)));
			Assert::IsTrue(EQ_F(std::log10(f), math::log_n(f, nf)));
		}
		TEST_METHOD(Pow) {
			int32  xi = 5, yi = 6;
			float  xf = 5, yf = 6;
			double xd = 5, yd = 6;
			Assert::IsTrue(EQ_D(std::pow(xi, yi), math::pow(xi, yi)));
			Assert::IsTrue(EQ_F(std::pow(xf, yf), math::pow(xf, yf)));
			Assert::IsTrue(EQ_D(std::pow(xd, yd), math::pow(xd, yd)));

			xi = 5, yi = -2;
			xf = 5, yf = -2;
			xd = 5, yd = -2;
			Assert::IsTrue(EQ_D(std::pow(xi, yi), math::pow(xi, yi)));
			Assert::IsTrue(EQ_F(std::pow(xf, yf), math::pow(xf, yf)));
			Assert::IsTrue(EQ_D(std::pow(xd, yd), math::pow(xd, yd)));

			xf = 2, yf = 1.5;
			xd = 2, yd = 1.5;
			Assert::IsTrue(EQ_F(std::pow(xf, yf), math::pow(xf, yf)));
			Assert::IsTrue(EQ_D(std::pow(xd, yd), math::pow(xd, yd)));

			xf = 2, yf = -1.5;
			xd = 2, yd = -1.5;
			Assert::IsTrue(EQ_F(std::pow(xf, yf), math::pow(xf, yf)));
			Assert::IsTrue(EQ_D(std::pow(xd, yd), math::pow(xd, yd)));
		}
	};
	TEST_CLASS(Triangle) {
	public:
		TEST_METHOD(Sin) {
			constexpr double p_d = suika::PI / 6.0;
			constexpr float  p_f = suika::PI_F / 6.0f;
			for (int i = 0; i < 12; i++) {
				Assert::IsTrue(EQ_D(std::sin(i * p_d), math::sin(i * p_d)));
				Assert::IsTrue(EQ_F(std::sin(i * p_f), math::sin(i * p_f)));
			}
		}
		TEST_METHOD(Cos) {
			constexpr double p_d = suika::PI / 6.0;
			constexpr float  p_f = suika::PI_F / 6.0f;
			for (int i = 0; i < 12; i++) {
				Assert::IsTrue(EQ_D(std::cos(i * p_d), math::cos(i * p_d)));
				Assert::IsTrue(EQ_F(std::cos(i * p_f), math::cos(i * p_f)));
			}
		}
		TEST_METHOD(Tan) {
			constexpr double p_d = suika::PI;
			constexpr float  p_f = suika::PI_F;
			for (int i = 0; i < 12; i++) {
				if (i == 3 || i == 9) {
					Assert::IsTrue(math::abs(math::tan(i * p_d / 6.0)) > 1e14);
					Assert::IsTrue(math::abs(math::tan(i * p_f / 6.0f)) > 1e7);
				}
				else {
					Assert::IsTrue(math::abs(std::tan(i * p_d / 6.0) - math::tan(i * p_d / 6.0)) < eps_d);
					Assert::IsTrue(math::abs(std::tan(i * p_f / 6.0f) - math::tan(i * p_f / 6.0f)) < eps_f);
					Assert::IsTrue(EQ_D(std::tan(i * p_d / 6.0), math::tan(i * p_d / 6.0)));
					Assert::IsTrue(EQ_F(std::tan(i * p_f / 6.0f), math::tan(i * p_f / 6.0f)));
				}
			}
		}
		TEST_METHOD(Arcsin) {
			for (int i = -10; i <= 10; i++) {
				Assert::IsTrue(EQ_D(std::asin(i * 0.1), math::asin(i * 0.1)));
				Assert::IsTrue(EQ_F(std::asin(i * 0.1f), math::asin(i * 0.1f)));
			}
		}
		TEST_METHOD(Arccos) {
			for (int i = -10; i <= 10; i++) {
				Assert::IsTrue(EQ_D(std::acos(i * 0.1), math::acos(i * 0.1)));
				Assert::IsTrue(EQ_F(std::acos(i * 0.1f), math::acos(i * 0.1f)));
			}
		}
		TEST_METHOD(Arctan) {
			for (int i = -10; i <= 10; i++) {
				MES(i << ':' << ' ' << std::atan(i * 0.1) << ' ' << math::atan(i * 0.1));
				Assert::IsTrue(EQ_D(std::atan(i * 0.1), math::atan(i * 0.1)));
				Assert::IsTrue(EQ_F(std::atan(i * 0.1f), math::atan(i * 0.1f)));
			}
		}
	};
	TEST_CLASS(Rounding) {
	public:
		TEST_METHOD(Ceil) {
			for (int i = -20; i <= 20; i++) {
				double d = i * 0.1;
				Assert::AreEqual(std::ceil(d), math::ceil(d));
			}
		}
		TEST_METHOD(Floor) {
			for (int i = -20; i <= 20; i++) {
				double d = i * 0.1;
				Assert::AreEqual(std::floor(d), math::floor(d));
			}
		}
		TEST_METHOD(Round) {
			for (int i = -20; i <= 20; i++) {
				double d = i * 0.1;
				Assert::AreEqual(std::round(d), math::round(d));
			}
		}
		TEST_METHOD(Trunc) {
			for (int i = -20; i <= 20; i++) {
				double d = i * 0.1;
				Assert::AreEqual(std::trunc(d), math::trunc(d));
			}
		}
	};
	TEST_CLASS(Other) {
	public:
		TEST_METHOD(Abs) {
			int32  i = 5;
			float  f = 5.0f;
			double d = 5.0;

			Assert::AreEqual(i, math::abs(i));
			Assert::AreEqual(i, math::abs(-i));

			Assert::AreEqual(f, math::abs(f));
			Assert::AreEqual(f, math::abs(-f));

			Assert::AreEqual(d, math::abs(d));
			Assert::AreEqual(d, math::abs(-d));
		}
		TEST_METHOD(Sqrt) {
			for (int i = 0; i <= 100; i++) {
				Assert::IsTrue(EQ_D(std::sqrt(i), math::sqrt(i)));
			}
		}
		TEST_METHOD(Fmod) {
			define e = 2.1;
			define ef = 2.1f;
			for (int i = -20; i <= 20; i++) {
				double d = i * 0.1;
				float df = i * 0.1f;
				Assert::AreEqual(std::fmod(d, e), math::fmod(d, e));
				Assert::AreEqual(std::fmod(df, ef), math::fmod(df, ef));
			}
		}
	};
}
