#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    if (argc != 2 || argc < 2)
    {
        printf("Invalid input.\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    unsigned char *buffer = malloc(512);
    FILE *img;
    int counter = 0;
    char filename[7];

    while (fread(buffer, 512, 1, file))
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter > 0)
            {
                fclose(img);
            }

            sprintf(filename, "%03d.jpg", counter);
            img = fopen(filename, "w");

            if (img == NULL)
            {
                fclose(file);
                free(buffer);
                return 2;
            }

            counter++;
        }

        if (counter > 0)
        {
            fwrite(buffer, 512, 1, img);
        }

    }
    fclose(img);
    fclose(file);
    free(buffer);
    return 0;
}
