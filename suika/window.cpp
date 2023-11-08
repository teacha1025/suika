#include <string>
#include <unordered_map>
#include <memory>
#include <windows.h>
#include "..\include\suika\def.h"

#include "..\include\suika\point.h"
#include "..\include\suika\color.h"
#include "..\include\suika\pallet.h"
#include "..\include\suika\logger.h"
#include "..\include\suika\canvas.h"

#include "..\include\suika\window.h"
#include "..\include\suika\string.h"

#include "d3d/device.hpp"
#include "..\include\suika\vertex.h"




namespace suika {
	namespace sys {
		extern bool exit_flag;
	}
	namespace window {
		template<class T>
		struct historical {
			T now, old = T();

			historical(const T& new_val) {
				old = now;
				now = new_val;
			}

			historical& operator=(const T& new_val) {
				old = now;
				now = new_val;
				return *this;
			}

			bool eq() const {
				return now == old;
			}

			operator T() const {
				return now;
			}
		};
		id default_id = nullptr;
		struct window {
			historical<point<uint>> _size = point<uint>{ 1280u, 960u };
			historical<point<double>> _rate = point<double>{ 1.0, 1.0 };
			historical<color> _bg = pallet::black;
			historical<bool> _fullscreen_flag = false;
			//historical<uint> _fullscreen_type = fullscreen_type::borderless | fullscreen_type::dotbydot;
			historical<string> _title = string("Application");
			std::shared_ptr<suika::canvas> _canvas = nullptr;
			HINSTANCE _hinstance = NULL;
			bool _isclosed = false;
			bool _vsync = false;
			MSG msg{};
		};
		std::unordered_map<id, window> window_list;

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
			case WM_DESTROY:
				PostQuitMessage(0);
				sys::exit_flag = true;
				return 0;
			}

			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		void SetClientBound(int x, int y, int width, int height, HWND hWnd) {
			RECT clientRect, windowRect;
			GetClientRect(hWnd, &clientRect);
			GetWindowRect(hWnd, &windowRect);

			windowRect.left = x;
			windowRect.top = y;
			clientRect.right = width;
			clientRect.bottom = height;


			AdjustWindowRect(
				&clientRect,
				static_cast<DWORD>(GetWindowLongPtr(hWnd, GWL_STYLE)),
				FALSE);

			SetWindowPos(
				hWnd,
				0,
				windowRect.left + clientRect.left,
				windowRect.top + clientRect.top,
				clientRect.right - clientRect.left,
				clientRect.bottom - clientRect.top,
				0);
		}

		void init() {
			window_list.insert(std::make_pair(static_cast<suika::window::id>(nullptr), window{}));
		}

		id create(const point<uint>& size, point<double> rate, const color& bg, const string& title, bool vsync) {
			static const uint x = (uint)GetSystemMetrics(SM_CXSCREEN);
			static const uint y = (uint)GetSystemMetrics(SM_CYSCREEN);

			auto lt = point<uint>(x, y); lt -= size; lt /= 2u;
			return create(size, rate, bg, title, vsync, lt);
		}
		id create(const point<uint>& size, point<double> rate, const color& bg, const string& title, bool vsync, const point<uint>& pos) {
			auto			  wtitle = title.to_wstring();
			std::wstring_view title_view = wtitle;
			HINSTANCE hinst = GetModuleHandle(NULL);
			WNDCLASS  wclass;
			wclass.style = CS_HREDRAW | CS_VREDRAW;
			wclass.lpfnWndProc = WndProc;
			wclass.cbClsExtra = 0;
			wclass.cbWndExtra = 0;
			wclass.hInstance = GetModuleHandle(NULL);
			wclass.hIcon = NULL;
			wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
			wclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wclass.lpszMenuName = NULL;
			wclass.lpszClassName = title_view.data();

			if (!RegisterClass(&wclass)) {
				//throw EXCEPT("ウィンドウの作成に失敗");
			}

			id hwnd = CreateWindow(
				title.to_wstring().data(),
				title.to_wstring().c_str(),
				WS_OVERLAPPEDWINDOW,
				static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x * rate.x), static_cast<int>(size.y * rate.y),
				NULL, NULL, wclass.hInstance, NULL);

