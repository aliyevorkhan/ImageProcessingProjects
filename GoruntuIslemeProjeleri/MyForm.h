#pragma once
#include <atlstr.h>
#include <windows.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include "imge_bmp.h"
#include "Canny.h"
#include "Histogram.h"
#include "EqualHistogram.h"


using namespace std;

float maske[9] = { 0.25,0.50,0.25,
				   0.50,  1 ,0.50,
				   0.25,0.50,0.25 };

//float maske[9] = { 0,1,0,
//				   1,1,1,
//				   0,1,0 };
float maske1[25] = { 0.0625,	0.125,	0.25,	0.125,	0.0625,
								0.125,	0.25,	0.5,	0.25,	0.125,
								0.25,	0.5,	1,		0.5,	0.25,
								0.125,	0.25,	0.5,	0.25,	0.125,
								0.0625,	0.125,	0.25,	0.125,	0.0625 };

float maske2[49] = { 0.015625 ,	0.03125,	0.0625,	0.125,	0.0625,	0.03125,0.015625,
								0.03125,	0.0625,		0.125,	0.25,	0.125,	0.0625,	0.03125,
								0.625,		0.125,		0.25,	0.5,	0.25,	0.125,	0.625,
								0.125,		0.25,		0.5,	1,		0.5,	0.25,	0.125,
								0.625,		0.125,		0.25,	0.5,	0.25,	0.125,	0.625,
								0.03125,	0.0625,		0.125,	0.25,	0.125,	0.0625,	0.03125,
								0.015625,	0.03125,	0.0625, 0.125,	0.0625,	0.03125,0.015625 };

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
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem1;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::ToolStripMenuItem^  processesToolStripMenuItem;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown6;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown5;
	private: System::Windows::Forms::ToolStripMenuItem^  clearToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  kMeansToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  convertIntensityToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  morfolgyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dilationToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  erosionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  closingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  histogramToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  setHistogramToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  histogramEqualizationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  drawToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  lineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  circleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  angerToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  drawEdgeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  drawBlackEdgeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  drawWhiteEdgeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  drawBlackEdgeToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  drawWhiteEdgeToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  drawBlackEdgeToolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  ıntegrationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ıntegrationWithZeroToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ıntegrationWith255ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  objectRecogToolStripMenuItem;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ToolStripMenuItem^  findLineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ımageGeometryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  moveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rotateToolStripMenuItem;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  rotateAliasToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  mirrorToolStripMenuItem;



	private: System::Windows::Forms::ToolStripMenuItem^  shearingToolStripMenuItem;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;





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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->processesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->convertIntensityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->circleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->setHistogramToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramEqualizationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMeansToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->morfolgyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dilationToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->erosionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->angerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawEdgeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawWhiteEdgeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawBlackEdgeToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawBlackEdgeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawWhiteEdgeToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawBlackEdgeToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ıntegrationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ıntegrationWithZeroToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ıntegrationWith255ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->objectRecogToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->findLineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ımageGeometryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->moveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rotateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rotateAliasToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mirrorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->shearingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
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
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openToolStripMenuItem,
					this->processesToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1032, 24);
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
			this->processesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
				this->convertIntensityToolStripMenuItem,
					this->drawToolStripMenuItem, this->histogramToolStripMenuItem, this->kMeansToolStripMenuItem, this->morfolgyToolStripMenuItem,
					this->angerToolStripMenuItem, this->ıntegrationToolStripMenuItem, this->objectRecogToolStripMenuItem, this->findLineToolStripMenuItem,
					this->ımageGeometryToolStripMenuItem
			});
			this->processesToolStripMenuItem->Name = L"processesToolStripMenuItem";
			this->processesToolStripMenuItem->Size = System::Drawing::Size(50, 20);
			this->processesToolStripMenuItem->Text = L"Apply";
			// 
			// convertIntensityToolStripMenuItem
			// 
			this->convertIntensityToolStripMenuItem->Name = L"convertIntensityToolStripMenuItem";
			this->convertIntensityToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->convertIntensityToolStripMenuItem->Text = L"Convert Intensity";
			this->convertIntensityToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::convertIntensityToolStripMenuItem_Click);
			// 
			// drawToolStripMenuItem
			// 
			this->drawToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->lineToolStripMenuItem,
					this->circleToolStripMenuItem
			});
			this->drawToolStripMenuItem->Name = L"drawToolStripMenuItem";
			this->drawToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->drawToolStripMenuItem->Text = L"Draw";
			// 
			// lineToolStripMenuItem
			// 
			this->lineToolStripMenuItem->Name = L"lineToolStripMenuItem";
			this->lineToolStripMenuItem->Size = System::Drawing::Size(104, 22);
			this->lineToolStripMenuItem->Text = L"Line";
			this->lineToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::lineToolStripMenuItem_Click);
			// 
			// circleToolStripMenuItem
			// 
			this->circleToolStripMenuItem->Name = L"circleToolStripMenuItem";
			this->circleToolStripMenuItem->Size = System::Drawing::Size(104, 22);
			this->circleToolStripMenuItem->Text = L"Circle";
			this->circleToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::circleToolStripMenuItem_Click);
			// 
			// histogramToolStripMenuItem
			// 
			this->histogramToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->setHistogramToolStripMenuItem1,
					this->histogramEqualizationToolStripMenuItem
			});
			this->histogramToolStripMenuItem->Name = L"histogramToolStripMenuItem";
			this->histogramToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->histogramToolStripMenuItem->Text = L"Histogram";
			// 
			// setHistogramToolStripMenuItem1
			// 
			this->setHistogramToolStripMenuItem1->Name = L"setHistogramToolStripMenuItem1";
			this->setHistogramToolStripMenuItem1->Size = System::Drawing::Size(197, 22);
			this->setHistogramToolStripMenuItem1->Text = L"Set Histogram";
			this->setHistogramToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::setHistogramToolStripMenuItem1_Click);
			// 
			// histogramEqualizationToolStripMenuItem
			// 
			this->histogramEqualizationToolStripMenuItem->Name = L"histogramEqualizationToolStripMenuItem";
			this->histogramEqualizationToolStripMenuItem->Size = System::Drawing::Size(197, 22);
			this->histogramEqualizationToolStripMenuItem->Text = L"Histogram Equalization";
			this->histogramEqualizationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::histogramEqualizationToolStripMenuItem_Click);
			// 
			// kMeansToolStripMenuItem
			// 
			this->kMeansToolStripMenuItem->Name = L"kMeansToolStripMenuItem";
			this->kMeansToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->kMeansToolStripMenuItem->Text = L"KMeansClustering1D";
			this->kMeansToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMeansToolStripMenuItem_Click);
			// 
			// morfolgyToolStripMenuItem
			// 
			this->morfolgyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->dilationToolStripMenuItem1,
					this->erosionToolStripMenuItem, this->openingToolStripMenuItem, this->closingToolStripMenuItem
			});
			this->morfolgyToolStripMenuItem->Name = L"morfolgyToolStripMenuItem";
			this->morfolgyToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->morfolgyToolStripMenuItem->Text = L"Morfolgy";
			// 
			// dilationToolStripMenuItem1
			// 
			this->dilationToolStripMenuItem1->Name = L"dilationToolStripMenuItem1";
			this->dilationToolStripMenuItem1->Size = System::Drawing::Size(120, 22);
			this->dilationToolStripMenuItem1->Text = L"Dilation";
			this->dilationToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::dilationToolStripMenuItem1_Click);
			// 
			// erosionToolStripMenuItem
			// 
			this->erosionToolStripMenuItem->Name = L"erosionToolStripMenuItem";
			this->erosionToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->erosionToolStripMenuItem->Text = L"Erosion";
			this->erosionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::erosionToolStripMenuItem_Click);
			// 
			// openingToolStripMenuItem
			// 
			this->openingToolStripMenuItem->Name = L"openingToolStripMenuItem";
			this->openingToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->openingToolStripMenuItem->Text = L"Opening";
			this->openingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openingToolStripMenuItem_Click);
			// 
			// closingToolStripMenuItem
			// 
			this->closingToolStripMenuItem->Name = L"closingToolStripMenuItem";
			this->closingToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->closingToolStripMenuItem->Text = L"Closing";
			this->closingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::closingToolStripMenuItem_Click);
			// 
			// angerToolStripMenuItem
			// 
			this->angerToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->drawEdgeToolStripMenuItem,
					this->drawBlackEdgeToolStripMenuItem
			});
			this->angerToolStripMenuItem->Name = L"angerToolStripMenuItem";
			this->angerToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->angerToolStripMenuItem->Text = L"Edge Detection";
			// 
			// drawEdgeToolStripMenuItem
			// 
			this->drawEdgeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->drawWhiteEdgeToolStripMenuItem,
					this->drawBlackEdgeToolStripMenuItem1
			});
			this->drawEdgeToolStripMenuItem->Name = L"drawEdgeToolStripMenuItem";
			this->drawEdgeToolStripMenuItem->Size = System::Drawing::Size(115, 22);
			this->drawEdgeToolStripMenuItem->Text = L"Dilation";
			// 
			// drawWhiteEdgeToolStripMenuItem
			// 
			this->drawWhiteEdgeToolStripMenuItem->Name = L"drawWhiteEdgeToolStripMenuItem";
			this->drawWhiteEdgeToolStripMenuItem->Size = System::Drawing::Size(164, 22);
			this->drawWhiteEdgeToolStripMenuItem->Text = L"Draw White Edge";
			this->drawWhiteEdgeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::drawWhiteEdgeToolStripMenuItem_Click);
			// 
			// drawBlackEdgeToolStripMenuItem1
			// 
			this->drawBlackEdgeToolStripMenuItem1->Name = L"drawBlackEdgeToolStripMenuItem1";
			this->drawBlackEdgeToolStripMenuItem1->Size = System::Drawing::Size(164, 22);
			this->drawBlackEdgeToolStripMenuItem1->Text = L"Draw Black Edge";
			this->drawBlackEdgeToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::drawBlackEdgeToolStripMenuItem1_Click);
			// 
			// drawBlackEdgeToolStripMenuItem
			// 
			this->drawBlackEdgeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->drawWhiteEdgeToolStripMenuItem1,
					this->drawBlackEdgeToolStripMenuItem2
			});
			this->drawBlackEdgeToolStripMenuItem->Name = L"drawBlackEdgeToolStripMenuItem";
			this->drawBlackEdgeToolStripMenuItem->Size = System::Drawing::Size(115, 22);
			this->drawBlackEdgeToolStripMenuItem->Text = L"Erosion";
			// 
			// drawWhiteEdgeToolStripMenuItem1
			// 
			this->drawWhiteEdgeToolStripMenuItem1->Name = L"drawWhiteEdgeToolStripMenuItem1";
			this->drawWhiteEdgeToolStripMenuItem1->Size = System::Drawing::Size(164, 22);
			this->drawWhiteEdgeToolStripMenuItem1->Text = L"Draw White Edge";
			this->drawWhiteEdgeToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::drawWhiteEdgeToolStripMenuItem1_Click);
			// 
			// drawBlackEdgeToolStripMenuItem2
			// 
			this->drawBlackEdgeToolStripMenuItem2->Name = L"drawBlackEdgeToolStripMenuItem2";
			this->drawBlackEdgeToolStripMenuItem2->Size = System::Drawing::Size(164, 22);
			this->drawBlackEdgeToolStripMenuItem2->Text = L"Draw Black Edge";
			this->drawBlackEdgeToolStripMenuItem2->Click += gcnew System::EventHandler(this, &MyForm::drawBlackEdgeToolStripMenuItem2_Click);
			// 
			// ıntegrationToolStripMenuItem
			// 
			this->ıntegrationToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ıntegrationWithZeroToolStripMenuItem,
					this->ıntegrationWith255ToolStripMenuItem
			});
			this->ıntegrationToolStripMenuItem->Name = L"ıntegrationToolStripMenuItem";
			this->ıntegrationToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->ıntegrationToolStripMenuItem->Text = L"Integration";
			// 
			// ıntegrationWithZeroToolStripMenuItem
			// 
			this->ıntegrationWithZeroToolStripMenuItem->Name = L"ıntegrationWithZeroToolStripMenuItem";
			this->ıntegrationWithZeroToolStripMenuItem->Size = System::Drawing::Size(92, 22);
			this->ıntegrationWithZeroToolStripMenuItem->Text = L"0";
			this->ıntegrationWithZeroToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ıntegrationWithZeroToolStripMenuItem_Click);
			// 
			// ıntegrationWith255ToolStripMenuItem
			// 
			this->ıntegrationWith255ToolStripMenuItem->Name = L"ıntegrationWith255ToolStripMenuItem";
			this->ıntegrationWith255ToolStripMenuItem->Size = System::Drawing::Size(92, 22);
			this->ıntegrationWith255ToolStripMenuItem->Text = L"255";
			this->ıntegrationWith255ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ıntegrationWith255ToolStripMenuItem_Click);
			// 
			// objectRecogToolStripMenuItem
			// 
			this->objectRecogToolStripMenuItem->Name = L"objectRecogToolStripMenuItem";
			this->objectRecogToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->objectRecogToolStripMenuItem->Text = L"Object Recognition";
			this->objectRecogToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::objectRecogToolStripMenuItem_Click);
			// 
			// findLineToolStripMenuItem
			// 
			this->findLineToolStripMenuItem->Name = L"findLineToolStripMenuItem";
			this->findLineToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->findLineToolStripMenuItem->Text = L"Find Line";
			this->findLineToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::findLineToolStripMenuItem_Click);
			// 
			// ımageGeometryToolStripMenuItem
			// 
			this->ımageGeometryToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->moveToolStripMenuItem,
					this->rotateToolStripMenuItem, this->rotateAliasToolStripMenuItem, this->mirrorToolStripMenuItem, this->shearingToolStripMenuItem
			});
			this->ımageGeometryToolStripMenuItem->Name = L"ımageGeometryToolStripMenuItem";
			this->ımageGeometryToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->ımageGeometryToolStripMenuItem->Text = L"Image Geometry";
			// 
			// moveToolStripMenuItem
			// 
			this->moveToolStripMenuItem->Name = L"moveToolStripMenuItem";
			this->moveToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->moveToolStripMenuItem->Text = L"Move";
			this->moveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::moveToolStripMenuItem_Click);
			// 
			// rotateToolStripMenuItem
			// 
			this->rotateToolStripMenuItem->Name = L"rotateToolStripMenuItem";
			this->rotateToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->rotateToolStripMenuItem->Text = L"Rotate";
			this->rotateToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::rotateToolStripMenuItem_Click);
			// 
			// rotateAliasToolStripMenuItem
			// 
			this->rotateAliasToolStripMenuItem->Name = L"rotateAliasToolStripMenuItem";
			this->rotateAliasToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->rotateAliasToolStripMenuItem->Text = L"Rotate Alias";
			this->rotateAliasToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::rotateAliasToolStripMenuItem_Click);
			// 
			// mirrorToolStripMenuItem
			// 
			this->mirrorToolStripMenuItem->Name = L"mirrorToolStripMenuItem";
			this->mirrorToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->mirrorToolStripMenuItem->Text = L"Mirror";
			this->mirrorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::mirrorToolStripMenuItem_Click);
			// 
			// shearingToolStripMenuItem
			// 
			this->shearingToolStripMenuItem->Name = L"shearingToolStripMenuItem";
			this->shearingToolStripMenuItem->Size = System::Drawing::Size(136, 22);
			this->shearingToolStripMenuItem->Text = L"Shearing";
			this->shearingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::shearingToolStripMenuItem_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(402, 27);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(384, 256);
			this->pictureBox3->TabIndex = 13;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(12, 289);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(384, 256);
			this->pictureBox2->TabIndex = 18;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseDown_1);
			this->pictureBox2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseUp_1);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(402, 289);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 20;
			this->label2->Text = L"label2";
			this->label2->Visible = false;
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(124, 22);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(41, 20);
			this->numericUpDown1->TabIndex = 21;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(2, 16);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(116, 34);
			this->label1->TabIndex = 22;
			this->label1->Text = L"Please enter the \r\nangle for rotation";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->numericUpDown2);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->numericUpDown3);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->numericUpDown1);
			this->groupBox1->Location = System::Drawing::Point(849, 27);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(171, 294);
			this->groupBox1->TabIndex = 23;
			this->groupBox1->TabStop = false;
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(124, 212);
			this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(41, 20);
			this->numericUpDown2->TabIndex = 29;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(2, 122);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(116, 153);
			this->label3->TabIndex = 28;
			this->label3->Text = L"Please enter the \r\ndirection for \r\nshearing\r\n(direction\r\n     x=>0\r\n    -x=>1    "
				L" \r\n     y=>2\r\n    -y=>3\r\n)";
			// 
			// numericUpDown3
			// 
			this->numericUpDown3->DecimalPlaces = 1;
			this->numericUpDown3->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->numericUpDown3->Location = System::Drawing::Point(124, 78);
			this->numericUpDown3->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15, 0, 0, 65536 });
			this->numericUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->numericUpDown3->Name = L"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(41, 20);
			this->numericUpDown3->TabIndex = 26;
			this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(2, 62);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(116, 51);
			this->label4->TabIndex = 25;
			this->label4->Text = L"Please enter the \r\ncoefficients for \r\nshearing";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1032, 551);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Image Processing";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
