#ifndef GIB_HPP
#define GIB_HPP

#include <iostream>
#include <vector>
#include <fstream>

#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_truetype.h"

#include "../include/Plage.hpp"

class GIB{

    public:

        static bool build(std::vector<std::vector<Plage>> PlagesOfFontsofGlyphs){
    
            std::vector<const char*> Filenames;

            int sidePlane = 0;

            fontBuffer.clear();
            fonts.clear();

            std::vector<std::vector<Plage>> finalPlages;

            for(int i = 0; i < PlagesOfFontsofGlyphs.size(); i++)
            {
                for(int j = 0; j < PlagesOfFontsofGlyphs[i].size(); j++)
                {

                    bool testP = true;
                    int locationP = -1;

                    for(int k = 0; k < finalPlages.size(); k++)
                    {
                        if(finalPlages[k][0].fontFilename == PlagesOfFontsofGlyphs[i][j].fontFilename)
                        {
                            locationP = k;
                            testP = false;
                            break;
                        }
                    }

                    if(testP)
                    {
                        finalPlages.push_back(std::vector<Plage>());
                        Filenames.push_back(PlagesOfFontsofGlyphs[i][j].fontFilename.c_str());
                        finalPlages[finalPlages.size()-1].push_back(PlagesOfFontsofGlyphs[i][j]);
                    }
                    else
                    {
                        finalPlages[locationP].push_back(PlagesOfFontsofGlyphs[i][j]);
                    }                    
                }
            }


            GIB::loadFontFile(Filenames);
            GIB::createPlanes(finalPlages, sidePlane, 16, "spacingGlyphs.dat");
            sidePlane = 0;
            GIB::createPlanes(finalPlages, sidePlane, 20, "spacingGlyphs.dat");
            sidePlane = 0;
            GIB::createPlanes(finalPlages, sidePlane, 26, "spacingGlyphs.dat");
            sidePlane = 0;
            GIB::createPlanes(finalPlages, sidePlane, 38, "spacingGlyphs.dat");
            sidePlane = 0;
            GIB::createPlanes(finalPlages, sidePlane, 64, "spacingGlyphs.dat");



            return true;
        };

        static bool isAllCaractersPresentInPlage(Plage p)
        {
            fonts.clear();
            fontBuffer.clear();

            GIB::loadFontFile({p.fontFilename.c_str()});

            return checkPresence(p);    
        }

    public:

        static inline std::vector<std::vector<unsigned char>> fontBuffer;
        static inline std::vector<stbtt_fontinfo> fonts;

        static inline unsigned char* ImageData;     

    private:

        
        
        static bool loadFontFile(std::vector<const char*> filenames){
            try {

                for(unsigned int i = 0; i < filenames.size(); i++)
                {
                    const char* filename = filenames[i];
                    const char* fontPath = filename; // Replace with your font file

                    fonts.push_back(stbtt_fontinfo());

                    
                    // Open file in binary mode
                    std::ifstream fontFile(fontPath, std::ios::binary | std::ios::ate);
                    if (!fontFile) {
                        std::cerr << "Error: Could not open font file: " << fontPath << "\n";
                        return false;
                    }

                    // Get file size and read into buffer
                    std::streamsize size = fontFile.tellg();
                    fontFile.seekg(0, std::ios::beg);

                    if (size <= 0) {
                        std::cerr << "Error: Font file is empty or unreadable.\n";
                        return false;
                    }
                    
                    fontBuffer.push_back(std::vector<unsigned char>(static_cast<unsigned int>(size)));
                    
                    if (!fontFile.read(reinterpret_cast<char*>(fontBuffer[i].data()), size)) {
                        std::cerr << "Error: Failed to read font file.\n";
                        return false;
                    }

                    // Initialize font
                    
                    int offset = stbtt_GetFontOffsetForIndex(fontBuffer[i].data(), 0); // 0 = first font in file
                    if (offset < 0) {
                        std::cerr << "Error: Could not find font offset.\n";
                        return false;
                    }


                    if (!stbtt_InitFont(&fonts[i], fontBuffer[i].data(), offset)) {
                        std::cerr << "Error: stbtt_InitFont failed. Font may be corrupted or unsupported.\n";
                        return false;
                    }

                    fontFile.close();
                }
            } catch (const std::exception &e) {

                std::cerr << "Error: " << e.what() << "\n";
                
                return false;
            }

            return true;
        };

