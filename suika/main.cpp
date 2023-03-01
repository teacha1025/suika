#include <Windows.h>
#include "../include/suika/logger.h"
#include "../include/suika/window.h"

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
	{
		suika::d3d::vertex_shader vs;
		suika::d3d::pixel_shader ps;
		vs.create(g_vs_main, sizeof(g_vs_main), "shape");
		ps.create(g_ps_main, sizeof(g_ps_main), "shape");
		vs.set();
		ps.set();
	}
	auto cb = suika::d3d::set_view({1280,960});
	Microsoft::WRL::ComPtr<ID3D11Buffer> cbf;
	if (!suika::d3d::create_cbuffer(cbf.GetAddressOf(), sizeof(cb))) {
		suika::log.error("cb");
		return 0;
	}
	suika::d3d::update_cbuffer(cbf.Get(), &cb, 0);

	if (suika::window::create({ 1280,920 }, { 128,128 }, { 1.0,1.0 }, { 255,255,255 }, "Application") == nullptr) {
		return 0;
	}
	suika::window::background(suika::color(255, 127, 0));
	suika::window::title("APP");


	suika::vertex vertices[4] = {
		{{128,128,0, 0},{1.0f,1.0f,1.0f,1.0f},{0,0}},
		{{192,128,0, 0},{1.0f,1.0f,1.0f,1.0f},{0,0}},
		{{128,192,0, 0},{1.0f,1.0f,1.0f,1.0f},{0,0}},
		{{192,192,0, 0},{1.0f,1.0f,1.0f,1.0f},{0,0}},
	};

	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> g_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> g_vertexBuffer;

		// �o�b�t�@���쐬
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		// ���_�o�b�t�@�̐ݒ�
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;                 // �f�t�H���g�A�N�Z�X
		bufferDesc.ByteWidth = sizeof(suika::vertex) * 4;              // �T�C�Y��Vertex�\���́~4
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;        // ���_�o�b�t�@���g�p
		bufferDesc.CPUAccessFlags = 0;                          // CPU�̃o�b�t�@�ւ̃A�N�Z�X����

		// ���\�[�X�̐ݒ�
		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));
		initData.pSysMem = vertices;

		// ���_�o�b�t�@���쐬
		if (FAILED(suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, g_vertexBuffer.GetAddressOf())))
		{
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
		bufferDesc.ByteWidth = sizeof(WORD) * 6;                // �T�C�Y�̓C���f�b�N�X�̐� 6
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;         // �C���f�b�N�X�o�b�t�@���g�p
		bufferDesc.CPUAccessFlags = 0;                          // CPU�̃o�b�t�@�ւ̃A�N�Z�X����
		initData.pSysMem = index;

		// �C���f�b�N�X�o�b�t�@���쐬
		if (FAILED(suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, &g_indexBuffer)))
		{
			//MessageBox(NULL, L"�C���f�b�N�X�o�b�t�@���쐬�ł��܂���ł����B", WINDOW_TITLE, MB_OK | MB_ICONERROR);
			return E_FAIL;
		}

		// �\������C���f�b�N�X�o�b�t�@��I��
		suika::d3d::pContext->IASetIndexBuffer(g_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

		// �g�p����v���~�e�B�u�^�C�v��ݒ�
		suika::d3d::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	

	auto update = [&]() {suika::window::flip(); suika::window::clear(); return suika::window::process(); };
	while (update()) {
		cb = suika::d3d::set_view({ 1280,960 });
		suika::d3d::update_cbuffer(cbf.Get(), &cb, 0);
		//suika::d3d::pContext->IASetVertexBuffers(0, 1, g_vertexBuffer.GetAddressOf(), &stride, &offset);

		suika::d3d::pContext->DrawIndexed(6, 0, 0);
	}
	suika::log.info("fin");
}