private: System::Void openToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) 
{
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

		this->pictureBox1->ImageLocation = openFileDialog1->FileName;
	}	

	pictureBox3->Visible = false;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);
//this->chart1->Location = System::Drawing::Point(12, pictureBox1->Bottom + 10);


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

//	chart1->Titles->Clear();
//	chart1->Series->Clear();

	

}
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}
private: System::Void kMeansToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(k_means_buffer[(row * Width) + column], k_means_buffer[(row * Width) + column], k_means_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}

}
private: System::Void convertIntensityToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
		int row, column;
		Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = surface;
		Color c;
		this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);
		for (row = 0; row < Height; row++)
			for (column = 0; column < Width; column++)
			{
				c = Color::FromArgb(Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column]);
				surface->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
			}
	
}
private: System::Void pictureBox2_MouseDown_1(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	zoom_width1 = e->X;
	zoom_height1 = e->Y;
}
private: System::Void pictureBox2_MouseUp_1(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	pictureBox3->Visible = true;

	zoom_width2 = e->X;
	zoom_height2 = e->Y;

	int k = 0;
	int zoom_width = ((zoom_width2 - zoom_width1) * 2) + 1;
	int zoom_height = ((zoom_height2 - zoom_height1) * 2) + 1;
	BYTE *Zoom_buffer = new BYTE[zoom_width*zoom_height];


	pictureBox3->Width = zoom_width;
	pictureBox3->Height = zoom_height;

	for (int i = zoom_height1; i < zoom_height2; i++)
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

	BYTE* Sonuc = new BYTE[zoom_width*zoom_height];
	Sonuc = Mask(Zoom_buffer, zoom_width, zoom_height, maske, 9, newWidth, newHeight);

	unsigned int row1, column1;
	Bitmap^ surface1 = gcnew Bitmap(pictureBox3->Width, pictureBox3->Height);
	pictureBox3->Image = surface1;
	Color c1;
	this->pictureBox3->Location = System::Drawing::Point(10, pictureBox1->Bottom+ 10);

	for (row1 = 0; row1 < newHeight; row1++)
		for (column1 = 0; column1 < newWidth; column1++)
		{
			c1 = Color::FromArgb(Sonuc[(row1*newWidth) + column1], Sonuc[(row1*newWidth) + column1], Sonuc[(row1*newWidth) + column1]);
			surface1->SetPixel(column1, row1, c1);
		}
}
private: System::Void openingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	BYTE *erosion_buffer = new BYTE[Width * Height];
	erosion_buffer = erosion(k_means_buffer, Width, Height);

	BYTE *dilation_buffer = new BYTE[Width * Height];
	dilation_buffer = dilation(erosion_buffer, Width, Height);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(dilation_buffer[(row * Width) + column], dilation_buffer[(row * Width) + column], dilation_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}
}
private: System::Void closingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	BYTE *dilation_buffer = new BYTE[Width * Height];
	dilation_buffer = dilation(k_means_buffer , Width, Height);

	BYTE *erosion_buffer = new BYTE[Width * Height];
	erosion_buffer = erosion(dilation_buffer, Width, Height);


	pictureBox2->Width = Width;
	pictureBox2->Height = Height;

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(dilation_buffer[(row * Width) + column], dilation_buffer[(row * Width) + column], dilation_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}
}
private: System::Void dilationToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	BYTE *dilation_buffer = new BYTE[Width * Height];
	dilation_buffer = dilation(k_means_buffer, Width, Height);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(dilation_buffer[(row * Width) + column], dilation_buffer[(row * Width) + column], dilation_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}
}
private: System::Void erosionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	BYTE *erosion_buffer = new BYTE[Width * Height];
	erosion_buffer = erosion(k_means_buffer, Width, Height);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}
}
private: System::Void setHistogramToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {

	BYTE* t_intensity = new BYTE[Width*Height];
	for (unsigned int i = 0; i < Height*Width; i++)
		t_intensity[i] = Raw_Intensity[i];

	int *hist = histogram(t_intensity, Width, Height);

	Histogram^ histogram1 = gcnew Histogram;
	histogram1->setHistogram(hist);
	histogram1->Show();
}
private: System::Void histogramEqualizationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	

	BYTE* t_intensity = new BYTE[Width*Height];
	for (unsigned int i = 0; i < Height*Width; i++)
		t_intensity[i] = Raw_Intensity[i];

	BYTE* new_intensity = HistogramEqualization(t_intensity, Width, Height);

	int *tempHistogram = histogram(new_intensity, Width, Height);

	Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = img;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	int temp;

	for (unsigned int row = 0; row < Height; row++)
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(new_intensity[temp], new_intensity[temp], new_intensity[temp]);
			img->SetPixel(column, row, c);
		}

	EqualHistogram^ histogram1 = gcnew EqualHistogram;
	histogram1->equalHistogram(tempHistogram);
	histogram1->Show();

	delete[]tempHistogram;
	delete[]new_intensity;
}
private: System::Void lineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	cizgiCiz(Raw_Intensity, 200, 30, 30, 200, Width, Height);

	int row, column;
	Bitmap ^ surface3 = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface3;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column]);
			surface3->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
		}

}
private: System::Void circleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	cemberCiz(Raw_Intensity, 200, 200, 50, Width, Height);

	int row, column;
	Bitmap ^ surface3 = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface3;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column], Raw_Intensity[row * Width + column]);
			surface3->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
		}
}
private: System::Void drawWhiteEdgeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	BYTE *erosion_buffer = new BYTE[Width * Height];
	erosion_buffer = Sinirlar(k_means_buffer, Width, Height, 0);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}
}
private: System::Void drawBlackEdgeToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {

	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	BYTE *erosion_buffer = new BYTE[Width * Height];
	erosion_buffer = Sinirlar(k_means_buffer, Width, Height,1);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}
}
private: System::Void drawWhiteEdgeToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	BYTE *erosion_buffer = new BYTE[Width * Height];
	erosion_buffer = Sinirlar(k_means_buffer, Width, Height, 2);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}
}
private: System::Void drawBlackEdgeToolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) {

	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	BYTE *erosion_buffer = new BYTE[Width * Height];
	erosion_buffer = Sinirlar(k_means_buffer, Width, Height, 3);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}
}
private: System::Void ıntegrationWithZeroToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	BYTE *erosion_buffer = new BYTE[Width * Height];
	erosion_buffer = Tumleme(k_means_buffer, Width, Height, 0);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}
}
private: System::Void ıntegrationWith255ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	BYTE *k_means_buffer = new BYTE[Width * Height];
	k_means_buffer = k_means(Raw_Intensity, Width, Height);

	BYTE *erosion_buffer = new BYTE[Width * Height];
	erosion_buffer = Tumleme(k_means_buffer, Width, Height, 255);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;

	unsigned int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column], erosion_buffer[(row * Width) + column]);
			surface->SetPixel(column, row, c);
		}
}
private: System::Void objectRecogToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	BYTE* t_intensity = new BYTE[Width*Height];
	for (unsigned int i = 0; i < Height*Width; i++)
		t_intensity[i] = Raw_Intensity[i];

	int label;
	BYTE* binary = k_means(t_intensity, Width, Height);

	BYTE *dilation_buffer = new BYTE[Width * Height];
	dilation_buffer = dilation(binary, Width, Height);

	BYTE *erosion_buffer = new BYTE[Width * Height];
	erosion_buffer = erosion(dilation_buffer, Width, Height);

	BYTE* Object = ObjectDetect(erosion_buffer, Width, Height, label);

	Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = img;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);

	int temp;
	this->label2->Visible = true;
	label2->Text =label + " object detected!";

	this->label2->Location = System::Drawing::Point(pictureBox2->Left + 10, pictureBox2->Bottom + 10);
	for (unsigned int row = 0; row < Height; row++)
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(Object[temp], Object[temp], Object[temp]);
			img->SetPixel(column, row, c);
		}
}
private: System::Void findLineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	

	canny_Andhough(Raw_Intensity, Width, Height);

	Canny^ form = gcnew Canny;
	form->findLine();
	form->Show();
}
private: System::Void moveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	BYTE *MovedBuff = new BYTE[Width * Height];
	MovedBuff = MoveImage(Raw_Intensity, Width, Height);

	int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);
	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(MovedBuff[row * Width + column], MovedBuff[row * Width + column], MovedBuff[row * Width + column]);
			surface->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
		}
}
private: System::Void rotateToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	int angle= (int) numericUpDown1->Value;

	BYTE *RotateBuff = new BYTE[Width * Height];
	RotateBuff = RotateImage(Raw_Intensity, Width, Height, angle);

	int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);
	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(RotateBuff[row * Width + column], RotateBuff[row * Width + column], RotateBuff[row * Width + column]);
			surface->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
		}
}
private: System::Void rotateAliasToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	int angle = (int)numericUpDown1->Value;

	BYTE *RotateBuff = new BYTE[Width * Height];
	RotateBuff = RotateImageAlias(Raw_Intensity, Width, Height, angle);

	int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);
	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(RotateBuff[row * Width + column], RotateBuff[row * Width + column], RotateBuff[row * Width + column]);
			surface->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
		}
}
private: System::Void mirrorToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	int angle = (int)numericUpDown1->Value;

	BYTE *testBuff = new BYTE[Width * Height];
	testBuff = MirrorImage(Raw_Intensity, Width, Height, angle);

	int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);
	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(testBuff[row * Width + column], testBuff[row * Width + column], testBuff[row * Width + column]);
			surface->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
		}
}
private: System::Void shearingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	double coefficients = (double)numericUpDown3->Value;
	int direction = (int)numericUpDown2->Value;
	BYTE *testBuff = new BYTE[Width * Height];
	testBuff = Shearing(Raw_Intensity, Width, Height, coefficients, direction);

	int row, column;
	Bitmap ^ surface = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
	pictureBox2->Image = surface;
	Color c;
	this->pictureBox2->Location = System::Drawing::Point(pictureBox1->Left + pictureBox1->Width + 10, 27);
	for (row = 0; row < Height; row++)
		for (column = 0; column < Width; column++)
		{
			c = Color::FromArgb(testBuff[row * Width + column], testBuff[row * Width + column], testBuff[row * Width + column]);
			surface->SetPixel(column, row, c); // x ve y korinatlar� 3. parametre ise rengi
		}
}

};
}
