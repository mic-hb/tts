#include "Form1.h"
#include <list>
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
			difficultyButtons = gcnew array<Button^>{ btnEasy, btnMedium, btnHard };
			categoryButtons = gcnew array<Button^>{ btnAnimals, btnCities, btnColors };
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
	private: System::Windows::Forms::Button^ btnEasy;
	private: System::Windows::Forms::Button^ btnHard;
	private: System::Windows::Forms::Button^ btnMedium;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ btnAnimals;
	private: System::Windows::Forms::Button^ btnCities;
	private: System::Windows::Forms::Button^ btnColors;
	private: System::Windows::Forms::Button^ btnStart;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		array<Button^>^ difficultyButtons;
		array<Button^>^ categoryButtons;
		String^ difficulty;
		String^ category;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnEasy = (gcnew System::Windows::Forms::Button());
			this->btnHard = (gcnew System::Windows::Forms::Button());
			this->btnMedium = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btnAnimals = (gcnew System::Windows::Forms::Button());
			this->btnCities = (gcnew System::Windows::Forms::Button());
			this->btnColors = (gcnew System::Windows::Forms::Button());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnEasy
			// 
			this->btnEasy->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->btnEasy->Location = System::Drawing::Point(12, 52);
			this->btnEasy->Name = L"btnEasy";
			this->btnEasy->Size = System::Drawing::Size(67, 35);
			this->btnEasy->TabIndex = 0;
			this->btnEasy->Text = L"Easy";
			this->btnEasy->UseVisualStyleBackColor = false;
			this->btnEasy->Click += gcnew System::EventHandler(this, &GameSetup::btnEasy_Click);
			// 
			// btnHard
			// 
			this->btnHard->Location = System::Drawing::Point(251, 52);
			this->btnHard->Name = L"btnHard";
			this->btnHard->Size = System::Drawing::Size(67, 35);
			this->btnHard->TabIndex = 0;
			this->btnHard->Text = L"Hard";
			this->btnHard->UseVisualStyleBackColor = true;
			this->btnHard->Click += gcnew System::EventHandler(this, &GameSetup::btnEasy_Click);
			// 
			// btnMedium
			// 
			this->btnMedium->Location = System::Drawing::Point(130, 52);
			this->btnMedium->Name = L"btnMedium";
			this->btnMedium->Size = System::Drawing::Size(67, 35);
			this->btnMedium->TabIndex = 0;
			this->btnMedium->Text = L"Medium";
			this->btnMedium->UseVisualStyleBackColor = true;
			this->btnMedium->Click += gcnew System::EventHandler(this, &GameSetup::btnEasy_Click);
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
			// btnAnimals
			// 
			this->btnAnimals->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->btnAnimals->Location = System::Drawing::Point(12, 162);
			this->btnAnimals->Name = L"btnAnimals";
			this->btnAnimals->Size = System::Drawing::Size(72, 53);
			this->btnAnimals->TabIndex = 2;
			this->btnAnimals->Text = L"Animals";
			this->btnAnimals->UseVisualStyleBackColor = false;
			this->btnAnimals->Click += gcnew System::EventHandler(this, &GameSetup::btnCat_Click);
			// 
			// btnCities
			// 
			this->btnCities->Location = System::Drawing::Point(246, 162);
			this->btnCities->Name = L"btnCities";
			this->btnCities->Size = System::Drawing::Size(72, 53);
			this->btnCities->TabIndex = 2;
			this->btnCities->Text = L"Cities";
			this->btnCities->UseVisualStyleBackColor = true;
			this->btnCities->Click += gcnew System::EventHandler(this, &GameSetup::btnCat_Click);
			// 
			// btnColors
			// 
			this->btnColors->Location = System::Drawing::Point(128, 162);
			this->btnColors->Name = L"btnColors";
			this->btnColors->Size = System::Drawing::Size(72, 53);
			this->btnColors->TabIndex = 2;
			this->btnColors->Text = L"Colors";
			this->btnColors->UseVisualStyleBackColor = true;
			this->btnColors->Click += gcnew System::EventHandler(this, &GameSetup::btnCat_Click);
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
			this->Controls->Add(this->btnColors);
			this->Controls->Add(this->btnCities);
			this->Controls->Add(this->btnAnimals);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnMedium);
			this->Controls->Add(this->btnHard);
			this->Controls->Add(this->btnEasy);
			this->Name = L"GameSetup";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"GameSetup";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		/*
		* Function untuk pindah ke form baru
		*/
	private: System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e) {
		// Form1 adalah nama class form barunya yang kita deklarasi
		// gcnew digunakan untuk membuat object baru dari class Form1
		// difficulty dan category adalah parameter yang dipassing ke constructor Form1
		Form1^ baru = gcnew Form1(difficulty, category);
		baru->ShowDialog();
	}

		   /*
		   * Function untuk mengganti-ganti warna button Difficulty
		   */
	private: System::Void btnEasy_Click(System::Object^ sender, System::EventArgs^ e) {
		// Variable pressed menyimpan button yang diklik
		// safe_cast digunakan untuk mengubah tipe data dari sender (Object) menjadi Button
		// karena sender berupa Object, maka tidak bisa langsung diambil nama buttonnya
		Button^ pressed = safe_cast<Button^>(sender);

		// pressed->Name mengambil nama button yang diklik
		if (pressed->Name == "btnEasy") {
			// Jika warna button belum hijau, maka warna button akan diubah menjadi hijau
			if (pressed->BackColor != System::Drawing::Color::FromArgb(128, 255, 128)) {
				pressed->BackColor = System::Drawing::Color::FromArgb(128, 255, 128);
				difficulty = "Easy";
			}
		}
		else if (pressed->Name == "btnMedium") {
			if (pressed->BackColor != System::Drawing::Color::FromArgb(255, 255, 128)) {
				pressed->BackColor = System::Drawing::Color::FromArgb(255, 255, 128);
				difficulty = "Medium";
			}
		}
		else if (pressed->Name == "btnHard") {
			if (pressed->BackColor != System::Drawing::Color::FromArgb(255, 128, 128)) {
				pressed->BackColor = System::Drawing::Color::FromArgb(255, 128, 128);
				difficulty = "Hard";
			}
		}

		// Looping untuk mengubah warna button lain yang tidak diklik menjadi abu-abu
		for each (Button ^ btn in difficultyButtons) {
			if (btn != pressed) {
				btn->BackColor = System::Drawing::Color::LightGray;
			}
		}
	}


		   /*
		   * Function untuk mengganti-ganti warna button Category
		   * kurang lebih sama dengan function di atas
		   */
	private: System::Void btnCat_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ pressed = safe_cast<Button^>(sender);
		if (pressed->BackColor != System::Drawing::Color::FromArgb(128, 255, 128)) {
			pressed->BackColor = System::Drawing::Color::FromArgb(128, 255, 128);
		}

		if (pressed->Name == "btnAnimals") {
			category = "Animals";
		}
		else if (pressed->Name == "btnCities") {
			category = "Cities";
		}
		else if (pressed->Name == "btnColors") {
			category = "Colors";
		}

		for each (Button ^ btn in categoryButtons) {
			if (btn != pressed) {
				btn->BackColor = System::Drawing::Color::LightGray;
			}
		}
	}
	};
}
