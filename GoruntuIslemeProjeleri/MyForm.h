#pragma once
#include <atlstr.h>
#include <windows.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "imge_bmp.h"
using namespace std;
//
float maske[9] = { 0.25,0.50,0.25,
				   0.50,  1 ,0.50,
				   0.25,0.50,0.25 };
//
//float maske[25] = { 0.0625,	0.125,	0.25,	0.125,	0.0625,
//								0.125,	0.25,	0.5,	0.25,	0.125,
//								0.25,	0.5,	1,		0.5,	0.25,
//								0.125,	0.25,	0.5,	0.25,	0.125,
//								0.0625,	0.125,	0.25,	0.125,	0.0625 };
//
//float maske[49] = { 0.015625 ,	0.03125,	0.0625,	0.125,	0.0625,	0.03125,0.015625,
//								0.03125,	0.0625,		0.125,	0.25,	0.125,	0.0625,	0.03125,
//								0.625,		0.125,		0.25,	0.5,	0.25,	0.125,	0.625,
//								0.125,		0.25,		0.5,	1,		0.5,	0.25,	0.125,
//								0.625,		0.125,		0.25,	0.5,	0.25,	0.125,	0.625,
//								0.03125,	0.0625,		0.125,	0.25,	0.125,	0.0625,	0.03125,
//								0.015625,	0.03125,	0.0625, 0.125,	0.0625,	0.03125,0.015625 };

namespace GoruntuIslemeProjeleri {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	
	private:
		BYTE* Buffer;
		BYTE* Raw_Intensity;
		int Width, Height;
		long Size, new_size, newWidth, newHeight;
		unsigned int zoom_height1;
		unsigned int zoom_height2;
		unsigned int zoom_width1;
		unsigned int zoom_width2;
	
		

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem1;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::ToolStripMenuItem^  processesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  drawLineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  drawCircleToolStripMenuItem;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::ToolStripMenuItem^  clearToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  setHistogramToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::ToolStripMenuItem^  histogramEqualToolStripMenuItem;


	private: System::ComponentModel::IContainer^  components;

		/// <summary>
		/// Required designer variable.
		/// </summary>
	public:

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->processesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawLineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawCircleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->setHistogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramEqualToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 27);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(384, 256);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(405, 27);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(384, 256);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseDown);
			this->pictureBox2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseUp);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openToolStripMenuItem,
					this->processesToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1366, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openToolStripMenuItem1,
					this->clearToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->openToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem1
			// 
			this->openToolStripMenuItem1->Name = L"openToolStripMenuItem1";
			this->openToolStripMenuItem1->Size = System::Drawing::Size(103, 22);
			this->openToolStripMenuItem1->Text = L"Open";
			this->openToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem1_Click);
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->clearToolStripMenuItem->Text = L"Clear";
			this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::clearToolStripMenuItem_Click_1);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exitToolStripMenuItem_Click);
			// 
			// processesToolStripMenuItem
			// 
			this->processesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->drawLineToolStripMenuItem,
					this->drawCircleToolStripMenuItem, this->setHistogramToolStripMenuItem, this->histogramEqualToolStripMenuItem
			});
			this->processesToolStripMenuItem->Name = L"processesToolStripMenuItem";
			this->processesToolStripMenuItem->Size = System::Drawing::Size(50, 20);
			this->processesToolStripMenuItem->Text = L"Apply";
			// 
			// drawLineToolStripMenuItem
			// 
			this->drawLineToolStripMenuItem->Name = L"drawLineToolStripMenuItem";
			this->drawLineToolStripMenuItem->Size = System::Drawing::Size(197, 22);
			this->drawLineToolStripMenuItem->Text = L"Draw Line";
			this->drawLineToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::drawLineToolStripMenuItem_Click);
			// 
			// drawCircleToolStripMenuItem
			// 
			this->drawCircleToolStripMenuItem->Name = L"drawCircleToolStripMenuItem";
			this->drawCircleToolStripMenuItem->Size = System::Drawing::Size(197, 22);
			this->drawCircleToolStripMenuItem->Text = L"Draw Circle";
			this->drawCircleToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::drawCircleToolStripMenuItem_Click);
			// 
			// setHistogramToolStripMenuItem
			// 
			this->setHistogramToolStripMenuItem->Name = L"setHistogramToolStripMenuItem";
			this->setHistogramToolStripMenuItem->Size = System::Drawing::Size(197, 22);
			this->setHistogramToolStripMenuItem->Text = L"Set Histogram";
			this->setHistogramToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::setHistogramToolStripMenuItem_Click);
			// 
			// histogramEqualToolStripMenuItem
			// 
			this->histogramEqualToolStripMenuItem->Name = L"histogramEqualToolStripMenuItem";
			this->histogramEqualToolStripMenuItem->Size = System::Drawing::Size(197, 22);
			this->histogramEqualToolStripMenuItem->Text = L"Histogram Equalization";
			this->histogramEqualToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::histogramEqualToolStripMenuItem_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(795, 27);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(384, 256);
			this->pictureBox3->TabIndex = 13;
			this->pictureBox3->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 286);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(76, 13);
			this->label1->TabIndex = 14;
			this->label1->Text = L"Orginal Picture";
			this->label1->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(405, 286);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(65, 13);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Gray Picture";
			this->label2->Visible = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(792, 286);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(82, 13);
			this->label3->TabIndex = 16;
			this->label3->Text = L"Zoomed Picture";
			this->label3->Visible = false;
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(12, 302);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::SeaGreen;
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(384, 220);
			this->chart1->TabIndex = 17;
			this->chart1->Text = L"chart1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1366, 749);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"GORUNTU ISLEME";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	
