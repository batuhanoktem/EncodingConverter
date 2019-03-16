using System;

namespace EncodingConverter.Core
{
    public class SystemTools
    {
        public static bool Is64BitProcess
        {
            get
            {
                return IntPtr.Size == 8;
            }
        }
    }
}