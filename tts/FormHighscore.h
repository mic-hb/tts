#pragma once

namespace tts {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FormHighscore
	/// </summary>
	public ref class FormHighscore : public System::Windows::Forms::Form
	{
	public:
		HashMap* scores;
		FormHighscore(HashMap* scores)
		{
			this->scores = scores;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormHighscore()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::DataGridView^ dgvHighscore;
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
			this->dgvHighscore = (gcnew System::Windows::Forms::DataGridView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvHighscore))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(251, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(106, 24);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Highscore";
			// 
			// dgvHighscore
			// 
			this->dgvHighscore->AllowUserToAddRows = false;
			this->dgvHighscore->AllowUserToDeleteRows = false;
			this->dgvHighscore->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvHighscore->Location = System::Drawing::Point(138, 67);
			this->dgvHighscore->Name = L"dgvHighscore";
			this->dgvHighscore->ReadOnly = true;
			this->dgvHighscore->Size = System::Drawing::Size(339, 301);
			this->dgvHighscore->TabIndex = 1;
			// 
			// FormHighscore
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(626, 413);
			this->Controls->Add(this->dgvHighscore);
			this->Controls->Add(this->label1);
			this->Name = L"FormHighscore";
			this->Text = L"FormHighscore";
			this->Load += gcnew System::EventHandler(this, &FormHighscore::FormHighscore_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvHighscore))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void FormHighscore_Load(System::Object^ sender, System::EventArgs^ e) {
		dgvHighscore->Rows->Clear();
		dgvHighscore->Columns->Clear();
		dgvHighscore->Columns->Add("Name", "Name");
		dgvHighscore->Columns->Add("Score", "Score");
		for (int i = 0; i < scores->size(); i++) {
			dgvHighscore->Rows->Add();
			dgvHighscore->Rows[i]->Cells[0]->Value = gcnew String(scores->get(i)->getName().c_str());
			dgvHighscore->Rows[i]->Cells[1]->Value = gcnew String(scores->get(i)->getScore().c_str());
		}
	}
	};
}