#include <unordered_map>
#include <d2d1_3.h>
#include <d3d11.h>
#include <dwrite.h>
#include <wrl/client.h>
#pragma comment( lib, "D2d1.lib" )
#pragma comment( lib, "Dwrite.lib" )
#include "info.hpp"

#include "../../include/suika/point.h"
#include "dwrite.h"
using namespace Microsoft::WRL;

namespace suika {
	namespace d3d {
		namespace dwrite {
			ComPtr<ID2D1Factory> pD2DFactory;
			ComPtr<IDWriteFactory> pDWriteFactory;
			ComPtr<IDWriteTextFormat> pTextFormat;
			ComPtr<IDWriteTextLayout> pTextLayout;
			std::unordered_map<canvas_id, ComPtr<ID2D1RenderTarget>> pRT;
			ComPtr<ID2D1SolidColorBrush> pSolidBrush;
			ComPtr<IDXGISurface> pBackBuffer;

			void init(canvas_id window) {
				// Direct2D,DirectWriteの初期化
				D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, pD2DFactory.GetAddressOf());

				// バックバッファの取得
				// 型：IDXGISwapChain
				d3d::pSwapChain.at(window).Get()->GetBuffer(0, IID_PPV_ARGS(pBackBuffer.GetAddressOf()));

				// dpiの設定
				FLOAT dpiX;
				FLOAT dpiY;
				pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

				// レンダーターゲットの作成
				D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

				if (!pRT.contains(window)) {
					pRT.insert({ window,{} });
				}
				// サーフェスに描画するレンダーターゲットを作成
				pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer.Get(), &props, pRT[window].GetAddressOf());

				// アンチエイリアシングモード
				pRT[window]->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

				// IDWriteFactoryの作成
				DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(pDWriteFactory.GetAddressOf()));
			}

			void set(const font_data& font, canvas_id window) {
				//関数CreateTextFormat()
				//第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
				//第2引数：フォントコレクション（nullptr）
				//第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
				//第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
				//第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
				//第6引数：フォントサイズ（20, 30等）
				//第7引数：ロケール名（L""）
				//第8引数：テキストフォーマット（&g_pTextFormat）
				pDWriteFactory->CreateTextFormat(
					font.font.to_wstring().c_str(),
					//font->fontCollection,
					nullptr,
					font.fontWeight,
					font.fontStyle,
					font.fontStretch,
					font.fontSize,
					font.localeName.to_wstring().c_str(),
					pTextFormat.GetAddressOf());

				//関数SetTextAlignment()
				//第1引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, DWRITE_TEXT_ALIGNMENT_TRAILING：後, DWRITE_TEXT_ALIGNMENT_CENTER：中央,
				//                         DWRITE_TEXT_ALIGNMENT_JUSTIFIED：行いっぱい）
				pTextFormat->SetTextAlignment(font.textAlignment);

				//関数CreateSolidColorBrush()
				//第1引数：フォント色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定）
				float r = font.Color.r / 255.0f;
				float g = font.Color.g / 255.0f;
				float b = font.Color.b / 255.0f;
				float a = font.Color.a / 255.0f;
				pRT[window]->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), pSolidBrush.GetAddressOf());
			}

			void draw(string str, point<float> pos, canvas_id window, D2D1_DRAW_TEXT_OPTIONS options)
			{
				// 文字列の変換
				std::wstring wstr = str.to_wstring();

				// ターゲットサイズの取得
				D2D1_SIZE_F TargetSize = pRT[window]->GetSize();

				// テキストレイアウトを作成
				pDWriteFactory->CreateTextLayout(wstr.c_str(), wstr.size(), pTextFormat.Get(), TargetSize.width, TargetSize.height, &pTextLayout);

				// 描画位置の確定
				D2D1_POINT_2F pounts;
				pounts.x = pos.x;
				pounts.y = pos.y;

				// 描画の開始
				pRT[window]->BeginDraw();

				// 描画処理
				pRT[window]->DrawTextLayout(pounts, pTextLayout.Get(), pSolidBrush.Get(), options);

				// 描画の終了
				pRT[window]->EndDraw();
			}
		}
	}
}