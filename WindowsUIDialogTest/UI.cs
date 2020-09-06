using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

namespace WindowsUIDialogTest
{
    public class UI
    {
        const string NativeDLLName = "WindowsUiDialogs.dll";
        [DllImport(NativeDLLName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr OpenFileSaveDialog();

        [DllImport(NativeDLLName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr OpenFileDialog();

        [DllImport(NativeDLLName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void FreeString(IntPtr Str);

        [DllImport(NativeDLLName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetTextInput([MarshalAs(UnmanagedType.LPWStr)] string Title);

        [DllImport(NativeDLLName, CallingConvention = CallingConvention.Cdecl)]
        public static extern ulong GetColor(ulong Default);

        [DllImport(NativeDLLName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetNumberInput([MarshalAs(UnmanagedType.LPWStr)] string Title, double X, double Y);

        [DllImport(NativeDLLName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CustomUI(
            [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPWStr)] string[] Pairs,
            [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPWStr)] string[] TypeInfo,
            int PairNum
        );

        public static void Save(Object Content, String SaveFileName)
        {
            Save(JsonConvert.SerializeObject(Content, new JsonSerializerSettings
            {
                TypeNameHandling = TypeNameHandling.Auto,
                ReferenceLoopHandling = ReferenceLoopHandling.Ignore,
                Formatting = Formatting.Indented
            }), SaveFileName);
        }

        public static void Save(String Content, String SaveFileName)
        {
            if (SaveFileName == "" || SaveFileName == null)
                return;
            FileStream Stream = null;
            try
            {
                if (File.Exists(SaveFileName))
                    Stream = File.Open(SaveFileName, FileMode.Truncate, FileAccess.Write);
                else
                    Stream = File.Open(SaveFileName, FileMode.CreateNew, FileAccess.Write);
                Stream.Write(Encoding.UTF8.GetBytes(Content));
                Stream.Flush();
                Stream.Close();
            }
            finally
            {
                if (Stream != null)
                    Stream.Dispose();
            }
        }

        public static String Save(String Content)
        {
            String DirectoryState = Directory.GetCurrentDirectory();
            IntPtr RawPtr = OpenFileSaveDialog();
            Directory.SetCurrentDirectory(DirectoryState);
            string SaveFileName = Marshal.PtrToStringUni(RawPtr);
            FreeString(RawPtr);
            if (SaveFileName == "")
                return SaveFileName;
            Save(Content, SaveFileName);
            return SaveFileName;
        }

        public static String Save(Object Content)
        {
            return Save(JsonConvert.SerializeObject(Content, new JsonSerializerSettings
            {
                TypeNameHandling = TypeNameHandling.Auto,
                ReferenceLoopHandling = ReferenceLoopHandling.Ignore
            }));
        }

        public static String Open()
        {
            IntPtr FileName = OpenFileDialog();
            string Marshalled = Marshal.PtrToStringUni(FileName);
            FreeString(FileName);
            return Marshalled;
        }

        public static String OpenRelative()
        {
            String Path = Open();
            if (Path == "" || Path == null)
                return "";
            Uri SelectedSongPath = new Uri(Path, UriKind.Absolute);
            return new Uri(
                "./",
                UriKind.Absolute
            )
            .MakeRelativeUri(SelectedSongPath)
            .ToString();
        }

        /*public static void Save(Object Content, bool Binary = true) {
            if(!Binary) {
                Save(JsonConvert.SerializeObject(Content, new JsonSerializerSettings {
                    TypeNameHandling = TypeNameHandling.Auto,
                    ReferenceLoopHandling = ReferenceLoopHandling.Ignore
                }));
                return;
            }
            Save()
        }*/

        public static String GetText(string Title)
        {
            IntPtr Text = GetTextInput(Title);
            string Marshalled = Marshal.PtrToStringUni(Text);
            FreeString(Text);
            return Marshalled;
        }

        public static String GetNumber(string Title, double X, double Y)
        {
            IntPtr Text = GetNumberInput(Title, X, Y);
            string Marshalled = Marshal.PtrToStringUni(Text);
            FreeString(Text);
            return Marshalled;
        }

        public static String GetCustomFromObj(Object O)
        {
            List<string> Pairs = new List<string>();
            List<string> Types = new List<string>();
            foreach (var Prop in O.GetType().GetProperties())
            {
                Pairs.Add(Prop.Name);
                Pairs.Add(Prop.GetValue(O).ToString());
                Types.Add(Prop.PropertyType.Name);
            }
            return GetCustom(Pairs.ToArray(), Types.ToArray());
        }

        public static T GetCustom<T>(T Obj, Type MyType) where T : class
        {
            String Serialized = GetCustomFromObj(Obj);
            return (T)JsonConvert.DeserializeObject(Serialized, MyType);
        }

        public static String GetCustom(String[] Pairs, String[] Types)
        {
            IntPtr Text = CustomUI(Pairs, Types, Pairs.Length / 2);
            string Marshalled = Marshal.PtrToStringUni(Text);
            FreeString(Text);
            return Marshalled;
        }
    }
}
