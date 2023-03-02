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

	if (suika::window::create({ 1280,960 }, { 128,128 }, { 1.0,1.0 }, { 255,255,255 }, "Application") == nullptr) {
		return 0;
	}

	suika::d3d::vertex_shader vs;
	suika::d3d::pixel_shader ps;
	vs.create(g_vs_main, sizeof(g_vs_main), "shape");
	ps.create(g_ps_main, sizeof(g_ps_main), "shape");
	//vs.create("../suika/d3d/shader/shape.hlsl", "shape");
	//ps.create("../suika/d3d/shader/shape.hlsl", "shape");
	vs.set();
	ps.set();

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
	{
		suika::vertex vertices[4] = {
			{{64,64,0,1},{1.0f,0.0f,0.0f,1.0f} ,{0,0}},
			{{480,64,0,1},{1.0f,1.0f,0.0f,1.0f},{0,0}},
			{{64,480,0,1},{0.0f,0.0f,1.0f,1.0f},{0,0}},
			{{480,480,0,1},{0.0f,1.0f,1.0f,1.0f},{0,0}},
		};


		Microsoft::WRL::ComPtr<ID3D11Buffer> g_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> g_vertexBuffer;

		// バッファを作成
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));

		// 頂点バッファの設定
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;                 // デフォルトアクセス
		bufferDesc.ByteWidth = sizeof(suika::vertex) * 4;              // サイズはVertex構造体×4
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;        // 頂点バッファを使用
		bufferDesc.CPUAccessFlags = 0;                          // CPUのバッファへのアクセス拒否

		// リソースの設定
		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));
		initData.pSysMem = vertices;

		// 頂点バッファを作成
		if (FAILED(suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, g_vertexBuffer.GetAddressOf()))) {
			//MessageBox(NULL, L"頂点バッファを作成できませんでした。", WINDOW_TITLE, MB_OK | MB_ICONERROR);
			return E_FAIL;
		}

		// 表示する頂点バッファを選択
		UINT stride = sizeof(suika::vertex);
		UINT offset = 0;
		suika::d3d::pContext->IASetVertexBuffers(0, 1, g_vertexBuffer.GetAddressOf(), &stride, &offset);

		// 四角形のインデックスを定義
		WORD index[] =
		{
			0, 1, 2,
			2, 1, 3
		};

		// インデックス情報の追加
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;                 // デフォルトアクセス
		bufferDesc.ByteWidth = sizeof(index);                // サイズはインデックスの数 6
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;         // インデックスバッファを使用
		bufferDesc.CPUAccessFlags = 0;                          // CPUのバッファへのアクセス拒否
		initData.pSysMem = index;

		// インデックスバッファを作成
		if (FAILED(suika::d3d::pDevice->CreateBuffer(&bufferDesc, &initData, &g_indexBuffer))) {
			//MessageBox(NULL, L"インデックスバッファを作成できませんでした。", WINDOW_TITLE, MB_OK | MB_ICONERROR);
			return E_FAIL;
		}

		// 表示するインデックスバッファを選択
		suika::d3d::pContext->IASetIndexBuffer(g_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

		// 使用するプリミティブタイプを設定
		suika::d3d::pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
		
	auto update = [&]() {suika::window::flip(); suika::window::clear(); return suika::window::process(); };
	while (update()) {
		
		//suika::d3d::pContext->UpdateSubresource(cbf.Get(), 0, nullptr, &cb, 0, 0);
		//D3D11_MAPPED_SUBRESOURCE cData;
		//auto er = suika::d3d::pContext->Map(cbf.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &cData);
		//if (FAILED(er)) {
		//	suika::d3d::log_d3d.error("Failed to Map");
		//	suika::d3d::log_d3d.result(er);
		//	//return;
		//}
		//else {
		//	memcpy_s(cData.pData, cData.RowPitch, &cb, sizeof(cb));
		//	suika::d3d::pContext->Unmap(cbf.Get(), 0);
		//}
		suika::d3d::pContext->DrawIndexed(6, 0, 0);
	}
	suika::log.info("fin");

	return 0;
}