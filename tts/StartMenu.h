#include "GameSetup.h"
#include "HashMap.h"
#include "FormHighscore.h"
#include <vector>
#include <string>
#include <msclr/marshal_cppstd.h>
#pragma once

namespace tts {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for StartMenu
	/// </summary>
	public ref class StartMenu : public System::Windows::Forms::Form
	{
	public:
		// deklarasi & bikin HashMap ukuran 20
		HashMap* scores = new HashMap(20);
		StartMenu(void)
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
		~StartMenu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btnPlay;
	private: System::Windows::Forms::Button^ btnHighscore;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnPlay = (gcnew System::Windows::Forms::Button());
			this->btnHighscore = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(111, 27);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(64, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"TTS";
			// 
			// btnPlay
			// 
			this->btnPlay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnPlay->Location = System::Drawing::Point(87, 118);
			this->btnPlay->Name = L"btnPlay";
			this->btnPlay->Size = System::Drawing::Size(106, 41);
			this->btnPlay->TabIndex = 1;
			this->btnPlay->Text = L"Play Game";
			this->btnPlay->UseVisualStyleBackColor = true;
			this->btnPlay->Click += gcnew System::EventHandler(this, &StartMenu::btnPlay_Click);
			// 
			// btnHighscore
			// 
			this->btnHighscore->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnHighscore->Location = System::Drawing::Point(87, 174);
			this->btnHighscore->Name = L"btnHighscore";
			this->btnHighscore->Size = System::Drawing::Size(106, 41);
			this->btnHighscore->TabIndex = 2;
			this->btnHighscore->Text = L"Highscore";
			this->btnHighscore->UseVisualStyleBackColor = true;
			this->btnHighscore->Click += gcnew System::EventHandler(this, &StartMenu::btnHighscore_Click);
			// 
			// StartMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->btnHighscore);
			this->Controls->Add(this->btnPlay);
			this->Controls->Add(this->label1);
			this->Name = L"StartMenu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"StartMenu";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//Buat kalau klik play game
	private: System::Void btnPlay_Click(System::Object^ sender, System::EventArgs^ e) {
		// deklarasi form atau windows baru supaya dimunculin
		GameSetup^ baru = gcnew GameSetup();
		baru->ShowDialog();


		if (baru->score != 0 && baru->player_name != "") {
			// Ambil name dan score player
			// Variabel di passing dari Form1 ke GameSetup ke StartMenu
			int^ current_score = baru->score;
			String^ current_name = baru->player_name;

			// Convert String^ ke std::string
			std::string name = marshal_as<std::string>(current_name);
			int score = (int)current_score;

			// Nama & scorenya dimasukin Hashmap
			scores->put(name, score);
		}

	}

		   //Buat kalau klik highscore
	private: System::Void btnHighscore_Click(System::Object^ sender, System::EventArgs^ e) {
		// Bikin form baru juga
		FormHighscore^ baru = gcnew FormHighscore(scores);
		baru->ShowDialog();
	}
	};
}
