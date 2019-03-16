#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encode.h"

__declspec(dllexport) void show_menu()
{
    int choice = -1;
    printf("ENCODING CONVERTER\n\n");

    while (choice != 6)
    {
        printf("1- Choose input text format\n");
        printf("2- Choose output text format\n");
        printf("3- Enter input filename\n");
        printf("4- Enter output filename\n");
        printf("5- Convert\n");
        printf("6- Quit\n\n");

        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            choose_input_text_format();
            break;
        case 2:
            choose_output_text_format();
            break;
        case 3:
            enter_input_filename();
            break;
        case 4:
            enter_output_filename();
            break;
        case 5:
            convert();
            break;
        case 6:
            choice = 6;
            break;
        default:
            break;
        }
    }
}

__declspec(dllexport) void choose_input_text_format()
{
    int choice = -1;
    printf("1 - UTF-8\n");
    printf("2 - UTF-16BE\n");
    printf("3 - UTF-16LE\n");
    printf("4 - UTF-32BE\n");
    printf("5 - UTF-32LE\n");
    printf("6 - ISO8859-1\n");
    printf("7 - ISO8859-9\n");
    printf("8 - Detect encoding\n\n");

    printf("Choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        input_text_format = "UTF-8";
        break;
    case 2:
        input_text_format = "UTF-16BE";
        break;
    case 3:
        input_text_format = "UTF-16LE";
        break;
    case 4:
        input_text_format = "UTF-32BE";
        break;
    case 5:
        input_text_format = "UTF-32LE";
        break;
    case 6:
        input_text_format = "ISO8859-1";
        break;
    case 7:
        input_text_format = "ISO8859-9";
        break;
    default:
        input_text_format = NULL;
        break;
    }
}

__declspec(dllexport) void set_input_text_format(const char *text_format)
{
    if (text_format != NULL)
    {
        input_text_format = malloc(strlen(text_format) + 1);
        strcpy(input_text_format, text_format);
    }
    else
        input_text_format = NULL;
}

__declspec(dllexport) void choose_output_text_format()
{
    int choice = -1;
    printf("1  - UTF-8\n");
    printf("2  - UTF-8 without BOM\n");
    printf("3  - UTF-16BE\n");
    printf("4  - UTF-16BE without BOM\n");
    printf("5  - UTF-16LE\n");
    printf("6  - UTF-16LE without BOM\n");
    printf("7  - UTF-32BE\n");
    printf("8  - UTF-32BE without BOM\n");
    printf("9  - UTF-32LE\n");
    printf("10 - UTF-32LE without BOM\n");
    printf("11 - ISO8859-1\n");
    printf("12 - ISO8859-9\n");

    printf("Choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        output_text_format = "UTF-8";
        break;
    case 2:
        output_text_format = "UTF-8 without BOM";
        break;
    case 3:
        output_text_format = "UTF-16BE";
        break;
    case 4:
        output_text_format = "UTF-16BE without BOM";
        break;
    case 5:
        output_text_format = "UTF-16LE";
        break;
    case 6:
        output_text_format = "UTF-16LE without BOM";
        break;
    case 7:
        output_text_format = "UTF-32BE";
        break;
    case 8:
        output_text_format = "UTF-32BE without BOM";
        break;
    case 9:
        output_text_format = "UTF-32LE";
        break;
    case 10:
        output_text_format = "UTF-32LE without BOM";
        break;
    case 11:
        output_text_format = "ISO8859-1";
        break;
    case 12:
        output_text_format = "ISO8859-9";
        break;
    default:
        output_text_format = "UTF-8";
        break;
    }
}

__declspec(dllexport) void set_output_text_format(const char *text_format)
{
    output_text_format = malloc(strlen(text_format) + 1);
    strcpy(output_text_format, text_format);
}

__declspec(dllexport) void enter_input_filename()
{
    unsigned int len_max = 4;
    unsigned int current_size = 0;

    input_filename = malloc(len_max);
    current_size = len_max;

    printf("Please enter input filename: ");

    if (input_filename != NULL)
    {
        int c = EOF;
        unsigned int i = 0;

        getchar();

        while ((c = getchar()) != '\n' && c != EOF)
        {
            input_filename[i++] = (char)c;

            if (i == current_size)
            {
                current_size = i + len_max;
                input_filename = realloc(input_filename, current_size);
            }
        }

        input_filename[i] = '\0';
    }
}