    static bool createPlanes(std::vector<std::vector<Plage>> PlagesOfFontsofGlyphs, int& panelWidth, int targetPixelHeight, const char* outSpacingGlyphsFilename){

        std::vector<unsigned char*> bitmap;

        std::vector<int*> width;
        std::vector<int*> height;
        std::vector<int*> xoff;
        std::vector<int*> yoff;
        std::vector<unsigned int> unicodeValues;
        long totalWidth = 0;
        
        int maxHeight = 0;

        calculateSizeAndPosition(PlagesOfFontsofGlyphs, targetPixelHeight, bitmap, width, height, xoff, yoff, unicodeValues, maxHeight, totalWidth);

        int sideSizeSqrt = sqrt(totalWidth * maxHeight * 1.01f);
        unsigned char* bitmapPlane = new unsigned char[sideSizeSqrt * sideSizeSqrt];

        clearColorToZero(bitmapPlane, sideSizeSqrt, sideSizeSqrt);

        int cntrH = 0;
        int cntrV = 0;

        int cc = 0;
        
        for(unsigned int i = 0; i < bitmap.size(); i++)
        {
            drawSubImage(bitmapPlane, bitmap[cc], sideSizeSqrt, sideSizeSqrt, cntrH, cntrV, *width[cc], *height[cc]);

            cntrH += *(width[cc]);

            if (cntrH > sideSizeSqrt)
            {
                cntrH = 0;
                cntrV += maxHeight;
            }
            else
            {
                cc++;
            }

            if (cntrV > sideSizeSqrt)
            {
                std::cerr << "Error: Panel height exceeded. Consider increasing panel size or reducing target pixel height.\n";
                return false;
            }            
        }

        panelWidth = sideSizeSqrt;
        bitmap.clear();
        
        //stbi_write_bmp("output.bmp", panelWidth, panelWidth, 1, bitmapPlane);
        if (!stbi_write_png(("output" + std::to_string(targetPixelHeight) + ".png").c_str(), panelWidth, panelWidth, 1, bitmapPlane, 0)) {
        
            fprintf(stderr, "Failed to write PNG file\n");
            free(bitmapPlane);
            return 1;
        }

        free(bitmapPlane);

        //fff.Close();

        /*
        // Open file in binary mode
        std::ofstream fontFile(outSpacingGlyphsFilename, std::ios::binary);
        if (!fontFile) {
            std::cerr << "Error: Could not open font file: " << outSpacingGlyphsFilename << "\n";
            return false;
        }

        if (!fontFile.write(reinterpret_cast<char*>(fontBuffer.data()), size)) {
            std::cerr << "Error: Failed to write font file.\n";
            return false;
        }

        fontFile.close();*/

        return true;
    }

    static void clearColorToZero(unsigned char* bmp, int width, int height)
    {
        int length = width * height;

        for(int i = 0; i < length; i++)
        {
            bmp[i] = 255;
        }
    }

    static void calculateSizeAndPosition(std::vector<std::vector<Plage>> PlagesOfFontsofGlyphs, int pixelHeight, std::vector<unsigned char*>& bitmap, std::vector<int*>& width, std::vector<int*>& height,
         std::vector<int*>& xoff, std::vector<int*>& yoff, std::vector<unsigned int>& unicodeValues, int& maxDeltaHeight, long& totalWidth)
    {     
                
        int maxHeight = 0;

        int pos = 0;

        for(unsigned int j = 0; j < PlagesOfFontsofGlyphs.size(); j++)
        {

            for(unsigned int i = 0; i < PlagesOfFontsofGlyphs[j].size(); i++)
            {

                for (unsigned int k = (unsigned int)PlagesOfFontsofGlyphs[j][i].startPos; k < (unsigned int)PlagesOfFontsofGlyphs[j][i].endPos; k++)
                {
            
                    // Get bitmap for the glyph
                    float scale = stbtt_ScaleForPixelHeight(&fonts[j], (float)pixelHeight); // 32px height
        
                    int exist = stbtt_FindGlyphIndex(&fonts[j], k);

                    if(exist == 0) continue;

                    width.push_back(new int);
                    height.push_back(new int);
                    xoff.push_back(new int);
                    yoff.push_back(new int);

                    bitmap.push_back(stbtt_GetGlyphBitmap(&fonts[j], 0, scale, exist, width[pos], height[pos], xoff[pos], yoff[pos]));

                    unicodeValues.push_back(k + PlagesOfFontsofGlyphs[j][i].jumpForCJK);

                    totalWidth += *width[pos];

                    if(maxHeight < *height[pos]) maxHeight = *height[pos];

                    pos++;
                }
            }          
        }

        maxDeltaHeight = maxHeight;
    };

