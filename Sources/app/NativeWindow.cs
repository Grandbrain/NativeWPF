using lib;
using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Interop;

namespace app
{
    public class NativeWindow : HwndHost
    {
        public new IntPtr Handle { get; private set; }
        Procedure procedure;
        Scene scene;
        const int WM_PAINT = 0x000F;
        const int WM_SIZE = 0x0005;

        [StructLayout(LayoutKind.Sequential)]
        struct WindowClass
        {
            public uint Style;
            public IntPtr Callback;
            public int ClassExtra;
            public int WindowExtra;
            public IntPtr Instance;
            public IntPtr Icon;
            public IntPtr Cursor;
            public IntPtr Background;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string Menu;
            [MarshalAs(UnmanagedType.LPWStr)]
            public string Class;
        }

        [StructLayout(LayoutKind.Sequential)]
        struct Rect
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }

        [StructLayout(LayoutKind.Sequential)]
        struct Paint
        {
            public IntPtr Context;
            public bool Erase;
            public Rect Area;
            public bool Restore;
            public bool Update;
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public byte[] Reserved;
        }

        delegate IntPtr Procedure
            (IntPtr handle,
            uint message,
            IntPtr wparam,
            IntPtr lparam);

        [DllImport("user32.dll")]
        static extern IntPtr CreateWindowEx
            (uint extended,
            [MarshalAs(UnmanagedType.LPWStr)] 
            string name,
            [MarshalAs(UnmanagedType.LPWStr)]
            string caption,
            uint style,
            int x,
            int y,
            int width,
            int height,
            IntPtr parent,
            IntPtr menu,
            IntPtr instance,
            IntPtr param);

        [DllImport("user32.dll")]
        static extern IntPtr LoadCursor
            (IntPtr instance,
            int name);

        [DllImport("user32.dll")]
        static extern IntPtr DefWindowProc
            (IntPtr handle,
            uint message,
            IntPtr wparam,
            IntPtr lparam);

        [DllImport("user32.dll")]
        static extern ushort RegisterClass
            ([In] 
            ref WindowClass register);

        [DllImport("user32.dll")]
        static extern bool DestroyWindow
            (IntPtr handle);

        [DllImport("user32.dll")]
        static extern IntPtr BeginPaint
            (IntPtr handle,
            out Paint paint);

        [DllImport("user32.dll")]
        static extern bool EndPaint
            (IntPtr handle,
            [In] ref Paint paint);

        protected override HandleRef BuildWindowCore(HandleRef parent)
        {
            var callback = Marshal.GetFunctionPointerForDelegate(procedure = WndProc);
            var width = Convert.ToInt32(ActualWidth);
            var height = Convert.ToInt32(ActualHeight);
            var cursor = LoadCursor(IntPtr.Zero, 32512);
            var menu = string.Empty;
            var background = new IntPtr(1);
            var zero = IntPtr.Zero;
            var caption = string.Empty;
            var style = 3u;
            var extra = 0;
            var extended = 0u;
            var window = 0x50000000u;
            var point = 0;
            var name = "Win32";

            var wnd = new WindowClass
            {
                Style = style,
                Callback = callback,
                ClassExtra = extra,
                WindowExtra = extra,
                Instance = zero,
                Icon = zero,
                Cursor = cursor,
                Background = background,
                Menu = menu,
                Class = name
            };

            RegisterClass(ref wnd);
            Handle = CreateWindowEx(extended, name, caption,
                window, point, point, width, height,
                parent.Handle, zero, zero, zero);

            scene = new Scene(Handle);

            return new HandleRef(this, Handle);
        }

        protected override void DestroyWindowCore(HandleRef handle)
        {
            DestroyWindow(handle.Handle);
        }

        protected override IntPtr WndProc(IntPtr handle, int message, IntPtr wparam, IntPtr lparam, ref bool handled)
        {
            try
            {
                if (message == WM_PAINT)
                {
                    Paint paint;
                    BeginPaint(handle, out paint);
                    scene.Draw();
                    EndPaint(handle, ref paint);
                    handled = true;
                }

                if (message == WM_SIZE)
                {
                    scene.Resize(handle);
                    handled = true;
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }

            return base.WndProc(handle, message, wparam, lparam, ref handled);
        }

        static IntPtr WndProc(IntPtr handle, uint message, IntPtr wparam, IntPtr lparam)
        {
            return DefWindowProc(handle, message, wparam, lparam);
        }
    }
}