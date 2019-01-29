#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage ./resize resize_factor bmp_input_file bmp_output_file\n");
        return 1;
    }
    // the first (n) must be a positive integer less than or equal to 100,
    // the second must be the name of a BMP to be resized, and
    // the third must be the name of the resized version to be written.
    int resize_factor = atoi(argv[1]);
    char *bmp_input_file = argv[2];
    char *bmp_output_file = argv[3];

    printf("rsf %i | input %s | output %s\n", resize_factor, bmp_input_file, bmp_output_file);

    if (!resize_factor || resize_factor < 1 || resize_factor > 100 || bmp_input_file == NULL || bmp_output_file == NULL)
    {
        printf("Usage ./resize resize_factor bmp_input_file bmp_output_file\n");
        return 1;
    }
    // inputs validated

    // open input file
    FILE *inptr = fopen(bmp_input_file, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", bmp_input_file);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(bmp_output_file, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", bmp_output_file);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // dimensions of the original pixel-only scanline
    int original_width = bi.biWidth;
    // total bit width must be divisible by 4
    int original_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // printf("BEFORE bfSize %i biSizeImage %i biWidth %i biHeight %i original_padding %i\n", bf.bfSize, bi.biSizeImage, bi.biWidth, bi.biHeight, original_padding);
    // note: If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.

    // Adjust header data as well as dimensions of the bitmap based on the resize_factor provided
    // resizing width w * resize_factor = new width
    bi.biWidth *= resize_factor;
    // resizing height h * r_f = new height
    bi.biHeight *= resize_factor;

    // total bit width must be divisible by 4
    int row_padding = (4 - (original_width * sizeof(RGBTRIPLE) * resize_factor) % 4) % 4;

    // Set the new bitmap image size based on the adjusted dimensions
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth + row_padding) * abs(bi.biHeight));
    // Set the new bitmap file size based on the updated dimensions
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    // printf("AFTER  bfSize %i biSizeImage %i biWidth %i biHeight %i row_padding %i\n", bf.bfSize, bi.biSizeImage, bi.biWidth, bi.biHeight, row_padding);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(original_width); i < biHeight; i++)
    {
        // the starting line position in the original bitmap
        int original_line = ftell(inptr);

        // repeat writing each line resize_factor number of times
        for (int r = 0; r < resize_factor; r++)
        {
            // set read position to start of the current scanline
            fseek(inptr, original_line, SEEK_SET);
            int scan_line = ftell(inptr);
            // printf("Line %i. Reading initial pos %i.", r, scan_line);

            // iterate over pixels in scanline
            for (int j = 0; j < original_width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // repeat the write resize_factor number of times
                for (int w = 0; w < resize_factor; w++)
                {
                    // int pos = ftell(inptr);
                    // printf("writing %i,", pos);
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, original_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < row_padding; k++)
            {
                // printf("adding padding %i of %i. ", k+1, row_padding);
                fputc(0x00, outptr);
            }
            // printf("\n");
        }
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    // printf("Success!\n");
    return 0;
}
