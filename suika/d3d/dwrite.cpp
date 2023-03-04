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
				// Direct2D,DirectWrite�̏�����
				D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, pD2DFactory.GetAddressOf());

				// �o�b�N�o�b�t�@�̎擾
				// �^�FIDXGISwapChain
				d3d::pSwapChain.at(window).Get()->GetBuffer(0, IID_PPV_ARGS(pBackBuffer.GetAddressOf()));

				// dpi�̐ݒ�
				FLOAT dpiX;
				FLOAT dpiY;
				pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

				// �����_�[�^�[�Q�b�g�̍쐬
				D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

				if (!pRT.contains(window)) {
					pRT.insert({ window,{} });
				}
				// �T�[�t�F�X�ɕ`�悷�郌���_�[�^�[�Q�b�g���쐬
				pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer.Get(), &props, pRT[window].GetAddressOf());

				// �A���`�G�C���A�V���O���[�h
				pRT[window]->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

				// IDWriteFactory�̍쐬
				DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(pDWriteFactory.GetAddressOf()));
			}

			void set(const font_data& font, canvas_id window) {
				//�֐�CreateTextFormat()
				//��1�����F�t�H���g���iL"���C���I", L"Arial", L"Meiryo UI"���j
				//��2�����F�t�H���g�R���N�V�����inullptr�j
				//��3�����F�t�H���g�̑����iDWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD���j
				//��4�����F�t�H���g�X�^�C���iDWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC�j
				//��5�����F�t�H���g�̕��iDWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED���j
				//��6�����F�t�H���g�T�C�Y�i20, 30���j
				//��7�����F���P�[�����iL""�j
				//��8�����F�e�L�X�g�t�H�[�}�b�g�i&g_pTextFormat�j
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

				//�֐�SetTextAlignment()
				//��1�����F�e�L�X�g�̔z�u�iDWRITE_TEXT_ALIGNMENT_LEADING�F�O, DWRITE_TEXT_ALIGNMENT_TRAILING�F��, DWRITE_TEXT_ALIGNMENT_CENTER�F����,
				//                         DWRITE_TEXT_ALIGNMENT_JUSTIFIED�F�s�����ς��j
				pTextFormat->SetTextAlignment(font.textAlignment);

				//�֐�CreateSolidColorBrush()
				//��1�����F�t�H���g�F�iD2D1::ColorF(D2D1::ColorF::Black)�F��, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))�FRGBA�w��j
				float r = font.Color.r / 255.0f;
				float g = font.Color.g / 255.0f;
				float b = font.Color.b / 255.0f;
				float a = font.Color.a / 255.0f;
				pRT[window]->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), pSolidBrush.GetAddressOf());
			}

			void draw(string str, point<float> pos, canvas_id window, D2D1_DRAW_TEXT_OPTIONS options)
			{
				// ������̕ϊ�
				std::wstring wstr = str.to_wstring();

				// �^�[�Q�b�g�T�C�Y�̎擾
				D2D1_SIZE_F TargetSize = pRT[window]->GetSize();

				// �e�L�X�g���C�A�E�g���쐬
				pDWriteFactory->CreateTextLayout(wstr.c_str(), wstr.size(), pTextFormat.Get(), TargetSize.width, TargetSize.height, &pTextLayout);

				// �`��ʒu�̊m��
				D2D1_POINT_2F pounts;
				pounts.x = pos.x;
				pounts.y = pos.y;

				// �`��̊J�n
				pRT[window]->BeginDraw();

				// �`�揈��
				pRT[window]->DrawTextLayout(pounts, pTextLayout.Get(), pSolidBrush.Get(), options);

				// �`��̏I��
				pRT[window]->EndDraw();
			}
		}
	}
}