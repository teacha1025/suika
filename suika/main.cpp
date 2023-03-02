#include <Windows.h>
#include "../include/suika/logger.h"
#include "../include/suika/window.h"
#include "../include/suika/shader.h"
#include "../include/suika/vertex.h"

#include "d3d/info.hpp"
#include "d3d/device.hpp"
#include "d3d/vs.hpp"
#include "d3d/ps.hpp"
#include "d3d/cbuffer.hpp"

#include "d3d/shader/shape_vs.h"
#include "d3d/shader/shape_ps.h"

extern void init();
extern int main();

namespace suika {
	//logger log;
	struct vertex
	{
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 uv;
	};
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	suika::log.init();
	if (!suika::d3d::init()) {
		suika::log.error("d3d error");
		return 0;
	}	

	if (suika::window::create({ 1280,960 }, { 1.0,1.0 }, { 255,255,255 }, "Application") == nullptr) {
		return 0;
	}

	suika::add_vs(g_vs_main, sizeof(g_vs_main), "shape");
	suika::add_ps(g_ps_main, sizeof(g_ps_main), "shape");
	//suika::add_vs("../suika/d3d/shader/shape.hlsl", "shape");
	//suika::add_ps("../suika/d3d/shader/shape.hlsl", "shape");
	suika::set_vs("shape");
	suika::set_ps("shape");

	auto cb = suika::d3d::set_view({ 1280,960 });
	Microsoft::WRL::ComPtr<ID3D11Buffer> cbf;
	if (!suika::d3d::create_cbuffer(cbf.GetAddressOf(), sizeof(cb))) {
		suika::log.error("cb");
		return 0;
	}
	suika::d3d::update_cbuffer(cbf.Get(), &cb, sizeof(cb), 0);
	suika::d3d::set_cbuffer(cbf.GetAddressOf());

	suika::window::background(suika::color(0, 0, 0));
	suika::window::title("APP");

	suika::window::canvas().get()->set();
	
		suika::vertex::vertex_2d vertices[4] = {
			{{64,64,0,1},{1.0f,0.0f,0.0f,1.0f} ,{0,0}},
			{{480,64,0,1},{1.0f,1.0f,0.0f,1.0f},{0,0}},
			{{64,480,0,1},{0.0f,0.0f,1.0f,1.0f},{0,0}},
			{{480,480,0,1},{0.0f,1.0f,1.0f,1.0f},{0,0}},
		};

		
		Microsoft::WRL::ComPtr<ID3D11Buffer> g_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> g_vertexBuffer;

		// �o�b�t�@���쐬
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		// ���_�o�b�t�@�̐ݒ�
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(vertices);
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;

		// ���\�[�X�̐ݒ�
		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));
		initData.pSysMem = vertices;

		// ���_�o�b�t�@���쐬
		if (FAILED(suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, g_vertexBuffer.GetAddressOf()))) {
			//MessageBox(NULL, L"���_�o�b�t�@���쐬�ł��܂���ł����B", WINDOW_TITLE, MB_OK | MB_ICONERROR);
			return E_FAIL;
		}

		// �\�����钸�_�o�b�t�@��I��
		UINT stride = sizeof(suika::vertex);
		UINT offset = 0;
		suika::d3d::pContext->IASetVertexBuffers(0, 1, g_vertexBuffer.GetAddressOf(), &stride, &offset);

		// �l�p�`�̃C���f�b�N�X���`
		WORD index[] =
		{
			0, 1, 2,
			2, 1, 3
		};

		// �C���f�b�N�X���̒ǉ�
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;                 // �f�t�H���g�A�N�Z�X
		bufferDesc.ByteWidth = sizeof(index);                // �T�C�Y�̓C���f�b�N�X�̐� 6
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;         // �C���f�b�N�X�o�b�t�@���g�p
		bufferDesc.CPUAccessFlags = 0;                          // CPU�̃o�b�t�@�ւ̃A�N�Z�X����
		initData.pSysMem = index;

		// �C���f�b�N�X�o�b�t�@���쐬
		if (FAILED(suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, &g_indexBuffer))) {
			//MessageBox(NULL, L"�C���f�b�N�X�o�b�t�@���쐬�ł��܂���ł����B", WINDOW_TITLE, MB_OK | MB_ICONERROR);
			return E_FAIL;
		}

		// �\������C���f�b�N�X�o�b�t�@��I��
		suika::d3d::pContext->IASetIndexBuffer(g_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

		// �g�p����v���~�e�B�u�^�C�v��ݒ�
		suika::d3d::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
		
	auto update = [&]() {suika::window::flip(); suika::window::clear(); return suika::window::process(); };
	while (update()) {
		vertices[0].position.x += 1.0f;
		{
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));

			// ���_�o�b�t�@�̐ݒ�
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;                 // �f�t�H���g�A�N�Z�X
			bufferDesc.ByteWidth = sizeof(vertices);              // �T�C�Y��Vertex�\���́~4
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;        // ���_�o�b�t�@���g�p
			bufferDesc.CPUAccessFlags = 0;                          // CPU�̃o�b�t�@�ւ̃A�N�Z�X����

			// ���\�[�X�̐ݒ�
			ZeroMemory(&initData, sizeof(initData));
			initData.pSysMem = vertices;

			// ���_�o�b�t�@���쐬
			if (FAILED(suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, g_vertexBuffer.GetAddressOf()))) {
				//MessageBox(NULL, L"���_�o�b�t�@���쐬�ł��܂���ł����B", WINDOW_TITLE, MB_OK | MB_ICONERROR);
				return E_FAIL;
			}
			suika::d3d::pContext->IASetVertexBuffers(0, 1, g_vertexBuffer.GetAddressOf(), &stride, &offset);



			// �C���f�b�N�X���̒ǉ�
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.ByteWidth = sizeof(index);
			bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bufferDesc.CPUAccessFlags = 0;
			initData.pSysMem = index;

			// �C���f�b�N�X�o�b�t�@���쐬
			if (FAILED(suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, &g_indexBuffer))) {
				//MessageBox(NULL, L"�C���f�b�N�X�o�b�t�@���쐬�ł��܂���ł����B", WINDOW_TITLE, MB_OK | MB_ICONERROR);
				return E_FAIL;
			}

			// �\������C���f�b�N�X�o�b�t�@��I��
			suika::d3d::pContext->IASetIndexBuffer(g_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

			// �g�p����v���~�e�B�u�^�C�v��ݒ�
			suika::d3d::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}
		suika::d3d::pContext->DrawIndexed(6, 0, 0);
	}
	suika::log.info("fin");

	return 0;
}