using System;

namespace WindowsUIDialogTest
{
    class Program
    {
        static void Main(string[] args)
        {
            UI.GetCustomFromObj(new
            {
                ABC = "Hello",
                DEF = 23
            });
        }
    }
}
