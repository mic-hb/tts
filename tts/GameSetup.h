#include "Form1.h"
#pragma once

namespace tts {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GameSetup
	/// </summary>
	public ref class GameSetup : public System::Windows::Forms::Form
	{
	public:
		GameSetup(void)
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
		~GameSetup()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ btnStart;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button1->Location = System::Drawing::Point(12, 52);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(67, 35);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Easy";
			this->button1->UseVisualStyleBackColor = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(251, 52);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(67, 35);
			this->button2->TabIndex = 0;
			this->button2->Text = L"Hard";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(130, 52);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(67, 35);
			this->button3->TabIndex = 0;
			this->button3->Text = L"Medium";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(47, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Difficulty";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 127);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(57, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Categories";
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button4->Location = System::Drawing::Point(12, 162);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(72, 53);
			this->button4->TabIndex = 2;
			this->button4->Text = L"Animals";
			this->button4->UseVisualStyleBackColor = false;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(246, 162);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(72, 53);
			this->button5->TabIndex = 2;
			this->button5->Text = L"Cities";
			this->button5->UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(128, 162);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(72, 53);
			this->button6->TabIndex = 2;
			this->button6->Text = L"Colors";
			this->button6->UseVisualStyleBackColor = true;
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(12, 339);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(306, 35);
			this->btnStart->TabIndex = 3;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &GameSetup::btnStart_Click);
			// 
			// GameSetup
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(330, 386);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"GameSetup";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"GameSetup";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e) {
		Form1 baru;
		baru.ShowDialog();
	}
};
}
