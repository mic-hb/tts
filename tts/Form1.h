////#include "stdafx.h"
//#include <string>
//#include <vector>
//#include <Windows.h>
//#include "PuzzleLetter.h"
//
//#pragma once
//
//namespace tts {
//
//	using namespace System;
//	using namespace System::ComponentModel;
//	using namespace System::Collections;
//	using namespace System::Windows::Forms;
//	using namespace System::Data;
//	using namespace System::Drawing;
//
//	/// <summary>
//	/// Summary for Form1
//	/// </summary>
//	public ref class Form1 : public System::Windows::Forms::Form
//	{
//	public:
//		Form1(void)
//		{
//			InitializeComponent();
//			//
//			//TODO: Add the constructor code here
//			//
//			Text = "Word Puzzle Game";
//			Size = System::Drawing::Size(200, 200);
//			InitializePuzzleGrid();
//			InitializeHiddenWords();
//		}
//
//	protected:
//		/// <summary>
//		/// Clean up any resources being used.
//		/// </summary>
//		~Form1()
//		{
//			if (components)
//			{
//				delete components;
//			}
//		}
//
//	private:
//		/// <summary>
//		/// Required designer variable.
//		/// </summary>
//		System::ComponentModel::Container^ components;
//		array<PuzzleLetter^, 2>^ puzzleGrid;
//		array<String^>^ hiddenWords;
//		array<String^>^ foundWords;
//
//		void InitializePuzzleGrid() {
//			puzzleGrid = gcnew array<PuzzleLetter^, 2>(3, 3);
//
//			// Initialize puzzle grid with letters
//			for (int i = 0; i < 3; i++) {
//				for (int j = 0; j < 3; j++) {
//					puzzleGrid[i, j] = gcnew PuzzleLetter();
//					puzzleGrid[i, j]->Text = Convert::ToChar('A' + i * 3 + j).ToString();
//					//puzzleGrid[i, j]->Location = Point(50 * j, 50 * i);
//					puzzleGrid[i, j]->Location = Point(50 * (j + 1), 50 * (i + 1));
//					puzzleGrid[i, j]->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
//					Controls->Add(puzzleGrid[i, j]);
//				}
//			}
//		}
//
//		void InitializeHiddenWords() {
//			hiddenWords = gcnew array<String^>{"CAT", "DOG", "RAT"};
//			foundWords = gcnew array<String^>(hiddenWords->Length);
//		}
//
//		void PuzzleLetter_Click(Object^ sender, EventArgs^ e) {
//			PuzzleLetter^ clickedLetter = dynamic_cast<PuzzleLetter^>(sender);
//
//			if (!clickedLetter->IsHighlighted) {
//				clickedLetter->IsHighlighted = true;
//				CheckForWords();
//			}
//		}
//
//		void CheckForWords() {
//			for (int i = 0; i < hiddenWords->Length; i++) {
//				if (IsWordFound(hiddenWords[i]) && foundWords[i] == nullptr) {
//					MessageBox::Show("Found word: " + hiddenWords[i]);
//					foundWords[i] = hiddenWords[i];
//				}
//			}
//		}
//
//		bool IsWordFound(String^ word) {
//			String^ highlightedLetters = "";
//
//			for (int i = 0; i < 3; i++) {
//				for (int j = 0; j < 3; j++) {
//					if (puzzleGrid[i, j]->IsHighlighted) {
//						highlightedLetters += puzzleGrid[i, j]->Text;
//					}
//				}
//			}
//
//			return highlightedLetters->Equals(word);
//		}
//
//#pragma region Windows Form Designer generated code
//		/// <summary>
//		/// Required method for Designer support - do not modify
//		/// the contents of this method with the code editor.
//		/// </summary>
//		void InitializeComponent(void)
//		{
//			this->SuspendLayout();
//			// 
//			// Form1
//			// 
//			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
//			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
//			this->ClientSize = System::Drawing::Size(300, 300);
//			this->Name = L"Form1";
//			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
//			this->Text = L"Form1";
//			this->ResumeLayout(false);
//
//		}
//#pragma endregion
//	};
//}

#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include "PuzzleLetter.h"
#include <string>

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

		public:
			BST() {
				root = nullptr;
			}

			void insert(String^ key) {
				root = insertRecursive(root, key);
			}

			void displayInOrder() {
				MessageBox::Show("In-order traversal of the BST: ");
				inOrderTraversal(root);
				Console::WriteLine();
			}
			Node^ find(String^ key) {
				return findRecursive(root, key);
			}

		};
		Form1(void)
		{
			InitializeComponent();
			Text = "Word Puzzle Game";
			//Size = System::Drawing::Size(1000, 1000);
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
			private: System::Windows::Forms::FontDialog^ fontDialog1;
			array<String^>^ foundWords;

		   void InitializeHiddenWords() {
			   hiddenWords = gcnew array<String^>{"CAT", "DOG", "RAT"};
			   foundWords = gcnew array<String^>(hiddenWords->Length);
		   }

		   void InitializePuzzleGrid() {
			   puzzleGrid = gcnew array<PuzzleLetter^, 2>(3, 3);

			   int idx = 0;
			   for each (String^ word in hiddenWords)
			   {
				   for each(char letter in word)
				   {
					   puzzleGrid[idx / 3, idx % 3] = gcnew PuzzleLetter();
					   puzzleGrid[idx / 3, idx % 3]->Text = Char::ToString(letter);
					   puzzleGrid[idx / 3, idx % 3]->Size = System::Drawing::Size(50, 50);
					   puzzleGrid[idx / 3, idx % 3]->BackColor = System::Drawing::Color::White;
					   puzzleGrid[idx / 3, idx % 3]->Location = Point(50 * (idx % 3) + 50, 50 * (idx / 3) + 50);
					   puzzleGrid[idx / 3, idx % 3]->Click += gcnew EventHandler(this, &Form1::PuzzleLetter_Click);
					   puzzleGrid[idx / 3, idx % 3]->Visible = true;
					   Controls->Add(puzzleGrid[idx / 3, idx % 3]);
					   puzzleGrid[idx / 3, idx % 3]->BringToFront();

					   // Increment the letter for the next iteration
					   idx++;
				   }
			   }
			   array<char, 1>^ letters = gcnew array<char, 1>{'D', 'O', 'G', 'C', 'A', 'T', 'R', 'A', 'T'};
			   char letter = 'A';

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

			   for (int i = 0; i < 3; i++) {
				   for (int j = 0; j < 3; j++) {
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
			   BST^ tree = gcnew BST();


			   //cara insert
			   tree->insert("apple");
			   tree->insert("banana");
			   tree->insert("orange");
			   tree->insert("grape");
			   tree->insert("kiwi");

			   //display semua dengan urutan inorderTraversal
			   tree->displayInOrder();

			   //find di dalam tree
			   String^ x = "oranges";
			   Node^ foundNode = tree->find(x);

			   if (foundNode != nullptr) {
				   MessageBox::Show("Found: " + foundNode->key);
			   }
			   else {
				   MessageBox::Show(x + " not found.");
			   }

		   }
#pragma endregion
	};
}

