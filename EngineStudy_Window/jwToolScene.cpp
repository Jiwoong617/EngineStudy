#include "jwToolScene.h"
#include "jwObject.h"
#include "jwTile.h"
#include "jwTilemapRenderer.h"
#include "jwResources.h"
#include "jwTexture.h"
#include "jwCamera.h"
#include "jwRenderer.h"
#include "jwInput.h"

namespace jw
{

    ToolScene::ToolScene()
    {
    }

    ToolScene::~ToolScene()
    {
    }

    void ToolScene::Initialize()
    {
        GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(344.0f, 442.0f));
        Camera* cameraComp = camera->AddComponent<Camera>();
        renderer::mainCamera = cameraComp;

        Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
        TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();


        tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));

        Scene::Initialize();
    }

    void ToolScene::Update()
    {
        Scene::Update();
    }

    void ToolScene::LateUpdate()
    {
        Scene::LateUpdate();

        //좌표에 타일 생성
        if (Input::GetKeyDown(eKeyCode::LButton))
        {
            Vector2 pos = Input::GetMousePosition();

            int idxX = pos.x / TilemapRenderer::TileSize.x;
            int idxY = pos.y / TilemapRenderer::TileSize.y;

            Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
            TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
            tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
            tmr->SetIndex(TilemapRenderer::SelectedIndex);

            tile->SetPosition(idxX, idxY);
        }
    }

    void ToolScene::Render(HDC hdc)
    {
        Scene::Render(hdc);

        //타일 그리드 그리기
        for (size_t i = 0; i < 50; i++)
        {
            MoveToEx(hdc, TilemapRenderer::TileSize.x * i, 0, NULL);
            LineTo(hdc, TilemapRenderer::TileSize.x * i, 1000);
        }

        for (size_t i = 0; i < 50; i++)
        {
            MoveToEx(hdc, 0, TilemapRenderer::TileSize.y * i, NULL);
            LineTo(hdc, 1000, TilemapRenderer::TileSize.y * i);
        }
    }

    void ToolScene::OnEnter()
    {
        Scene::OnEnter();
    }

    void ToolScene::OnExit()
    {
        Scene::OnExit();
    }
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
		//마우스 클릭 좌표에 따른 타일 선택 및 생성
        POINT mousePos = { };
        GetCursorPos(&mousePos);
        ScreenToClient(hWnd, &mousePos);

        jw::math::Vector2 mousePosition;
        mousePosition.x = mousePos.x;
        mousePosition.y = mousePos.y;

        int idxX = mousePosition.x / jw::TilemapRenderer::OriginTileSize.x;
        int idxY = mousePosition.y / jw::TilemapRenderer::OriginTileSize.y;

        jw::TilemapRenderer::SelectedIndex = Vector2(idxX, idxY);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        //Rectangle(hdc, 100, 100, 200, 200);
        jw::graphics::Texture* texture
            = jw::Resources::Find<jw::graphics::Texture>(L"SpringFloor");

        TransparentBlt(hdc
            , 0, 0
            , texture->GetWidth()
            , texture->GetHeight()
            , texture->GetHdc()
            , 0, 0
            , texture->GetWidth()
            , texture->GetHeight()
            , RGB(255, 0, 255));

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}