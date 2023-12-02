#include "StartMenu.h"

using namespace System;

using namespace System::Windows::Forms;

[STAThread]

int main(array<String^>^ args)

{

    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    tts::StartMenu form;

    Application::Run(% form);

    return 0;
}

//#include "StartMenu.h"
//#include <string>
//#include <vector>
//#include <Windows.h>
//
//using namespace System;
//using namespace System::Windows::Forms;
//using namespace System::Drawing;
//
//// Class to represent a letter in the puzzle grid
//ref class PuzzleLetter : public Label {
//public:
//    property bool IsHighlighted;
//
//    PuzzleLetter() {
//        IsHighlighted = false;
//    }
//};
//
//public ref class WordPuzzleForm : public Form {
//private:
//    array<PuzzleLetter^, 2>^ puzzleGrid;
//    array<String^>^ hiddenWords;
//    array<String^>^ foundWords;
//
//    void InitializePuzzleGrid() {
//        puzzleGrid = gcnew array<PuzzleLetter^, 2>(3, 3);
//
//        // Initialize puzzle grid with letters
//        for (int i = 0; i < 3; i++) {
//            for (int j = 0; j < 3; j++) {
//                puzzleGrid[i, j] = gcnew PuzzleLetter();
//                puzzleGrid[i, j]->Text = Convert::ToChar('A' + i * 3 + j).ToString();
//                puzzleGrid[i, j]->Location = Point(50 * j, 50 * i);
//                puzzleGrid[i, j]->Click += gcnew EventHandler(this, &WordPuzzleForm::PuzzleLetter_Click);
//                Controls->Add(puzzleGrid[i, j]);
//            }
//        }
//    }
//
//    void InitializeHiddenWords() {
//        hiddenWords = gcnew array<String^>{"CAT", "DOG", "RAT"};
//        foundWords = gcnew array<String^>(hiddenWords->Length);
//    }
//
//    void PuzzleLetter_Click(Object^ sender, EventArgs^ e) {
//        PuzzleLetter^ clickedLetter = dynamic_cast<PuzzleLetter^>(sender);
//
//        if (!clickedLetter->IsHighlighted) {
//            clickedLetter->IsHighlighted = true;
//            CheckForWords();
//        }
//    }
//
//    void CheckForWords() {
//        for (int i = 0; i < hiddenWords->Length; i++) {
//            if (IsWordFound(hiddenWords[i]) && foundWords[i] == nullptr) {
//                MessageBox::Show("Found word: " + hiddenWords[i]);
//                foundWords[i] = hiddenWords[i];
//            }
//        }
//    }
//
//    bool IsWordFound(String^ word) {
//        String^ highlightedLetters = "";
//
//        for (int i = 0; i < 3; i++) {
//            for (int j = 0; j < 3; j++) {
//                if (puzzleGrid[i, j]->IsHighlighted) {
//                    highlightedLetters += puzzleGrid[i, j]->Text;
//                }
//            }
//        }
//
//        return highlightedLetters->Equals(word);
//    }
//
//public:
//    WordPuzzleForm() {
//        Text = "Word Puzzle Game";
//        Size = System::Drawing::Size(200, 200);
//        InitializePuzzleGrid();
//        InitializeHiddenWords();
//    }
//};
//
//int main() {
//    Application::Run(gcnew WordPuzzleForm());
//    return 0;
//}