			SetClientBound(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x * rate.x), static_cast<int>(size.y * rate.y), hwnd);

			ShowWindow(hwnd, SW_SHOW);
			UpdateWindow(hwnd);

			

			window wnd;
			wnd._size = size;
			wnd._rate = rate;
			wnd._title = title;
			wnd._bg = bg;
			wnd._bg.now.a = 255;
			wnd._fullscreen_flag = false;
			wnd._canvas = make_canvas(size,{0,0}, hwnd, wnd._bg.now);
			wnd._vsync = vsync;

			if (window_list.size() == 1ull) {
				default_id = hwnd;
				window_list.clear();
			}
			window_list.insert({ hwnd, wnd });
			log.info("window create");
			return hwnd;
		}

		bool process() {
			if (window_list.empty()) {
				return false;
			}
			for (auto& w : window_list) {
				if (PeekMessage(&w.second.msg, w.first == default_id ? NULL : w.first, 0, 0, PM_REMOVE)) {
					TranslateMessage(&w.second.msg);
					DispatchMessage(&w.second.msg);
				}
				if (w.second.msg.message == WM_QUIT) {
					return false;
				}
			}
			return true;
		}

		auto& param(id id) {
			if (!window_list.contains(id)) {
				throw ("存在しないウィンドウを参照しようとしました");
			}
			return window_list[id];
		}

		void flip() {
			if (window_list.empty()) {
				return;
			}
			for (auto& w : window_list) {
				w.second._canvas->present(w.second._vsync);
			}
		}

		void clear() {
			if (window_list.empty()) {
				return;
			}
			for (auto& w : window_list) {
				w.second._canvas->clear();
			}
		}

		void adapt_param();

		void size(const point<uint>& size, id id) {
			auto& p = param(id);
			p._size = size;
			adapt_param();
		}

		void fullscreen(bool flag, uint16 type) {
			//_fullscreen_flag = flag;
			//_fullscreen_type = type;
		}

		void extends(point<double> rate, id id) {
			auto& p = param(id);
			p._rate = rate;
			adapt_param();
		}

		void background(const color& bg_color, id id) {
			auto& p = param(id);
			p._bg = bg_color;
			adapt_param();
		}

		void title(const string& title, id id) {
			auto& p = param(id);
			p._title = title;
			adapt_param();
		}

		void canvas(const std::shared_ptr<suika::canvas>& canvas, id id) {
			auto& p = param(id);
			p._canvas = canvas;
			adapt_param();
		}

		void vsync(bool vsync, id id) {
			auto& p = param(id);
			p._vsync = vsync;
			adapt_param();
		}

		point<uint> size(id id) {
			auto p = param(id);
			return p._size;
		}

		point<double> center(id id) {
			auto p = param(id);
			return { p._size.now.x / 2.0, p._size.now.y / 2.0 };
		}

		bool fullscreen() {
			auto p = param(default_id);
			return p._fullscreen_flag;
		}

		point<double> extends(id id) {
			auto p = param(id);
			return p._rate;
		}

		color background(id id) {
			auto p = param(id);
			return p._bg;
		}

		string title(id id) {
			auto p = param(id);
			return p._title;
		}

		std::shared_ptr<suika::canvas> canvas(id id) {
			auto p = param(id);
			return p._canvas;
		}

		bool vsync(id id) {
			auto p = param(id);
			return p._vsync;
		}

		

		void adapt_param() {
			if (window_list.empty() || window_list.begin()->first == nullptr) {
				return;
			}
			for (const auto& p_ : window_list) {
				const auto& p = p_.second;

				/*if (!initialized) {
				}
				else*/ {
					/*if (!_fullscreen_flag.eq() || !_fullscreen_type.eq()) {
						if (p_.first == default_id) {
							if (_fullscreen_flag) {
								if (_fullscreen_type & fullscreen_type::borderless) {
									SetUseBorderlessWindowFlag(true);
									ChangeWindowMode(true);
								}
								else {
									ChangeWindowMode(false);
								}
							}
							else {
								ChangeWindowMode(true);
							}
						}
					}*/
					if (!p._bg.eq()) {
						//SetBackgroundColor(p._bg.now.r, p._bg.now.g, p._bg.now.b);
						p._canvas->bg_color = p._bg.now;
					}
					if (!p._title.eq()) {
						SetWindowText(p_.first, p._title.now.to_wstring().c_str());
					}
					if (!p._size.eq() || !p._rate.eq()) {
						if (p_.first == default_id) {
							//SetGraphMode(static_cast<int>(p.size.now.x * p.rate), static_cast<int>(p.size.now.y * p.rate), 32);
							//SetWindowSize(static_cast<int>(p._size.now.x * p._rate.now.x), static_cast<int>(p._size.now.y * p._rate.now.y));
							//SetBackgroundColor(p._bg.now.r, p._bg.now.g, p._bg.now.b);
						}
					}
				}
			}
		}
	}
}