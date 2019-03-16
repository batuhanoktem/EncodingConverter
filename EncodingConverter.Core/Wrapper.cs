using System.Runtime.InteropServices;

namespace EncodingConverter.Core
{
    public static class Wrapper
    {
        #region ShowMenu
        [DllImport("EncodingConverter.x86.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "show_menu")]
        static extern void ShowMenuX86();

        [DllImport("EncodingConverter.x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "show_menu")]
        static extern void ShowMenuX64();

        public static void ShowMenu()
        {
            if (SystemTools.Is64BitProcess)
                ShowMenuX64();
            else
                ShowMenuX86();
        }
        #endregion

        #region ChooseInputTextFormat
        [DllImport("EncodingConverter.x86.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "choose_input_text_format")]
        static extern void ChooseInputTextFormatX86();

        [DllImport("EncodingConverter.x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "choose_input_text_format")]
        static extern void ChooseInputTextFormatX64();

        public static void ChooseInputTextFormat()
        {
            if (SystemTools.Is64BitProcess)
                ChooseInputTextFormatX64();
            else
                ChooseInputTextFormatX86();
        }
        #endregion

        #region SetInputTextFormat
        [DllImport("EncodingConverter.x86.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "set_input_text_format")]
        static extern void SetInputTextFormatX86(string textFormat);

        [DllImport("EncodingConverter.x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "set_input_text_format")]
        static extern void SetInputTextFormatX64(string textFormat);

        public static void SetInputTextFormat(string textFormat)
        {
            if (SystemTools.Is64BitProcess)
                SetInputTextFormatX64(textFormat);
            else
                SetInputTextFormatX86(textFormat);
        }
        #endregion

        #region ChooseOutputTextFormat
        [DllImport("EncodingConverter.x86.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "choose_output_text_format")]
        static extern void ChooseOutputTextFormatX86();

        [DllImport("EncodingConverter.x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "choose_output_text_format")]
        static extern void ChooseOutputTextFormatX64();

        public static void ChooseOutputTextFormat()
        {
            if (SystemTools.Is64BitProcess)
                ChooseOutputTextFormatX64();
            else
                ChooseOutputTextFormatX86();
        }
        #endregion

        #region SetOutputTextFormat
        [DllImport("EncodingConverter.x86.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "set_output_text_format")]
        static extern void SetOutputTextFormatX86(string textFormat);

        [DllImport("EncodingConverter.x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "set_output_text_format")]
        static extern void SetOutputTextFormatX64(string textFormat);

        public static void SetOutputTextFormat(string textFormat)
        {
            if (SystemTools.Is64BitProcess)
                SetOutputTextFormatX64(textFormat);
            else
                SetOutputTextFormatX86(textFormat);
        }
        #endregion

        #region EnterInputFilename
        [DllImport("EncodingConverter.x86.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "enter_input_filename")]
        static extern void EnterInputFilenameX86();

        [DllImport("EncodingConverter.x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "enter_input_filename")]
        static extern void EnterInputFilenameX64();

        public static void EnterInputFilename()
        {
            if (SystemTools.Is64BitProcess)
                EnterInputFilenameX64();
            else
                EnterInputFilenameX86();
        }
        #endregion

        #region SetInputFilename
        [DllImport("EncodingConverter.x86.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "set_input_filename")]
        static extern void SetInputFilenameX86(string textFormat);

        [DllImport("EncodingConverter.x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "set_input_filename")]
        static extern void SetInputFilenameX64(string filename);

        public static void SetInputFilename(string filename)
        {
            if (SystemTools.Is64BitProcess)
                SetInputFilenameX64(filename);
            else
                SetInputFilenameX86(filename);
        }
        #endregion

        #region EnterOutputFilename
        [DllImport("EncodingConverter.x86.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "enter_input_filename")]
        static extern void EnterOutputFilenameX86();

        [DllImport("EncodingConverter.x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "enter_input_filename")]
        static extern void EnterOutputFilenameX64();

        public static void EnterOutputFilename()
        {
            if (SystemTools.Is64BitProcess)
                EnterOutputFilenameX64();
            else
                EnterOutputFilenameX86();
        }
        #endregion

        #region SetOutputFilename
        [DllImport("EncodingConverter.x86.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "set_output_filename")]
        static extern void SetOutputFilenameX86(string filename);

        [DllImport("EncodingConverter.x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "set_output_filename")]
        static extern void SetOutputFilenameX64(string filename);

        public static void SetOutputFilename(string filename)
        {
            if (SystemTools.Is64BitProcess)
                SetOutputFilenameX64(filename);
            else
                SetOutputFilenameX86(filename);
        }
        #endregion

        #region Convert
        [DllImport("EncodingConverter.x86.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "convert")]
        static extern void ConvertX86();

        [DllImport("EncodingConverter.x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "convert")]
        static extern void ConvertX64();

        public static void Convert()
        {
            if (SystemTools.Is64BitProcess)
                ConvertX64();
            else
                ConvertX86();
        }

        public static void Convert(string inputFilename, string outputFilename, string inputTextFormat = null, string outputTextFormat = "UTF-8 without BOM")
        {
            if (SystemTools.Is64BitProcess)
            {
                SetInputTextFormatX64(inputTextFormat);
                SetOutputTextFormatX64(outputTextFormat);
                SetInputFilenameX64(inputFilename);
                SetOutputFilenameX64(outputFilename);
                ConvertX64();
            }
            else
            {
                SetInputTextFormatX86(inputTextFormat);
                SetOutputTextFormatX86(outputTextFormat);
                SetInputFilenameX86(inputFilename);
                SetOutputFilenameX86(outputFilename);
                ConvertX86();
            }
        }
        #endregion
    }
}
