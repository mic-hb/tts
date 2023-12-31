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

			Size = System::Drawing::Size(50 * puzzleGrid->GetLength(0) + 100, 50 * puzzleGrid->GetLength(1) + 100);
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
				   puzzle_dimension = 8;
			   }
			   else if (difficulty == "Hard") {
				   puzzle_dimension = 12;
			   }

			   // Inisialisasi array 2 dimensi untuk puzzle
			   puzzleGrid = gcnew array<PuzzleLetter^, 2>(puzzle_dimension, puzzle_dimension);
			   for each (PuzzleLetter ^ letter in puzzleGrid) {
				   letter = gcnew PuzzleLetter();	// Inisialisasi setiap kotak puzzle
				   letter->Text = "";				// Property Text nya dikosongin dulu
			   }

			   // Random penempatan setiap kata di array hiddenWords
			   for each (String ^ word in hiddenWords) {
				   int wordLength = word->Length;

				   int x, y, direction;
				   bool isValid;
				   int tries = 0;

				   do {
					   // Random starting position and direction
					   x = rand() % puzzle_dimension;
					   y = rand() % puzzle_dimension;
					   direction = rand() % 3;

					   // Check if the word fits in the chosen direction
					   isValid = true;
					   for (int i = 0; i < wordLength; i++) {
						   int newX = x, newY = y;

						   if (direction == 0) {
							   newX += i;
						   }
						   else if (direction == 1) {
							   newY += i;
						   }
						   else if (direction == 2) {
							   newX += i;
							   newY += i;
						   }

						   if (newX >= puzzle_dimension || newY >= puzzle_dimension || puzzleGrid[newX, newY] != nullptr) {
							   isValid = false;
							   break;
						   }
					   }

					   tries++;
					   if (tries == 100) goto nextWord;
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

				   // Place the word in the puzzle
				   //for (int i = 0; i < wordLength; i++) {
					  // int newX = x, newY = y;

					  // if (direction == 0) {
						 //  newX += i;
					  // }
					  // else if (direction == 1) {
						 //  newY += i;
					  // }
					  // else if (direction == 2) {
						 //  newX += i;
						 //  newY += i;
					  // }


					  // // Kalau udah valid, masukin huruf-hurufnya
					  // puzzleGrid[newX, newY] = gcnew PuzzleLetter();
					  // puzzleGrid[newX, newY]->Text = Char::ToString(word[i]);
					  // puzzleGrid[newX, newY]->Size = System::Drawing::Size(50, 50);
					  // puzzleGrid[newX, newY]->BackColor = System::Drawing::Color::White;
					  // puzzleGrid[newX, newY]->Location = Point(50 * newY + 50, 50 * newX + 50);
					  // puzzleGrid[newX, newY]->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
					  // puzzleGrid[newX, newY]->Visible = true;
					  // Controls->Add(puzzleGrid[x, y]);
					  // puzzleGrid[newX, newY]->BringToFront();
				   //}


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

