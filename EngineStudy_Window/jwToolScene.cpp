#include "jwToolScene.h"
#include "jwObject.h"
#include "jwTile.h"
#include "jwTilemapRenderer.h"
#include "jwResources.h"
#include "jwTexture.h"
#include "jwCamera.h"
#include "jwRenderer.h"
#include "jwInput.h"
#include "jwCameraScript.h"

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
		camera->AddComponent<CameraScript>();

        renderer::mainCamera = cameraComp;

        //Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
        //TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
        //tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));

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
            pos = renderer::mainCamera->CaluateTilePosition(pos);

            if (pos.x >= 0.0f && pos.y >= 0.0f)
            {
                int idxX = pos.x / TilemapRenderer::TileSize.x;
                int idxY = pos.y / TilemapRenderer::TileSize.y;

                Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
                TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
                tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
                tmr->SetIndex(TilemapRenderer::SelectedIndex);

                tile->SetIndexPosition(idxX, idxY);
                mTiles.push_back(tile);
            }
        }

        if (Input::GetKeyDown(eKeyCode::S))
            Save();
        if (Input::GetKeyDown(eKeyCode::L))
            Load();
    }

    void ToolScene::Render(HDC hdc)
    {
        Scene::Render(hdc);

        //타일 그리드 그리기
        for (size_t i = 0; i < 50; i++)
        {
            Vector2 pos = renderer::mainCamera->CaluatePosition(Vector2(TilemapRenderer::TileSize.x * i, 0.0f));

            MoveToEx(hdc, pos.x, 0, NULL);
            LineTo(hdc, pos.x, 1000);
        }

        for (size_t i = 0; i < 50; i++)
        {
            Vector2 pos = renderer::mainCamera->CaluatePosition(Vector2(0.0f, TilemapRenderer::TileSize.y * i));

            MoveToEx(hdc, 0, pos.y, NULL);
            LineTo(hdc, 1000, pos.y);
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

    void ToolScene::Save()
    {
        OPENFILENAME ofn = {};

        wchar_t szFilePath[256] = {};

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = szFilePath;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = 256;
        ofn.lpstrFilter = L"Tile\0*.tile\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (false == GetSaveFileName(&ofn))
            return;

        FILE* pFile = nullptr;
        errno_t err = _wfopen_s(&pFile, szFilePath, L"wb");
        if (err != 0 || pFile == nullptr)
        {
            // 파일 열기에 실패했을 때의 처리 (에러 메시지 출력 등)
            MessageBox(NULL, L"파일 열기에 실패했습니다.", L"Error", MB_OK | MB_ICONERROR);
            return;
        }

        //타일 인덱스, 좌표 저장
        for (Tile* tile : mTiles)
        {
            TilemapRenderer* tmr = tile->GetComponent<TilemapRenderer>();
            Transform* tr = tile->GetComponent<Transform>();

            Vector2 sourceIndex = tmr->GetIndex();
            Vector2 position = tr->GetPosition();

            int x = sourceIndex.x;
            fwrite(&x, sizeof(int), 1, pFile);
            int y = sourceIndex.y;
            fwrite(&y, sizeof(int), 1, pFile);

            x = position.x;
            fwrite(&x, sizeof(int), 1, pFile);
            y = position.y;
            fwrite(&y, sizeof(int), 1, pFile);
        }

        fclose(pFile);
    }

    void ToolScene::Load()
    {
        OPENFILENAME ofn = {};

        wchar_t szFilePath[256] = {};

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = szFilePath;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = 256;
        ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (false == GetOpenFileName(&ofn))
            return;

        FILE* pFile = nullptr;
        errno_t err = _wfopen_s(&pFile, szFilePath, L"rb");
        if (err != 0 || pFile == nullptr)
        {
            // 파일 열기에 실패했을 때의 처리 (에러 메시지 출력 등)
            MessageBox(NULL, L"파일 열기에 실패했습니다.", L"Error", MB_OK | MB_ICONERROR);
            return;
        }

        //파일 읽어 저장된 타일 가져오기
        while (true)
        {
            int idxX = 0;
            int idxY = 0;

            int posX = 0;
            int posY = 0;

            //NULL- 더이상 읽을게 없음 -> 빠져나가기
            if (fread(&idxX, sizeof(int), 1, pFile) == NULL)
                break;
            if (fread(&idxY, sizeof(int), 1, pFile) == NULL)
                break;
            if (fread(&posX, sizeof(int), 1, pFile) == NULL)
                break;
            if (fread(&posY, sizeof(int), 1, pFile) == NULL)
                break;

            Tile* tile = object::Instantiate<Tile>(eLayerType::Tile, Vector2(posX, posY));
            TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
            tmr->SetTexture(Resources::Find<graphics::Texture>(L"SpringFloor"));
            tmr->SetIndex(Vector2(idxX, idxY));

            mTiles.push_back(tile);
        }

        fclose(pFile);
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