private: System::Void openToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
	LPCTSTR input;
	CString str;


	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		str = openFileDialog1->FileName;
		input = (LPCTSTR)str;

		Buffer = LoadBMP(Width, Height, Size, input);				  //foto'nun RGB bilgileriyle beraber tutuldu�u dizi
		Raw_Intensity = ConvertBMPToIntensity(Buffer, Width, Height); // foto�rafla ayn� boyutda ama ilk indisde foto�rag�n sol alt piksel bilgisi var

		pictureBox1->Width = Width;
		pictureBox1->Height = Height;
		pictureBox2->Width = Width;
		pictureBox2->Height = Height;

		

		int row, column;
		Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = surface;
		Color c;

		for (row = 0; row < Height; row++)
			for (column = 0; column < Width; column++)
			{
				c = Color::FromArgb(Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column]);
				surface->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
			}
	}
	this->pictureBox1->ImageLocation = openFileDialog1->FileName;
	this->label1->Visible = true;
	this->label1->Location = System::Drawing::Point(12, 286);

	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27); // yeni g�r�nt�y�n�n konumu ayarlad�k
	this->label2->Visible = true;
	this->label2->Location = System::Drawing::Point(405, 286);

}


private: System::Void pictureBox2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	zoom_width1 = e->X;
	zoom_height1 = e->Y;
}
//
//private: System::Void pictureBox2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
//	try
//	{
//		if (pictureBox2->Image && flag == 1)
//		{
//			BYTE* t_intensity = new BYTE[Width*Height];
//
//			for (unsigned int i = 0; i < Height*Width; i++)
//				t_intensity[i] = Raw_Intensity[i];
//
//			zoom_width2 = e->X;
//			zoom_height2 = e->Y;
//
//			Bitmap^ imgCrop = gcnew Bitmap(pictureBox3->Width, pictureBox3->Height);
//			pictureBox3->Image = imgCrop;
//			Color c;
//			int temp;
//
//			for (unsigned int row = zoom_height1; row < zoom_height2; row++)
//			{
//				for (unsigned int column = zoom_width1; column < zoom_height2; column++)
//				{
//					temp = row * Width + column;
//					c = Color::FromArgb(t_intensity[temp], t_intensity[temp], t_intensity[temp]);
//					imgCrop->SetPixel(column, row, c);
//				}
//			}
//			pictureBox3->Refresh();
//			delete[]t_intensity;
//
//		}
//
//	}
//	catch (const System::ArgumentOutOfRangeException^ e)
//	{
//		flag = 0;
//		MessageBox::Show("Hata");
//	}
//}1
private: System::Void pictureBox2_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	zoom_width2 = e->X;
	zoom_height2 = e->Y;

	unsigned int k = 0;
	unsigned int zoom_width = ((zoom_width2 - zoom_width1) * 2) + 1;
	unsigned int zoom_height = ((zoom_height2 - zoom_height1) * 2) + 1;
	BYTE *Zoom_buffer = new BYTE[zoom_width*zoom_height];


	pictureBox3->Width = zoom_width;
	pictureBox3->Height = zoom_height;

	for (unsigned int i = zoom_height1; i < zoom_height2; i++)
	{
		for (int m = 0; m < (zoom_width); m++)
		{
			Zoom_buffer[k] = 0;
			k++;
		}
		Zoom_buffer[k] = 0;
		k++;
		for (unsigned int j = zoom_width1; j < zoom_width2; j++)
		{
			Zoom_buffer[k] = Raw_Intensity[(i*Width) + j];
			k++;
			Zoom_buffer[k] = 0;
			k++;
		}
	}

	for (int m = 0; m < (zoom_width); m++)
	{
		Zoom_buffer[k] = 0;
		k++;
	}
	this->pictureBox3->Location = System::Drawing::Point(pictureBox2->Left + pictureBox2->Width + 10, 34);

	BYTE* Sonuc = new BYTE[zoom_width*zoom_height];
	Sonuc = Mask(Zoom_buffer, zoom_width, zoom_height, maske, 9, newWidth, newHeight);

	unsigned int row1, column1;
	Bitmap^ surface1 = gcnew Bitmap(pictureBox3->Width, pictureBox3->Height);
	pictureBox3->Image = surface1;
	Color c1;

	for (row1 = 0; row1 < newHeight; row1++)
		for (column1 = 0; column1 < newWidth; column1++)
		{
			c1 = Color::FromArgb(Sonuc[(row1*newWidth) + column1], Sonuc[(row1*newWidth) + column1], Sonuc[(row1*newWidth) + column1]);
			surface1->SetPixel(column1, row1, c1);
		}
