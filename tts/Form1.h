#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include "PuzzleLetter.h"

namespace tts {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(String^ difficulty, String^ category)
		{
			// Mengambil string yang dipassing dari form sebelumnya
			this->difficulty = difficulty;
			this->category = category;

			InitializeComponent();
			Text = "Word Puzzle Game";
			InitializeHiddenWords();
			InitializePuzzleGrid();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		array<PuzzleLetter^, 2>^ puzzleGrid;
		array<String^>^ hiddenWords;
		String^ difficulty;
		String^ category;

	private: System::Windows::Forms::FontDialog^ fontDialog1;
		   array<String^>^ foundWords;

		   void InitializeHiddenWords() {
			   hiddenWords = gcnew array<String^>{
				   "CAT",
					   "DOG",
					   "RAT",
					   "DEER",
					   "MOUSE",
					   "SNAKE"
			   };
			   foundWords = gcnew array<String^>(hiddenWords->Length);
		   }

		   void InitializePuzzleGrid() {
			   // Deklarasi ukuran puzzle sesuai dengan tingkat difficulty
			   int puzzle_dimension = 6;
			   if (difficulty == "Easy") {
				   puzzle_dimension = 6;
			   }
			   else if (difficulty == "Medium") {
				   puzzle_dimension = 10;
			   }
			   else if (difficulty == "Hard") {
				   puzzle_dimension = 15;
			   }

			   // Inisialisasi array 2 dimensi untuk puzzle
			   puzzleGrid = gcnew array<PuzzleLetter^, 2>(puzzle_dimension, puzzle_dimension);
			   for each (PuzzleLetter ^ letter in puzzleGrid) {
				   letter = gcnew PuzzleLetter();	// Inisialisasi setiap kotak puzzle
				   letter->Text = "";				// Property Text nya dikosongin dulu
			   }

			   // Random penempatan setiap kata di array hiddenWords
			   for each (String ^ word in hiddenWords) {
				   int max_position = puzzle_dimension - word->Length;	// Maksimal posisi buat huruf pertama setiap kata
				   int x = 0;
				   int y = 0;
				   int direction = 0;	// 0 = kanan, 1 = turun, 2 = diagonal kanan bawah
				   bool isValid;		// ngecek apakah posisi yang dipilih valid atau tidak
				   int tries = 0;		// safety measure, kalau ada kata yang ga bisa dimasukin ke puzzle langsung diskip biar ga infinite loop

				   do {
					   // random x, y dan direction
					   x = rand() % max_position;
					   y = rand() % max_position;
					   direction = rand() % 3;

					   // Pengecekan valid atau tidak
					   isValid = true;
					   if (x > max_position || y > max_position) {		// ini ngecek apakah posisi yang dipilih masih muat buat diagonal atau tdk
						   if (direction == 2) {
							   isValid = false;
						   }
					   }
					   if (puzzleGrid[x, y] != nullptr) {				// kalau posisi yang dipilih udah ada hurufnya, cek apakah hurufnya sama atau tidak
						   if (puzzleGrid[x, y]->Text != word[0].ToString()) {
							   isValid = false;
						   }
					   }
					   if (direction == 0) {							// cek masing-masing hurufnya
						   for (int i = 0; i < word->Length; i++) {		// kalau misal arahnya horizontal, dan ada huruf yang ga sama atau udah ga muat, jadinya invalid
							   if (puzzleGrid[x + i, y] != nullptr) {
								   if (puzzleGrid[x + i, y]->Text != word[i].ToString()) {
									   isValid = false;
								   }
							   }
						   }
					   }
					   else if (direction == 1) {
						   for (int i = 0; i < word->Length; i++) {
							   if (puzzleGrid[x, y + i] != nullptr) {
								   if (puzzleGrid[x, y + i]->Text != word[i].ToString()) {
									   isValid = false;
								   }
							   }
						   }
					   }
					   else if (direction == 2) {
						   for (int i = 0; i < word->Length; i++) {
							   if (puzzleGrid[x + i, y + i] != nullptr) {
								   if (puzzleGrid[x + i, y + i]->Text != word[i].ToString()) {
									   isValid = false;
								   }
							   }
						   }
					   }

					   tries++;
					   if (tries == 10) goto nextWord;
				   } while (!isValid);

				   // Kalau udah valid, masukin huruf pertamanya ke puzzle
				   puzzleGrid[x, y] = gcnew PuzzleLetter();
				   puzzleGrid[x, y]->Text = Char::ToString(word[0]);
				   puzzleGrid[x, y]->Size = System::Drawing::Size(50, 50);
				   puzzleGrid[x, y]->BackColor = System::Drawing::Color::White;
				   puzzleGrid[x, y]->Location = Point(50 * y + 50, 50 * x + 50);
				   puzzleGrid[x, y]->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
				   puzzleGrid[x, y]->Visible = true;
				   Controls->Add(puzzleGrid[x, y]);
				   puzzleGrid[x, y]->BringToFront();

				   // Lanjut masukkin huruf lainnya
				   for each (char letter in word) {
					   puzzleGrid[x, y] = gcnew PuzzleLetter();
					   puzzleGrid[x, y]->Text = Char::ToString(letter);
					   puzzleGrid[x, y]->Size = System::Drawing::Size(50, 50);
					   puzzleGrid[x, y]->BackColor = System::Drawing::Color::White;
					   puzzleGrid[x, y]->Location = Point(50 * y + 50, 50 * x + 50);
					   puzzleGrid[x, y]->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
					   puzzleGrid[x, y]->Visible = true;
					   Controls->Add(puzzleGrid[x, y]);
					   puzzleGrid[x, y]->BringToFront();

					   // Ubah posisi X dan Y untuk huruf selanjutnya
					   if (direction == 0) {
						   x++;
					   }
					   else if (direction == 1) {
						   y++;
					   }
					   else if (direction == 2) {
						   x++;
						   y++;
					   }
				   }

			   nextWord:;
			   }

			   /*
					Ngisi kotak-kotak yang masih kosong
			   */
			   for (int i = 0; i < puzzle_dimension; i++) {
				   for (int j = 0; j < puzzle_dimension; j++) {
					   if (puzzleGrid[i, j] == nullptr) {
						   // ngerandom ascii code dari huruf a sampai z
						   int letter = rand() % (90 - 65) + 65;

						   puzzleGrid[i, j] = gcnew PuzzleLetter();
						   puzzleGrid[i, j]->Text = gcnew String(static_cast<char>(letter), 1);
						   puzzleGrid[i, j]->Size = System::Drawing::Size(50, 50);
						   puzzleGrid[i, j]->BackColor = System::Drawing::Color::White;
						   puzzleGrid[i, j]->Location = Point(50 * j + 50, 50 * i + 50);
						   puzzleGrid[i, j]->Visible = true;
						   puzzleGrid[i, j]->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
						   Controls->Add(puzzleGrid[i, j]);
						   puzzleGrid[i, j]->BringToFront();
					   }
				   }
			   }
		   }

