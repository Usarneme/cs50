#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // validate usage/inputs: there should only be a single filename provided as input to this function
    if (argc != 2)
    {
        fprintf(stderr, "usage ./recover.c <source_file>\n");
        return 1;
    }

    // open the file for reading
    FILE *read_file = fopen(argv[1], "r");

    // exit if there is a problem with the read file
    if (read_file == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 2;
    }

    // create a buffer to look for jpg magic byte, of size 512 bytes per spec
    // use of unsigned required as a signed char will result in compile error
    // as a signed char isn't large enough to hold a hexadecimal numeral
    unsigned char *currently_buffered = malloc(512);

    // increment as images are discovered, for naming and tracking total
    int image_count = 0;

    // create a FILE pointer to hold any jpgs as they are uncovered
    FILE *output_write_file = NULL;

    // while there are still bytes to be read
    // iterate through the read_file one 512 byte block at a time
    while (fread(currently_buffered, 512, 1, read_file))
    {

        // Check if the first four bytes are JPG signature
        // bytes 0, 1, and 2 are defined
        // byte 3 may be any of the following: 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef
        if (currently_buffered[0] == 0xff && currently_buffered[1] == 0xd8 && currently_buffered[2] == 0xff
            && (currently_buffered[3] == 0xe0 || currently_buffered[3] == 0xe1 || currently_buffered[3] == 0xe2
                || currently_buffered[3] == 0xe3 || currently_buffered[3] == 0xe4 || currently_buffered[3] == 0xe5 || currently_buffered[3] == 0xe6
                || currently_buffered[3] == 0xe7 || currently_buffered[3] == 0xe8 || currently_buffered[3] == 0xe9 || currently_buffered[3] == 0xea
                || currently_buffered[3] == 0xeb || currently_buffered[3] == 0xec || currently_buffered[3] == 0xed || currently_buffered[3] == 0xee
                || currently_buffered[3] == 0xef))
        {
            // TRUE -> a jpg file was found
            // if the file was already opened, we were writing a jpg before, therefore we need to end/close the previous jpg
            if (output_write_file != NULL)
            {
                fclose(output_write_file);
            }

            // create and name a new file by pattern e.g.: 000.jpg through NNN.jpg, spec wants 3 digits .jpg starting at index 000
            char output_file_name[8];
            sprintf(output_file_name, "%03d.jpg", image_count);

            // open the output file for writing "w"
            output_write_file = fopen(output_file_name, "w");

            // increment the counter
            image_count++;
        }

        // if there is an open output file...write 512 bytes to it
        if (output_write_file != NULL)
        {
            fwrite(currently_buffered, 512, 1, output_write_file);
        }
    }

    // if the output file pointer points to a valid memory location the file is open...close it
    if (output_write_file != NULL)
    {
        fclose(output_write_file);
    }

    // no memory leaks, free the buffer
    free(currently_buffered);

    // at this point we have traversed all blocks, written all outputs and closed all output files, and freed buffer memory...close the read file
    fclose(read_file);

    // return success!
    return 0;
}
