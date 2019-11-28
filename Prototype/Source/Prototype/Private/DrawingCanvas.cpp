// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawingCanvas.h"

UDrawingCanvas::UDrawingCanvas(){}
UDrawingCanvas::~UDrawingCanvas(){}

//void UDrawingCanvas::InitializeCanvas(const int32 pixelsH, const int32 pixelsV)
void UDrawingCanvas::InitializeCanvas(const int32 pixelsH, const int32 pixelsV)
{
    //dynamic texture initialization
    canvasWidth = pixelsH;
    canvasHeight = pixelsV;
 
    dynamicCanvas = UTexture2D::CreateTransient(canvasWidth, canvasHeight, PF_A8 );
#if WITH_EDITORONLY_DATA
    dynamicCanvas->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
#endif
    dynamicCanvas->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
    dynamicCanvas->SRGB = 0;
    dynamicCanvas->AddToRoot();
    //dynamicCanvas->Filter = TextureFilter::TF_Default;
    dynamicCanvas->Filter = TextureFilter::TF_Nearest;
    dynamicCanvas->UpdateResource();
 
    echoUpdateTextureRegion = std::unique_ptr<FUpdateTextureRegion2D>(new FUpdateTextureRegion2D(0, 0, 0, 0, canvasWidth, canvasHeight));
 
 
    // buffers initialization
    //bytesPerPixel = 4; // r g b a
    bytesPerPixel = 1; // r g b a
    bufferPitch = canvasWidth * bytesPerPixel;
    bufferSize = canvasWidth * canvasHeight * bytesPerPixel;
    canvasPixelData = std::unique_ptr<uint8[]>(new uint8[bufferSize]);
 
    ClearCanvas();
}

void UDrawingCanvas::ClearCanvas()
{
    uint8* canvasPixelPtr = canvasPixelData.get();
    for (int i = 0; i < canvasWidth * canvasHeight; ++i)
    {
        setPixelColor(canvasPixelPtr, 255); //white
        canvasPixelPtr += bytesPerPixel;
    }
    UpdateCanvas();
}

void UDrawingCanvas::DrawLife(AGoLUser* GoL)
{
    if (GoL == nullptr) {UE_LOG(LogTemp, Warning, TEXT("no navGoLinText"));return;}
    uint8* canvasPixelPtr = canvasPixelData.get();
    //const bool* const* field = GoL->GoL->GetField();
    const bool* const* field = GoL->VisibleGoLField;
    if (field == nullptr) {UE_LOG(LogTemp, Warning, TEXT("no field in DrawingCanvas"));return;}
    int _canvasWidth = std::min(GoL->get_width(),canvasWidth);
    int _canvasHeight = std::min(GoL->get_height(),canvasHeight);
    for (int i = 0; i < _canvasWidth; ++i)
    {
        for (int j = 0; j < _canvasHeight; ++j)
        {
            canvasPixelPtr[i*canvasHeight+j] = 255*field[j][i]; //white
			//canvasPixelPtr[i*canvasHeight + j] = 128 * field[j][i] + 64*GoL->WillBeAlive(j,i);
            //canvasPixelPtr[i*canvasWidth+j] = 0; //white
        }
    }
    UpdateCanvas();
}

void UDrawingCanvas::UpdateCanvas()
{
    if (echoUpdateTextureRegion)
    {
        dynamicCanvas->UpdateTextureRegions((int32)0, (uint32)1, echoUpdateTextureRegion.get(), (uint32)bufferPitch, (uint32)bytesPerPixel, canvasPixelData.get());
    }
}


inline void UDrawingCanvas::setPixelColor(uint8*& pointer, uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
    *pointer = blue; //b
    *(pointer + 1) = green; //g
    *(pointer + 2) = red; //r
    *(pointer + 3) = alpha; //a
}

inline void UDrawingCanvas::setPixelColor(uint8*& pointer, uint8 red)
{
    *pointer = red; //b
}
