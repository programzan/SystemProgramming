using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab6
{
    public partial class Form1 : Form
    {
        public bool is_draw_olympics = false;
        public bool is_play = false;
        public bool win1 = false, win2 = false;
        PointF mouse_coords;
        public int[,] mas = new int[5, 5];
        public int player = 1;
        public Form1()
        {
            InitializeComponent();
            FillMasZeros(mas);
        }

        public void FillMasZeros(int[,] mas)
        {
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 5; j++)
                    mas[i, j] = 0;
        }

        private void DrawImgOnBtn(PaintEventArgs e)
        {
            Pen rPen = new Pen(Color.Red, 4);
            SolidBrush rBrush = new SolidBrush(Color.Tomato);
            Point[] points = new Point[8];
            points[0] = new Point(25, 50);
            points[1] = new Point(10, 30);
            points[2] = new Point(15, 20);
            points[3] = new Point(20, 20);
            points[4] = new Point(25, 30);
            points[5] = new Point(30, 20);
            points[6] = new Point(35, 20);
            points[7] = new Point(40, 30);
            e.Graphics.DrawPolygon(rPen, points);
            e.Graphics.FillPolygon(rBrush, points);
        }

        private void button1_Paint(object sender, PaintEventArgs e)
        {
            DrawImgOnBtn(e);
        }

        private void button2_Paint(object sender, PaintEventArgs e)
        {
            DrawImgOnBtn(e);
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            if (is_draw_olympics)
            {
                Pen rPen = new Pen(Color.Red, 6);
                Pen bPen = new Pen(Color.Black, 6);
                Pen bluePen = new Pen(Color.Blue, 6);
                Pen gPen = new Pen(Color.Green, 6);
                Pen yPen = new Pen(Color.Yellow, 6);
                SolidBrush wBrush = new SolidBrush(Color.White);
                e.Graphics.DrawRectangle(bPen, 0, 0, 325, 175);
                e.Graphics.FillRectangle(wBrush, 0, 0, 325, 175);
                e.Graphics.DrawEllipse(bluePen, 10, 10, 90, 90);
                e.Graphics.DrawEllipse(bPen, 110, 10, 90, 90);
                e.Graphics.DrawEllipse(yPen, 60, 60, 90, 90);
                Rectangle r1 = new Rectangle(110, 10, 90, 90);
                Rectangle r = new Rectangle(10, 10, 90, 90);
                e.Graphics.DrawArc(bluePen, r, -30, 90);
                e.Graphics.DrawArc(bPen, r1, 90, 20);
                e.Graphics.DrawEllipse(rPen, 210, 10, 90, 90);
                e.Graphics.DrawEllipse(gPen, 160, 60, 90, 90);
                Rectangle r2 = new Rectangle(110, 10, 90, 90);
                e.Graphics.DrawArc(bPen, r2, -30, 90);
                Rectangle r3 = new Rectangle(210, 10, 90, 90);
                e.Graphics.DrawArc(rPen, r3, 90, 20);
            }
            if (is_play)
            {
                Image background = Image.FromFile("D:\\учеба\\5th_semester\\СистПрог\\lab6\\imglab6.jpg");
                Pen bPen = new Pen(Color.Black, 4);
                Rectangle myR = new Rectangle(350, 100, 250, 250);
                LinearGradientBrush myLGB = new LinearGradientBrush(myR, Color.Aqua, Color.LightGreen, LinearGradientMode.Vertical);
                e.Graphics.FillRectangle(myLGB, myR);
                TextureBrush myTB = new TextureBrush(background);
                e.Graphics.FillRectangle(myTB, 400, 150, 150, 150);
                HatchBrush myHB = new HatchBrush(HatchStyle.Percent90, Color.LightGray);
                e.Graphics.FillRectangle(myHB, 450, 200, 50, 50);
                for (int i = 100; i <= 350; i += 50)
                {
                    PointF point1 = new PointF(350, i);
                    PointF point2 = new PointF(600, i);
                    e.Graphics.DrawLine(bPen, point1, point2);
                }
                for (int i = 350; i <= 600; i += 50)
                {
                    PointF point1 = new PointF(i, 100);
                    PointF point2 = new PointF(i, 350);
                    e.Graphics.DrawLine(bPen, point1, point2);
                }
                DrawCrossOrZero(e);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            is_draw_olympics = !is_draw_olympics;
            Refresh();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            is_play = !is_play;
            label1.Visible = !label1.Visible;
            label1.Text = "Ход игрока №1";
            Refresh();
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)
        {
            if (is_play)
            {
                mouse_coords = new PointF(e.X, e.Y);
                Tictactoe();
                Refresh();
            }
        }

        public void Tictactoe()
        {
            if (player == 1)
            {
                label1.Text = "Ход игрока №2";
                int indi = 0;
                int indj = 0;
                bool br = false;
                for (int i = 100; i < 350; i += 50)
                {
                    indj = 0;
                    for (int j = 350; j < 600; j += 50)
                    {
                        if ((mouse_coords.X >= j && mouse_coords.X <= j + 50) &&
                            ((mouse_coords.Y >= i && mouse_coords.Y <= i + 50)))
                            br = true;
                        if (br)
                            break;
                        indj++;
                    }
                    if (br)
                        break;
                    indi++;
                }
                if (indi > 4 || indj > 4 || mas[indi, indj] != 0)
                {
                    label1.Text = "Выберите пустую клетку";
                    return;
                }
                mas[indi, indj] = 1;
                player = 2;
            }
            else
            {
                label1.Text = "Ход игрока №1";
                int indi = 0;
                int indj = 0;
                bool br = false;
                for (int i = 100; i < 350; i += 50)
                {
                    indj = 0;
                    for (int j = 350; j < 600; j += 50)
                    {
                        if ((mouse_coords.X >= j && mouse_coords.X <= j + 50) &&
                            ((mouse_coords.Y >= i && mouse_coords.Y <= i + 50)))
                            br = true;
                        if (br)
                            break;
                        indj++;
                    }
                    if (br)
                        break;
                    indi++;
                }
                if (indi > 4 || indj > 4 || mas[indi, indj] != 0)
                {
                    label1.Text = "Выберите пустую клетку";
                    return;
                }
                mas[indi, indj] = 2;
                player = 1;
            }
        }

        public void DrawCrossOrZero(PaintEventArgs e)
        {
            Pen p1Pen = new Pen(Color.Red, 4);
            Pen p2Pen = new Pen(Color.Blue, 4);
            for (int i = 2; i < 7; i++)
                for (int j = 7; j < 12; j++)
                {
                    if (mas[i - 2, j - 7] == 1)
                    {
                        PointF point1 = new PointF(j * 50, i * 50);
                        PointF point2 = new PointF(j * 50 + 50, i * 50 + 50);
                        e.Graphics.DrawLine(p1Pen, point1, point2);
                        point1 = new PointF(j * 50, i * 50 + 50);
                        point2 = new PointF(j * 50 + 50, i * 50);
                        e.Graphics.DrawLine(p1Pen, point1, point2);
                    }
                    if (mas[i - 2, j - 7] == 2)
                        e.Graphics.DrawEllipse(p2Pen, j * 50, i * 50, 50, 50);
                }
            CheckWinner(e);
        }

        public void CheckWinner(PaintEventArgs e)
        {
            Pen gPen = new Pen(Color.Green, 4);
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 2; j++)
                {
                    if (mas[i, j] == 1 && mas[i, j + 1] == 1 && mas[i, j + 2] == 1 && mas[i, j + 3] == 1)
                    {
                        PointF point1 = new PointF((j + 7) * 50, (2 + i) * 50 + 25);
                        PointF point2 = new PointF((11 + j) * 50, (2 + i) * 50 + 25);
                        e.Graphics.DrawLine(gPen, point1, point2);
                        win1 = true;
                        WhoWin();
                        return;
                    }
                    else if (mas[i, j] == 2 && mas[i, j + 1] == 2 && mas[i, j + 2] == 2 && mas[i, j + 3] == 2)
                    {
                        PointF point1 = new PointF((j + 7) * 50, (2 + i) * 50 + 25);
                        PointF point2 = new PointF((11 + j) * 50, (2 + i) * 50 + 25);
                        e.Graphics.DrawLine(gPen, point1, point2);
                        win2 = true;
                        WhoWin();
                        return;
                    }
                }
            for (int i = 0; i < 5; i++)
                for (int j = 0; j < 2; j++)
                {
                    if (mas[j, i] == 1 && mas[j + 1, i] == 1 && mas[j + 2, i] == 1 && mas[j + 3, i] == 1)
                    {
                        PointF point1 = new PointF((i + 7) * 50 + 25, (2 + j) * 50);
                        PointF point2 = new PointF((7 + i) * 50 + 25, (6 + j) * 50);
                        e.Graphics.DrawLine(gPen, point1, point2);
                        win1 = true;
                        WhoWin();
                        return;
                    }
                    else if (mas[j, i] == 2 && mas[j + 1, i] == 2 && mas[j + 2, i] == 2 && mas[j + 3, i] == 2)
                    {
                        PointF point1 = new PointF((i + 7) * 50 + 25, (2 + j) * 50);
                        PointF point2 = new PointF((7 + i) * 50 + 25, (6 + j) * 50);
                        e.Graphics.DrawLine(gPen, point1, point2);
                        win2 = true;
                        WhoWin();
                        return;
                    }
                }
            WhoWin();
        }

        public void WhoWin() {
            if (win1)
            {
                label1.Text = "Победитель: игрок №1";
                win1 = false;
                player = 1;
                FillMasZeros(mas);
            }
            else if (win2)
            {
                label1.Text = "Победитель: игрок №2";
                win2 = false;
                player = 1;
                FillMasZeros(mas);
            }
            else
            {
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < 5; j++)
                        if (mas[i, j] == 0)
                            return;
                label1.Text = "Игра закончилась вничью";
            }
        }
    }
}
