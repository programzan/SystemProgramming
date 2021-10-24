//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TRect circle, btn2 = Rect(450,880,750,950);
TColor color, color_all;
bool pic = false, text = false, fig = false, fill = false, fcircle = false;
int x, y;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	pic = true;
	Form1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	if ((X > 450 && X < 750) && (Y > 880 && Y < 950) && Button == mbLeft)
	{
		Canvas->Brush->Color=clGray;
		Canvas->FillRect(btn2);
		Canvas->Font->Name="Tahoma";
		Canvas->Font->Color=clBlack;
		Canvas->Font->Size=8;
		Canvas->TextOut(490,900,"Нарисованная кнопка");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if ((X > 450 && X < 750) && (Y > 880 && Y < 950) && Button == mbLeft)
	{
		text = true;
		Canvas->Brush->Color=clSilver;
		Canvas->FillRect(btn2);
		Canvas->Font->Name="Tahoma";
		Canvas->Font->Color=clBlack;
		Canvas->Font->Size=8;
		Canvas->TextOut(490,900,"Нарисованная кнопка");
		Form1->Refresh();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DrawPic() {
    Canvas->Brush->Color=clSkyBlue;
	Canvas->FillRect(Rect(100,100,1250,500));
	Canvas->Brush->Color=clGreen;
	Canvas->FillRect(Rect(100,500,1250,700));
	Canvas->Pen->Color=clYellow;
	Canvas->Pen->Width=3;
	Canvas->Brush->Color=clYellow;
	Canvas->Ellipse(1050,200,1150,300);
	Canvas->MoveTo(1040, 250); Canvas->LineTo(1000, 250);
	Canvas->MoveTo(1100, 310); Canvas->LineTo(1100, 350);
	Canvas->MoveTo(1160, 250); Canvas->LineTo(1200, 250);
	Canvas->MoveTo(1100, 190); Canvas->LineTo(1100, 150);
	Canvas->MoveTo(1050, 195); Canvas->LineTo(1030, 175);
	Canvas->MoveTo(1150, 195); Canvas->LineTo(1170, 175);
	Canvas->MoveTo(1050, 305); Canvas->LineTo(1030, 325);
	Canvas->MoveTo(1150, 305); Canvas->LineTo(1170, 325);
	Canvas->Brush->Color=clOlive;
	Canvas->Pen->Color=clOlive;
	Canvas->RoundRect(500,400,550,600,25,25);
	Canvas->Brush->Color=clLime;
	Canvas->Pen->Color=clLime;
	Canvas->Ellipse(400,120,650,430);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DrawText() {
    Canvas->Font->Name="Arial";
	Canvas->Font->Size=10;
	Canvas->Brush->Color=clBlack;
	Canvas->Font->Color=clWhite;
	Canvas->TextOut(800,720,"Привет! Хорошего дня!");
	Canvas->Font->Color=clBlack;
	Canvas->Brush->Color=clBtnFace;
	Canvas->Font->Name="Times New Roman";
	Canvas->TextOut(800,760,"Привет! Хорошего дня!");
	Canvas->Font->Name="Comic Sans MS";
	Canvas->TextOut(800,800,"Привет! Хорошего дня!");
	Canvas->Font->Name="Calibri";
	Canvas->Font->Color=clFuchsia;
	Canvas->Font->Size=20;
	Canvas->TextOut(800,840,"Привет! Хорошего дня!");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DrawFigRandColor(){
	Canvas->Brush->Color=color;
	Canvas->Pen->Style=psClear;
	Canvas->Ellipse(500, 750, 700, 850);
    Canvas->Pen->Style=psSolid;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FillClient() {
    Canvas->Brush->Color=color_all;
	Canvas->FillRect(TRect(TPoint(0,0), TPoint(Form1->Width, Form1->Height)));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DrawCircle() {
	Canvas->Pen->Width=3;
	Canvas->Pen->Color=clTeal;
	Canvas->Brush->Color = clTeal;
	Canvas->Ellipse(circle);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
	if (pic) DrawPic();
	if (text) DrawText();
	if (fig) DrawFigRandColor();
	if (fcircle) DrawCircle();
	if (fill) FillClient();
    Canvas->Brush->Color=clSilver;
	Canvas->FillRect(btn2);
	Canvas->Font->Name="Tahoma";
	Canvas->Font->Color=clBlack;
	Canvas->Font->Size=8;
	Canvas->TextOut(490,900,"Нарисованная кнопка");
}
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	fig = true;
	color = (TColor)RGB(random(255), random(255), random(255));
	DrawFigRandColor();
	Form1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	fill = true;
	color_all = (TColor)RGB(random(255), random(255), random(255));
	Form1->Refresh();
	fill = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
    fcircle = true;
	circle={100,200,200,100};
	Form1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	x = X; y = Y;
	if (Shift.Contains(ssLeft) && fcircle &&
		(X-circle.Left)*(X-circle.Left)+(Y-circle.Top)*(Y-circle.Top)<=10000) {
		::InvalidateRect(Form1->Handle, &circle, true);
		circle = TRect(X-50, Y-50, X+50, Y+50);
		Form1->Refresh();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClick(TObject *Sender)
{
	if (fcircle && (x-circle.Left)*(x-circle.Left)+(y-circle.Top)*(y-circle.Top)<=10000) {
		fcircle=false;
		Form1->Refresh();
    }
}
//---------------------------------------------------------------------------

