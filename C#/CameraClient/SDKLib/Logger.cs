using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SDKLib
{
    public class Logger
    {
        private enum WriteType
        {
            Operate = 0,
            Warning = 1,
            Error = 2,
        }
        private static StreamWriter _sw = null;
        private static bool _canWriteLog = false;

        public static void Initialize(string path)
        {
            if (_sw != null)
                return;
            DateTime time = DateTime.Now;
            string name = String.Format(@"\{0}.txt", time.ToString("yyMMddHHmmss"));
            _sw = new StreamWriter(path + name);
            _canWriteLog = true;
        }

        public static void Release()
        {
            _sw.Close();
            _sw.Dispose();
            _sw = null;
            _canWriteLog = false;
        }
        public static void LogOperate(string content)
        {
            try
            {
                LogInfo(content, Logger.WriteType.Operate);
            }
            catch (Exception e)
            {
                ExceptionForm form = new ExceptionForm();
                form.SetModal(e);
                _canWriteLog = false;
            }
        }
        public static void LogWarning(string content)
        {
            try
            {
                LogInfo(content, Logger.WriteType.Warning);
            }
            catch (Exception e)
            {
                ExceptionForm form = new ExceptionForm();
                form.SetModal(e);
                _canWriteLog = false;
            }
        }
        public static void LogError(string content)
        {
            try
            {
                LogInfo(content, Logger.WriteType.Error);
            }
            catch (Exception e)
            {
                ExceptionForm form = new ExceptionForm();
                form.SetModal(e);
                _canWriteLog = false;
            }
        }

        private static void LogInfo(string content, WriteType type)
        {
            if (_canWriteLog == false)
            {
                return;
            }
            if (_sw == null)
            {
                throw new ArgumentNullException();
            }
            string title = null;
            if (type == WriteType.Warning)
            {
                title = "[Warning]";
            }
            else if (type == WriteType.Error)
            {
                title = "[Error]";
            }
            else
            {
                title = "[Operate]";
            }
            DateTime now = DateTime.Now;
            _sw.WriteLine("{0}{1} {2}", title, now.ToString("yyyy-MM-dd HH:mm:ss.fff"), content);
            _sw.Flush();
        }
    }
}
