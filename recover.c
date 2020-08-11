#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<cs50.h>




int main(int argc, char * argv[]) {

    if (argc != 2)
    {
        printf("Usage : ./recover image");
        return 1;
    }




    FILE * given_file = fopen(argv[1], "r");




    if (given_file == NULL)
    {
        printf("There is no file !");
        return 1;
    }



    fseek(given_file, 0L, SEEK_END);
    int size = ftell(given_file);
    rewind(given_file);



    unsigned char data[size];




    fread(data, size, 1, given_file);




    FILE * out_put = NULL;

    int index = 0;

    char name[8];

    int j = size/ 512 ;


    for (int i = 0  ; i < j; i += 512)
    {

        if (data[i] == 0xff && data[i + 1] == 0xd8 && data[i + 2] == 0xff && (data[i + 3] & 0xe0) == 0xe0)
        {


            if (index == 0)
            {
                index++;

                sprintf(name, "%03d.jpg", index);

                out_put = fopen(name, "a");


                for (int k = 0; k < 512; k++)
                {
                    fwrite(&data[i], 1, 1, out_put);
                }



            } else if (index > 0)
            {
                fclose(out_put);



                index++;

                sprintf(name, "%03d.jpg", index);

                out_put = fopen(name, "a");


                for (int k = 0; k < 512; k++)
                {
                    fwrite(&data[i], 1, 1, out_put);
                }




            }




        } else if (index > 0)
        {



            for (int k = 0; k < 512; k++)
            {
                fwrite(&data[i], 1, 1, out_put);
            }


        }




    }




    fclose(out_put);
    fclose(given_file);

    return 0;




}
