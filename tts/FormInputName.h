#pragma once

namespace tts {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FormInputName
	/// </summary>
	public ref class FormInputName : public System::Windows::Forms::Form
	{
	public:
		String^ name;
		FormInputName(void)
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
		~FormInputName()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ txtName;
	private: System::Windows::Forms::Button^ btnSave;
	protected:


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtName = (gcnew System::Windows::Forms::TextBox());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(44, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(192, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Enter Your Name";
			// 
			// txtName
			// 
			this->txtName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtName->Location = System::Drawing::Point(29, 82);
			this->txtName->Name = L"txtName";
			this->txtName->Size = System::Drawing::Size(226, 35);
			this->txtName->TabIndex = 1;
			this->txtName->TextChanged += gcnew System::EventHandler(this, &FormInputName::txtName_TextChanged);
			// 
			// btnSave
			// 
			this->btnSave->Location = System::Drawing::Point(77, 133);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(128, 30);
			this->btnSave->TabIndex = 2;
			this->btnSave->Text = L"Save";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &FormInputName::btnSave_Click);
			// 
			// FormInputName
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 175);
			this->Controls->Add(this->btnSave);
			this->Controls->Add(this->txtName);
			this->Controls->Add(this->label1);
			this->Name = L"FormInputName";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Game Over";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void txtName_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
		if (txtName->Text != "") {
			name = txtName->Text;
			this->Close();
		}
	}
	};
}