//	MessageBox::Show("("+zoom_width1 + ", " + zoom_height1 + ") noktasindan\n" + "(" + zoom_width2 + ", " + zoom_height2 + ") noktasina kadar zoomlandi");
	
	surface1->Save("zoomed.bmp");
}
private: System::Void drawLineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	cizgiCiz(Raw_Intensity, 200, 30, 30, 200, Width, Height);

	int row, column;
	Bitmap ^ surface3 = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface3;
	Color c;

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column]);
			surface3->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
		}
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27); // yeni g�r�nt�y�n�n konumu ayarlad�k
}

private: System::Void drawCircleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	cemberCiz(Raw_Intensity, 200, 200, 50, Width, Height);

	int row, column;
	Bitmap ^ surface3 = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface3;
	Color c;

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column]);
			surface3->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
		}
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27); // yeni g�r�nt�y�n�n konumu ayarlad�k

}
private: System::Void clearToolStripMenuItem_Click_1(System::Object^  sender, System::EventArgs^  e) {
	pictureBox1->Image = nullptr;
	pictureBox1->Width = 384;
	pictureBox1->Height = 256;

	pictureBox2->Image = nullptr;
	pictureBox2->Width = 384;
	pictureBox2->Height = 256;

	pictureBox3->Image = nullptr;
	pictureBox3->Width = 384;
	pictureBox3->Height = 256;


}
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}
private: System::Void setHistogramToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	chart1->Titles->Clear();
	chart1->Series->Clear();
	chart1->Series->Add("Number Of Pixel");

	BYTE* t_intensity = new BYTE[Width*Height];
	for (unsigned int i = 0; i < Height*Width; i++)
		t_intensity[i] = Raw_Intensity[i];

	int *hist = Histogram(t_intensity, Width, Height);
	for (unsigned int i = 0; i < 256; i++)
	{
		chart1->Series["Number Of Pixel"]->Points->AddXY(i, hist[i]);
	}

	chart1->Titles->Add("Histogram");
	delete[]hist;
	delete[]t_intensity;
}

private: System::Void histogramEqualToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	chart1->Titles->Clear();
	chart1->Series->Clear();
	chart1->Series->Add("Number Of Pixel");

	BYTE* t_intensity = new BYTE[Width*Height];
	for (unsigned int i = 0; i < Height*Width; i++)
		t_intensity[i] = Raw_Intensity[i];

	BYTE* new_intensity = HistogramEqualization(t_intensity, Width, Height);

	int *tempHistogram = Histogram(new_intensity, Width, Height);

	for (unsigned int i = 0; i < 256; i++)
	{
		chart1->Series["Number Of Pixel"]->Points->AddXY(i, tempHistogram[i]);
	}
	chart1->Titles->Add("Histogram(Stretch)");

	Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = img;
	Color c;
	int temp;

	for (unsigned int row = 0; row < Height; row++)
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(new_intensity[temp], new_intensity[temp], new_intensity[temp]);
			img->SetPixel(column, row, c);
		}

	delete[]tempHistogram;
	delete[]new_intensity;
}
};
}
