#include <unordered_map>
#include <d2d1_3.h>
#include <d3d11.h>
#include <dwrite_3.h>
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
			ComPtr<IDWriteFactory5> pDWriteFactory;
			//IDWriteFactory* pDWriteFactory;
			ComPtr<IDWriteTextFormat> pTextFormat;
			//IDWriteTextFormat* pTextFormat;
			ComPtr<IDWriteTextLayout> pTextLayout;
			std::unordered_map<canvas_id, ComPtr<ID2D1RenderTarget>> pRT;
			std::unordered_map<string, ComPtr<IDWriteFontFace>> fontFaceMap;
			std::unordered_map<string, std::pair<ComPtr<ID2D1PathGeometry>, ComPtr<ID2D1GeometrySink>>> pathGeometryMap;
			ComPtr<ID2D1SolidColorBrush> pSolidBrush;
			ComPtr<ID2D1SolidColorBrush> pEdgeSolidBrush;
			ComPtr<IDWriteFontFile> fontFile;
			ComPtr<IDWriteFontCollection> pFontCollection;
			
			void registerFontFace(const string& fontFamilyName, ComPtr<IDWriteFontFile>& fontFile) noexcept {
				std::array<IDWriteFontFile*, 1U> fontFileArray = { fontFile.Get() };
				ComPtr<IDWriteFontFace> fontFace = nullptr;
				auto er = pDWriteFactory->CreateFontFace(DWRITE_FONT_FACE_TYPE_TRUETYPE, 1U, fontFileArray.data(), 0U, DWRITE_FONT_SIMULATIONS_NONE, fontFace.ReleaseAndGetAddressOf());
				if (SUCCEEDED(er)) [[likely]] {
					fontFaceMap[fontFamilyName] = fontFace;
				}
				else [[unlikely]] {
					log_d3d.error("Failed to CreateFontFace");
					log_d3d.result(er);
				}
			}

			void registerFontFace(const string& fontFamilyName) {
				ComPtr<IDWriteFontFamily> family;
				ComPtr<IDWriteFont> pFont;
				UINT index = 0;
				BOOL exist = false;
				
				auto er = pFontCollection->FindFamilyName(fontFamilyName.to_wstring().c_str(), &index, &exist);
				if (FAILED(er) || !exist) {
					log_d3d.error(fontFamilyName + " was not found.");
					log_d3d.result(er);
					return;
				}
				er = pFontCollection->GetFontFamily(index, family.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to GetFontFamily");
					log_d3d.result(er);
					return;
				}
				er = family->GetFont(0, pFont.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to GetFont");
					log_d3d.result(er);
					return;
				}
				er = pFont->CreateFontFace(fontFaceMap[fontFamilyName].GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to CreateFontFace");
					log_d3d.result(er);
					return;
				}
			}

			void registerTextPathGeometry(const string& key, const string& text_s, const string& fontFamilyName, const FLOAT size) noexcept {
				if(pathGeometryMap.contains(key)) [[likely]] {
					return;
				}
				auto text = text_s.to_u16string();
				//グリフインデックス列を取得する
				std::vector<UINT> codePoints;
				std::vector<UINT16> glyphIndices(text.length());
				for (auto character : text) {
					codePoints.emplace_back(character);
				}
				const auto fontFace = fontFaceMap[fontFamilyName];
				auto er = fontFace->GetGlyphIndicesW(codePoints.data(), static_cast<UINT32>(codePoints.size()), glyphIndices.data());
				ComPtr<ID2D1PathGeometry> pathGeometry = nullptr;
				if (FAILED(er=pD2DFactory->CreatePathGeometry(pathGeometry.ReleaseAndGetAddressOf()))) [[unlikely]] {
					log_d3d.error("Failed to Create PathGeometry");
					log_d3d.result(er);
					return;
				}
				ComPtr<ID2D1GeometrySink> geometrySink = nullptr;
				if (FAILED(er = pathGeometry->Open(geometrySink.ReleaseAndGetAddressOf()))) [[unlikely]] {
					log_d3d.error("Failed to Create Open GeometrySink");
					log_d3d.result(er);
					return;
				}
				//アウトライン情報を取得する
				
				//pD2DFactory->GetDesktopDpi(&dpi.x, &dpi.y);
				uint dpi = GetDpiForWindow(window::all_id()[0]);
				if (FAILED(er = fontFace->GetGlyphRunOutline((size / dpi) * 96.0f, glyphIndices.data(), nullptr, nullptr, static_cast<UINT32>(text.length()), FALSE, FALSE, geometrySink.Get()))) [[unlikely]] {
					log_d3d.error("Failed to GetGlyphRunOutline");
					log_d3d.result(er);
					return;
				}
				if (FAILED(er = geometrySink->Close())) [[unlikely]] {
					log_d3d.error("Failed to Close GeometrySink");
					log_d3d.result(er);
					return;
				}
				codePoints.clear();
				pathGeometryMap.insert({ key,{ pathGeometry, geometrySink } });
			}

			void init(canvas_id window) {
				// Direct2D,DirectWriteの初期化
				auto er = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, pD2DFactory.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Text Format");
					log_d3d.result(er);
					return;
				}
				ComPtr<IDXGISurface> pBackBuffer;
				// バックバッファの取得
				// 型：IDXGISwapChain
				er = d3d::pSwapChain.at(window).Get()->GetBuffer(0, IID_PPV_ARGS(pBackBuffer.GetAddressOf()));
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Text Format");
					log_d3d.result(er);
					return;
				}

				// dpiの設定
				FLOAT dpiX;
				FLOAT dpiY;
				HWND hwnd = WindowID.at(window);
				HDC hdc = GetDC(hwnd);
				point<FLOAT> dpi = { static_cast<FLOAT>(GetDeviceCaps(hdc, LOGPIXELSX)), static_cast<FLOAT>(GetDeviceCaps(hdc, LOGPIXELSY)) };
				dpiX = dpi.x / 96.0f;
				dpiY = dpi.y / 96.0f;
				ReleaseDC(hwnd, hdc);

				// レンダーターゲットの作成
				D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpi.x, dpi.y);

				if (!pRT.contains(window)) {
					pRT.insert({ window,{} });
				}
				// サーフェスに描画するレンダーターゲットを作成
				er = pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer.Get(), &props, pRT[window].GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to Create DXGI Surface RT");
					log_d3d.result(er);
					return;
				}
				// アンチエイリアシングモード
				pRT[window]->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

				// IDWriteFactoryの作成
				er = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(pDWriteFactory.GetAddressOf()));
				if (FAILED(er)) {
					log_d3d.error("Failed to Create DWrite Factory");
					log_d3d.result(er);
					return;
				}

				pDWriteFactory->GetSystemFontCollection(pFontCollection.GetAddressOf());

				log_d3d.info("Initialize DWrite");
			}

			void set(const font_data& font, canvas_id window) {
				set(font.font, font.weight, font.style, font.stretch, font.size, font.locale, font.alignment, window);
			}

			void set(const string& font, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch, float size, const string& locale, DWRITE_TEXT_ALIGNMENT alignment, canvas_id window) {
				//関数CreateTextFormat()
				//第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
				//第2引数：フォントコレクション（nullptr）
				//第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
				//第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
				//第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
				//第6引数：フォントサイズ（20, 30等）
				//第7引数：ロケール名（L""）
				//第8引数：テキストフォーマット（&g_pTextFormat）
				auto er = pDWriteFactory->CreateTextFormat(
					font.to_wstring().c_str(),
					//font->fontCollection,
					nullptr,
					weight,
					style,
					stretch,
					size,
					locale.to_wstring().c_str(),
					&pTextFormat);
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Text Format");
					log_d3d.result(er);
					return;
				}
				//関数SetTextAlignment()
				//第1引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, DWRITE_TEXT_ALIGNMENT_TRAILING：後, DWRITE_TEXT_ALIGNMENT_CENTER：中央,
				//                         DWRITE_TEXT_ALIGNMENT_JUSTIFIED：行いっぱい）
				er = pTextFormat->SetTextAlignment(alignment);
				if (FAILED(er)) {
					log_d3d.error("Failed to Set Text Alignment");
					log_d3d.result(er);
					return;
				}
				
				registerFontFace(font);
			}

			void draw(string str, point<float> pos, canvas_id window, const color_f& color, D2D1_DRAW_TEXT_OPTIONS options, float alpha) {
				// 文字列の変換
				std::wstring wstr = str.to_wstring();

				// ターゲットサイズの取得
				D2D1_SIZE_F TargetSize = pRT[window]->GetSize();

				// テキストレイアウトを作成
				auto er = pDWriteFactory->CreateTextLayout(wstr.c_str(), static_cast<UINT32>(wstr.size()), pTextFormat.Get(), TargetSize.width, TargetSize.height, & pTextLayout);
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Text Layout");
					log_d3d.result(er);
					return;
				}

				//関数CreateSolidColorBrush()
				//第1引数：フォント色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定）
				er = pRT[window]->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), pSolidBrush.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Solid Color Brush");
					log_d3d.result(er);
					return;
				}
				// 描画位置の確定

				D2D1::Matrix3x2F matricx = D2D1::Matrix3x2F::Translation(pos.x, pos.y);
				pRT[window]->SetTransform(matricx);

				//D2D1_MATRIX_3X2_F matricx;

				// 描画の開始
				pRT[window]->BeginDraw();

				pSolidBrush->SetOpacity(alpha);
				DWRITE_TEXT_METRICS text_metrics;
				pTextLayout->GetMetrics(&text_metrics);
				// 描画処理
				pRT[window]->DrawTextLayout({-text_metrics.left,-text_metrics.top}, pTextLayout.Get(), pSolidBrush.Get(), options);

				pSolidBrush->SetOpacity(1.0f);

				// 描画の終了
				er = pRT[window]->EndDraw();
				if (FAILED(er)) {
					log_d3d.error("Failed to EndDraw");
					log_d3d.result(er);
					return;
				}
			}

			void draw(string font, float size, string str, point<float> pos, canvas_id window, const color_f& color, uint32 edge_px, const color_f& edge_color, D2D1_DRAW_TEXT_OPTIONS options, float alpha, const string& key) {
				// 文字列の変換
				std::wstring wstr = str.to_wstring();
				
				string textPathGeometryKey = string(str.to_u32string() + key.to_u32string());
				registerTextPathGeometry(textPathGeometryKey,str,font,size+edge_px);

				const auto textPathGeometry = pathGeometryMap.at(textPathGeometryKey).first;

				/*
				// ターゲットサイズの取得
				D2D1_SIZE_F TargetSize = pRT[window]->GetSize();

				// テキストレイアウトを作成
				auto er = pDWriteFactory->CreateTextLayout(wstr.c_str(), static_cast<UINT32>(wstr.size()), pTextFormat.Get(), TargetSize.width, TargetSize.height, &pTextLayout);
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Text Layout");
					log_d3d.result(er);
					return;
				}
				*/
				//関数CreateSolidColorBrush()
				//第1引数：フォント色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定）
				auto er = pRT[window]->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), pSolidBrush.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Solid Color Brush");
					log_d3d.result(er);
					return;
				}
				er = pRT[window]->CreateSolidColorBrush(D2D1::ColorF(edge_color.r, edge_color.g, edge_color.b, edge_color.a), pEdgeSolidBrush.GetAddressOf());
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Solid EdgeColor Brush");
					log_d3d.result(er);
					return;
				}

				//D2D1_MATRIX_3X2_F matricx;

				// 描画の開始
				pRT[window]->BeginDraw();

				pSolidBrush->SetOpacity(alpha);
				pEdgeSolidBrush->SetOpacity(alpha);
				D2D1_RECT_F rect{};
				textPathGeometry->GetBounds(nullptr, &rect);
				D2D1::Matrix3x2F matricx = D2D1::Matrix3x2F::Translation(pos.x - rect.left + edge_px, pos.y - rect.top + edge_px);
				pRT[window]->SetTransform(matricx);
				// 描画処理
				//pRT[window]->DrawTextLayout({ -text_metrics.left,-text_metrics.top }, pTextLayout.Get(), pSolidBrush.Get(), options);
				
				pRT[window]->FillGeometry(textPathGeometry.Get(), pSolidBrush.Get());
				pRT[window]->DrawGeometry(textPathGeometry.Get(), pEdgeSolidBrush.Get(), edge_px);

				pSolidBrush->SetOpacity(1.0f);
				pEdgeSolidBrush->SetOpacity(1.0f);

				// 描画の終了
				er = pRT[window]->EndDraw();
				if (FAILED(er)) {
					log_d3d.error("Failed to EndDraw");
					log_d3d.result(er);
					return;
				}
			}

			point<float> get_size(string str, canvas_id window) {
				// 文字列の変換
				std::wstring wstr = str.to_wstring();
				// ターゲットサイズの取得
				D2D1_SIZE_F TargetSize = pRT[window]->GetSize();

				// テキストレイアウトを作成
				auto er = pDWriteFactory->CreateTextLayout(wstr.c_str(), static_cast<UINT32>(wstr.size()), pTextFormat.Get(), TargetSize.width, TargetSize.height, &pTextLayout);
				if (FAILED(er)) {
					log_d3d.error("Failed to Create Text Layout");
					log_d3d.result(er);
					return {-1,-1};
				}

				DWRITE_TEXT_METRICS text_metrics;
				pTextLayout->GetMetrics(&text_metrics);
				return { text_metrics.width, text_metrics.height };
			}

			point<float> get_size_edged(const string& font, const string& str, float size, uint32 edge_width, const string& key) {
				const string textPathGeometryKey = string(str.to_u32string() + key.to_u32string());
				registerTextPathGeometry(textPathGeometryKey, str, font, size+edge_width);

				const auto textPathGeometry = pathGeometryMap.at(textPathGeometryKey).first;
				D2D1_RECT_F rect{};
				textPathGeometry->GetBounds(nullptr, &rect);
				return { rect.right - rect.left + edge_width*2, rect.bottom - rect.top + edge_width * 2 };
			}

			void free() {
				//pTextFormat->Release();
				//pDWriteFactory->Release();
				log_d3d.info("Finalize DWrite");
			}
		}
	}
}