/**
 * resize.c
 *
 * CS50
 * pset4
 *
 * Resizes an input bmp file by a (positive) factor of n (<= 100)
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // remember n
    int n = atoi(argv[1]);
    
    // ensure proper useage
    if (n < 1 || n > 100)
    {
        printf("n must be 0 < n <= 100\n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // declare new file header
    BITMAPFILEHEADER newbf;
    BITMAPINFOHEADER newbi;
    
    // set equal to input file headers
    newbf = bf;
    newbi = bi;
    
    
    
    // modify new file headers by n
    
    newbi.biWidth = bi.biWidth * n;
    newbi.biHeight = bi.biHeight * n;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newpadding = (4 - (newbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // newbi.biSizeImage = bi.biSizeImage * n * n;
    newbi.biSizeImage = abs(newbi.biHeight) * (newbi.biWidth * sizeof(RGBTRIPLE) + newpadding);
    
    // newbf.bfSize = (bf.bfSize - 54) * n * n + 54;
    newbf.bfSize = newbi.biSizeImage + 54; 
   

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    
    // counter for repeating vertical line scanning
    int fseekcount = 0;

    // iterate over infile's scanlines
    for (int i = 0, newbiHeight = abs(newbi.biHeight); i < newbiHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile n times for horizontal resizing
            for (int jj = 0; jj < n; jj++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // skip over input padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // add output padding, if any
        for (int k = 0; k < newpadding; k++)
        {
            fputc(0x00, outptr);
        }
        
        // fseek the inptr back to the start of the row n-1 times 
        // to resize vertically
        if (fseekcount < (n - 1))
        {
            fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE) + padding), SEEK_CUR);
            fseekcount++;
        }
        else
        {
            fseekcount = 0;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
