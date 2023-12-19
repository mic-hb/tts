#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include "PuzzleLetter.h"
#include "FormInputName.h"
#include <iostream>

namespace tts {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		int^ score;
		int seconds;
		bool playAgain;
	private: System::Windows::Forms::Timer^ timer1;
	public:
		String^ player_name;

		ref class Node {
		public:
			String^ key;
			Node^ left;
			Node^ right;

			Node(String^ data) {
				key = data;
				left = nullptr;
				right = nullptr;
			}
		};
		ref class BST {
		private:
			Node^ root;
			List<String^>^ hiddenWords;

			Node^ insertRecursive(Node^ root, String^ key) {
				if (root == nullptr) {
					return gcnew Node(key);
				}

				if (String::Compare(key, root->key) < 0) {
					root->left = insertRecursive(root->left, key);
				}
				else if (String::Compare(key, root->key) > 0) {
					root->right = insertRecursive(root->right, key);
				}

				return root;
			}

			Node^ findRecursive(Node^ root, String^ key) {
				if (root == nullptr || root->key == key) {
					return root;
				}

				if (String::Compare(key, root->key) < 0) {
					return findRecursive(root->left, key);
				}
				else {
					return findRecursive(root->right, key);
				}
			}

			void inOrderTraversal(Node^ root) {
				if (root != nullptr) {
					inOrderTraversal(root->left);
					MessageBox::Show(root->key + " ");
					inOrderTraversal(root->right);
				}
			}

			void inOrderTrav(Node^ root) {
				if (root != nullptr) {
					inOrderTrav(root->left);
					//return root;
					this->hiddenWords->Add(root->key);
					inOrderTrav(root->right);
				}

			}

		public:
			BST() {
				root = nullptr;
				hiddenWords = gcnew List<String^>();
			}

			void insert(String^ key) {
				root = insertRecursive(root, key);
			}

			void displayInOrder() {
				MessageBox::Show("In-order traversal of the BST: ");
				inOrderTraversal(root);
				Console::WriteLine();
			}

			void checkWordInOrder() {

			}

			List<String^>^ getHiddenWords() {
				inOrderTrav(root);
				return hiddenWords;
			}

			String^ find(String^ key) {
				Node^ foundNode = findRecursive(root, key);
				if (foundNode != nullptr) return foundNode->key;
				else return nullptr;
			}

		};
		Form1(String^ difficulty, String^ category)
		{
			// Mengambil string yang dipassing dari form sebelumnya
			this->difficulty = difficulty;
			this->category = category;

			this->score = 0;
			this->player_name = "";
			this->seconds = 0;
			this->playAgain = false;

			InitializeComponent();
			Text = "Word Puzzle Game";
			InitializeHiddenWords();
			InitializePuzzleGrid();
			InitializeLB();

			Size = System::Drawing::Size(50 * puzzleGrid->GetLength(0) + 125 + 125, 50 * puzzleGrid->GetLength(1) + 125);

			timer1->Start();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:

		array<PuzzleLetter^, 2>^ puzzleGrid;
		List<String^>^ hiddenWords;
		BST^ hiddens;
		String^ difficulty;
		String^ category;
		ListBox^ lbFoundWords;
		ListBox^ lbHiddenWords;
		String^ highlightedLetters = "";

	private:
		System::Windows::Forms::FontDialog^ fontDialog1;
		List<String^>^ foundWords;


		void InitializeHiddenWords() {
			hiddens = gcnew BST();
			hiddens->insert("CAT");
			hiddens->insert("DOG");
			hiddens->insert("RAT");
			hiddens->insert("DEER");
			hiddens->insert("MOUSE");
			hiddens->insert("SNAKE");

			hiddenWords = hiddens->getHiddenWords();

			foundWords = gcnew List<String^>();
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
			for (int i = hiddenWords->Count - 1; i >= 0; i--) {
				//for each (String ^ word in hiddenWords) {
				String^ word = hiddenWords[i];
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
					if (tries == 100)
					{
						MessageBox::Show(word);
						hiddenWords->RemoveAt(i);
						goto nextWord;
					}
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

		void InitializeLB() {
			int starting_x = 50 * puzzleGrid->GetLength(0) + 75;
			int starting_y = 50;

			// List kata yang mau dicari
			lbHiddenWords = gcnew ListBox();
			lbHiddenWords->Location = Point(starting_x, starting_y);
			lbHiddenWords->Size = System::Drawing::Size(100, 15 * hiddenWords->Count);
			lbHiddenWords->Visible = true;
			lbHiddenWords->Enabled = false;
			lbHiddenWords->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			Controls->Add(lbHiddenWords);
			lbHiddenWords->BringToFront();

			// List kata yg udah ketemu
			lbFoundWords = gcnew ListBox();
			lbFoundWords->Location = Point(starting_x, starting_y + (14 * hiddenWords->Count) + 25);
			lbFoundWords->Size = System::Drawing::Size(100, 15 * hiddenWords->Count);
			lbFoundWords->Visible = true;
			lbFoundWords->Enabled = false;
			lbFoundWords->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			Controls->Add(lbFoundWords);
			lbFoundWords->BringToFront();

			for each (String ^ word in hiddenWords) {
				lbHiddenWords->Items->Add(word);
			}
		}

		void PuzzleLetter_Click(Object^ sender, EventArgs^ e) {
			PuzzleLetter^ clickedLetter = dynamic_cast<PuzzleLetter^>(sender);

			if (!clickedLetter->IsHighlighted) {
				if (clickedLetter->BackColor == System::Drawing::Color::White)
					clickedLetter->BackColor = System::Drawing::Color::LightSalmon;
				else
					clickedLetter->BackColor = System::Drawing::Color::Salmon;

				clickedLetter->IsHighlighted = true;

				highlightedLetters += clickedLetter->Text;

				CheckForWords();
			}
			else {
				if (clickedLetter->BackColor == System::Drawing::Color::LightSalmon) {
					clickedLetter->BackColor = System::Drawing::Color::White;
				}
				else {
					clickedLetter->BackColor = System::Drawing::Color::LightGreen;
				}
				clickedLetter->IsHighlighted = false;

				highlightedLetters = highlightedLetters->Replace(clickedLetter->Text, "");
			}

			this->Text = highlightedLetters;
		}

		void CheckForWords() {
			String^ wordToCheck = hiddens->find(highlightedLetters);

			bool duplicate = false;
			if (wordToCheck != nullptr) {
				for each (String ^ foundWord in foundWords) {
					if (foundWord == wordToCheck) {
						duplicate = true;
					}
				}

				if (duplicate == false) {
					wordFound(wordToCheck);
					//MessageBox::Show("Found: " + highlightedLetters);
				}
				else {
					for (int i = 0; i < puzzleGrid->GetLength(0); i++) {
						for (int j = 0; j < puzzleGrid->GetLength(1); j++) {
							if (puzzleGrid[i, j]->IsHighlighted) {
								puzzleGrid[i, j]->IsHighlighted = false;
								puzzleGrid[i, j]->BackColor = System::Drawing::Color::LightGreen;
							}
						}
					}

					MessageBox::Show(wordToCheck + " has already been found!");
				}

				highlightedLetters = "";
			}
		}

		void wordFound(String^ word) {
			foundWords->Add(word);
			lbHiddenWords->Items->Remove(word);
			lbFoundWords->Items->Add(word);

			for (int i = 0; i < puzzleGrid->GetLength(0); i++) {
				for (int j = 0; j < puzzleGrid->GetLength(1); j++) {
					if (puzzleGrid[i, j]->IsHighlighted) {
						puzzleGrid[i, j]->IsHighlighted = false;
						puzzleGrid[i, j]->BackColor = System::Drawing::Color::LightGreen;
					}
				}
			}

			if (foundWords->Count == hiddenWords->Count) {
				timer1->Stop();
				score = seconds;

				// 
				FormInputName^ baru = gcnew FormInputName();
				baru->ShowDialog();
				this->player_name = baru->name;

				// Show a message box and capture the user's response
				System::Windows::Forms::DialogResult result = MessageBox::Show("Do you want to play again?", "Game Over", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

				// Process the user's response
				if (result == System::Windows::Forms::DialogResult::Yes) {
					// User clicked Yes
					this->playAgain = true;
				}
				else {
					// User clicked No or closed the dialog
					this->playAgain = false;
				}
				//MessageBox::Show(player_name);
				//MessageBox::Show(score->ToString());
				this->Close();
			}
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(726, 709);
			this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form1";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		seconds++;
		//TimeSpan elapsed = timer1.`
	}
	};
}

