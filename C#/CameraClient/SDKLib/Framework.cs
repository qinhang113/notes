using System;
using System.IO;
using System.Windows.Forms;

namespace SDKLib
{
    public static class Framework
    {
        private static string _cacheDir = null;
        private static string _logsDir = null;
        private static string _appPath = null;

        public static bool Initialize(string appPath)
        {
            if (_appPath != null)
                return false;

            _appPath = appPath;

            _logsDir = Path.Combine(_appPath, "logs");
            _cacheDir = Path.Combine(_appPath, "caches");

            if (!Directory.Exists(_logsDir))
            {
                Directory.CreateDirectory(_logsDir);
            }
            if (!Directory.Exists(_cacheDir))
            {
                Directory.CreateDirectory(_cacheDir);
            }

            Logger.Initialize(_logsDir);
            Logger.LogOperate("初始化完成!");

            return true;
        }
        public static void Release()
        {
            Logger.Release();
            ClearCache();
        }

        public static void Delay(float second)
        {
            int tt = Environment.TickCount;
            int ms = (int)(second * 1000);
            while ((Environment.TickCount - tt) < ms)
            {
                Application.DoEvents();
            }
        }

        public static void ShowException(Exception e)
        {
#if DEBUG
            ExceptionForm form = new ExceptionForm();
            form.SetModal(e);
#endif
        }

        private static void ClearCache()
        {
            string[] fs = Directory.GetFiles(_cacheDir);
            foreach (var f in fs)
            {
                File.Delete(f);
            }
        }

        public static string PathWithRoot(string path)
        {
            return System.IO.Path.Combine(_appPath, path);
        }


    }
}
