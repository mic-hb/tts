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
				   letter = gcnew PuzzleLetter();
				   letter->Text = "";
				   letter->Size = System::Drawing::Size(50, 50);
				   letter->BackColor = System::Drawing::Color::White;
				   //letter->Location = Point(50 * j + 50, 50 * i + 50);
				   letter->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
			   }

			   for each (String ^ word in hiddenWords) {
				   int max_position = puzzle_dimension - word->Length;
				   int x = 0;
				   int y = 0;
				   int direction = 0;
				   bool isValid;
				   int tries = 0;
				   do {
					   x = rand() % max_position;
					   y = rand() % max_position;
					   direction = rand() % 3;

					   // Check if the position is already occupied
					   isValid = true;
					   if (x > max_position || y > max_position) {
						   if (direction == 2) {
							   isValid = false;
						   }
					   }
					   if (puzzleGrid[x, y] != nullptr) {
						   if (puzzleGrid[x, y]->Text != word[0].ToString()) {
							   isValid = false;
						   }
					   }
					   if (direction == 0) {
						   for (int i = 0; i < word->Length; i++) {
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

				   puzzleGrid[x, y] = gcnew PuzzleLetter();
				   puzzleGrid[x, y]->Text = Char::ToString(word[0]);
				   puzzleGrid[x, y]->Size = System::Drawing::Size(50, 50);
				   puzzleGrid[x, y]->BackColor = System::Drawing::Color::White;
				   puzzleGrid[x, y]->Location = Point(50 * y + 50, 50 * x + 50);
				   puzzleGrid[x, y]->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
				   puzzleGrid[x, y]->Visible = true;
				   Controls->Add(puzzleGrid[x, y]);
				   puzzleGrid[x, y]->BringToFront();



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

					   // Increment the letter for the next iteration
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

			   for (int i = 0; i < puzzle_dimension; i++) {
				   for (int j = 0; j < puzzle_dimension; j++) {
					   if (puzzleGrid[i, j] == nullptr) {
						   puzzleGrid[i, j] = gcnew PuzzleLetter();
						   puzzleGrid[i, j]->Size = System::Drawing::Size(50, 50);
						   puzzleGrid[i, j]->Location = Point(50 * j + 50, 50 * i + 50);
						   puzzleGrid[i, j]->Visible = true;  // Ensure visibility
						   Controls->Add(puzzleGrid[i, j]);
						   puzzleGrid[i, j]->BringToFront();
					   }
				   }
			   }

			   //int idx = 0;
			   //for each (String ^ word in hiddenWords)
			   //{
				  // for each (char letter in word)
				  // {
					 //  puzzleGrid[idx / 3, idx % 3] = gcnew PuzzleLetter();
					 //  puzzleGrid[idx / 3, idx % 3]->Text = Char::ToString(letter);
					 //  puzzleGrid[idx / 3, idx % 3]->Size = System::Drawing::Size(50, 50);
					 //  puzzleGrid[idx / 3, idx % 3]->BackColor = System::Drawing::Color::White;
					 //  puzzleGrid[idx / 3, idx % 3]->Location = Point(50 * (idx % 3) + 50, 50 * (idx / 3) + 50);
					 //  puzzleGrid[idx / 3, idx % 3]->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
					 //  puzzleGrid[idx / 3, idx % 3]->Visible = true;
					 //  Controls->Add(puzzleGrid[idx / 3, idx % 3]);
					 //  puzzleGrid[idx / 3, idx % 3]->BringToFront();

					 //  // Increment the letter for the next iteration
					 //  idx++;
				  // }
			   //}
			   //array<char, 1>^ letters = gcnew array<char, 1>{'D', 'O', 'G', 'C', 'A', 'T', 'R', 'A', 'T'};
			   //char letter = 'A';

			   //for (int i = 0; i < 3; i++) {
				  // for (int j = 0; j < 3; j++) {
					 //  puzzleGrid[i, j] = gcnew PuzzleLetter();
					 //  puzzleGrid[i, j]->Text = Char::ToString(letters[idx]);
					 //  puzzleGrid[i, j]->Size = System::Drawing::Size(50, 50);
					 //  puzzleGrid[i, j]->BackColor = System::Drawing::Color::White;
					 //  puzzleGrid[i, j]->Location = Point(50 * j + 50, 50 * i + 50);
					 //  puzzleGrid[i, j]->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
					 //  puzzleGrid[i, j]->Visible = true;  // Ensure visibility
					 //  Controls->Add(puzzleGrid[i, j]);
					 //  PerformLayout();
					 //  Invalidate();
					 //  Update();
					 //  puzzleGrid[i, j]->BringToFront();

					 //  // Increment the letter for the next iteration
					 //  letter++;
					 //  idx++;
				  // }
			   //}

			   //puzzleGrid = gcnew array<Label^, 2>(3, 3);

			   //char letter = 'A';

			   //for (int i = 0; i < 3; i++) {
			   //    for (int j = 0; j < 3; j++) {
			   //        puzzleGrid[i, j] = gcnew Label();
			   //        puzzleGrid[i, j]->Text = Char::ToString(letter);
			   //        puzzleGrid[i, j]->Location = Point(50 * j, 50 * i);
			   //        //puzzleGrid[i, j]->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
			   //        puzzleGrid[i, j]->Visible = true;  // Ensure visibility
			   //        Controls->Add(puzzleGrid[i, j]);
			   //        PerformLayout();
			   //        Invalidate();
			   //        Update();
			   //        puzzleGrid[i, j]->BringToFront();

			   //        // Increment the letter for the next iteration
			   //        letter++;
			   //    }
			   //}


			   /*Label^ tmp;
			   tmp = gcnew Label();
			   tmp->Text = Char::ToString('A');
			   tmp->Location = Point(0, 0);
			   tmp->Visible = true;
			   Controls->Add(tmp);

			   Label^ tmp1;
			   tmp1 = gcnew Label();
			   tmp1->Text = Char::ToString('B');
			   tmp1->Location = Point(50, 0);
			   tmp1->Visible = true;
			   Controls->Add(tmp1);

			   Label^ tmp2;
			   tmp2 = gcnew Label();
			   tmp2->Text = Char::ToString('C');
			   tmp2->Location = Point(100, 0);
			   tmp2->Visible = true;
			   Controls->Add(tmp2);

			   tmp->BringToFront();
			   tmp1->BringToFront();
			   tmp2->BringToFront();*/
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

