#ifndef ENCODE_H
#define ENCODE_H

char *input_text_format;
char *output_text_format;
char *input_filename;
char *output_filename;
unsigned char *input;
char *output;

__declspec(dllexport) void show_menu();
__declspec(dllexport) void choose_input_text_format();
__declspec(dllexport) void set_input_text_format(const char *text_format);
__declspec(dllexport) void choose_output_text_format();
__declspec(dllexport) void set_output_text_format(const char *text_format);
__declspec(dllexport) void enter_input_filename();
__declspec(dllexport) void set_input_filename(const char *filename);
__declspec(dllexport) void enter_output_filename();
__declspec(dllexport) void set_output_filename(const char *filename);
__declspec(dllexport) void convert();

#endif
