#pragma once

#include "Sphinx\Button.h"
#include "Sphinx\CheckBox.h"
#include "Sphinx\ComboBox.h"
#include "Sphinx\Form.h"
#include "Sphinx\GroupBox.h"
#include "Sphinx\Label.h"
#include "Sphinx\RadioButton.h"
#include "Sphinx\TabControl.h"
#include "Sphinx\TabPage.h"
#include "Sphinx\TrackBar.h"

namespace Project1
{
	using namespace Sphinx::Forms;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	class MyForm : public Sphinx::Forms::CForm
	{
	public:
		MyForm(CRenderer* renderer)
		{
			this->renderer = renderer;
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
			for (auto& c : this->Controls->Collection)
			{
				delete c;
				this->renderer->RemoveFont(c->Font);
			}
		}

	private: Sphinx::Forms::CTabControl* tabControl1;
	private: Sphinx::Forms::CTabPage* tabPage1;
	private: Sphinx::Forms::CTabPage* tabPage2;
	private: Sphinx::Forms::CGroupBox* groupBox1;
	private: Sphinx::Forms::CGroupBox* groupBox2;
	private: Sphinx::Forms::CLabel* label1;
	private: Sphinx::Forms::CButton* button1;
	private: Sphinx::Forms::CCheckBox* checkBox1;
	private: Sphinx::Forms::CCheckBox* checkBox2;
	private: Sphinx::Forms::CRadioButton* radioButton1;
	private: Sphinx::Forms::CRadioButton* radioButton2;
	private: Sphinx::Forms::CTrackBar* trackBar1;
	private: Sphinx::Forms::CTrackBar* trackBar2;
	private: Sphinx::Forms::CTrackBar* trackBar3;
	private: Sphinx::Forms::CRadioButton* radioButton3;
	private: Sphinx::Forms::CRadioButton* radioButton4;

	private:
		/// <summary>
		/// Required renderer variable.
		/// </summary>
		CRenderer* renderer;

#pragma region Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent()
		{
			this->tabControl1 = new Sphinx::Forms::CTabControl();
			this->tabPage1 = new Sphinx::Forms::CTabPage();
			this->tabPage2 = new Sphinx::Forms::CTabPage();
			this->groupBox1 = new Sphinx::Forms::CGroupBox();
			this->groupBox2 = new Sphinx::Forms::CGroupBox();
			this->label1 = new Sphinx::Forms::CLabel();
			this->button1 = new Sphinx::Forms::CButton();
			this->checkBox1 = new Sphinx::Forms::CCheckBox();
			this->checkBox2 = new Sphinx::Forms::CCheckBox();
			this->radioButton1 = new Sphinx::Forms::CRadioButton();
			this->radioButton2 = new Sphinx::Forms::CRadioButton();
			this->trackBar1 = new Sphinx::Forms::CTrackBar();
			this->trackBar2 = new Sphinx::Forms::CTrackBar();
			this->trackBar3 = new Sphinx::Forms::CTrackBar();
			this->radioButton3 = new Sphinx::Forms::CRadioButton();
			this->radioButton4 = new Sphinx::Forms::CRadioButton();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(tabPage1);
			this->tabControl1->Controls->Add(tabPage2);
			this->tabControl1->Location = D3DXVECTOR2(10.0f, 10.0f);
			this->tabControl1->Size = D3DXVECTOR2(379.0f, 256.0f);
			this->renderer->AddFont(this->tabControl1->Font);
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(groupBox1);
			this->tabPage1->Controls->Add(groupBox2);
			this->tabPage1->Text = "tabPage1";
			this->renderer->AddFont(this->tabPage1->Font);
			// 
			// m_pTabPage2
			// 
			this->tabPage2->Text = "tabPage2";
			this->renderer->AddFont(this->tabPage2->Font);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(label1);
			this->groupBox1->Controls->Add(button1);
			this->groupBox1->Controls->Add(checkBox1);
			this->groupBox1->Controls->Add(checkBox2);
			this->groupBox1->Controls->Add(radioButton1);
			this->groupBox1->Controls->Add(radioButton2);
			this->groupBox1->Location = D3DXVECTOR2(10.0f, 10.0f);
			this->groupBox1->Size = D3DXVECTOR2(175.0f, 209.0f);
			this->groupBox1->Text = "groupBox1";
			this->renderer->AddFont(this->groupBox1->Font);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(trackBar1);
			this->groupBox2->Controls->Add(trackBar2);
			this->groupBox2->Controls->Add(trackBar3);
			this->groupBox2->Controls->Add(radioButton3);
			this->groupBox2->Controls->Add(radioButton4);
			this->groupBox2->Location = D3DXVECTOR2(194.0f, 10.0f);
			this->groupBox2->Size = D3DXVECTOR2(174.0f, 209.0f);
			this->groupBox2->Text = "groupBox2";
			this->renderer->AddFont(this->groupBox2->Font);
			// 
			// label1
			// 
			this->label1->Location = D3DXVECTOR2(10.0f, 15.0f);
			this->label1->Text = "label1";
			this->renderer->AddFont(this->label1->Font);
			// 
			// button1
			// 
			this->button1->Location = D3DXVECTOR2(10.0f, 43.0f);
			this->button1->Text = "button1";
			this->renderer->AddFont(this->button1->Font);
			// 
			// checkBox1
			// 
			this->checkBox1->Location = D3DXVECTOR2(10.0f, 73.0f);
			this->checkBox1->Text = "checkBox1";
			this->renderer->AddFont(this->checkBox1->Font);
			// 
			// checkBox2
			// 
			this->checkBox2->Location = D3DXVECTOR2(10.0f, 103.0f);
			this->checkBox2->Text = "checkBox2";
			this->renderer->AddFont(this->checkBox2->Font);
			// 
			// radioButton1
			// 
			this->radioButton1->Location = D3DXVECTOR2(10.0f, 133.0f);
			this->radioButton1->Text = "radioButton1";
			this->renderer->AddFont(this->radioButton1->Font);
			// 
			// radioButton2
			// 
			this->radioButton2->Location = D3DXVECTOR2(10.0f, 163.0f);
			this->radioButton2->Text = "radioButton2";
			this->renderer->AddFont(this->radioButton2->Font);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = D3DXVECTOR2(10.0f, 10.0f);
			this->trackBar1->Text = "trackBar1";
			this->trackBar1->Maximum = 255;
			this->renderer->AddFont(this->trackBar1->Font);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = D3DXVECTOR2(10.0f, 50.0f);
			this->trackBar2->Text = "trackBar2";
			this->trackBar2->Maximum = 255;
			this->renderer->AddFont(this->trackBar2->Font);
			// 
			// trackBar3
			// 
			this->trackBar3->Location = D3DXVECTOR2(10.0f, 90.0f);
			this->trackBar3->Text = "trackBar3";
			this->trackBar3->Maximum = 255;
			this->renderer->AddFont(this->trackBar3->Font);
			// 
			// radioButton3
			// 
			this->radioButton3->Location = D3DXVECTOR2(10.0f, 133.0f);
			this->radioButton3->Text = "radioButton3";
			this->renderer->AddFont(this->radioButton3->Font);
			// 
			// radioButton4
			// 
			this->radioButton4->Location = D3DXVECTOR2(10.0f, 163.0f);
			this->radioButton4->Text = "radioButton4";
			this->renderer->AddFont(this->radioButton4->Font);
			// 
			// MyForm
			// 
			this->Size = D3DXVECTOR2(400.0f, 300.0f);
			this->Controls->Add(tabControl1);
			this->Text = "MyForm";
			this->renderer->AddFont(this->Font);
		}
#pragma endregion
	};
}