		   void PuzzleLetter_Click(Object^ sender, EventArgs^ e) {
			   PuzzleLetter^ clickedLetter = dynamic_cast<PuzzleLetter^>(sender);

			   if (!clickedLetter->IsHighlighted) {
				   clickedLetter->BackColor = System::Drawing::Color::Green;
				   clickedLetter->IsHighlighted = true;
				   CheckForWords();
			   }
			   else {
				   clickedLetter->BackColor = System::Drawing::Color::White;
				   clickedLetter->IsHighlighted = false;
			   }
		   }

		   void CheckForWords() {
			   for (int i = 0; i < hiddenWords->Length; i++) {
				   if (IsWordFound(hiddenWords[i]) && foundWords[i] == nullptr) {
					   MessageBox::Show("Found word: " + hiddenWords[i]);
					   foundWords[i] = hiddenWords[i];
				   }
			   }
		   }

		   bool IsWordFound(String^ word) {
			   String^ highlightedLetters = "";

			   for (int i = 0; i < puzzleGrid->GetLength(0); i++) {
				   for (int j = 0; j < puzzleGrid->GetLength(1); j++) {
					   if (puzzleGrid[i, j]->IsHighlighted) {
						   highlightedLetters += puzzleGrid[i, j]->Text;
					   }
				   }
			   }

			   return highlightedLetters->Equals(word);
		   }

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			   this->SuspendLayout();
			   // 
			   // Form1
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(484, 461);
			   this->Name = L"Form1";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Form1";
			   this->ResumeLayout(false);

		   }
#pragma endregion
	};
}