__declspec(dllexport) void set_input_filename(const char *filename)
{
    input_filename = malloc(strlen(filename) + 1);
    strcpy(input_filename, filename);
}

__declspec(dllexport) void enter_output_filename()
{
    unsigned int len_max = 4;
    unsigned int current_size = 0;

    output_filename = malloc(len_max);
    current_size = len_max;

    printf("Please enter output filename: ");

    if (output_filename != NULL)
    {
        int c = EOF;
        unsigned int i = 0;

        getchar();

        while ((c = getchar()) != '\n' && c != EOF)
        {
            output_filename[i++] = (char)c;

            if (i == current_size)
            {
                current_size = i + len_max;
                output_filename = realloc(output_filename, current_size);
            }
        }

        output_filename[i] = '\0';
    }
}

__declspec(dllexport) void set_output_filename(const char *filename)
{
    output_filename = malloc(strlen(filename) + 1);
    strcpy(output_filename, filename);
}

__declspec(dllexport) void convert()
{
    int start_index = 0;
    unsigned int j = 0;
    unsigned int size = 0;
    unsigned int output_size;
    FILE *input_file;
    FILE *output_file;
    unsigned char *file;
    input_file = fopen(input_filename, "r");

    fseek(input_file, 0, SEEK_END);
    size = ftell(input_file);

    rewind(input_file);
    file = malloc((size + 1) * sizeof(*file));
    fread(file, size, 1, input_file);
    fclose(input_file);
    file[size] = '\0';

    if (input_text_format == NULL)
    {
        if (size >= 3 && file[0] == 0xEF && file[1] == 0xBB && file[2] == 0xBF)
            input_text_format = "UTF-8";
        else if (size >= 4 && file[0] == 0x00 && file[1] == 0x00 && file[2] == 0xFE && file[3] == 0xFF)
            input_text_format = "UTF-32BE";
        else if (size >= 4 && file[0] == 0xFF && file[1] == 0xFE && file[2] == 0x00 && file[3] == 0x00)
            input_text_format = "UTF-32LE";
        else if (size >= 2 && file[0] == 0xFE && file[1] == 0xFF)
            input_text_format = "UTF-16BE";
        else if (size >= 2 && file[0] == 0xFF && file[1] == 0xFE)
            input_text_format = "UTF-16LE";
        else
            input_text_format = "ISO8859-1";
    }

    if (strcmp(input_text_format, "UTF-8") == 0)
    {
        if (size >= 3 && file[0] == 0xEF && file[1] == 0xBB && file[2] == 0xBF)
            start_index = 3;

        input = file + start_index;
    }
    else if (strcmp(input_text_format, "UTF-16BE") == 0)
    {
        unsigned int i;
        int code_point;
        int code_unit, code_unit2;
        if (size >= 2 && file[0] == 0xFE && file[1] == 0xFF)
            start_index = 2;

        input = malloc((size * 2) * sizeof(*file));

        i = start_index;

        while (i < size)
        {
            code_unit = (file[i] * 16 * 16) + file[i + 1];
            if (code_unit >= 0xD800 && code_unit <= 0xDBFF)
            {
                code_unit2 = (file[i + 2] * 16 * 16) + file[i + 3];
                if (code_unit2 >= 0xDC00 && code_unit2 <= 0xDFFF)
                    code_point = (code_unit << 10) + code_unit2 - 0x35FDC00;

                i += 4;
            }
            else
            {
                code_point = code_unit;
                i += 2;
            }

            if (code_point < 0x80)
            {
                input[j] = code_point;
                j++;
            }
            else if (code_point < 0x800)
            {
                input[j] = 0xC0 | (code_point >> 6);
                input[j + 1] = 0x80 | (code_point & 0x3F);
                j += 2;
            }
            else if (code_point < 0x10000)
            {
                input[j] = 0xE0 | (code_point >> 12);
                input[j + 1] = 0x80 | ((code_point >> 6) & 0x3F);
                input[j + 2] = 0x80 | (code_point & 0x3F);
                j += 3;
            }
            else if (code_point < 0x11000)
            {
                input[j] = 0xF0 | (code_point >> 18);
                input[j + 1] = 0x80 | ((code_point >> 12) & 0x3F);
                input[j + 2] = 0x80 | ((code_point >> 6) & 0x3F);
                input[j + 3] = 0x80 | (code_point & 0x3F);
                j += 4;
            }
        }
    }
    else if (strcmp(input_text_format, "UTF-16LE") == 0)
    {
        unsigned int i;
        int code_point;
        int code_unit, code_unit2;
        if (size >= 2 && file[0] == 0xFF && file[1] == 0xFE)
            start_index = 2;

        input = malloc((size * 2) * sizeof(*file));

        i = start_index;

        while (i < size)
        {
            code_unit = (file[i + 1] * 16 * 16) + file[i];
            if (code_unit >= 0xD800 && code_unit <= 0xDBFF)
            {
                code_unit2 = (file[i + 3] * 16 * 16) + file[i + 2];
                if (code_unit2 >= 0xDC00 && code_unit2 <= 0xDFFF)
                    code_point = (code_unit << 10) + code_unit2 - 0x35FDC00;

                i += 4;
            }
            else
            {
                code_point = code_unit;
                i += 2;
            }

            if (code_point < 0x80)
                input[j++] = code_point;
            else if (code_point < 0x800)
            {
                input[j] = 0xC0 | (code_point >> 6);
                input[j + 1] = 0x80 | (code_point & 0x3F);
                j += 2;
            }
            else if (code_point < 0x10000)
            {
                input[j] = 0xE0 | (code_point >> 12);
                input[j + 1] = 0x80 | ((code_point >> 6) & 0x3F);
                input[j + 2] = 0x80 | (code_point & 0x3F);
                j += 3;
            }
            else if (code_point < 0x11000)
            {
                input[j] = 0xF0 | (code_point >> 18);
                input[j + 1] = 0x80 | ((code_point >> 12) & 0x3F);
                input[j + 2] = 0x80 | ((code_point >> 6) & 0x3F);
                input[j + 3] = 0x80 | (code_point & 0x3F);
                j += 4;
            }
        }
    }
    else if (strcmp(input_text_format, "UTF-32BE") == 0)
    {
        unsigned int i;
        int code_point;
        int code_unit, code_unit2;
        if (size >= 4 && file[0] == 0x00 && file[1] == 0x00 && file[2] == 0xFE && file[3] == 0xFF)
            start_index = 4;

        input = malloc(size * sizeof(*file));

        i = start_index;

        while (i < size)
        {
            code_point = (file[i + 1] * 16 * 16 * 16 * 16) + (file[i + 2] * 16 * 16) + file[i + 3];
            if (code_point < 0x80)
                input[j++] = code_point;
            else if (code_point < 0x800)
            {
                input[j] = 0xC0 | (code_point >> 6);
                input[j + 1] = 0x80 | (code_point & 0x3F);
                j += 2;
            }
            else if (code_point < 0x10000)
            {
                input[j] = 0xE0 | (code_point >> 12);
                input[j + 1] = 0x80 | ((code_point >> 6) & 0x3F);
                input[j + 2] = 0x80 | (code_point & 0x3F);
                j += 3;
            }
            else if (code_point < 0x11000)
            {
                input[j] = 0xF0 | (code_point >> 18);
                input[j + 1] = 0x80 | ((code_point >> 12) & 0x3F);
                input[j + 2] = 0x80 | ((code_point >> 6) & 0x3F);
                input[j + 3] = 0x80 | (code_point & 0x3F);
                j += 4;
            }
            i += 4;
        }
    }
    else if (strcmp(input_text_format, "UTF-32LE") == 0)
    {
        unsigned int i;
        int code_point;
        int code_unit, code_unit2;
        if (size >= 4 && file[0] == 0xFF && file[1] == 0xFE && file[2] == 0x00 && file[3] == 0x00)
            start_index = 4;

        input = malloc(size * sizeof(*file));

        i = start_index;

        while (i < size)
        {
            code_point = (file[i + 2] * 16 * 16 * 16 * 16) + (file[i + 1] * 16 * 16) + file[i];
            if (code_point < 0x80)
                input[j++] = code_point;
            else if (code_point < 0x800)
            {
                input[j] = 0xC0 | (code_point >> 6);
                input[j + 1] = 0x80 | (code_point & 0x3F);
                j += 2;
            }
            else if (code_point < 0x10000)
            {
                input[j] = 0xE0 | (code_point >> 12);
                input[j + 1] = 0x80 | ((code_point >> 6) & 0x3F);
                input[j + 2] = 0x80 | (code_point & 0x3F);
                j += 3;
            }
            else if (code_point < 0x11000)
            {
                input[j] = 0xF0 | (code_point >> 18);
                input[j + 1] = 0x80 | ((code_point >> 12) & 0x3F);
                input[j + 2] = 0x80 | ((code_point >> 6) & 0x3F);
                input[j + 3] = 0x80 | (code_point & 0x3F);
                j += 4;
            }
            i += 4;
        }
    }
    else if (strcmp(input_text_format, "ISO8859-1") == 0)
    {
        unsigned int i = 0;

        input = malloc((size * 2) * sizeof(*file));

        while (i < size)
        {
            if (file[i] < 0x80)
                input[j++] = file[i];
            else
            {
                input[j++] = 0xC2 + (file[i] > 0xBF);
                input[j++] = (file[i] & 0x3F) + 0x80;
            }
            i++;
        }
    }
    else if (strcmp(input_text_format, "ISO8859-9") == 0)
    {
        int i = 0;

        input = malloc((size * 2) * sizeof(*file));

        while (i < size)
        {
            if (file[i] < 0x80)
                input[j++] = file[i];
            else
            {
                switch (file[i])
                {
                case 0xD0:
                    input[j++] = 0xC4;
                    input[j++] = 0x9E;
                case 0xDD:
                    input[j++] = 0xC4;
                    input[j++] = 0xB0;
                case 0xDE:
                    input[j++] = 0xC5;
                    input[j++] = 0x9E;
                case 0xF0:
                    input[j++] = 0xC4;
                    input[j++] = 0x9F;
                case 0xFD:
                    input[j++] = 0xC4;
                    input[j++] = 0xB1;
                case 0xFE:
                    input[j++] = 0xC5;
                    input[j++] = 0x9F;
                default:
                    input[j++] = 0xC2 + (file[i] > 0xBF);
                    input[j++] = (file[i] & 0x3F) + 0x80;
                    break;
                }
            }
            i++;
        }
    }

    output_file = fopen(output_filename, "wb");

    if (output_text_format == NULL)
        output_text_format = "UTF-8 without BOM";

    if (j != 0)
        output_size = j;
    else
        output_size = size - start_index;

    if (strcmp(output_text_format, "UTF-8") == 0)
    {
        output = malloc((output_size + 3) * sizeof(*file));
        output[0] = 0xEF;
        output[1] = 0xBB;
        output[2] = 0xBF;
        memcpy(output + 3, input, output_size);
        output_size += 3;
    }
    else if (strcmp(output_text_format, "UTF-8 without BOM") == 0)
        output = input;
    else if (strcmp(output_text_format, "UTF-16BE") == 0)
    {
        unsigned int i = 0, k = 2;
        int code_point;
        int code_point2;

        output = malloc(((output_size * 4) + 2) * sizeof(*file));
        output[0] = 0xFE;
        output[1] = 0xFF;

        while (i < output_size)
        {
            if (input[i] < 0x80)
            {
                output[k] = 0x00;
                output[k + 1] = input[i];

                k += 2;
                i++;
            }
            else if ((input[i] & 0xE0) == 0xE0)
            {
                code_point = (input[i] & 0x0F) << 12 | (input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F);
                if (code_point < 0x10000)
                {
                    output[k] = ((code_point - (code_point % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 1] = code_point % (16 * 16);

                    k += 2;
                }
                else if (code_point <= 0x10FFFF)
                {
                    code_point2 = (code_point >> 10) + 0xD7C0;
                    output[k] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 1] = code_point2 % (16 * 16);

                    code_point2 = (code_point & 0x3FF) + 0xDC00;
                    output[k + 2] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 3] = code_point2 % (16 * 16);

                    k += 4;
                }

                i += 3;
            }
            else if ((input[i] & 0xC0) == 0xC0)
            {
                code_point = (input[i] & 0x1F) << 6 | (input[i + 1] & 0x3F);
                if (code_point < 0x10000)
                {
                    output[k] = ((code_point - (code_point % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 1] = code_point % (16 * 16);

                    k += 2;
                }
                else if (code_point <= 0x10FFFF)
                {
                    code_point2 = (code_point >> 10) + 0xD7C0;
                    output[k] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 1] = code_point2 % (16 * 16);

                    code_point2 = (code_point & 0x3FF) + 0xDC00;
                    output[k + 2] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 3] = code_point2 % (16 * 16);

                    k += 4;
                }
                i += 2;
            }
        }
        output_size = k;
    }
    else if (strcmp(output_text_format, "UTF-16BE without BOM") == 0)
    {
        unsigned int i = 0, k = 0;
        int code_point;
        int code_point2;

        output = malloc((output_size * 4) * sizeof(*file));

        while (i < output_size)
        {
            if (input[i] < 0x80)
            {
                output[k] = 0x00;
                output[k + 1] = input[i];

                k += 2;
                i++;
            }
            else if ((input[i] & 0xE0) == 0xE0)
            {
                code_point = (input[i] & 0x0F) << 12 | (input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F);
                if (code_point < 0x10000)
                {
                    output[k] = ((code_point - (code_point % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 1] = code_point % (16 * 16);

                    k += 2;
                }
                else if (code_point <= 0x10FFFF)
                {
                    code_point2 = (code_point >> 10) + 0xD7C0;
                    output[k] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 1] = code_point2 % (16 * 16);

                    code_point2 = (code_point & 0x3FF) + 0xDC00;
                    output[k + 2] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 3] = code_point2 % (16 * 16);

                    k += 4;
                }

                i += 3;
            }
            else if ((input[i] & 0xC0) == 0xC0)
            {
                code_point = (input[i] & 0x1F) << 6 | (input[i + 1] & 0x3F);
                if (code_point < 0x10000)
                {
                    output[k] = ((code_point - (code_point % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 1] = code_point % (16 * 16);

                    k += 2;
                }
                else if (code_point <= 0x10FFFF)
                {
                    code_point2 = (code_point >> 10) + 0xD7C0;
                    output[k] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 1] = code_point2 % (16 * 16);

                    code_point2 = (code_point & 0x3FF) + 0xDC00;
                    output[k + 2] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 3] = code_point2 % (16 * 16);

                    k += 4;
                }
                i += 2;
            }
        }
        output_size = k;
    }
    else if (strcmp(output_text_format, "UTF-16LE") == 0)
    {
        unsigned int i = 0, k = 2;
        int code_point;
        int code_point2;

        output = malloc(((output_size * 4) + 2) * sizeof(*file));
        output[0] = 0xFF;
        output[1] = 0xFE;

        while (i < output_size)
        {
            if (input[i] < 0x80)
            {
                output[k + 1] = 0x00;
                output[k] = input[i];

                k += 2;
                i++;
            }
            else if ((input[i] & 0xE0) == 0xE0)
            {
                code_point = (input[i] & 0x0F) << 12 | (input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F);
                if (code_point < 0x10000)
                {
                    output[k + 1] = ((code_point - (code_point % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k] = code_point % (16 * 16);

                    k += 2;
                }
                else if (code_point <= 0x10FFFF)
                {
                    code_point2 = (code_point >> 10) + 0xD7C0;
                    output[k + 1] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k] = code_point2 % (16 * 16);

                    code_point2 = (code_point & 0x3FF) + 0xDC00;
                    output[k + 3] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 2] = code_point2 % (16 * 16);

                    k += 4;
                }

                i += 3;
            }
            else if ((input[i] & 0xC0) == 0xC0)
            {
                code_point = (input[i] & 0x1F) << 6 | (input[i + 1] & 0x3F);
                if (code_point < 0x10000)
                {
                    output[k + 1] = ((code_point - (code_point % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k] = code_point % (16 * 16);

                    k += 2;
                }
                else if (code_point <= 0x10FFFF)
                {
                    code_point2 = (code_point >> 10) + 0xD7C0;
                    output[k + 1] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k] = code_point2 % (16 * 16);

                    code_point2 = (code_point & 0x3FF) + 0xDC00;
                    output[k + 3] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 2] = code_point2 % (16 * 16);

                    k += 4;
                }
                i += 2;
            }
        }
        output_size = k;
    }
    else if (strcmp(output_text_format, "UTF-16LE without BOM") == 0)
    {
        unsigned int i = 0, k = 0;
        int code_point;
        int code_point2;

        output = malloc((output_size * 4) * sizeof(*file));

        while (i < output_size)
        {
            if (input[i] < 0x80)
            {
                output[k + 1] = 0x00;
                output[k] = input[i];

                k += 2;
                i++;
            }
            else if ((input[i] & 0xE0) == 0xE0)
            {
                code_point = (input[i] & 0x0F) << 12 | (input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F);
                if (code_point < 0x10000)
                {
                    output[k + 1] = ((code_point - (code_point % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k] = code_point % (16 * 16);

                    k += 2;
                }
                else if (code_point <= 0x10FFFF)
                {
                    code_point2 = (code_point >> 10) + 0xD7C0;
                    output[k + 1] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k] = code_point2 % (16 * 16);

                    code_point2 = (code_point & 0x3FF) + 0xDC00;
                    output[k + 3] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 2] = code_point2 % (16 * 16);

                    k += 4;
                }

                i += 3;
            }
            else if ((input[i] & 0xC0) == 0xC0)
            {
                code_point = (input[i] & 0x1F) << 6 | (input[i + 1] & 0x3F);
                if (code_point < 0x10000)
                {
                    output[k + 1] = ((code_point - (code_point % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k] = code_point % (16 * 16);

                    k += 2;
                }
                else if (code_point <= 0x10FFFF)
                {
                    code_point2 = (code_point >> 10) + 0xD7C0;
                    output[k + 1] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k] = code_point2 % (16 * 16);

                    code_point2 = (code_point & 0x3FF) + 0xDC00;
                    output[k + 3] = ((code_point2 - (code_point2 % (16 * 16))) % (16 * 16 * 16 * 16)) / (16 * 16);
                    output[k + 2] = code_point2 % (16 * 16);

                    k += 4;
                }
                i += 2;
            }
        }
        output_size = k;
    }
    else if (strcmp(output_text_format, "UTF-32BE") == 0)
    {
        unsigned int i = 0, k = 4;
        int code_point;
        int code_point2;

        output = malloc(((output_size * 4) + 2) * sizeof(*file));
        output[0] = 0x00;
        output[1] = 0x00;
        output[2] = 0xFE;
        output[3] = 0xFF;

        while (i < output_size)
        {
            if (input[i] < 0x80)
            {
                output[k] = 0x00;
                output[k + 1] = 0x00;
                output[k + 2] = 0x00;
                output[k + 3] = input[i];

                k += 4;
                i++;
            }
            else if ((input[i] & 0xE0) == 0xE0)
            {
                code_point = (input[i] & 0x0F) << 12 | (input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F);
                output[k + 3] = code_point % (16 * 16);
                output[k + 2] = ((code_point - output[k + 3]) % (16 * 16 * 16 * 16)) / (16 * 16);
                output[k + 1] = ((code_point - output[k + 3] - (output[k + 2] * 16 * 16)) % (16 * 16 * 16 * 16 * 16 * 16)) / (16 * 16 * 16 * 16);
                output[k] = 0x00;

                k += 4;
                i += 3;
            }
            else if ((input[i] & 0xC0) == 0xC0)
            {
                code_point = (input[i] & 0x1F) << 6 | (input[i + 1] & 0x3F);
                output[k + 3] = code_point % (16 * 16);
                output[k + 2] = ((code_point - output[k + 3]) % (16 * 16 * 16 * 16)) / (16 * 16);
                output[k + 1] = ((code_point - output[k + 3] - (output[k + 2] * 16 * 16)) % (16 * 16 * 16 * 16 * 16 * 16)) / (16 * 16 * 16 * 16);
                output[k] = 0x00;

                k += 4;
                i += 2;
            }
        }
        output_size = k;
    }
    else if (strcmp(output_text_format, "UTF-32BE without BOM") == 0)
    {
        unsigned int i = 0, k = 0;
        int code_point;
        int code_point2;

        output = malloc((output_size * 4) * sizeof(*file));

        while (i < output_size)
        {
            if (input[i] < 0x80)
            {
                output[k] = 0x00;
                output[k + 1] = 0x00;
                output[k + 2] = 0x00;
                output[k + 3] = input[i];

                k += 4;
                i++;
            }
            else if ((input[i] & 0xE0) == 0xE0)
            {
                code_point = (input[i] & 0x0F) << 12 | (input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F);
                output[k + 3] = code_point % (16 * 16);
                output[k + 2] = ((code_point - output[k + 3]) % (16 * 16 * 16 * 16)) / (16 * 16);
                output[k + 1] = ((code_point - output[k + 3] - (output[k + 2] * 16 * 16)) % (16 * 16 * 16 * 16 * 16 * 16)) / (16 * 16 * 16 * 16);
                output[k] = 0x00;

                k += 4;
                i += 3;
            }
            else if ((input[i] & 0xC0) == 0xC0)
            {
                code_point = (input[i] & 0x1F) << 6 | (input[i + 1] & 0x3F);
                output[k + 3] = code_point % (16 * 16);
                output[k + 2] = ((code_point - output[k + 3]) % (16 * 16 * 16 * 16)) / (16 * 16);
                output[k + 1] = ((code_point - output[k + 3] - (output[k + 2] * 16 * 16)) % (16 * 16 * 16 * 16 * 16 * 16)) / (16 * 16 * 16 * 16);
                output[k] = 0x00;

                k += 4;
                i += 2;
            }
        }
        output_size = k;
    }
    else if (strcmp(output_text_format, "UTF-32LE") == 0)
    {
        unsigned int i = 0, k = 4;
        int code_point;
        int code_point2;

        output = malloc(((output_size * 4) + 2) * sizeof(*file));
        output[0] = 0xFF;
        output[1] = 0xFE;
        output[2] = 0x00;
        output[3] = 0x00;

        while (i < output_size)
        {
            if (input[i] < 0x80)
            {
                output[k + 3] = 0x00;
                output[k + 2] = 0x00;
                output[k + 1] = 0x00;
                output[k] = input[i];

                k += 4;
                i++;
            }
            else if ((input[i] & 0xE0) == 0xE0)
            {
                code_point = (input[i] & 0x0F) << 12 | (input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F);
                output[k] = code_point % (16 * 16);
                output[k + 1] = ((code_point - output[k]) % (16 * 16 * 16 * 16)) / (16 * 16);
                output[k + 2] = ((code_point - output[k] - (output[k + 1] * 16 * 16)) % (16 * 16 * 16 * 16 * 16 * 16)) / (16 * 16 * 16 * 16);
                output[k + 3] = 0x00;

                k += 4;
                i += 3;
            }
            else if ((input[i] & 0xC0) == 0xC0)
            {
                code_point = (input[i] & 0x1F) << 6 | (input[i + 1] & 0x3F);
                output[k] = code_point % (16 * 16);
                output[k + 1] = ((code_point - output[k]) % (16 * 16 * 16 * 16)) / (16 * 16);
                output[k + 2] = ((code_point - output[k] - (output[k + 1] * 16 * 16)) % (16 * 16 * 16 * 16 * 16 * 16)) / (16 * 16 * 16 * 16);
                output[k + 3] = 0x00;

                k += 4;
                i += 2;
            }
        }
        output_size = k;
    }
    else if (strcmp(output_text_format, "UTF-32LE without BOM") == 0)
    {
        unsigned int i = 0, k = 0;
        int code_point;
        int code_point2;

        output = malloc(((output_size * 4) + 2) * sizeof(*file));

        while (i < output_size)
        {
            if (input[i] < 0x80)
            {
                output[k + 3] = 0x00;
                output[k + 2] = 0x00;
                output[k + 1] = 0x00;
                output[k] = input[i];

                k += 4;
                i++;
            }
            else if ((input[i] & 0xE0) == 0xE0)
            {
                code_point = (input[i] & 0x0F) << 12 | (input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F);
                output[k] = code_point % (16 * 16);
                output[k + 1] = ((code_point - output[k]) % (16 * 16 * 16 * 16)) / (16 * 16);
                output[k + 2] = ((code_point - output[k] - (output[k + 1] * 16 * 16)) % (16 * 16 * 16 * 16 * 16 * 16)) / (16 * 16 * 16 * 16);
                output[k + 3] = 0x00;

                k += 4;
                i += 3;
            }
            else if ((input[i] & 0xC0) == 0xC0)
            {
                code_point = (input[i] & 0x1F) << 6 | (input[i + 1] & 0x3F);
                output[k] = code_point % (16 * 16);
                output[k + 1] = ((code_point - output[k]) % (16 * 16 * 16 * 16)) / (16 * 16);
                output[k + 2] = ((code_point - output[k] - (output[k + 1] * 16 * 16)) % (16 * 16 * 16 * 16 * 16 * 16)) / (16 * 16 * 16 * 16);
                output[k + 3] = 0x00;

                k += 4;
                i += 2;
            }
        }
        output_size = k;
    }
    else if (strcmp(output_text_format, "ISO8859-1") == 0)
    {
        unsigned int i = 0, k = 0;
        int code_point;
        int code_point2;

        output = malloc(output_size * sizeof(*file));

        while (i < output_size)
        {
            if (input[i] < 0x80)
            {
                output[k++] = input[i];
                i++;
            }
            else if ((input[i] & 0xE0) == 0xE0)
            {
                code_point = (input[i] & 0x0F) << 12 | (input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F);
                if (code_point <= 0xFF)
                    output[k++] = code_point;
                else
                    output[k++] = '?';

                i += 3;
            }
            else if ((input[i] & 0xC0) == 0xC0)
            {
                code_point = (input[i] & 0x1F) << 6 | (input[i + 1] & 0x3F);
                if (code_point <= 0xFF)
                    output[k++] = code_point;
                else
                    output[k++] = '?';

                i += 2;
            }
        }
        output_size = k;
    }
    else if (strcmp(output_text_format, "ISO8859-9") == 0)
    {
        unsigned int i = 0, k = 0;
        int code_point;
        int code_point2;

        output = malloc(output_size * sizeof(*file));

        while (i < output_size)
        {
            if (input[i] < 0x80)
            {
                output[k++] = input[i];
                i++;
            }
            else if ((input[i] & 0xE0) == 0xE0)
            {
                code_point = (input[i] & 0x0F) << 12 | (input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F);
                if (code_point <= 0xFF)
                    output[k++] = code_point;
                else
                {
                    switch (code_point)
                    {
                    case 0x011E:
                        output[k++] = 0xD0;
                        break;
                    case 0x0130:
                        output[k++] = 0xDD;
                        break;
                    case 0x015E:
                        output[k++] = 0xDE;
                        break;
                    case 0x011F:
                        output[k++] = 0xF0;
                        break;
                    case 0x0131:
                        output[k++] = 0xFD;
                        break;
                    case 0x015F:
                        output[k++] = 0xFE;
                        break;
                    default:
                        output[k++] = '?';
                        break;
                    }
                }

                i += 3;
            }
            else if ((input[i] & 0xC0) == 0xC0)
            {
                code_point = (input[i] & 0x1F) << 6 | (input[i + 1] & 0x3F);
                if (code_point <= 0xFF)
                    output[k++] = code_point;
                else
                {
                    switch (code_point)
                    {
                    case 0x011E:
                        output[k++] = 0xD0;
                        break;
                    case 0x0130:
                        output[k++] = 0xDD;
                        break;
                    case 0x015E:
                        output[k++] = 0xDE;
                        break;
                    case 0x011F:
                        output[k++] = 0xF0;
                        break;
                    case 0x0131:
                        output[k++] = 0xFD;
                        break;
                    case 0x015F:
                        output[k++] = 0xFE;
                        break;
                    default:
                        output[k++] = '?';
                        break;
                    }
                }

                i += 2;
            }
        }
        output_size = k;
    }
    fwrite(output, sizeof(*file), output_size, output_file);
    fclose(output_file);
}
