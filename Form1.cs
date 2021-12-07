using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab7_CSharp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ShowPresentation();
        }

        private void ShowPresentation()
        {
            Graphics GB = PB.CreateGraphics();
            Font font = new Font("Comic Sans MS", 36, FontStyle.Bold);
            System.Drawing.Bitmap bitmap;

            GB.Clear(Color.White);
            bitmap = new Bitmap(@"D:\учеба\5th_semester\СистПрог\lab7\lab7_CSharp\Screenshot_1.png");
            for (float i = 0; i <= 10; i++)
            {
                GB.DrawImage(bitmap, bitmap.Width - i * 76, bitmap.Height - i * 48, bitmap.Width, bitmap.Height);
                System.Threading.Thread.Sleep(50);
            }
            GB.DrawString("Ирис щетинистый", font, Brushes.White, 0, 0);
            bitmap.Dispose();
            System.Threading.Thread.Sleep(2000);

            GB.Clear(Color.White);
            bitmap = new Bitmap(@"D:\учеба\5th_semester\СистПрог\lab7\lab7_CSharp\Screenshot_2.png");
            for (int i = 10; i >= 0; --i)
            {
                GB.DrawImage(bitmap, 20 * i, 16 * i, bitmap.Width - 40 * i, bitmap.Height - 32 * i);
                System.Threading.Thread.Sleep(50);
            }
            GB.DrawString("Ирис виргинский", font, Brushes.Lime, 140, 200);
            bitmap.Dispose();
            System.Threading.Thread.Sleep(2000);

            GB.Clear(Color.White);
            bitmap = new Bitmap(@"D:\учеба\5th_semester\СистПрог\lab7\lab7_CSharp\Screenshot_3.png");
            for (int i = 12; i > 0; --i)
            {
                GB.DrawImage(bitmap, 0, 0, bitmap.Width / i, bitmap.Height / i);
                System.Threading.Thread.Sleep(50);
            }
            GB.DrawString("Ирис разноцветный", font, Brushes.Orange, 280, 400);
            bitmap.Dispose();
        }
    }
}