    static bool checkPresence(Plage p)
    {

        int count = 0;

        for(unsigned int j = p.startPos; j < p.endPos; j++)
        {

            int exist = stbtt_FindGlyphIndex(&fonts[0], j);
            
            if(exist > 0) count++;

            if(count > 3) return true;
        }

        return false;
    };
        
    static void getGlyphAscentAndHeight(unsigned char* bmp, int width, int height, int& asc, int& desc){
    
        int fasc = 0;
        bool jump = false;

        unsigned char pixelColor;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                pixelColor = GIB::getPixel(bmp, x, y, width, height);
                
                if (pixelColor > 0) // Assuming black text on white background
                {
                    fasc = y;
                    jump = true;
                    break;
                }
            }

            if (jump) break;
        }

        for (int y = height - 1; y >= 0; y--)
        {
            for (int x = 0; x < width; x++)
            {
                pixelColor = GIB::getPixel(bmp, x, y, width, height);
                
                if (pixelColor > 0) // Assuming black text on white background
                {
                    asc = fasc;
                    desc = y;

                    return;
                }
            }
        }

        asc = height;
        desc = 0;
    };
        
    static unsigned char getPixel(unsigned char* bmp, int x, int y, int width, int height){

        unsigned char data;

        data = bmp[y * width + x];
        
        return data;
    };
        
   
    
    static unsigned char* getSubImage(unsigned char* bmp, int width, int height, int destPosX, int destPosY, int destWidth, int destHeight){

        unsigned char* subImage = new unsigned char[destWidth * destHeight];

        int posSubX = 0;
        int posSubY = 0;
        int lineY = 0;

        for(int i = destPosX; i < destWidth; i++)
        {

            posSubX = i - destWidth;
            lineY = i * width;

            for(int j = destPosY; j < destHeight; j++)
            {

                subImage[posSubX * destWidth + j - destHeight] = bmp[posSubX * width + j - destPosY];
            }
        }

        return subImage;
    };
          
    static bool drawSubImage(unsigned char* bmp, unsigned char* subImage, int width, int height, int destPosX, int destPosY, int destWidth, int destHeight){
    
        int posSubX = 0;
        int lineY = 0;

        int distY = 0;
        int distX = 0;

        for(int i = destPosY; i < destPosY + destHeight; i++)
        {     
            distY = i * width;
            distX = (i - destPosY) * destWidth;

            if(i >= height) break;

            for(int j = destPosX; j < destPosX + destWidth; j++)
            {
                if(j >= width) break;
                // Assuming black text on white background
                bmp[distY + j] = 255 - subImage[distX + j - destPosX];
            }
        }

        return true;
    };
        
    static unsigned char* cutGlyphRemoveSides(unsigned char* bmp, int width, int height){
    
        int left = width;
        int right = 0;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                unsigned char bmpPixel = getPixel(bmp, x, y, width, height);

                if (bmpPixel > 0) // Assuming black text on white background
                {
                    if (x < left) left = x;
                    if (x > right) right = x;
                }
            }
        }

        if (right >= left)
        {

            return getSubImage(bmp, width, height, left, 0, right - left, height);
        }
        else
        {

            return nullptr; // Return a single pixel bitmap if no glyph is found
        }
    };
};

#endif